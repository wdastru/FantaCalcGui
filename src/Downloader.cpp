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

#include <QtGui/QtGui>
//#include <QtWidgets/QDialogButtonBox>
#include <QtGui/QDialogButtonBox>
#include <QtCore/QDebug>

#include "httpwindow.h"
#include "Downloader.h"
#include "Repository.h"
#include "toString.h"

Downloader::Downloader(QWidget *parent, std::vector<QUrl>* _urls,
		std::vector<QString>* _savePaths, bool _silent) :
	QDialog(parent) {

	//qDebug() << "In Downloader::Downloader(...).";
    //
	//for (int i = 0; i < _savePaths->size(); ++i) {
	//	qDebug() << "In Downloader::Downloader(...). _savePaths.at(" + my::toQString<int>(i) + ") = " + _savePaths->at(i);
	//}

	this->setFont(THE_REPO->fontVariableWidthSmall);

	this->silent = _silent; // per evitare di notificare l'avvenuto download in
	this->resize(600, 0);
	this->setMinimumSize(600, 0);

	this->savePaths = _savePaths;
	this->urls = _urls;
	this->statusLabelText = "";
	this->hasBeenQuitted = false;
	this->httpRequestSucceded = false;
	this->httpClients.resize(urls->size());

	for (size_t i = 0; i < this->urls->size(); i++) {
		this->urlLineEditVector.push_back(
				new QLineEdit(this->urls->at(i).path()));
		this->urlLineEditVector.at(i)->setReadOnly(true);
		this->urlLineEditVector.at(i)->setStyleSheet(
				"border-color: rgb(255, 0, 0); background-color: rgb(255, 200, 200);");
		this->urlLineEditVector.at(i)->setFont(THE_REPO->fontVariableWidthSmall);
		this->urlLabelVector.push_back(new QLabel(tr("URL:")));
	}

	statusLabel = new QLabel(tr("Please enter the URL of a file you want to "
		"download."));

	downloadButton = new QPushButton(tr("Download"));
	downloadButton->setDefault(true);
	quitButton = new QPushButton(tr("Cancel"));
	quitButton->setAutoDefault(false);

	buttonBox = new QDialogButtonBox;
	buttonBox->addButton(downloadButton, QDialogButtonBox::ActionRole);
	buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

	connect(downloadButton, SIGNAL(clicked()), this, SLOT(downloadFiles()));
	connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()));

	QVBoxLayout *vLayout = new QVBoxLayout;
	for (size_t i = 0; i < this->urls->size(); i++) {
		QHBoxLayout *hLayout = new QHBoxLayout;
		hLayout->addWidget(this->urlLabelVector.at(i));
		hLayout->addWidget(this->urlLineEditVector.at(i));
		vLayout->addLayout(hLayout);
	}

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(vLayout);
	mainLayout->addWidget(buttonBox);

	setLayout(mainLayout);
	this->setWindowTitle("FantaCalcGui - Download");

	if (silent) {
		this->downloadFiles();
		/*
		 * TODO:
		 * indagare cosa succede se silent == FALSE
		 * eventualmente aggiungere un else
		 *
		 * * * * * * * * * * * * * * * * * * * * */
	}
}
void Downloader::quit() {
	//qDebug() << "In void Downloader::quit().";
	this->hasBeenQuitted = true;
	this->close();
}
void Downloader::downloadFiles() {
	this->statusLabelText = "";
	this->downloadFailures = 0;
	this->downloadSuccesses = 0;
	this->downloadAborts = 0;

	for (unsigned int i = 0; i < urlLineEditVector.size(); ++i) {
		QUrl url = QUrl(urlLineEditVector.at(i)->text());
		QString fullUrlString = url.scheme() + "://" + url.authority()
				+ url.path();

		//qDebug() << "In Downloader::downloadFile() --> url : " + fullUrlString;
		//qDebug() << "In Downloader::downloadFile() --> savePaths->at(" + my::toQString<unsigned int>(i) + ") : "	+ savePaths->at(i);

		if (!this->silent) {
			//qDebug() << QObject::tr("Downloading %1").arg(fullUrlString);
			//qDebug() << QObject::tr("Saving to %1").arg(this->savePaths->at(i));
		}

		this->httpClients.at(i) = new HttpWindow(this, url, this->savePaths->at(i));
		this->httpClients.at(i)->exec();

		if (this->httpClients.at(i)->downloadSuccessful()) {
			this->downloadSuccesses++;
			//qDebug() << tr("In void Downloader::downloadFiles(). Download of %1 succeded.").arg(QFileInfo(this->savePaths->at(i)).fileName());
			if (!this->silent) {
				//LOG(INFO, tr("Scaricato %1").arg(QFileInfo(this->savePaths->at(i)).fileName()));
			}

		} else if(this->httpClients.at(i)->aborted()) {
			this->downloadAborts++;
			qDebug() << tr("In void Downloader::downloadFiles(). Download of %1 aborted.").arg(QFileInfo(this->savePaths->at(i)).fileName());
			LOG(WARN, tr("Scaricamento di %1 interrotto.").arg(QFileInfo(this->savePaths->at(i)).fileName()));
		} else {
			this->downloadFailures++;
			qDebug() << tr("In void Downloader::downloadFiles(). Download of %1 failed.").arg(QFileInfo(this->savePaths->at(i)).fileName());
			LOG(ERR, tr("Scaricamento di %1 fallito.").arg(QFileInfo(this->savePaths->at(i)).fileName()));
		}

		//qDebug() << tr("Download successes : %1").arg(my::toQString<unsigned int>(this->downloadSuccesses));
		//qDebug() << tr("Download failures : %1").arg(my::toQString<unsigned int>(this->downloadFailures));

		if (this->downloadSuccesses == this->savePaths->size()) {
			this->close();
		}
	}
}
bool Downloader::requestSucceded() {
	if (this->downloadSuccesses == this->savePaths->size()) {
		return true;
	} else {
		return false;
	}
}
bool Downloader::requestAborted() {
	if (this->downloadAborts > 0) {
		return true;
	} else {
		return false;
	}
}
bool Downloader::wasCancelClicked() {
	return this->hasBeenQuitted;
}
