/*
 * Repository.cpp
 *
 *  Created on: 22/nov/2011
 *      Author: WAleViolaeIvan
 */

#include "Repository.h"
#include "singletonQtLogger.h"
#include "defines.h"

#include <stdlib.h>
#include <QFile>

Repository::Repository() {
//	LOG(DEBUG, "In Repository::Repository().");
	/*
	 * DEFAULTS
	 */
	this->formazioniUrl
			= "http://www.cim.unito.it/private/fantacalcio/777/formazioni/";
	this->gazzettaUrl
			= "http://www.cim.unito.it/private/fantacalcio/777/filesGazzetta/";
	this->debugStatus = FALSE; // temporaneo prima che venga letto l'ini file.

	char * UserProfile = getenv("USERPROFILE");

	this->formazioniPath = QString::fromLocal8Bit(UserProfile)
			+ "\\FantaCalcGui\\formazioni";
	this->gazzettaPath = QString::fromLocal8Bit(UserProfile)
			+ "\\FantaCalcGui\\gazzetta";
	this->risultatiPath = QString::fromLocal8Bit(UserProfile)
			+ "\\FantaCalcGui\\risultati";
	this->downloadPath = QString::fromLocal8Bit(UserProfile)
			+ "\\FantaCalcGui\\download";
	this->listePath = QString::fromLocal8Bit(UserProfile)
			+ "\\FantaCalcGui\\liste";

	this->fontVariableWidthSmall.setFamily(QString::fromUtf8("Candara"));
	this->fontVariableWidthSmall.setPointSize(10);

	this->fontVariableWidthBig.setFamily(QString::fromUtf8("Candara"));
	this->fontVariableWidthBig.setPointSize(16);

	this->fontFixedWidth.setFamily(QString::fromUtf8("Lucida Console"));
	this->fontFixedWidth.setPointSize(9);
}

Repository::~Repository() {
}

Repository* Repository::pInstance = NULL;

Repository* Repository::Inst() {
	if (pInstance == NULL) {
		pInstance = new Repository();
	}
	return pInstance;
}
QString Repository::getFormazioniPath() {
	return this->formazioniPath;
}
QString Repository::getGazzettaPath() {
	return this->gazzettaPath;
}
QString Repository::getRisultatiPath() {
	return this->risultatiPath;
}
QString Repository::getDownloadPath() {
	return this->downloadPath;
}
QString Repository::getListePath() {
	return this->listePath;
}
QString Repository::getListaFormazioni() {
	return this->listePath + "/listaFormazioni.txt";
}
QString Repository::getListaGazFiles() {
	return this->listePath + "/listaGazFiles.txt";
}
QString Repository::getFileFormazioniUrl() {
	return this->getFormazioniUrl() + "listaFormazioni.txt";
}
QString Repository::getFileGazzettaUrl() {
	return this->getGazzettaUrl() + "listaGazFiles.txt";
}
QString Repository::getFormazioniUrl() {
	return this->formazioniUrl;
}
QString Repository::getGazzettaUrl() {
	return this->gazzettaUrl;
}
bool Repository::getDebugStatus() {
	return this->debugStatus;
}
//void Repository::setFormazioniPath(QString dir) {
//	this->formazioniPath = dir;
//}
