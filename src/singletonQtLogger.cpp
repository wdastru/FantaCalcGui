#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtGui/QMessageBox>
#include <QTime>
#include <QFile>

#include "singletonQtLogger.h"
#include "IniFileManager.h"
#include "IniFilePopulator.h"
#include "Repository.h"
#include "Downloader.h"
#include "NoNetFileDialog.h"
#include "ChooseFileFromAListDialog.h"
#include "GazzettaFileReader.h"
#include "FormazioniFileReader.h"
#include "FileFormazioniViewer.h"
#include "Fanta.h"

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
	this->setTitle("FantaCalcGui");
}
singletonQtLogger::~singletonQtLogger() {
}
void singletonQtLogger::Logging(QString type, QString message) {
	this->fileContent += (message + "\n");

	if (type == "INFO")
		this->ui.plainTextEdit->appendHtml(
				"[" + QTime::currentTime().toString("hh:mm:ss.zzz")
						+ "] INFO    : " + message);
	else if (type == "ERROR")
		this->ui.plainTextEdit->appendHtml(
				"<span style='color:#FF0000;'>["
						+ QTime::currentTime().toString("hh:mm:ss.zzz")
						+ "] ERROR   : " + message + "</span>");
	else if (type == "DEBUG") {
		if (THE_REPO->debugStatus) {
			this->ui.plainTextEdit->appendHtml(
					"[" + QTime::currentTime().toString("hh:mm:ss.zzz")
							+ "] DEBUG   : " + message);
		}
	} else if (type == "FATAL")
		this->ui.plainTextEdit->appendHtml(
				"<span style='color:#FF0000; font-weight:bold'>["
						+ QTime::currentTime().toString("hh:mm:ss.zzz")
						+ "] FATAL   : " + message + "</span>");
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
	this->ui.titleLabel->setText(_title);
}
void singletonQtLogger::setVersion(QString _version) {
	this->version = _version;
	this->ui.versionLabel->setText(_version);
}
void singletonQtLogger::saveLogFile() {
	QFile * file = new QFile;

	if (this->ui.outputFileNameLineEdit->text().isEmpty()) {
		this->setLogFileName(THE_MANAGER->getWorkDir() + "log.txt");
		file->setFileName(this->logFileName);
		this->Inst()->Logging(
				"DEBUG",
				"In singletonQtLogger::saveLogFile() --> logFileName is empty. Continue with "
						+ this->logFileName);
	} else {
		file->setFileName(
				THE_REPO->risultatiPath + "\\"
						+ this->ui.outputFileNameLineEdit->text());
		this->Inst()->Logging(
				"DEBUG",
				"In singletonQtLogger::saveLogFile() --> logFileName is "
						+ this->logFileName);
	}

	if (QFile::exists(this->logFileName)) {

		QMessageBox msgBox;
		msgBox.setWindowTitle("File exists !");
		msgBox.setInformativeText(
				tr("There already exists a file called %1. Overwrite?").arg(
						this->logFileName));
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::No);
		msgBox.setIcon(QMessageBox::Question);
		msgBox.setFont(THE_REPO->fontVariableWidthSmall);
		int reply = msgBox.exec();

		if (reply == QMessageBox::No)
			return;
		QFile::remove(this->logFileName);
	}

	if (!file->open(QIODevice::WriteOnly)) {

		QMessageBox msgBox;
		msgBox.setWindowTitle("File cannot be saved !");
		msgBox.setInformativeText(
				tr("Unable to save the file %1: %2.") .arg(this->logFileName).arg(
						file->errorString()));
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Ok);
		msgBox.setIcon(QMessageBox::Information);
		msgBox.setFont(THE_REPO->fontVariableWidthSmall);
		msgBox.exec();

		//		QMessageBox::information(
		//				this,
		//				tr("HTTP"),
		//				tr("Unable to save the file %1: %2.") .arg(this->logFileName).arg(
		//						file->errorString()));
		return;
	}

	fileContent.replace("<br/>", "\n");
	fileContent.replace("<br />", "\n");
	fileContent.replace("<pre>", "");
	fileContent.replace("</pre>", "\n");

	fileContent += "\n File prodotto da FantaCalcGui.exe " + this->getVersion()
			+ "\n";

	file->write(this->fileContent.toStdString().c_str());
	file->close();
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
	savePaths->push_back(THE_REPO->getListePath() + "/listaFormazioni.txt");
	savePaths->push_back(THE_REPO->getListePath() + "/listaGazFiles.txt");

	Downloader listsDownloader(THE_LOGGER, urls, savePaths);
	listsDownloader.show();
	listsDownloader.exec();

	if (listsDownloader.requestSucceded()) {
		LOG(DEBUG,
				"In singletonQtLogger::onlineClicked() --> the download of files succeded.");

		ChooseFileFromAListDialog * chooseFileFromAListDialog =
				new ChooseFileFromAListDialog(THE_REPO->getListaFormazioni(),
						THE_REPO->getListaGazFiles(), THE_LOGGER);
		chooseFileFromAListDialog->show();
		chooseFileFromAListDialog->exec();

		if (!chooseFileFromAListDialog->wasCancelClicked()) {
			THE_REPO->fileGazzetta
					= chooseFileFromAListDialog->getFileGazzetta();
			THE_REPO->fileFormazioni
					= chooseFileFromAListDialog->getFileFormazioni();

			LOG(
					DEBUG,
					"In void singletonQtLogger::onlineClicked() --> fileGazzetta : "
							+ THE_REPO->fileGazzetta);
			LOG(
					DEBUG,
					"In void singletonQtLogger::onlineClicked() --> fileFormazioni : "
							+ THE_REPO->fileFormazioni);

			emit(this->onOffClickedFinished());

		} else {
			LOG(
					DEBUG,
					"In void singletonQtLogger::onlineClicked() --> Cancel clicked in ChooseFileFromAListDialog.");
			return;
		}
	} else {
		/* TODO
		 * inserire exception
		 */
		;
	}
}
void singletonQtLogger::offlineClicked() {
	LOG(DEBUG,
			"In singletonQtLogger::offlineClicked() --> Network will not be accessed.");

	NoNetFileDialog * noNetFileDialog = new NoNetFileDialog(THE_LOGGER);
	noNetFileDialog->exec();

	if (!noNetFileDialog->hasBeenAborted) {
		THE_REPO->fileFormazioni = noNetFileDialog->getFileNameSquadre();
		THE_REPO->fileGazzetta = noNetFileDialog->getFileNameGazzetta();

		LOG(
				DEBUG,
				"In void singletonQtLogger::offlineClicked() --> fileGazzetta : "
						+ THE_REPO->fileGazzetta);
		LOG(
				DEBUG,
				"In void singletonQtLogger::offlineClicked() --> fileFormazioni : "
						+ THE_REPO->fileFormazioni);

		emit(this->onOffClickedFinished());

	} else {
		LOG(
				DEBUG,
				"In void singletonQtLogger::offlineClicked() --> noNetFileDialog has been aborted.");
		return;
	}
}
QString singletonQtLogger::getTitle(void) {
	return this->title;
}
QString singletonQtLogger::getVersion(void) {
	return this->version;
}
void singletonQtLogger::goOn() {
	LOG(DEBUG, "In singletonQtLogger::goOn().");

	// --> lettura file Gazzetta e Formazioni
	GazzettaFileReader * gazzettaFileReader = new GazzettaFileReader(
			THE_REPO->fileGazzetta);
	FormazioniFileReader * formazioniFileReader = new FormazioniFileReader(
			THE_REPO->fileFormazioni);

	formazioniFileReader->setPlayers(gazzettaFileReader->getOutput());

	THE_VIEWER->setFile(THE_REPO->fileFormazioni);
	unsigned int retVal;

	do {
		try {
			THE_VIEWER->show();
			THE_VIEWER->exec();

			if (THE_VIEWER->getResult() == 1) {
				LOG(DEBUG,
						"In singletonQtLogger::goOn() --> THE_VIEWER returned 1.");
			} else {
				LOG(DEBUG,
						"In singletonQtLogger::goOn() --> THE_VIEWER returned 0.");
				break;
			}

			Fanta::Refresh();

			retVal = formazioniFileReader->execute();

			LOG(
					DEBUG,
					"In singletonQtLogger::goOn() --> formazioniFileReader::execute() returned "
							+ my::toQString<unsigned int>(retVal) + ".");
		} catch (QString& str) {
			LOG(
					DEBUG,
					"In singletonQtLogger::goOn() --> exception caught! retVal : "
							+ my::toQString<unsigned int>(retVal) + ", " + str);
		}
	} while (retVal != FORMFILEREAD_OK);
	// <-- lettura file Gazzetta e Formazioni

	if (THE_VIEWER->getResult() == 0) { // in caso di break
		return;
	}

	try {
		FANTA->execute();
	} catch (...) {
		LOG(DEBUG, "In singletonQtLogger::goOn() --> exception caught.");
	}

	LOG(DEBUG, "In singletonQtLogger::goOn() --> after FANTA->execute() call.");

	try {
		QString fileName(
				"risultato_" + QString::fromStdString(FANTA->getTeamName(0))
						+ "-" + QString::fromStdString(FANTA->getTeamName(1))
						+ "_" + QFileInfo(THE_REPO->fileGazzetta).fileName());
		this->setLogFileName(THE_REPO->getRisultatiPath() + "/" + fileName);

		LOG(
				DEBUG,
				"In singletonQtLogger::goOn() --> file name temporaneo : "
						+ fileName + ".");

		FANTA->printTitolo(
				FANTA->getTeamName(0) + " - " + FANTA->getTeamName(1));
		FANTA->printRiepilogo();
		FANTA->printFormations();

		this->ui.outputFileNameLineEdit->setEnabled(true);
		this->ui.outputFileNameLineEdit->setText(fileName);
	} catch (...) {
		LOG(DEBUG,
				"In singletonQtLogger::goOn() --> exception caught after FANTA->execute().");
	}
}
void singletonQtLogger::setLogFileName(QString filename) {
	this->logFileName = filename;
}
