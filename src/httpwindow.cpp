/****************************************************************************
 /****************************************************************************
 **
 ** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#include <QtGui>
#include <QtNetwork>

#include "httpwindow.h"
#include "ui_authenticationdialog.h"

HttpWindow::HttpWindow(QWidget *parent, std::vector<QUrl>* _urls,
		std::vector<QString>* _savePaths) :
	QDialog(parent) {
	LOG(
			DEBUG,
			"In HttpWindow::HttpWindow(QWidget *parent, std::vector<QUrl>* _urls, std::vector<QString>* _savePaths) constructor.");

	this->savePaths = _savePaths;
	this->urls = _urls;

	for (size_t i = 0; i < this->urls->size(); i++) {
		this->urlLineEditVector.push_back(
				new QLineEdit(this->urls->at(i).path()));
		this->urlLabelVector.push_back(new QLabel(tr("&URL:")));
		this->urlLabelVector.at(i)->setBuddy(this->urlLineEditVector.at(i));
	}

	statusLabel = new QLabel(tr("Please enter the URL of a file you want to "
		"download."));

	downloadButton = new QPushButton(tr("Download"));
	downloadButton->setDefault(true);
	quitButton = new QPushButton(tr("Quit"));
	quitButton->setAutoDefault(false);

	buttonBox = new QDialogButtonBox;
	buttonBox->addButton(downloadButton, QDialogButtonBox::ActionRole);
	buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

	progressDialog = new QProgressDialog(this);

	for (size_t i = 0; i < this->urls->size(); i++) {
		connect(this->urlLineEditVector.at(i), SIGNAL(textChanged(QString)),
				this, SLOT(enableDownloadButton()));
	}

	connect(&qnam,
			SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
			this,
			SLOT(slotAuthenticationRequired(QNetworkReply*,QAuthenticator*)));
#ifndef QT_NO_OPENSSL
	connect(&qnam, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this,
			SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
#endif
	connect(progressDialog, SIGNAL(canceled()), this, SLOT(cancelDownload()));
	connect(downloadButton, SIGNAL(clicked()), this, SLOT(downloadAllFiles()));
	connect(quitButton, SIGNAL(clicked()), this, SLOT(closeDialog()));

	QVBoxLayout *vLayout = new QVBoxLayout;
	for (size_t i = 0; i < this->urls->size(); i++) {
		QHBoxLayout *hLayout = new QHBoxLayout;
		hLayout->addWidget(this->urlLabelVector.at(i));
		hLayout->addWidget(this->urlLineEditVector.at(i));
		vLayout->addLayout(hLayout);
	}

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(vLayout);
	mainLayout->addWidget(statusLabel);
	mainLayout->addWidget(buttonBox);
	setLayout(mainLayout);

	httpRequestSucceded = false;

	setWindowTitle(tr("HTTP"));
	//urlLineEditVector.at(0)->setFocus();
}

void HttpWindow::closeDialog() {
	this->close();
}

void HttpWindow::startRequest(QUrl url) {
	LOG(DEBUG, "In void HttpWindow::startRequest(QUrl url)");
	reply = qnam.get(QNetworkRequest(url));
	connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));
	connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
	connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this,
			SLOT(updateDataReadProgress(qint64,qint64)));
}

void HttpWindow::downloadAllFiles() {
	for (int i = 0; i < this->urls->size(); i++) {
		LOG(
				DEBUG,
				" In void HttpWindow::downloadAllFiles(std::vector<QUrl>* _urls, std::vector<QString>* _savePaths) --> downloading : "
						+ this->urls->at(i).authority()
						+ this->urls->at(i).path());
		LOG(DEBUG, " saving at : " + this->savePaths->at(i));
		this->downloadFile(this->urls->at(i), this->savePaths->at(i));
	}

	if (httpRequestSucceded) {
		LOG(
				DEBUG,
				" In void HttpWindow::downloadAllFiles(std::vector<QUrl>* _urls, std::vector<QString>* _savePaths) --> download of files succeded.");
		return;
	} else {
		LOG(
				DEBUG,
				" In void HttpWindow::downloadAllFiles(std::vector<QUrl>* _urls, std::vector<QString>* _savePaths) --> download of files failed.");
	}
}

void HttpWindow::downloadFile(QUrl _url, QString _savePath) {
	QUrl url = _url;
	QString savePath = _savePath;

	LOG(
			DEBUG,
			"In HttpWindow::downloadFile() --> url : " + url.authority()
					+ url.path());

	QFileInfo fileInfo(url.path());
	QString fileName = savePath + fileInfo.fileName();

	LOG(DEBUG, "In HttpWindow::downloadFile() --> fileName : " + fileName);

	if (fileName.isEmpty())
		fileName = savePath + "file.txt";

	if (QFile::exists(fileName)) {
		if (QMessageBox::question(
				this,
				tr("HTTP - File exists !!!"),
				tr("There already exists a file called %1. Overwrite?").arg(
						fileName), QMessageBox::Yes | QMessageBox::No,
				QMessageBox::No) == QMessageBox::No) {
			return;
		} else {
			QFile::remove(fileName);
			LOG(
					DEBUG,
					"In HttpWindow::downloadFile() --> " + fileName
							+ " exists : it will be overwritten.");
		}
	}

	file = new QFile(fileName);
	if (!file->open(QIODevice::WriteOnly)) {
		QMessageBox::information(
				this,
				tr("HTTP"),
				tr("Unable to save the file %1: %2.") .arg(fileName).arg(
						file->errorString()));
		delete file;
		file = 0;
		return;
	}

	progressDialog->setWindowTitle(tr("HTTP - Downloading ..."));
	progressDialog->setLabelText(tr("Downloading %1.").arg(fileName));
	downloadButton->setEnabled(false);

	// schedule the request
	httpRequestAborted = false;
	startRequest(url);
}

void HttpWindow::cancelDownload() {
	statusLabel->setText(tr("Download canceled."));
	httpRequestAborted = true;
	reply->abort();
	downloadButton->setEnabled(true);
}

void HttpWindow::httpFinished() {
	LOG(DEBUG, "In void HttpWindow::httpFinished()");
	if (httpRequestAborted) {
		if (file) {
			file->close();
			file->remove();
			delete file;
			file = 0;
		}
		reply->deleteLater();
		progressDialog->hide();
		return;
	}

	progressDialog->hide();
	file->flush();
	file->close();

	QVariant redirectionTarget = reply->attribute(
			QNetworkRequest::RedirectionTargetAttribute);

	if (reply->error()) {
		file->remove();
		QMessageBox::information(this, tr("HTTP"),
				tr("Download failed: %1.") .arg(reply->errorString()));
		downloadButton->setEnabled(true);
	} else {
		for (size_t i = 0; i < this->urls->size(); i++) {
			QString fileName = QFileInfo(
					QUrl(urlLineEditVector.at(i)->text()).path()).fileName();
			statusLabel->setText(
					tr("Downloaded %1 to current directory.").arg(fileName));

			LOG(
					DEBUG,
					"In void HttpWindow::httpFinished() --> " + QUrl(
							urlLineEditVector.at(i)->text()).path()
							+ " downloaded.");
		}

		httpRequestSucceded = true;
	}

	reply->deleteLater();
	reply = 0;
	delete file;
	file = 0;
}

void HttpWindow::httpReadyRead() {
	LOG(DEBUG, "In void HttpWindow::httpReadyRead()");
	// this slot gets called every time the QNetworkReply has new data.
	// We read all of its new data and write it into the file.
	// That way we use less RAM than when reading it at the finished()
	// signal of the QNetworkReply
	if (file)
		file->write(reply->readAll());
}

void HttpWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes) {
	if (httpRequestAborted)
		return;

	progressDialog->setMaximum(totalBytes);
	progressDialog->setValue(bytesRead);
}

void HttpWindow::enableDownloadButton() {
	bool enable = TRUE;
	for (size_t i = 0; i < this->urls->size(); i++) {
		enable = enable && !urlLineEditVector.at(i)->text().isEmpty();
	}
	downloadButton->setEnabled(enable);
}

void HttpWindow::slotAuthenticationRequired(QNetworkReply*,
		QAuthenticator *authenticator) {
	/*
	 QDialog dlg;
	 Ui::Dialog ui;
	 ui.setupUi(&dlg);
	 dlg.adjustSize();
	 ui.siteDescription->setText(tr("%1 at %2").arg(authenticator->realm()).arg(url.host()));

	 // Did the URL have information? Fill the UI
	 // This is only relevant if the URL-supplied credentials were wrong
	 ui.userEdit->setText(url.userName());
	 ui.passwordEdit->setText(url.password());

	 if (dlg.exec() == QDialog::Accepted) {
	 */
	authenticator->setUser("laboratorio");
	authenticator->setPassword("NMR12345");
	//}
}

bool HttpWindow::requestSucceded() {
	return httpRequestSucceded;
}

#ifndef QT_NO_OPENSSL
void HttpWindow::sslErrors(QNetworkReply*, const QList<QSslError> &errors) {
	QString errorString;
	foreach (const QSslError &error, errors)
		{
			if (!errorString.isEmpty())
				errorString += ", ";
			errorString += error.errorString();
		}

	if (QMessageBox::warning(this, tr("HTTP"),
			tr("One or more SSL errors has occurred: %1").arg(errorString),
			QMessageBox::Ignore | QMessageBox::Abort) == QMessageBox::Ignore) {
		reply->ignoreSslErrors();
	}
}
#endif
