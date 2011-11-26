#include "singletonQtLogger.h"
#include "IniFileManager.h"
#include "IniFilePopulator.h"
#include "Repository.h"
#include "httpwindow.h"
#include "NoNetFileDialog.h"

#include <vector>

singletonQtLogger* singletonQtLogger::pInstance = NULL;
singletonQtLogger* singletonQtLogger::Inst() {
	if (pInstance == NULL) {
		pInstance = new singletonQtLogger();
	}
	return pInstance;
}
singletonQtLogger::singletonQtLogger(QWidget *parent) :
	QWidget(parent) {
	this->ui.setupUi(this);
	this->init();
	this->show();
}
void singletonQtLogger::init() {
	this->setVersion("v3.0");
	this->setTitle("FantaCalcGui");
}
singletonQtLogger::~singletonQtLogger() {
}
//bool singletonQtLogger::debugStatus = FALSE;
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
		if (THE_REPO->debugStatus) {
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
	this->title = _title;
	this->ui.titleLabel->setText(
			"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
				"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
				"p, li { white-space: pre-wrap; }\n"
				"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
				"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#ff0000;\">"
					+ _title + "</span></p></body></html>");
}
void singletonQtLogger::setVersion(QString _version) {
	this->version = _version;
	this->ui.versionLabel->setText(
			"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"\n"
				"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
				"p, li {white-space: pre-wrap;}\n"
				"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
				"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">"
					+ _version + "</span></p></body></html>");
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
	THE_MANAGER->writeIniFile();
	this->saveLogFile();
	this->close();
}
void singletonQtLogger::configClicked() {
	THE_CONFIGURATOR->setFormazioniPath(THE_REPO->getFormazioniPath());
	THE_CONFIGURATOR->setGazzettaPath(THE_REPO->getGazzettaPath());
	THE_CONFIGURATOR->setRisultatiPath(THE_REPO->getRisultatiPath());
	THE_CONFIGURATOR->setListePath(THE_REPO->getListePath());
	THE_CONFIGURATOR->setDownloadPath(THE_REPO->getDownloadPath());
	THE_CONFIGURATOR->setFormazioniUrl(THE_REPO->getFormazioniUrl());
	THE_CONFIGURATOR->setGazzettaUrl(THE_REPO->getGazzettaUrl());
	THE_CONFIGURATOR->setDebugStatus(THE_REPO->getDebugStatus());
	THE_CONFIGURATOR->exec();
}
void singletonQtLogger::onlineClicked() {
	LOG(DEBUG,
			"In void singletonQtLogger::onlineClicked() : network will be accessed.");

	LOG(
			DEBUG,
			"In void singletonQtLogger::onlineClicked() --> THE_REPO->getFileFormazioniUrl() : "
					+ THE_REPO->getFileFormazioniUrl());
	LOG(
			DEBUG,
			"In void singletonQtLogger::onlineClicked() --> THE_REPO->getFileGazzettaUrl() : "
					+ THE_REPO->getFileGazzettaUrl());
	LOG(
			DEBUG,
			"In void singletonQtLogger::onlineClicked() --> THE_REPO->getListePath : "
					+ THE_REPO->getListePath());

	std::vector<QUrl> * urls = new std::vector<QUrl>;
	urls->push_back(QUrl::fromLocalFile(THE_REPO->getFileFormazioniUrl()));
	urls->push_back(QUrl::fromLocalFile(THE_REPO->getFileGazzettaUrl()));

	std::vector<QString> * savePaths = new std::vector<QString>;
	savePaths->push_back(THE_REPO->getListePath()+'/');
	savePaths->push_back(THE_REPO->getListePath()+'/');

	HttpWindow httpWin(this, urls, savePaths);
	httpWin.exec();

	if (httpWin.requestSucceded()) {
		LOG(
				DEBUG,
				"In singletonQtLogger::onlineClicked() --> the download of files succeded: closing useTheNetDialog.");
	} else {
		LOG(DEBUG,
				"In singletonQtLogger::onlineClicked() --> the download of files failed.");
	}
}
void singletonQtLogger::offlineClicked() {
	LOG(DEBUG,
			"In singletonQtLogger::offlineClicked() --> Network will not be accessed.");

	NoNetFileDialog * noNetFileDialog = new NoNetFileDialog(this);
	noNetFileDialog->exec();

	if (!noNetFileDialog->hasBeenAborted) {
		THE_REPO->noNetSquadreFile = noNetFileDialog->getFileNameSquadre();
		LOG(
				DEBUG,
				"In void singletonQtLogger::offlineClicked() -> fileNameSquadre : "
						+ THE_REPO->noNetSquadreFile);
		THE_REPO->noNetGazzettaFile = noNetFileDialog->getFileNameGazzetta();
		LOG(
				DEBUG,
				"In void singletonQtLogger::offlineClicked() -> fileNameSquadre : "
						+ THE_REPO->noNetGazzettaFile);
	} else {
		return;
	}
}
QString singletonQtLogger::getTitle(void) {
	return this->title;
}
QString singletonQtLogger::getVersion(void) {
	return this->version;
}

