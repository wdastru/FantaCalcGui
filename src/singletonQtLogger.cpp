#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtCore/QList>
#include <QtCore/QHash>
#include <QtCore/QDebug>
#include <QtGui/QMessageBox>
#include <QtXml/QDomDocument>
#include <QtCore/QTime>
#include <QtCore/QFile>
#include <QtCore/QObject>

#include "defines.h"
#include "singletonQtLogger.h"
#include "IniFileManager.h"
#include "IniFilePopulator.h"
#include "Repository.h"
#include "Downloader.h"
#include "NoNetFileDialog.h"
#include "ChooseFiles.h"
#include "GazzettaFileReader.h"
#include "FormazioniFileReader.h"
#include "FileFormazioniReader.h"
#include "FileFormazioniViewer.h"
#include "Fanta.h"

#include <vector>
#include <string>

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

	if (type == "INFO") {
		this->ui.plainTextEdit->appendHtml(" " + message);
	} else if (type == "ERROR") {
		this->ui.plainTextEdit->appendHtml(
				"<span style='color:#FF0000;'> ERROR : " + message + "</span>");
	} else if (type == "DEBUG") {
		if (THE_REPO->debugStatus) {
			this->ui.plainTextEdit->appendHtml(" " + message);
		}
	} else if (type == "FATAL") {
		this->ui.plainTextEdit->appendHtml(
				"<span style='color:#FF0000; font-weight:bold'> FATAL ERROR : "
						+ message + "</span>");
	} else if (type == "WARN") {
		this->ui.plainTextEdit->appendHtml(
				"<span style='color:#FF8800;'> WARNING : " + message
						+ "</span>");
	} else if (type == "FILE") {
		;
	} else if (type == "UPDATE") {
		this->ui.plainTextEdit->appendHtml(
				"<span style='color:#00CC00; font-weight:bold'> UPDATE : "
						+ message + "</span>");
	} else
		this->ui.plainTextEdit->appendHtml(
				" !!!! : Type " + type + " not recognized.");

	this->fileContent += (message + "<br/>");

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
void singletonQtLogger::setRevision(QString _revision) {
	this->revision = _revision;
	//qDebug() << "In void singletonQtLogger::setRevision(QString _revision): revision = " + this->revision;
	//this->ui.versionLabel->setText(_version);
}
void singletonQtLogger::saveLogFile() {
	QFile * file = new QFile;

	if (this->ui.outputFileNameLineEdit->text().isEmpty()) {
		QString logFileName = THE_MANAGER->getWorkDir() + "/log.txt";
		STR_MOD->fixSlashes(logFileName);
		this->setLogFileName(logFileName);
		file->setFileName(this->logFileName);
		//qDebug() << "In singletonQtLogger::saveLogFile() --> logFileName is empty.<br>Saving to " \
				+ this->logFileName;
	} else {
		file->setFileName(
				THE_REPO->risultatiPath
						+ this->ui.outputFileNameLineEdit->text());

		//qDebug() << "In singletonQtLogger::saveLogFile() --> logFileName is " \
				<< this->logFileName;

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
				tr("Unable to save the file %1: %2.").arg(this->logFileName).arg(
						file->errorString()));
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Ok);
		msgBox.setIcon(QMessageBox::Information);
		msgBox.setFont(THE_REPO->fontVariableWidthSmall);
		msgBox.exec();

		return;
	}

	fileContent.replace("<br>", "\n");
	fileContent.replace("<br/>", "\n");
	fileContent.replace("<br />", "\n");
	fileContent.replace("<pre>", "");
	fileContent.replace("</pre>", "\n");
	fileContent.replace("&nbsp;", " ");
	fileContent.replace("<span style='color:#FF0000;'> ERROR : ", "");
	fileContent.replace(
			"<span style='color:#FF0000; font-weight:bold'> FATAL ERROR : ",
			"");
	fileContent.replace("<span style='color:#FF8800;'> WARNING : ", "");
	fileContent.replace(
			"<span style='color:#00CC00; font-weight:bold'> UPDATE : ", "");
	fileContent.replace("</span>", "\n");

	fileContent += "\n File prodotto con FantaCalcGui v" + this->getVersion()
			+ " (rev. " + THE_LOGGER->getRevision().left(6) + ")\n\n";

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
	LOG(DEBUG, "<br> ========================");
	LOG(DEBUG, 	   " === Modalita' online ===");
	LOG(DEBUG,     " ========================<br>");

	//qDebug() << "In void singletonQtLogger::onlineClicked() --> THE_REPO->getFileFormazioniUrl() : " + THE_REPO->getFileFormazioniUrl();
	//qDebug() << "In void singletonQtLogger::onlineClicked() --> THE_REPO->getFileGazzettaUrl() : " + THE_REPO->getFileGazzettaUrl();
	//qDebug() << "In void singletonQtLogger::onlineClicked() --> THE_REPO->getListePath : " + THE_REPO->getListePath();

	std::vector<QUrl> * urls = new std::vector<QUrl>;
	urls->push_back(QUrl::fromLocalFile(THE_REPO->getFileFormazioniUrl()));
	urls->push_back(QUrl::fromLocalFile(THE_REPO->getFileGazzettaUrl()));

	std::vector<QString> *savePaths = new std::vector<QString>;
	savePaths->push_back(THE_REPO->getListePath() + "listaFormazioni.txt");
	savePaths->push_back(THE_REPO->getListePath() + "listaGazFiles.txt");

	Downloader listsDownloader(THE_LOGGER, urls, savePaths, TRUE);

	if (listsDownloader.requestSucceded()) {
		//qDebug() << "In singletonQtLogger::onlineClicked() --> listsDownloader request succeded.";

		ChooseFiles * chooseFiles = new ChooseFiles(
				THE_REPO->getListaFormazioni(), THE_REPO->getListaGazFiles(),
				THE_LOGGER);
		chooseFiles->show();
		chooseFiles->exec();

		if (!chooseFiles->wasCancelClicked()) {
			THE_REPO->fileGazzetta = chooseFiles->getFileGazzetta();
			THE_REPO->fileFormazioni = chooseFiles->getFileFormazioni();

			//qDebug() << "In void singletonQtLogger::onlineClicked() --> fileGazzetta : " + THE_REPO->fileGazzetta;
			//qDebug() << "In void singletonQtLogger::onlineClicked() --> fileFormazioni : " + THE_REPO->fileFormazioni;

			emit(this->onOffClickedFinished());

		} else {
			//qDebug() << "In void singletonQtLogger::onlineClicked() --> Cancel clicked in ChooseFiles.";
			return;
		}
	} else {
		qDebug() << "In singletonQtLogger::onlineClicked() --> listsDownloader request not succeded.";
		/* TODO
		 * handle exception
		 * * * * * * * * * * * */
	}
}
void singletonQtLogger::offlineClicked() {
	LOG(DEBUG, "<br> =========================");
	LOG(DEBUG,     " === Modalita' offline ===");
	LOG(DEBUG,     " =========================<br>");

	NoNetFileDialog * noNetFileDialog = new NoNetFileDialog(THE_LOGGER);
	noNetFileDialog->exec();

	if (!noNetFileDialog->hasBeenAborted) {
		THE_REPO->fileFormazioni = noNetFileDialog->getFileNameSquadre();
		THE_REPO->fileGazzetta = noNetFileDialog->getFileNameGazzetta();

		LOG(DEBUG,
				QObject::tr("    File gazzetta   : %1").arg(THE_REPO->fileGazzetta));
		LOG(DEBUG,
				QObject::tr("    File formazioni : %1").arg(
						THE_REPO->fileFormazioni));

		emit(this->onOffClickedFinished());

	} else {
		//qDebug() << "In void singletonQtLogger::offlineClicked() --> noNetFileDialog has been aborted.";
		return;
	}
}
QString singletonQtLogger::getTitle(void) {
	return this->title;
}
QString singletonQtLogger::getVersion(void) {
	return this->version;
}
QString singletonQtLogger::getRevision(void) {
	return this->revision;
}
void singletonQtLogger::goOn() {
	//qDebug() << "In singletonQtLogger::goOn().";

	// --> lettura file Gazzetta e Formazioni
	GazzettaFileReader * gazzettaFileReader = new GazzettaFileReader(
			THE_REPO->fileGazzetta);
	//FormazioniFileReader * formazioniFileReader = new FormazioniFileReader( \
				THE_REPO->fileFormazioni);

	/*
	 * new FileFormazioniReader class
	 * * * * * * * * * * * * * * * * * * */
	FileFormazioniReader * fileFormazioniReader = new FileFormazioniReader( \
				THE_REPO->fileFormazioni, THE_LOGGER);

	/* * * * * * * * * * * * * * * * * */

	//formazioniFileReader->setPlayers(gazzettaFileReader->getOutput());
	fileFormazioniReader->setPlayers(gazzettaFileReader->getOutput());

	THE_VIEWER->setFile(THE_REPO->fileFormazioni);
	unsigned int retVal;

	do {
		try {
			THE_VIEWER->show();
			THE_VIEWER->exec();

			if (THE_VIEWER->getResult() == 1) {
				//qDebug() << "In singletonQtLogger::goOn() --> THE_VIEWER returned 1.";
			} else {
				//qDebug() << "In singletonQtLogger::goOn() --> THE_VIEWER returned 0.";
				break;
			}

			Fanta::Refresh();

			//retVal = formazioniFileReader->execute();
			retVal = fileFormazioniReader->execute();

			//qDebug() << "In singletonQtLogger::goOn() --> formazioniFileReader::execute() returned " \
										+ my::toQString<unsigned int>(retVal) + ".");
			//qDebug() << "In singletonQtLogger::goOn() --> fileFormazioniReader::execute() returned " \
										+ my::toQString<unsigned int>(retVal) + ".");

		} catch (QString& str) {

			qDebug() << "In singletonQtLogger::goOn() --> exception caught! retVal : " + my::toQString<unsigned int>(retVal) + ", " + str;

		}
	} while (retVal != FORMFILEREAD_OK);
	// <-- lettura file Gazzetta e Formazioni

	if (THE_VIEWER->getResult() == 0) { // in caso di break
		return;
	}

	try {
		FANTA->execute();
	} catch (...) {
		qDebug() << "In singletonQtLogger::goOn() --> exception caught.";
	}

	//qDebug() << "In singletonQtLogger::goOn() --> after FANTA->execute() call.";

	try {
		QString fileName(
				"risultato_" + QString::fromStdString(FANTA->getTeamName(0))
						+ "-" + QString::fromStdString(FANTA->getTeamName(1))
						+ "_" + QFileInfo(THE_REPO->fileGazzetta).fileName());
		this->setLogFileName(THE_REPO->getRisultatiPath() + "/" + fileName);

		//qDebug() << QObject::tr("In singletonQtLogger::goOn() --> file name temporaneo : %1").arg(fileName);

		FANTA->printTitolo(
				FANTA->getTeamName(0) + " - " + FANTA->getTeamName(1), INFO);

		FANTA->printRiepilogo();
		FANTA->printFormations();

		LOG(DEBUG, "<br/><br/>    DETTAGLIO GIOCATORI<br/>");

		FANTA->printPlayersInfo();

		this->ui.outputFileNameLineEdit->setEnabled(true);
		this->ui.outputFileNameLineEdit->setText(fileName);
	} catch (...) {
		LOG(ERROR, "Exception caught after FANTA->execute().");
		qDebug() << "In singletonQtLogger::goOn() --> exception caught after FANTA->execute().";
	}
}
void singletonQtLogger::setLogFileName(QString filename) {
	this->logFileName = filename;
}
bool singletonQtLogger::checkForUpdates() {

	LOG(DEBUG, "<br> =============================");
	LOG(DEBUG,     " === Ricerca aggiornamenti ===");
	LOG(DEBUG,     " =============================<br>");
	//	qDebug << "In void singletonQtLogger::checkForUpdates().";

	QStringList current = this->getVersion().split(QRegExp("\\\."));
	int verCurrent = current.at(0).toInt();
	int majCurrent = current.at(1).toInt();
	int minCurrent = current.at(2).toInt();

	std::vector<QUrl> * urls = new std::vector<QUrl>;
	QString url = THE_REPO->getFileFormazioniUrl();
	unsigned int pos = url.lastIndexOf("/");
	url = url.left(pos);
	pos = url.lastIndexOf("/");
	url = url.left(pos);
	pos = url.lastIndexOf("/");
	url = url.left(pos) + "/download/updates.xml";

	urls->push_back(QUrl::fromLocalFile(url));

	// qDebug << "In void singletonQtLogger::checkForUpdates() --> url : " + url;

	std::vector<QString> *savePaths = new std::vector<QString>;
	QString savePath = THE_REPO->getDownloadPath() + "updates.xml";
	savePaths->push_back(savePath);

	// qDebug << "In void singletonQtLogger::checkForUpdates() --> savePath : " + savePath;

	Downloader updatesXmlDownloader(THE_LOGGER, urls, savePaths, TRUE);

	if (updatesXmlDownloader.requestSucceded()) { // download succeded

		//qDebug() << "    Scaricato le informazioni relative agli aggiornamenti disponibili";

		std::vector<QString> content;
		std::vector<QString> status;
		std::vector<QString> availableVersions;

		QDomDocument doc("updates");
		QFile file(savePath);
		if (!file.open(QIODevice::ReadOnly))
			return false;
		if (!doc.setContent(&file)) {
			file.close();
			return false;
		}
		file.close();

		// print out the element names of all elements that are direct children
		// of the outermost element.
		QDomElement docElem = doc.documentElement();

		QList<QList<QHash<QString, QString> > > listOfResources;

		QDomNode n = docElem.firstChild();
		QHash<QString, QString> hash;

		while (!n.isNull()) {

			hash.clear();
			QList<QHash<QString, QString> > list;

			QDomElement e = n.toElement(); // try to convert the node to an element.
			if (!e.isNull()) {

				QDomNode m = n.firstChild();
				while (!m.isNull()) {
					QDomElement f = m.toElement(); // try to convert the node to an element.
					if (!f.isNull()) {

						if (f.tagName() == "file") {
							hash.insert("file", f.text());
						} else if (f.tagName() == "version") {
							hash.insert("version", f.text());

							QStringList available = f.text().split(
									QRegExp("\\\."));
							int verAvailable = available.at(0).toInt();
							int majAvailable = available.at(1).toInt();
							int minAvailable = available.at(2).toInt();

							availableVersions.push_back(f.text());

							if (verAvailable > verCurrent) {
								hash.insert("status", "new");
							} else if (verAvailable == verCurrent) {
								if (majAvailable > majCurrent) {
									hash.insert("status", "new");
								} else if (majAvailable == majCurrent) {
									if (minAvailable > minCurrent) {
										hash.insert("status", "new");
									} else if (minAvailable == minCurrent) {
										hash.insert("status", "current");
									} else {
										hash.insert("status", "old");
									}
								} else {
									hash.insert("status", "old");
								}
							} else {
								hash.insert("status", "old");
							}

						} else if (f.tagName() == "description") {
							hash.insert("description", f.text());
						} else if (f.tagName() == "new") {
							hash.insert("new", f.text());
						}

					}
					m = m.nextSibling();
				}
				list.push_back(hash);
			}

			listOfResources.push_back(list);

			//for (int i = 0; i < list.size(); ++i) {
			//	qDebug() << "In void singletonQtLogger::checkForUpdates() --> \n hash[\"file\"] : " + hash["file"] \
			//			+ ", \n hash[\"version\"] : " + hash["version"] \
			//			+ ", \n hash[\"description\"] : " + hash["description"] \
			//			+ ", \n hash[\"status\"] : " + hash["status"] \
			//			+ ", \n hash[\"new\"] : " + hash["new"];
			//}

			n = n.nextSibling();
		}

		bool foundUpdates = false;

		for (int i = 0; i < listOfResources.size(); ++i) {
			for (int j = 0; j < listOfResources.at(i).size(); ++j) {

				if (listOfResources.at(i).at(j)["status"] == "new") {
					LOG(UPDATE, \
							"    E' possibile scaricare la versione " \
									+ listOfResources.at(i).at(j)["version"] \
									+ " : " \
									+ listOfResources.at(i).at(j)["file"] + " (" \
									+ listOfResources.at(i).at(j)["description"] \
									+ ")<br>changes : <br>" \
									+ listOfResources.at(i).at(j)["new"]);

					foundUpdates = true;
				}
			}
		}

		if (!foundUpdates) {
			LOG(UPDATE, \
					"    La versione e' aggiornata");

		}

		for (int i = 0; i < listOfResources.size(); ++i) {
			for (int j = 0; j < listOfResources.at(i).size(); ++j) {

				if (listOfResources.at(i).at(j)["status"] == "new") {

					QMessageBox msgBox;
					msgBox.setWindowTitle("HTTP");
					msgBox.setInformativeText(
							tr("Version %1 available.\nDownload \n%2\n(%3) ?").arg(
									listOfResources.at(i).at(j)["version"]).arg(
									listOfResources.at(i).at(j)["file"]).arg(
									listOfResources.at(i).at(j)["description"]));
					msgBox.setStandardButtons(
							QMessageBox::Yes | QMessageBox::No);
					msgBox.setDefaultButton(QMessageBox::No);
					msgBox.setIcon(QMessageBox::Question);
					msgBox.setFont(THE_REPO->fontVariableWidthSmall);
					int answer = msgBox.exec();

					if (answer == QMessageBox::Yes) {
						std::vector < QUrl > *urls = new std::vector<QUrl>;

						QString url = THE_REPO->getFileFormazioniUrl();
						unsigned int pos = url.lastIndexOf("/");
						url = url.left(pos);
						pos = url.lastIndexOf("/");
						url = url.left(pos);
						pos = url.lastIndexOf("/");
						url = url.left(pos) + "/download/"
								+ listOfResources.at(i).at(j)["file"];

						urls->push_back(QUrl::fromLocalFile(url));

						qDebug() << "In void singletonQtLogger::checkForUpdates() --> url : " + url;

						std::vector < QString > *savePaths = new std::vector<
								QString>;
						QString savePath = THE_REPO->getDownloadPath() + listOfResources.at(i).at(j)["file"];
						savePaths->push_back(savePath);

						qDebug() << "In void singletonQtLogger::checkForUpdates() --> savePath : " + savePath;

						Downloader updateDownloader(THE_LOGGER, urls, savePaths,
								true);

						if (updateDownloader.requestSucceded()) { // download succeded
							LOG(DEBUG,
									"Download of "
											+ listOfResources.at(i).at(j)["file"]
											+ " succeded.");
						} else {
							LOG(ERROR,
									listOfResources.at(i).at(j)["file"]
											+ " download failed.");

						}
					}
				}
			}
		}

	} else { // download failed
		LOG(WARN,
				"Non e' stato possibile scaricare le informazioni relative agli aggiornamenti disponibili.");
		return false;
	}

	return true;
}
