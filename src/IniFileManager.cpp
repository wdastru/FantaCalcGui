/*
 * IniFileManager.cpp
 *
 *  Created on: 13/lug/2011
 *      Author: WAleViolaeIvan
 */

#include "IniFileManager.h"
#include "IniFilePopulator.h"
#include "Repository.h"
#include "StringModifier.h"

#include <QtCore/QDir>
#include <QtCore/QTextStream>
#include <QObject>
#include <QtCore/QDebug>

IniFileManager* IniFileManager::Inst() {
	if (pInstance == NULL) {
		pInstance = new IniFileManager();
	}
	return pInstance;
}

IniFileManager* IniFileManager::pInstance = NULL;

IniFileManager::IniFileManager() {

	//qDebug() << "In IniFileManager::IniFileManager()";

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
		//qDebug() << "In IniFileManager::writeIniFile() --> " + this->iniFileName + " exists.";

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

		iniFile->write("\n[Url]\n");
		iniFile->write(THE_REPO->url.toAscii().trimmed());

		iniFile->write("\n[Debug]\n");
		if (THE_REPO->debugStatus)
			iniFile->write("TRUE");
		else
			iniFile->write("FALSE");

		iniFile->close();
	} else {
		qDebug() << "In IniFileManager::writeIniFile() --> " + this->iniFileName + " does not exists.";
		LOG(DBG,
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

			iniFile->write("\n[Url]\n");
			iniFile->write(THE_REPO->url.toAscii().trimmed());

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
		//qDebug() << QObject::tr("Reading %1").arg(this->iniFileName);
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

		iniFile->readLine(buf, sizeof(buf)); // [Url]
		iniFile->readLine(buf, sizeof(buf));
		/*
		 *  se buf è vuoto lascia il valore di default
		 *  impostato nel costruttore di THE_REPO
		 */
		if (!QString::fromAscii(buf).trimmed().isEmpty()) {
			THE_REPO->url = QString::fromAscii(buf).trimmed();
			THE_REPO->formazioniUrl = THE_REPO->getUrl() + "777/formazioni/";
			THE_REPO->gazzettaUrl = THE_REPO->getUrl() + "777/filesGazzetta/";
			// qDebug() << "In IniFileManager::readIniFile(). QString::fromAscii(buf).trimmed() is not empty";
		}

		iniFile->readLine(buf, sizeof(buf)); // [Debug]
		iniFile->readLine(buf, sizeof(buf));
		if (QString::fromAscii(buf).trimmed() == "TRUE")
			THE_REPO->debugStatus = TRUE;
		else
			THE_REPO->debugStatus = FALSE;

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
