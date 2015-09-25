/****************************************************************************
 ****************************************************************************
 **
 ** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies) .
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:BSD$
 ** You may use this file under the terms of the BSD license as follows:
 **
 ** "Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 **   * Redistributions of source code must retain the above copyright
 **     notice, this list of conditions and the following disclaimer.
 **   * Redistributions in binary form must reproduce the above copyright
 **     notice, this list of conditions and the following disclaimer in
 **     the documentation and/or other materials provided with the
 **     distribution.
 **   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
 **     the names of its contributors may be used to endorse or promote
 **     products derived from this software without specific prior written
 **     permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#define DO_DEBUG

#include <QtGui/QtGui>
//#include <QtWidgets/QProgressDialog>
//#include <QtWidgets/QMessageBox>
#include <QtGui/QProgressDialog>
#include <QtGui/QMessageBox>
#include <QtNetwork/QtNetwork>
#include <QtCore/QDebug>
#include <QtCore/QUrl>

#include "defines.h"
#include "Repository.h"
#include "httpwindow.h"
#include "singletonQtLogger.h"
#include "ui_authenticationdialog.h"

HttpWindow::HttpWindow(QWidget *parent, QUrl _url, QString _savePath) :
		QDialog(parent) {

	this->setFont(THE_REPO->fontVariableWidthSmall);
	this->fullUrlString = _url.scheme() + "://" + _url.authority()
	+ _url.path();
	this->downloadSuccess = false;
	this->uploadFlag = false;
	this->savePath = _savePath;
	progressDialog = new QProgressDialog(this);

	connect(&qnam,
			SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
			this,
			SLOT(slotAuthenticationRequired(QNetworkReply*,QAuthenticator*)));

	connect(progressDialog, SIGNAL(canceled()), this, SLOT(cancelDownload()));

	this->downloadFile();
}

void HttpWindow::startRequest(QUrl url) {
	reply = qnam.get(QNetworkRequest(url));
	connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));
	connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
	connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this,
			SLOT(updateDataReadProgress(qint64,qint64)));
}

void HttpWindow::downloadFile() {
	url = this->fullUrlString;

	QFileInfo fileInfo(url.path());
	QString fileName = this->savePath;

	if (fileName.isEmpty()) {
		LOG(FATAL, tr("In HttpWindow::downloadFile() --> fileName is empty."));
	}

	this->file = new QFile(fileName);
	if (!this->file->open(QIODevice::WriteOnly)) {

		QMessageBox msgBox;
		msgBox.setWindowTitle("HTTP");
		msgBox.setInformativeText(
				tr("Unable to save the file %1: %2.").arg(fileName).arg(
						this->file->errorString()));
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Ok);
		msgBox.setIcon(QMessageBox::Information);
		msgBox.setFont(THE_REPO->fontVariableWidthSmall);
		msgBox.exec();

		delete this->file;
		this->file = 0;
		this->downloadSuccess = false;
		return;
	}

	progressDialog->setWindowTitle(tr("HTTP"));
	progressDialog->setLabelText(tr("Downloading %1.").arg(fileName));

	// schedule the request
	httpRequestAborted = false;

	startRequest(url);
}

void HttpWindow::cancelDownload() {
	httpRequestAborted = true;
	reply->abort();
	this->close();
}

void HttpWindow::httpFinished() {
	if (httpRequestAborted) {
		if (this->file) {
			this->file->close();
			this->file->remove();
			delete this->file;
			this->file = 0;
		}
		reply->deleteLater();
		progressDialog->hide();
		this->downloadSuccess = false;
		this->close();
		return;
	}

	progressDialog->hide();
	this->file->flush();
	this->file->close();

	QVariant redirectionTarget = reply->attribute(
			QNetworkRequest::RedirectionTargetAttribute);

	if (reply->error()) {
		this->file->remove();

		LOG(
		ERR,
		tr("Error downloading %1 : %2.").arg(file->fileName()).arg(
				reply->errorString()));

		this->downloadSuccess = false;

	} else if (!redirectionTarget.isNull()) {

		this->downloadSuccess = false;

	} else {

		if (!uploadFlag) {
			LOG(
			DBG,
			tr("    Scaricato %1 in %2").arg(
					QFileInfo(this->file->fileName()).fileName()).arg(
					QFileInfo(this->file->fileName()).path()));
		} else {
			LOG(
					DBG,
					tr("    Upload di %1 riuscito").arg(
							QFileInfo(this->file->fileName()).fileName()));
		}

		this->downloadSuccess = true;
	}

	reply->deleteLater();
	reply = 0;
	delete this->file;
	this->file = 0;

	this->close();
}

void HttpWindow::httpReadyRead() {
	// this slot gets called every time the QNetworkReply has new data.
	// We read all of its new data and write it into the file.
	// That way we use less RAM than when reading it at the finished()
	// signal of the QNetworkReply
	if (this->file)
		this->file->write(reply->readAll());
}

void HttpWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes) {
	if (httpRequestAborted)
		return;

	progressDialog->setMaximum(totalBytes);
	progressDialog->setValue(bytesRead);
}

bool HttpWindow::downloadSuccessful() {
	return this->downloadSuccess;
}

void HttpWindow::upload(QString _file) {

	this->uploadFlag = true;
	QString bound;
	QString crlf;
	QString data;
	QByteArray dataToSend;

	QFile file(_file);
	file.open(QIODevice::ReadOnly);

	bound = "---------------------------7d935033608e2";
	crlf = 0x0d;
	crlf += 0x0a;
	data = "--" + bound + crlf
			+ "Content-Disposition: form-data; name=\"uploaded_file\"; ";
	data += "filename=\"" + file.fileName() + "\"";
	data += crlf + "Content-Type: application/octet-stream" + crlf + crlf;
	dataToSend.insert(0, data);
	dataToSend.append(file.readAll());
	dataToSend.append(crlf + "--" + bound + "--" + crlf);

	//QUrl url(THE_REPO->getUrl() + "test.php");
	QUrl url(THE_REPO->getUrl() + "uploader_FantaCalcGui.php");
	QNetworkRequest * req = new QNetworkRequest();
	req->setUrl(url);
	req->setHeader(QNetworkRequest::ContentTypeHeader,
			"multipart/form-data; boundary=" + bound);
	file.close();

	progressDialog->setLabelText(
			tr("Uploading %1.").arg(QFileInfo(file).fileName()));

	reply = qnam.post(*req, dataToSend);
}

void HttpWindow::slotAuthenticationRequired(QNetworkReply*,
		QAuthenticator *authenticator) {
	/*
	 QDialog dlg;
	 Ui::Dialog ui;
	 ui.setupUi(&dlg);
	 dlg.adjustSize();
	 ui.siteDescription->setText(
	 tr("%1 at %2").arg(authenticator->realm()).arg(url.host()));

	 // Did the URL have information? Fill the UI
	 // This is only relevant if the URL-supplied credentials were wrong
	 ui.userEdit->setText(url.userName());
	 ui.passwordEdit->setText(url.password());

	 if (dlg.exec() == QDialog::Accepted) {
	 authenticator->setUser(ui.userEdit->text());
	 authenticator->setPassword(ui.passwordEdit->text());
	 */
	authenticator->setUser("laboratorio");
	authenticator->setPassword("NMR12345");
	//	}
}

bool HttpWindow::aborted() {
	return this->httpRequestAborted;
}

/*
 #ifndef QT_NO_OPENSSL
 void HttpWindow::sslErrors(QNetworkReply*, const QList<QSslError> &errors) {
 QString errorString;
 foreach (const QSslError &error, errors)
 {
 if (!errorString.isEmpty())
 errorString += ", ";
 errorString += error.errorString();
 }

 QMessageBox msgBox;
 msgBox.setWindowTitle("HTTP");
 msgBox.setInformativeText(
 tr("One or more SSL errors has occurred: %1").arg(errorString));
 msgBox.setStandardButtons(QMessageBox::Ignore | QMessageBox::Abort);
 msgBox.setDefaultButton(QMessageBox::Ignore);
 msgBox.setIcon(QMessageBox::Warning);
 msgBox.setFont(THE_REPO->fontVariableWidthSmall);
 int answer = msgBox.exec();

 if (answer == QMessageBox::Ignore) {
 reply->ignoreSslErrors();
 }
 }
 #endif
 */
