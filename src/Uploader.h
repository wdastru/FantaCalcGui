#include<QtNetwork/QHttp>
#include<QtNetwork/QHttpRequestHeader>
#include<QBuffer>
#include<QFile>
#include<QTextEdit>

class Uploader: QObject {

Q_OBJECT

private:
	int httpID;
	QBuffer buffer;

public:
	QHttp http;
	QTextEdit textbox;
	Uploader();
	virtual ~Uploader();
	void upload();
	void SlotUploadDB(QString);

signals:
	void signalMessage(QString);

public slots:
	void httpDone(bool error);
};
