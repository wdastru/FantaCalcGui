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
	char *UserProfile = getenv("USERPROFILE");
	QDir dir(UserProfile);
	dir.mkdir("FantaCalcGui");
	workDir = QString::fromAscii(UserProfile) + "\\FantaCalcGui\\";
	iniFileName = workDir + "FantaCalcGui.ini";
	readIniFile();
}
IniFileManager::~IniFileManager() {
}
void IniFileManager::updateAndWriteIniFile() {

	THE_MANAGER->formazioniPath = THE_REPO->getFormazioniPath();
	THE_MANAGER->gazzettaPath = THE_REPO->getGazzettaPath();
	THE_MANAGER->risultatiPath = THE_REPO->getRisultatiPath();
	THE_MANAGER->downloadPath = THE_REPO->getDownloadPath();
	THE_MANAGER->listePath = THE_REPO->getListePath();
	THE_MANAGER->formazioniUrl = THE_REPO->getFormazioniUrl();
	THE_MANAGER->gazzettaUrl = THE_REPO->getGazzettaUrl();
	THE_MANAGER->debugStatus = THE_REPO->getDebugStatus();

	this->writeIniFile();
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
		THE_REPO->formazioniUrl = QString::fromAscii(buf).trimmed();

		iniFile->readLine(buf, sizeof(buf)); // [File Gazzetta Url]
		iniFile->readLine(buf, sizeof(buf));
		THE_REPO->gazzettaUrl = QString::fromAscii(buf).trimmed();

		iniFile->readLine(buf, sizeof(buf)); // [Debug]
		iniFile->readLine(buf, sizeof(buf));
		if (QString::fromAscii(buf).trimmed() == "TRUE")
			THE_REPO->debugStatus = TRUE;
		else
			THE_REPO->debugStatus = FALSE;

		iniFile->close();
	} else {
		LOG(
				DEBUG,
				"In IniFileManager::readIniFile() --> " + this->iniFileName
						+ " does not exists.");

		LOG(DEBUG, "In IniFileManager::readIniFile() --> " + this->workDir);

		IniFilePopulator::Inst()->setStartDir(this->workDir);
		IniFilePopulator::Inst()->exec();

		THE_REPO->formazioniPath = IniFilePopulator::Inst()->getFormazioniPath();
		THE_REPO->gazzettaPath = IniFilePopulator::Inst()->getGazzettaPath();
		THE_REPO->risultatiPath = IniFilePopulator::Inst()->getRisultatiPath();
		THE_REPO->downloadPath = IniFilePopulator::Inst()->getDownloadPath();
		THE_REPO->listePath = IniFilePopulator::Inst()->getListePath();
		THE_REPO->formazioniUrl = IniFilePopulator::Inst()->getFormazioniUrl();
		THE_REPO->gazzettaUrl = IniFilePopulator::Inst()->getGazzettaUrl();
		if (IniFilePopulator::Inst()->getDebugStatus())
			THE_REPO->debugStatus = TRUE;
		else
			THE_REPO->debugStatus = FALSE;

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
