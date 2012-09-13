
#include "Uploader.h"
#include <QtNetwork/QHttpRequestHeader>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>

Uploader::Uploader() {
	connect(&http, SIGNAL(done(bool)), this, SLOT(httpDone(bool)));
	connect(this, SIGNAL(signalMessage(QString)), &textbox, SLOT(
			append(QString)));
	//textbox.show();
}

Uploader::~Uploader() {
// TODO Auto-generated destructor stub
}

void Uploader::httpDone(bool error) {
	buffer.reset();
	emit signalMessage("XML is:" + buffer.readAll());
	buffer.close();
}

void Uploader::upload() {
	QUrl url;
	url.setUrl(
			"http://awh1.stagekatalyst.net/katalyst/services/v1.0/CreateDelivery");
	http.setHost(url.host(), QHttp::ConnectionModeHttp, url.port(80));

	QString boundary;
	QString sessionID = "6E17D5D3-3F0E-20E6-E8AD-51A3E8739003";
	QString data;
	QString crlf;
	QByteArray requestContent;

	boundary = "---------------------------7d934a10503cc";
	crlf = 0x0d;
	crlf += 0x0a;

	QFile *file = new QFile("d:\\Shared_ReadOnly\\upload_files\\1_page.pdf");

//**************** set-1 ************************
	data = "--" + boundary + crlf
			+ "Content-Disposition: form-data; name=\"file1\"; ";
	data += "filename=\"file1.pdf\"";
	data += crlf + "Content-Type: Application/Octet" + crlf + crlf;

	file->open(QIODevice::ReadOnly);
	requestContent.insert(0, data);
	requestContent.append(file->readAll());
	requestContent.append(crlf);
	file->close();
//**************** set-1 ended ************************

	file = new QFile("d:\\Shared_ReadOnly\\upload_files\\3_page.pdf");

//**************** set-2 ************************
	data = "--" + boundary + crlf
			+ "Content-Disposition: form-data; name=\"file2\"; ";
	data += "filename=\"file2.pdf\"";
	data += crlf + "Content-Type: Application/Octet" + crlf + crlf;

	file->open(QIODevice::ReadOnly);
	requestContent.append(data);
	requestContent.append(file->readAll());
	requestContent.append(crlf);
	file->close();
//**************** set-2 Ended ************************
	requestContent.append("--" + boundary + "--" + crlf); //this is the request terminator

//*********** Prepare request header ******************
	QHttpRequestHeader header = http.currentRequest();
	header.setRequest("POST",
			"http://awh1.stagekatalyst.net/katalyst/services/v1.0/CreateDelivery?mailBoxId=NETMBX09082&sessionId="
					+ sessionID
					+ "&siteAddress=katalyst3.stagekatalyst.net&subject=kjsdfhjksd");
	header.setContentType(tr("multipart/form-data; boundary=") + boundary);
	header.addValue("Connection", "Keep-Alive");
	header.addValue("Host", "http://awh1.stagekatalyst.net");

	buffer.open(QIODevice::ReadWrite);

	httpID = http.request(header, requestContent, &buffer); //sending the request

	http.close();
}

void Uploader::SlotUploadDB(QString _DB_FILE)
{
	QString bound;
	QString crlf;
	QString data;
	QByteArray dataToSend;
	QFile file(_DB_FILE);
	file.open(QIODevice::ReadOnly);

	bound = "---------------------------7d935033608e2";
	crlf = 0x0d;
	crlf += 0x0a;
	data = "--" + bound + crlf + "Content-Disposition: form-data; name=\"uploaded_file\"; ";
	data += "filename=\"" + file.fileName() + "\"";
	data += crlf + "Content-Type: application/octet-stream" + crlf + crlf;
	dataToSend.insert(0,data);
	dataToSend.append(file.readAll());
	dataToSend.append(crlf + "--" + bound + "--" + crlf);

	QUrl url("http://localhost/www.cim.unito.it/website/private/fantacalcio/test.php");
	QNetworkRequest * req = new QNetworkRequest();
	req->setUrl(url);
	req->setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary=" + bound);
	file.close();

	QNetworkAccessManager * manager = new QNetworkAccessManager();
	connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(SlotRequestFinished(QNetworkReply*)));
	QNetworkReply * reply = manager->post(*req, dataToSend);
	//connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(SlotSetProgressLevel(qint64, qint64)));
}
