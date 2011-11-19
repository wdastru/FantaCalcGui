#include "singletonQtLogger.h"

singletonQtLogger* singletonQtLogger::Inst() {
	if (pInstance == NULL) {
		pInstance = new singletonQtLogger();
	}
	return pInstance;
}
singletonQtLogger::singletonQtLogger(QWidget *parent) :
	QWidget(parent) {
	this->ui.setupUi(this);
	this->version = "v0.2 build 14";
	this->show();
}
singletonQtLogger::~singletonQtLogger() {
}
singletonQtLogger* singletonQtLogger::pInstance = NULL;
bool singletonQtLogger::debugStatus = FALSE;
void singletonQtLogger::Logging(QString type, QString message) {
	this->fileContent += (message + "\n");

	if (type == "INFO")
		this->ui.plainTextEdit->appendHtml(
				"[" + QTime::currentTime().toString("hh:mm:ss.zzz")
						+ "] INFO    : " + message);
	else if (type == "ERROR")
		this->ui.plainTextEdit->appendHtml(
				"[" + QTime::currentTime().toString("hh:mm:ss.zzz")
						+ "] ERROR   : " + message);
	else if (type == "DEBUG") {
		if (this->debugStatus) {
			this->ui.plainTextEdit->appendHtml(
					"[" + QTime::currentTime().toString("hh:mm:ss.zzz")
							+ "] DEBUG   : " + message);
		}
	} else if (type == "FATAL")
		this->ui.plainTextEdit->appendHtml(
				"[" + QTime::currentTime().toString("hh:mm:ss.zzz")
						+ "] FATAL   : " + message);
	else if (type == "WARN")
		this->ui.plainTextEdit->appendHtml(
				"[" + QTime::currentTime().toString("hh:mm:ss.zzz")
						+ "] WARNING : " + message);
	else if (type == "FILE") {
		;
	} else
		this->ui.plainTextEdit->appendHtml(
				"[" + QTime::currentTime().toString("hh:mm:ss.zzz")
						+ "] !!!! : Type " + type + " not recognized.");
	return;
}
void singletonQtLogger::setTitle(QString _title) {
	ui.label->setText(
			"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
				"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
				"p, li { white-space: pre-wrap; }\n"
				"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
				"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#ff0000;\">"
					+ _title + "</span></p><p>" + this->version
					+ "</p></body></html>");
}
void singletonQtLogger::setDebugStatus(bool _status) {
	this->debugStatus = _status;
}
void singletonQtLogger::setLogFileName(QString _filename) {
	this->logFileName = _filename;
}
void singletonQtLogger::saveLogFile() {
	if (this->logFileName.isEmpty()) {
		this->Inst()->Logging(
				"DEBUG",
				"In singletonQtLogger::saveLogFile() --> logFileName is empty. Continue with log.txt.");
		this->logFileName = "log.txt";
	} else {
		this->Inst()->Logging(
				"DEBUG",
				"In singletonQtLogger::saveLogFile() --> logFileName is "
						+ this->logFileName);
	}

	if (QFile::exists(this->logFileName)) {
		if (QMessageBox::question(
				this,
				tr("HTTP"),
				tr("There already exists a file called %1. Overwrite?").arg(
						this->logFileName), QMessageBox::Yes | QMessageBox::No,
				QMessageBox::No) == QMessageBox::No)
			return;
		QFile::remove(this->logFileName);
	}

	QFile file(this->logFileName);

	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::information(
				this,
				tr("HTTP"),
				tr("Unable to save the file %1: %2.") .arg(this->logFileName).arg(
						file.errorString()));
		return;
	}

	fileContent.replace("<br/>", "\n");
	fileContent.replace("<br />", "\n");
	fileContent.replace("<pre>", "");
	fileContent.replace("</pre>", "\n");

	file.write(this->fileContent.toStdString().c_str());
	file.close();
}
void singletonQtLogger::saveLogAndClose() {
	this->saveLogFile();
	this->close();
}
