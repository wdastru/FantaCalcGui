/*
 * IniFileManager.cpp
 *
 *  Created on: 13/lug/2011
 *      Author: WAleViolaeIvan
 */

#include "IniFileManager.h"

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

	this->formazioniPath = IniFilePopulator::Inst()->getFormazioniPath();
	this->gazzettaPath = IniFilePopulator::Inst()->getGazzettaPath();
	this->risultatiPath = IniFilePopulator::Inst()->getRisultatiPath();
	this->downloadPath = IniFilePopulator::Inst()->getDownloadPath();
	this->listePath = IniFilePopulator::Inst()->getListePath();
	this->formazioniUrl = IniFilePopulator::Inst()->getFormazioniUrl();
	this->gazzettaUrl = IniFilePopulator::Inst()->getGazzettaUrl();
	this->debugStatus = IniFilePopulator::Inst()->getDebugStatus();

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
		iniFile->write(this->formazioniPath.toAscii().trimmed());

		iniFile->write("\n[File Gazzetta Path]\n");
		iniFile->write(this->gazzettaPath.toAscii().trimmed());

		iniFile->write("\n[File Output Path]\n");
		iniFile->write(this->risultatiPath.toAscii().trimmed());

		iniFile->write("\n[Download Path]\n");
		iniFile->write(this->downloadPath.toAscii().trimmed());

		iniFile->write("\n[Liste Path]\n");
		iniFile->write(this->listePath.toAscii().trimmed());

		iniFile->write("\n[File Formazioni Url]\n");
		iniFile->write(this->formazioniUrl.toAscii().trimmed());

		iniFile->write("\n[File Gazzetta Url]\n");
		iniFile->write(this->gazzettaUrl.toAscii().trimmed());

		iniFile->write("\n[Debug]\n");
		if (this->debugStatus)
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
			iniFile->write(this->formazioniPath.toAscii().trimmed());

			iniFile->write("\n[File Gazzetta Path]\n");
			iniFile->write(this->gazzettaPath.toAscii().trimmed());

			iniFile->write("\n[File Output Path]\n");
			iniFile->write(this->risultatiPath.toAscii().trimmed());

			iniFile->write("\n[Download Path]\n");
			iniFile->write(this->downloadPath.toAscii().trimmed());

			iniFile->write("\n[Liste Path]\n");
			iniFile->write(this->listePath.toAscii().trimmed());

			iniFile->write("\n[File Formazioni Url]\n");
			iniFile->write(this->formazioniUrl.toAscii().trimmed());

			iniFile->write("\n[File Gazzetta Url]\n");
			iniFile->write(this->gazzettaUrl.toAscii().trimmed());

			iniFile->write("\n[Debug]\n");
			if (this->debugStatus)
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
		this->formazioniPath = QString::fromAscii(buf).trimmed();

		iniFile->readLine(buf, sizeof(buf)); // [File Gazzetta Path]
		iniFile->readLine(buf, sizeof(buf));
		this->gazzettaPath = QString::fromAscii(buf).trimmed();

		iniFile->readLine(buf, sizeof(buf)); // [File Output Path]
		iniFile->readLine(buf, sizeof(buf));
		this->risultatiPath = QString::fromAscii(buf).trimmed();

		iniFile->readLine(buf, sizeof(buf)); // [Download Path]
		iniFile->readLine(buf, sizeof(buf));
		this->downloadPath = QString::fromAscii(buf).trimmed();

		iniFile->readLine(buf, sizeof(buf)); // [Liste Path]
		iniFile->readLine(buf, sizeof(buf));
		this->listePath = QString::fromAscii(buf).trimmed();

		iniFile->readLine(buf, sizeof(buf)); // [File Formazioni Url]
		iniFile->readLine(buf, sizeof(buf));
		this->formazioniUrl = QString::fromAscii(buf).trimmed();

		iniFile->readLine(buf, sizeof(buf)); // [File Gazzetta Url]
		iniFile->readLine(buf, sizeof(buf));
		this->gazzettaUrl = QString::fromAscii(buf).trimmed();

		iniFile->readLine(buf, sizeof(buf)); // [Debug]
		iniFile->readLine(buf, sizeof(buf));
		if (QString::fromAscii(buf).trimmed() == "TRUE")
			this->debugStatus = TRUE;
		else
			this->debugStatus = FALSE;

		iniFile->close();
	} else {
		LOG(
				DEBUG,
				"In IniFileManager::readIniFile() --> " + this->iniFileName
						+ " does not exists.");

		LOG(DEBUG, "In IniFileManager::readIniFile() --> " + this->workDir);

		IniFilePopulator::Inst()->setStartDir(this->workDir);
		IniFilePopulator::Inst()->exec();

		this->formazioniPath = IniFilePopulator::Inst()->getFormazioniPath();
		this->gazzettaPath = IniFilePopulator::Inst()->getGazzettaPath();
		this->risultatiPath = IniFilePopulator::Inst()->getRisultatiPath();
		this->downloadPath = IniFilePopulator::Inst()->getDownloadPath();
		this->listePath = IniFilePopulator::Inst()->getListePath();
		this->formazioniUrl = IniFilePopulator::Inst()->getFormazioniUrl();
		this->gazzettaUrl = IniFilePopulator::Inst()->getGazzettaUrl();
		if (IniFilePopulator::Inst()->getDebugStatus())
			this->debugStatus = TRUE;
		else
			this->debugStatus = FALSE;

		this->writeIniFile();
	}
}
QString IniFileManager::getFormazioniPath() {
	return this->formazioniPath;
}
QString IniFileManager::getGazzettaPath() {
	return this->gazzettaPath;
}
QString IniFileManager::getRisultatiPath() {
	return this->risultatiPath;
}
QString IniFileManager::getDownloadPath() {
	return this->downloadPath;
}
QString IniFileManager::getIniFilePath() {
	return this->iniFileName;
}
QString IniFileManager::getWorkDir() {
	return this->workDir;
}
QString IniFileManager::getListePath() {
	return this->listePath;
}
QString IniFileManager::getListaFormazioni() {
	return this->listePath + "listaFormazioni.txt";
}
QString IniFileManager::getListaGazFiles() {
	return this->listePath + "listaGazFiles.txt";
}
QString IniFileManager::getFileFormazioniUrl() {
	return this->getFormazioniUrl() + "listaFormazioni.txt";
}
QString IniFileManager::getFileGazzettaUrl() {
	return this->getGazzettaUrl() + "listaGazFiles.txt";
}
QString IniFileManager::getFormazioniUrl() {
	return this->formazioniUrl;
}
QString IniFileManager::getGazzettaUrl() {
	return this->gazzettaUrl;
}
bool IniFileManager::getDebugStatus() {
	return this->debugStatus;
}
void IniFileManager::setFormazioniPath(QString dir) {
	this->formazioniPath = dir;
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
