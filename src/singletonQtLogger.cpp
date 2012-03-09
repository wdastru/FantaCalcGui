#include <QString>
#include <QTextStream>
#include <QList>
#include <QHash>
#include <QDebug>
#include <QMessageBox>
#include <QtXml/QDomDocument>
#include <QTime>
#include <QFile>
#include <QObject>

#include "defines.h"
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

	if (type == "INFO") {
		this->ui.plainTextEdit->appendHtml(" " + message);
	} else if (type == "ERROR") {
		this->ui.plainTextEdit->appendHtml(
			ERROR_STYLE(message));
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
void singletonQtLogger::saveLogFile() {
	QFile * file = new QFile;

	if (this->ui.outputFileNameLineEdit->text().isEmpty()) {
		this->setLogFileName(THE_MANAGER->getWorkDir() + "log.txt");
		file->setFileName(this->logFileName);
		this->Inst()->Logging("DEBUG",
				"In singletonQtLogger::saveLogFile() --> logFileName is empty. Continue with "
						+ this->logFileName);
	} else {
		file->setFileName(
				THE_REPO->risultatiPath + "\\"
						+ this->ui.outputFileNameLineEdit->text());
		this->Inst()->Logging("DEBUG",
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
	LOG(DEBUG, "Modalita' online<br>");

	//	LOG(
	//			DEBUG,
	//			"In void singletonQtLogger::onlineClicked() --> THE_REPO->getFileFormazioniUrl() : "
	//					+ THE_REPO->getFileFormazioniUrl());
	//	LOG(
	//			DEBUG,
	//			"In void singletonQtLogger::onlineClicked() --> THE_REPO->getFileGazzettaUrl() : "
	//					+ THE_REPO->getFileGazzettaUrl());
	//	LOG(
	//			DEBUG,
	//			"In void singletonQtLogger::onlineClicked() --> THE_REPO->getListePath : "
	//					+ THE_REPO->getListePath());

	std::vector<QUrl> * urls = new std::vector<QUrl>;
	urls->push_back(QUrl::fromLocalFile(THE_REPO->getFileFormazioniUrl()));
	urls->push_back(QUrl::fromLocalFile(THE_REPO->getFileGazzettaUrl()));

	std::vector<QString> * savePaths = new std::vector<QString>;
	savePaths->push_back(THE_REPO->getListePath() + "/listaFormazioni.txt");
	savePaths->push_back(THE_REPO->getListePath() + "/listaGazFiles.txt");

	Downloader listsDownloader(THE_LOGGER, urls, savePaths, TRUE);

	if (listsDownloader.requestSucceded()) {
		//		LOG(DEBUG,
		//				"In singletonQtLogger::onlineClicked() --> the download of files succeded.");

		ChooseFileFromAListDialog * chooseFileFromAListDialog =
				new ChooseFileFromAListDialog(THE_REPO->getListaFormazioni(),
						THE_REPO->getListaGazFiles(), THE_LOGGER);
		chooseFileFromAListDialog->show();
		chooseFileFromAListDialog->exec();

		if (!chooseFileFromAListDialog->wasCancelClicked()) {
			THE_REPO->fileGazzetta =
					chooseFileFromAListDialog->getFileGazzetta();
			THE_REPO->fileFormazioni =
					chooseFileFromAListDialog->getFileFormazioni();

			//			LOG(
			//					DEBUG,
			//					"In void singletonQtLogger::onlineClicked() --> fileGazzetta : "
			//							+ THE_REPO->fileGazzetta);
			//			LOG(
			//					DEBUG,
			//					"In void singletonQtLogger::onlineClicked() --> fileFormazioni : "
			//							+ THE_REPO->fileFormazioni);

			emit(this->onOffClickedFinished());

		} else {
			LOG(DEBUG,
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
	LOG(DEBUG, "Modalita' offline<br>");

	NoNetFileDialog * noNetFileDialog = new NoNetFileDialog(THE_LOGGER);
	noNetFileDialog->exec();

	if (!noNetFileDialog->hasBeenAborted) {
		THE_REPO->fileFormazioni = noNetFileDialog->getFileNameSquadre();
		THE_REPO->fileGazzetta = noNetFileDialog->getFileNameGazzetta();

		LOG(DEBUG,
				QObject::tr("File gazzetta : %1").arg(THE_REPO->fileGazzetta));
		LOG(DEBUG,
				QObject::tr("File formazioni : %1").arg(
						THE_REPO->fileFormazioni));

		emit(this->onOffClickedFinished());

	} else {
		//		LOG(
		//				DEBUG,
		//				"In void singletonQtLogger::offlineClicked() --> noNetFileDialog has been aborted.");
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
	//	LOG(DEBUG, "In singletonQtLogger::goOn().");

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
				//				LOG(DEBUG,
				//						"In singletonQtLogger::goOn() --> THE_VIEWER returned 1.");
			} else {
				//				LOG(DEBUG,
				//						"In singletonQtLogger::goOn() --> THE_VIEWER returned 0.");
				break;
			}

			Fanta::Refresh();

			retVal = formazioniFileReader->execute();

			LOG(DEBUG,
					"In singletonQtLogger::goOn() --> formazioniFileReader::execute() returned "
							+ my::toQString<unsigned int>(retVal) + ".");

		} catch (QString& str) {

			LOG(DEBUG,
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

		LOG(DEBUG,
				QObject::tr(
						"In singletonQtLogger::goOn() --> file name temporaneo : %1").arg(
						fileName));

		FANTA->printTitolo(
				FANTA->getTeamName(0) + " - " + FANTA->getTeamName(1));

		FANTA->printRiepilogo();
		FANTA->printFormations();

		LOG(INFO, "<br/><br/>&nbsp;&nbsp;&nbsp;DETTAGLIO SQUADRE : <br/>");

		FANTA->printPlayersInfo();

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
bool singletonQtLogger::checkForUpdates() {

	//	LOG(DEBUG, "In void singletonQtLogger::checkForUpdates().");

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

	//	LOG(DEBUG, "In void singletonQtLogger::checkForUpdates() --> url : " + url);

	std::vector<QString> * savePaths = new std::vector<QString>;
	QString savePath = THE_REPO->getDownloadPath() + "/updates.xml";
	savePaths->push_back(savePath);

	//	LOG(
	//			DEBUG,
	//			"In void singletonQtLogger::checkForUpdates() --> savePath : "
	//					+ savePath);

	Downloader updatesXmlDownloader(THE_LOGGER, urls, savePaths, TRUE);

	if (updatesXmlDownloader.requestSucceded()) { // download succeded

		LOG(DEBUG,
				"Scaricato le informazioni relative agli aggiornamenti disponibili");

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

			//			for (int i = 0; i < list.size(); ++i) {
			//				LOG(
			//						DEBUG,
			//						"In void singletonQtLogger::checkForUpdates() --> <br>hash[\"file\"] : "
			//								+ hash["file"] + ", <br>hash[\"version\"] : "
			//								+ hash["version"]
			//								+ ", <br>hash[\"description\"] : "
			//								+ hash["description"]
			//								+ ", <br>hash[\"status\"] : " + hash["status"]
			//								+ ", <br>hash[\"new\"] : " + hash["new"]);
			//			}

			n = n.nextSibling();
		}

		for (int i = 0; i < listOfResources.size(); ++i) {
			for (int j = 0; j < listOfResources.at(i).size(); ++j) {

				if (listOfResources.at(i).at(j)["status"] == "new") {
					LOG(UPDATE,
							"E' possibile scaricare la versione "
									+ listOfResources.at(i).at(j)["version"]
									+ " : "
									+ listOfResources.at(i).at(j)["file"] + " ("
									+ listOfResources.at(i).at(j)["description"]
									+ ")<br>changes : <br>"
									+ listOfResources.at(i).at(j)["new"]);
				}
			}
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
						std::vector<QUrl> * urls = new std::vector<QUrl>;

						QString url = THE_REPO->getFileFormazioniUrl();
						unsigned int pos = url.lastIndexOf("/");
						url = url.left(pos);
						pos = url.lastIndexOf("/");
						url = url.left(pos);
						pos = url.lastIndexOf("/");
						url = url.left(pos) + "/download/"
								+ listOfResources.at(i).at(j)["file"];

						urls->push_back(QUrl::fromLocalFile(url));

						LOG(DEBUG,
								"In void singletonQtLogger::checkForUpdates() --> url : "
										+ url);

						std::vector<QString> * savePaths = new std::vector<
								QString>;
						QString savePath = THE_REPO->getDownloadPath() + "/"
								+ listOfResources.at(i).at(j)["file"];
						savePaths->push_back(savePath);

						LOG(DEBUG,
								"In void singletonQtLogger::checkForUpdates() --> savePath : "
										+ savePath);

						Downloader updateDownloader(THE_LOGGER, urls, savePaths,
								true);

						if (updateDownloader.requestSucceded()) { // download succeded
							LOG(DEBUG,
									"In void singletonQtLogger::checkForUpdates() --> download of "
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
				"Non � stato possibile scaricare le informazioni relative agli aggiornamenti disponibili.");
		return false;
	}

	return true;
}
