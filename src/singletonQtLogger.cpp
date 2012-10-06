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
#include "FileFormazioniReader.h"
#include "FileFormazioniViewer.h"
#include "MatchChooserCamp.h"
#include "MatchChooserCoppa.h"
#include "UpdatesChooser.h"
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

	this->init();
	this->show();
}
void singletonQtLogger::init() {
	this->setFont(THE_REPO->fontVariableWidthSmall);
	this->ui.setupUi(this);
	//this->ui.titleLabel->setFont(THE_REPO->fontVariableWidthBig);
			this->ui.plainTextEdit->setFont(THE_REPO->fontFixedWidth);
			this->setWindowTitle("FantaCalcGui - Logger");
		}
singletonQtLogger::~singletonQtLogger() {
}
void singletonQtLogger::Logging(QString type, QString message) {

	if (type == "INFO") {
		this->ui.plainTextEdit->appendHtml(" " + message);
	} else if (type == "ERROR") {
		this->ui.plainTextEdit->appendHtml(
				"<span style='color:#FF0000;'> ERROR : " + message + "</span>");
	} else if (type == "DBG") {
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
	//this->ui.titleLabel->setText(_title);
}
void singletonQtLogger::setVersion(QString _version) {
	this->version = _version;
	this->ui.versionLabel->setText(
			"v" + _version + " rev. " + this->getRevision());
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
	fileContent.replace("<p>", "");
	fileContent.replace("</p>", "\n");
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
	THE_CONFIGURATOR->setUrl(THE_REPO->getUrl());
	THE_CONFIGURATOR->setDebugStatus(THE_REPO->getDebugStatus());
	THE_CONFIGURATOR->exec();
}
void singletonQtLogger::onlineClicked() {
	LOG(DBG, "<br> ========================");
	LOG(DBG, " === Modalita' online ===");
	LOG(DBG, " ========================<br>");

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
	LOG(DBG, "<br> =========================");
	LOG(DBG, " === Modalita' offline ===");
	LOG(DBG, " =========================<br>");

	NoNetFileDialog * noNetFileDialog = new NoNetFileDialog(THE_LOGGER);
	noNetFileDialog->exec();

	if (!noNetFileDialog->hasBeenAborted) {
		THE_REPO->fileFormazioni = noNetFileDialog->getFileNameSquadre();
		THE_REPO->fileGazzetta = noNetFileDialog->getFileNameGazzetta();

		LOG(DBG,
				QObject::tr("    File gazzetta   : %1").arg(THE_REPO->fileGazzetta));
		LOG(DBG,
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
			FileFormazioniReader * fileFormazioniReader = new FileFormazioniReader( \
				THE_REPO->fileFormazioni, THE_LOGGER);

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

			retVal = fileFormazioniReader->execute();

			//qDebug() << "In singletonQtLogger::goOn() --> fileFormazioniReader::execute() returned " \
										+ my::toQString<unsigned int>(retVal) + ".");

		} catch (QString& str) {

			qDebug() << "In singletonQtLogger::goOn() --> exception caught! retVal : " + my::toQString<unsigned int>(retVal) + ", " + str;

		}
	} while (retVal != FILEFORMREADER_OK);
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

		LOG(DBG, "<br/> =================");
		LOG(DBG,      " === Riepilogo ===");
		LOG(DBG,      " =================");

		FANTA->printTitolo(FANTA->getTeamName(0) + " - " + FANTA->getTeamName(1), INFO);

		FANTA->printRiepilogo();
		FANTA->printFormations();

		LOG(DBG, "<br/> ===========================");
		LOG(DBG,      " === Dettaglio giocatori ===");
		LOG(DBG,      " ===========================");

		FANTA->printPlayersInfo();

		this->ui.outputFileNameLineEdit->setEnabled(true);
		this->ui.outputFileNameLineEdit->setText(fileName);

		this->ui.uploadCampButton->setEnabled(true);
		this->ui.uploadCoppaButton->setEnabled(true);

	} catch (...) {
		LOG(ERROR, "Exception caught after FANTA->execute().");
		qDebug() << "In singletonQtLogger::goOn() --> exception caught after FANTA->execute().";
	}
}
void singletonQtLogger::setLogFileName(QString filename) {
	this->logFileName = filename;
}
bool singletonQtLogger::checkForUpdates() {

	LOG(DBG, "<br> =============================");
	LOG(DBG, " === Ricerca aggiornamenti ===");
	LOG(DBG, " =============================<br>");
	//	qDebug << "In void singletonQtLogger::checkForUpdates().";

#ifdef __MACH__
	QStringList current = this->getVersion().split(QRegExp("\\\\."));
#else
	QStringList current = this->getVersion().split(QRegExp("\\\."));
#endif

	int verCurrent = current.at(0).toInt();
	int majCurrent = current.at(1).toInt();
	int minCurrent = current.at(2).toInt();

	//qDebug() << verCurrent;
	//qDebug() << majCurrent;
	//qDebug() << minCurrent;

	std::vector<QUrl> * urls = new std::vector<QUrl>;
	QString url = THE_REPO->getFileFormazioniUrl();
	unsigned int pos = url.lastIndexOf("/");
	url = url.left(pos);
	pos = url.lastIndexOf("/");
	url = url.left(pos);
	pos = url.lastIndexOf("/");
	url = url.left(pos) + "/download/updates.xml";

	urls->push_back(QUrl::fromLocalFile(url));

	//qDebug() << "In void singletonQtLogger::checkForUpdates() --> url : " + url;

	std::vector<QString> *savePaths = new std::vector<QString>;
	QString savePath = THE_REPO->getDownloadPath() + "updates.xml";
	savePaths->push_back(savePath);

	//qDebug() << "In void singletonQtLogger::checkForUpdates() --> savePath : " + savePath;

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

		QList<QHash<QString, QString> > listOfResources;

		QDomNode n = docElem.firstChild();
		QHash<QString, QString> hash;

		while (!n.isNull()) {

			hash.clear();
			QHash<QString, QString> list;

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

							QStringList available = f.text().split(QRegExp("\\\."));
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
			}

			listOfResources.push_back(hash);
			n = n.nextSibling();
		}

		bool foundUpdates = false;

		for (int i = 0; i < listOfResources.size(); ++i) {
			if (listOfResources.at(i)["status"] == "new") {
				LOG(INFO, "");
				LOG(UPDATE,
				"    E' possibile scaricare la versione "
				+ listOfResources.at(i)["version"]
				+ " : "
				+ listOfResources.at(i)["file"] + " ("
				+ listOfResources.at(i)["description"]
				+ ")<br>changes : <br>"
				+ listOfResources.at(i)["new"]);

				foundUpdates = true;
			}
		}

		if (!foundUpdates) {
			LOG(UPDATE, "    La versione e' aggiornata");
			return true;
		}

		LOG(INFO, "");

		std::vector<QString> updates;

		UpdatesChooser *chooser = new UpdatesChooser(listOfResources, this);
		chooser->exec();

	} else { // download failed
		LOG(DBG,
		"Non e' stato possibile scaricare le informazioni relative agli aggiornamenti disponibili.");
		return false;
	}

	return true;
}
void singletonQtLogger::on_uploadCampButton_clicked() {
	//qDebug() << "In void singletonQtLogger::on_uploadCampButton_clicked()";

	LOG(DBG, "<br/> ==========================================");
	LOG(DBG, " === Pubblicazione risultati campionato ===");
	LOG(DBG, " ==========================================<br/><br/>");

	std::vector<QUrl> * urls = new std::vector<QUrl>;
	std::vector<QString> *savePaths = new std::vector<QString>;

	urls->push_back(
	QUrl::fromLocalFile(THE_REPO->getUrl() + "777/datiCampionato.txt"));
	savePaths->push_back(THE_REPO->getDownloadPath() + "datiCampionato.txt");
	urls->push_back(
	QUrl::fromLocalFile(THE_REPO->getUrl() + "calendario.inc"));
	savePaths->push_back(THE_REPO->getDownloadPath() + "calendario.inc");
	urls->push_back(
	QUrl::fromLocalFile(THE_REPO->getUrl() + "squadre.inc"));
	savePaths->push_back(THE_REPO->getDownloadPath() + "squadre.inc");

	Downloader datiCampDownloader(THE_LOGGER, urls, savePaths, TRUE);

	if (datiCampDownloader.requestSucceded()) { // download succeded
		// qDebug() << "In void singletonQtLogger::on_uploadCampButton_clicked(). Download of files succeded.";
	} else { // download failed
		LOG(WARN, "Non e' stato possibile scaricare i file necessari.");
		qDebug() << "In void singletonQtLogger::on_uploadCampButton_clicked(). Download of files failed.";
	}

	MatchChooserCamp *matchChooserCamp = new MatchChooserCamp();
	matchChooserCamp->setData();
	matchChooserCamp->exec();

}
void singletonQtLogger::on_uploadCoppaButton_clicked() {
	//qDebug() << "In void singletonQtLogger::on_uploadCoppaButton_clicked()";

	LOG(DBG, "<br/> =====================================");
	LOG(DBG, " === Pubblicazione risultati coppa ===");
	LOG(DBG, " =====================================<br/><br/>");

	std::vector<QUrl> * urls = new std::vector<QUrl>;
	std::vector<QString> *savePaths = new std::vector<QString>;

	urls->push_back(
	QUrl::fromLocalFile(THE_REPO->getUrl() + "777/datiCoppa.txt"));
	savePaths->push_back(THE_REPO->getDownloadPath() + "datiCoppa.txt");
	urls->push_back(
	QUrl::fromLocalFile(THE_REPO->getUrl() + "squadre.inc"));
	savePaths->push_back(THE_REPO->getDownloadPath() + "squadre.inc");
	urls->push_back(
	QUrl::fromLocalFile(THE_REPO->getUrl() + "calendarioCoppa.inc"));
	savePaths->push_back(THE_REPO->getDownloadPath() + "calendarioCoppa.inc");

	Downloader datiCoppaDownloader(THE_LOGGER, urls, savePaths, TRUE);

	if (datiCoppaDownloader.requestSucceded()) { // download succeded
		qDebug()
		<< "In void singletonQtLogger::on_uploadCoppaButton_clicked(). Download of files succeded.";
	} else { // download failed
		LOG(WARN, "Non e' stato possibile scaricare i file necessari.");
		qDebug() << "In void singletonQtLogger::on_uploadCoppaButton_clicked(). Download of files failed.";
	}

	MatchChooserCoppa *matchChooserCoppa = new MatchChooserCoppa();
	matchChooserCoppa->setData();
	matchChooserCoppa->exec();

}
