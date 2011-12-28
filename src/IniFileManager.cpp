/*
 * IniFileManager.cpp
 *
 *  Created on: 13/lug/2011
 *      Author: WAleViolaeIvan
 */

#include "IniFileManager.h"
#include "Repository.h"

#include <QtCore/QDir>
#include <QtCore/QTextStream>

IniFileManager* IniFileManager::Inst() {
	if (pInstance == NULL) {
		pInstance = new IniFileManager();
	}
	return pInstance;
}

IniFileManager* IniFileManager::pInstance = NULL;

IniFileManager::IniFileManager() {
	LOG(DEBUG, "In IniFileManager() constructor.");
	char * UserProfile = getenv("USERPROFILE");
	QDir dir(UserProfile);
	dir.mkdir("FantaCalcGui");
	this->workDir = QString::fromAscii(UserProfile) + "\\FantaCalcGui\\";
	this->iniFileName = workDir + "FantaCalcGui.ini";
	this->readIniFile();
}
IniFileManager::~IniFileManager() {
}
QString IniFileManager::getWorkDir() {
	return this->workDir;
}
void IniFileManager::writeIniFile() {
	QFile * iniFile = new QFile(this->iniFileName);
	if (iniFile->exists()) {
		LOG(
				DEBUG,
				"In IniFileManager::writeIniFile() --> " + this->iniFileName
						+ " exists.");
		iniFile->open(QIODevice::WriteOnly);

		iniFile->write("[File Formazioni Path]\n");
		iniFile->write(THE_REPO->formazioniPath.toAscii().trimmed());

		iniFile->write("\n[File Gazzetta Path]\n");
		iniFile->write(THE_REPO->gazzettaPath.toAscii().trimmed());

		iniFile->write("\n[File Output Path]\n");
		iniFile->write(THE_REPO->risultatiPath.toAscii().trimmed());

		iniFile->write("\n[Download Path]\n");
		iniFile->write(THE_REPO->downloadPath.toAscii().trimmed());

		iniFile->write("\n[Liste Path]\n");
		iniFile->write(THE_REPO->listePath.toAscii().trimmed());

		iniFile->write("\n[File Formazioni Url]\n");
		iniFile->write(THE_REPO->formazioniUrl.toAscii().trimmed());

		iniFile->write("\n[File Gazzetta Url]\n");
		iniFile->write(THE_REPO->gazzettaUrl.toAscii().trimmed());

		iniFile->write("\n[Debug]\n");
		if (THE_REPO->debugStatus)
			iniFile->write("TRUE");
		else
			iniFile->write("FALSE");

		iniFile->close();
	} else {
		LOG(
				DEBUG,
				"In IniFileManager::writeIniFile() --> " + this->iniFileName
						+ " does not exists.");
		QString path = this->workDir;

		path.replace("/", "\\");

		iniFile->open(QIODevice::WriteOnly);
		if (iniFile->isOpen()) {
			iniFile->write("[File Formazioni Path]\n");
			iniFile->write(THE_REPO->formazioniPath.toAscii().trimmed());

			iniFile->write("\n[File Gazzetta Path]\n");
			iniFile->write(THE_REPO->gazzettaPath.toAscii().trimmed());

			iniFile->write("\n[File Output Path]\n");
			iniFile->write(THE_REPO->risultatiPath.toAscii().trimmed());

			iniFile->write("\n[Download Path]\n");
			iniFile->write(THE_REPO->downloadPath.toAscii().trimmed());

			iniFile->write("\n[Liste Path]\n");
			iniFile->write(THE_REPO->listePath.toAscii().trimmed());

			iniFile->write("\n[File Formazioni Url]\n");
			iniFile->write(THE_REPO->formazioniUrl.toAscii().trimmed());

			iniFile->write("\n[File Gazzetta Url]\n");
			iniFile->write(THE_REPO->gazzettaUrl.toAscii().trimmed());

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
		LOG(
				DEBUG,
				"In IniFileManager::readIniFile() --> " + this->iniFileName
						+ " exists.");
		iniFile->open(QIODevice::ReadOnly);
		char buf[1024];

		iniFile->readLine(buf, sizeof(buf)); // [File Formazioni Path]
		iniFile->readLine(buf, sizeof(buf));
		THE_REPO->formazioniPath = QString::fromAscii(buf).trimmed();

		iniFile->readLine(buf, sizeof(buf)); // [File Gazzetta Path]
		iniFile->readLine(buf, sizeof(buf));
		THE_REPO->gazzettaPath = QString::fromAscii(buf).trimmed();

		iniFile->readLine(buf, sizeof(buf)); // [File Output Path]
		iniFile->readLine(buf, sizeof(buf));
		THE_REPO->risultatiPath = QString::fromAscii(buf).trimmed();

		iniFile->readLine(buf, sizeof(buf)); // [Download Path]
		iniFile->readLine(buf, sizeof(buf));
		THE_REPO->downloadPath = QString::fromAscii(buf).trimmed();

		iniFile->readLine(buf, sizeof(buf)); // [Liste Path]
		iniFile->readLine(buf, sizeof(buf));
		THE_REPO->listePath = QString::fromAscii(buf).trimmed();

		iniFile->readLine(buf, sizeof(buf)); // [File Formazioni Url]
		iniFile->readLine(buf, sizeof(buf));
		/*
		 *  se buf è vuoto lascia il valore di default
		 *  impostato nel costruttore di THE_REPO
		 */
		if (!QString::fromAscii(buf).trimmed().isEmpty()) {
			THE_REPO->formazioniUrl = QString::fromAscii(buf).trimmed();
		}

		iniFile->readLine(buf, sizeof(buf)); // [File Gazzetta Url]
		iniFile->readLine(buf, sizeof(buf));
		/*
		 *  se buf è vuoto lascia il valore di default
		 *  impostato nel costruttore di THE_REPO
		 */
		if (!QString::fromAscii(buf).trimmed().isEmpty()) {
			THE_REPO->gazzettaUrl = QString::fromAscii(buf).trimmed();
		}

		iniFile->readLine(buf, sizeof(buf)); // [Debug]
		iniFile->readLine(buf, sizeof(buf));
		if (QString::fromAscii(buf).trimmed() == "TRUE")
			THE_REPO->debugStatus = TRUE;
		else
			THE_REPO->debugStatus = FALSE;

		iniFile->close();
	} else {
		LOG(
				ERROR,
				this->iniFileName
						+ " non esiste. Inserire le informazioni richieste.");

		LOG(
				DEBUG,
				"In IniFileManager::readIniFile() --> " + this->iniFileName
						+ " does not exists.");

		LOG(DEBUG, "In IniFileManager::readIniFile() --> " + this->workDir);

		THE_CONFIGURATOR->setStartDir(this->workDir);

		/*
		 * utilizza i valori comunque presenti in Repository::Repository()
		 */
		THE_CONFIGURATOR->setFormazioniUrl(THE_REPO->formazioniUrl);
		THE_CONFIGURATOR->setGazzettaUrl(THE_REPO->gazzettaUrl);
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
			content += in.readLine(0) + "<br />";//reads a line of text file
		}
		iniFile->close();
	}
	return content;
}
/*
 QString Repository::getIniFilePath() {
 return this->iniFileName;
 }
 QString Repository::getWorkDir() {
 return this->workDir;
 }
 */
