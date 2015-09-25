/*
 * IniFileManager.cpp
 *
 *  Created on: 13/lug/2011
 *      Author: WAleViolaeIvan
 */

#define READ_NOT_EMPTY_LINE \
	do { \
		iniFile->readLine(buf, sizeof(buf)); \
	} while (QString::fromLatin1(buf).trimmed() == "");

#include "IniFileManager.h"
#include "IniFilePopulator.h"
#include "Repository.h"
#include "StringModifier.h"

#include <QtCore/QDir>
#include <QtCore/QTextStream>
#include <QtCore/QObject>
#include <QtCore/QDebug>

IniFileManager* IniFileManager::Inst() {
	if (pInstance == NULL) {
		pInstance = new IniFileManager();
	}
	return pInstance;
}

IniFileManager* IniFileManager::pInstance = NULL;

IniFileManager::IniFileManager() {

	DEBUG("In IniFileManager::IniFileManager()");

	QDir dir(THE_REPO->UserProfile);

	if (!dir.cd("FantaCalcGui")) {
		dir.mkdir("FantaCalcGui");
		dir.cd("FantaCalcGui");
	}

	this->workDir = dir.path();
	this->iniFileName = dir.absoluteFilePath("FantaCalcGui.ini");

	STR_MOD->fixSlashes(this->workDir);
	STR_MOD->fixSlashes(this->iniFileName);

	this->readIniFile();
}
IniFileManager::~IniFileManager() {
}
void IniFileManager::setWorkDir(QString dir) {
	this->workDir = dir;
	LOG(DBG,
	"In IniFileManager::setWorkDir(QString dir) --> workDir set to "
	+ this->workDir);
}
QString IniFileManager::getWorkDir() {
	return this->workDir;
}
void IniFileManager::writeIniFile() {
	QFile * iniFile = new QFile(this->iniFileName);
	if (iniFile->exists()) {
		DEBUG("In IniFileManager::writeIniFile() --> " << this->iniFileName.toStdString().c_str() << " exists.");

		iniFile->open(QIODevice::WriteOnly);

		iniFile->write("[File Formazioni Path]\n");
		iniFile->write(THE_REPO->formazioniPath.toLatin1().trimmed());

		iniFile->write("\n[File Gazzetta Path]\n");
		iniFile->write(THE_REPO->gazzettaPath.toLatin1().trimmed());

		iniFile->write("\n[File Output Path]\n");
		iniFile->write(THE_REPO->risultatiPath.toLatin1().trimmed());

		iniFile->write("\n[Download Path]\n");
		iniFile->write(THE_REPO->downloadPath.toLatin1().trimmed());

		iniFile->write("\n[Liste Path]\n");
		iniFile->write(THE_REPO->listePath.toLatin1().trimmed());

		iniFile->write("\n[Url]\n");
		iniFile->write(THE_REPO->url.toLatin1().trimmed());

		iniFile->write("\n[Debug]\n");
		if (THE_REPO->debugStatus)
		iniFile->write("TRUE");
		else
		iniFile->write("FALSE");

		iniFile->close();
	} else {
		DEBUG("In IniFileManager::writeIniFile() --> " << this->iniFileName.toStdString().c_str() << " does not exists.");
		LOG(DBG,
		"In IniFileManager::writeIniFile() --> " + this->iniFileName
		+ " does not exists.");
		QString path = this->workDir;

		path.replace("/", "\\");

		iniFile->open(QIODevice::WriteOnly);
		if (iniFile->isOpen()) {
			iniFile->write("[File Formazioni Path]\n");
			iniFile->write(THE_REPO->formazioniPath.toLatin1().trimmed());

			iniFile->write("\n[File Gazzetta Path]\n");
			iniFile->write(THE_REPO->gazzettaPath.toLatin1().trimmed());

			iniFile->write("\n[File Output Path]\n");
			iniFile->write(THE_REPO->risultatiPath.toLatin1().trimmed());

			iniFile->write("\n[Download Path]\n");
			iniFile->write(THE_REPO->downloadPath.toLatin1().trimmed());

			iniFile->write("\n[Liste Path]\n");
			iniFile->write(THE_REPO->listePath.toLatin1().trimmed());

			iniFile->write("\n[Url]\n");
			iniFile->write(THE_REPO->url.toLatin1().trimmed());

			iniFile->write("\n[Debug]\n");
			if (THE_REPO->debugStatus)
			iniFile->write("TRUE");
			else
			iniFile->write("FALSE");

		} else {
			;
		}
		iniFile->close();

		this->readIniFile();
	}
}
void IniFileManager::readIniFile() {

	QFile *iniFile = new QFile(this->iniFileName);
	if (iniFile->exists()) {
		iniFile->open(QIODevice::ReadOnly);
		char buf[1024];

		std::map<QString, int> map;
		map["[File Formazioni Path]"] = 1;
		map["[File Gazzetta Path]"] = 2;
		map["[File Output Path]"] = 3;
		map["[Download Path]"] = 4;
		map["[Liste Path]"] = 5;
		map["[Url]"] = 6;
		map["[Debug]"] = 7;

		while (!iniFile->atEnd()) {

			READ_NOT_EMPTY_LINE

			DEBUG(QString::fromLatin1(buf).trimmed().toStdString().c_str());

			switch (map[QString::fromLatin1(buf).trimmed()]) {
				case 1: { // [File Formazioni Path]
					READ_NOT_EMPTY_LINE
					DEBUG("1 : " << QString::fromLatin1(buf).trimmed().toStdString().c_str());
					THE_REPO->formazioniPath = QString::fromLatin1(buf).trimmed();
				}
				break;
				case 2: { // "[File Gazzetta Path]"
					READ_NOT_EMPTY_LINE
					DEBUG("2 : " << QString::fromLatin1(buf).trimmed().toStdString().c_str());
					THE_REPO->gazzettaPath = QString::fromLatin1(buf).trimmed();
				}
				break;
				case 3: { // "[File Output Path]"
					READ_NOT_EMPTY_LINE
					DEBUG("3 : " << QString::fromLatin1(buf).trimmed().toStdString().c_str());
					THE_REPO->risultatiPath = QString::fromLatin1(buf).trimmed();
				}
				break;
				case 4: { // "[Download Path]"
					READ_NOT_EMPTY_LINE
					DEBUG("4 : " << QString::fromLatin1(buf).trimmed().toStdString().c_str());
					THE_REPO->downloadPath = QString::fromLatin1(buf).trimmed();
				}
				break;
				case 5: { // "[Liste Path]"
					READ_NOT_EMPTY_LINE
					DEBUG("5 : " << QString::fromLatin1(buf).trimmed().toStdString().c_str());
					THE_REPO->listePath = QString::fromLatin1(buf).trimmed();
				}
				break;
				case 6: { // "[Url]"
					READ_NOT_EMPTY_LINE
					DEBUG("6 : " << QString::fromLatin1(buf).trimmed().toStdString().c_str());
					if (!QString::fromLatin1(buf).trimmed().isEmpty()) {
						THE_REPO->url = QString::fromLatin1(buf).trimmed();
						THE_REPO->formazioniUrl = THE_REPO->getUrl() + "777/formazioni/";
						THE_REPO->gazzettaUrl = THE_REPO->getUrl() + "777/filesGazzetta/";
					}
				}
				break;
				case 7: { // "[Debug]"
					READ_NOT_EMPTY_LINE
					DEBUG("7 : " << QString::fromLatin1(buf).trimmed().toStdString().c_str());
					if (QString::fromLatin1(buf).trimmed() == "TRUE") {
						THE_REPO->debugStatus = TRUE;
					} else {
						THE_REPO->debugStatus = FALSE;
					}
				}
				break;

				default:
					/* no more valid entries are ignored
					 * a line has to be read (the value)
					 * * * * * * * * * * * * * * * * * * */
					READ_NOT_EMPTY_LINE
				break;
			}
		}
		iniFile->close();
	} else {
		LOG(INFO,
		QObject::tr(
				"%1 non esiste<br>Inserire le informazioni di configurazione").arg(
				this->iniFileName));

		THE_CONFIGURATOR->setStartDir(this->workDir);

		/*
		 * utilizza i valori comunque presenti in Repository::Repository()
		 */

		THE_CONFIGURATOR->setUrl(THE_REPO->url);
		THE_CONFIGURATOR->setFormazioniPath(THE_REPO->formazioniPath);
		THE_CONFIGURATOR->setGazzettaPath(THE_REPO->gazzettaPath);
		THE_CONFIGURATOR->setRisultatiPath(THE_REPO->risultatiPath);
		THE_CONFIGURATOR->setDownloadPath(THE_REPO->downloadPath);
		THE_CONFIGURATOR->setListePath(THE_REPO->listePath);
		if (THE_REPO->debugStatus == TRUE) {
			THE_CONFIGURATOR->setDebugStatus(TRUE);
		} else {
			THE_CONFIGURATOR->setDebugStatus(FALSE);
		}
		THE_CONFIGURATOR->exec();

		this->writeIniFile();
	}
}
QString IniFileManager::showIniFile() {
	QFile *iniFile = new QFile(this->iniFileName);
	QString content = "\n";

	if (iniFile->exists()) {
		iniFile->open(QIODevice::ReadOnly);
		QTextStream in(iniFile);
		while (!in.atEnd()) {
			content += in.readLine(0) + "<br />"; //reads a line of text file
		}
		iniFile->close();
	}
	return content;
}
