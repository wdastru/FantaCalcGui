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
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QHttpResponseHeader>

#include "Uploader.h"
#include "Repository.h"
#include "toString.h"

Uploader::Uploader(QWidget *parent) :
		QDialog(parent) {
}

void Uploader::upload(QString _file) {
	_file = "ciccio.txt";

	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	//connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

	QFileInfo finfo(_file);

	QString target =
			"http://localhost/www.cim.unito.it/private/fantacalcio/777/tappo.txt";
	QUrl url;
	url.setUrl(target);

	QNetworkRequest *request = new QNetworkRequest();
	request->setUrl(url);

	QString bound = "---------------------------723690991551375881941828858";
	QByteArray data(QString("--" + bound + "\r\n").toAscii());
	data += "Content-Disposition: form-data; name=\"action\"\r\n\r\n";
	data += "\r\n";
	data += QString("--" + bound + "\r\n").toAscii();
	data += "Content-Disposition: form-data; name=\"file\"; filename=\""
			+ finfo.fileName() + "\"\r\n";
	data += "Content-Type: image/" + finfo.suffix().toLower() + "\r\n\r\n";
	QFile file(finfo.absoluteFilePath());
	file.open(QIODevice::ReadOnly);
	data += file.readAll();
	data += "\r\n";
	data += QString("--" + bound + "\r\n").toAscii();
	data += QString("--" + bound + "\r\n").toAscii();
	data += "Content-Disposition: form-data; name=\"desc\"\r\n\r\n";
	data += "Description for my image here :)\r\n";
	data += "\r\n";
	request->setRawHeader(QString("Accept-Encoding").toAscii(),
			QString("gzip,deflate").toAscii());
	request->setRawHeader(QString("Content-Type").toAscii(),
			QString("multipart/form-data; boundary=" + bound).toAscii());
	request->setRawHeader(QString("Content-Length").toAscii(),
			QString::number(data.length()).toAscii());

	qDebug() << data;

	QNetworkReply * reply = manager->post(*request, data);

	//connect(reply, SIGNAL(finished()), this, SLOT(fin()));

	//QHttp *http = new QHttp(this); // http declared as a member of Uploader class
	//connect(http, SIGNAL(requestFinished(int,bool)), SLOT(httpRequestFinished(int, bool)));
	//
	//QString boundary = "---------------------------723690991551375881941828858";
	//
	//// action
	//QByteArray data(QString("--" + boundary + "\r\n").toAscii());
	//data += "Content-Disposition: form-data; name=\"action\"\r\n\r\n";
	//data += "file_upload\r\n";
	//
	//// file
	//data += QString("--" + boundary + "\r\n").toAscii();
	//data += "Content-Disposition: form-data; name=\"sfile\"; filename=\"test1.jpg\"\r\n";
	//data += "Content-Type: image/jpeg\r\n\r\n";
	//
	//QFile file(_file);
	//if (!file.open(QIODevice::ReadOnly))
	//    return;
	//
	//data += file.readAll();
	//data += "\r\n";
	//
	//// password
	//data += QString("--" + boundary + "\r\n").toAscii();
	//data += "Content-Disposition: form-data; name=\"password\"\r\n\r\n";
	////data += "password\r\n"; // put password if needed
	//data += "\r\n";
	//
	//// description
	//data += QString("--" + boundary + "\r\n").toAscii();
	//data += "Content-Disposition: form-data; name=\"description\"\r\n\r\n";
	////data += "description\r\n"; // put description if needed
	//data += "\r\n";
	//
	//// agree
	//data += QString("--" + boundary + "\r\n").toAscii();
	//data += "Content-Disposition: form-data; name=\"agree\"\r\n\r\n";
	//data += "1\r\n";
	//
	//data += QString("--" + boundary + "--\r\n").toAscii();
	//
	//QHttpRequestHeader header("POST", "/cabinet/upload/");
	//header.setValue("Host", "data.cod.ru");
	//header.setValue("User-Agent", "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.1.9) Gecko/20100401 Ubuntu/9.10 (karmic) Firefox/3.5.9");
	//header.setValue("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
	//header.setValue("Accept-Language", "en-us,en;q=0.5");
	//header.setValue("Accept-Encoding", "gzip,deflate");
	//header.setValue("Accept-Charset", "ISO-8859-1,utf-8;q=0.7,*;q=0.7");
	//header.setValue("Keep-Alive", "300");
	//header.setValue("Connection", "keep-alive");
	//header.setValue("Referer", "http://data.cod.ru/");
	//
	////multipart/form-data; boundary=---------------------------723690991551375881941828858
	//
	//header.setValue("Content-Type", "multipart/form-data; boundary=" + boundary);
	//header.setValue("Content-Length", QString::number(data.length()));
	//
	//http->setHost("data.cod.ru");
	//http->request(header, data);
	//
	//file.close();
}

//void Uploader::httpRequestFinished(int, bool)
//{
//    //QHttpResponseHeader response = http->lastResponse();
//    //if (response.statusCode()==302)
//    //{
//    //    qDebug() << "file accepted; get it from:";
//    //    qDebug() << "data.cod.ru" << response.value("Location");
//    //}
//}

//void Uploader::uploader(QString _file)
//{
//  QNetworkAccessManager *http=new QNetworkAccessManager(this);
//  QFileInfo finfo(_file);
//
//  QUrl *url = new QUrl("http://localhost/www.cim.unito.it/fantacalcio/777/uploadedfile.txt");
//  QNetworkRequest r;
//
//  QString bound="---------------------------723690991551375881941828858";
//  QByteArray data(QString("--"+bound+"\r\n").toAscii());
//  data += "Content-Disposition: form-data; name=\"action\"\r\n\r\n";
//  data += "\r\n";
//  data += QString("--" + bound + "\r\n").toAscii();
//  data += "Content-Disposition: form-data; name=\"file\"; filename=\""+finfo.fileName()+"\"\r\n";
//  data += "Content-Type: image/"+finfo.suffix().toLower()+"\r\n\r\n";
//  QFile file(finfo.absoluteFilePath());
//  file.open(QIODevice::ReadOnly);
//  data += file.readAll();
//  data += "\r\n";
//  data += QString("--" + bound + "\r\n").toAscii();
//  data += QString("--" + bound + "\r\n").toAscii();
//  data += "Content-Disposition: form-data; name=\"desc\"\r\n\r\n";
//  data += "Description for my image here :)\r\n";
//  data += "\r\n";
//  r.setRawHeader(QString("Accept-Encoding").toAscii(), QString("gzip,deflate").toAscii());
//  r.setRawHeader(QString("Content-Type").toAscii(),QString("multipart/form-data; boundary=" + bound).toAscii());
//  r.setRawHeader(QString("Content-Length").toAscii(), QString::number(data.length()).toAscii());
//
//  QNetworkReply * rep = http->post(r,data);
//
//  connect(rep,SIGNAL(finished()),this,SLOT(fin()));
//  }
