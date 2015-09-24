/*
 * Repository.cpp
 *
 *  Created on: 22/nov/2011
 *      Author: WAleViolaeIvan
 */

#include <QtCore/QFile>
#include <QtCore/QDebug>

#include <stdlib.h>

#include "Repository.h"
#include "defines.h"
#include "singletonQtLogger.h"
#include "StringModifier.h"

Repository::Repository() {
	/*
	 * DEFAULTS
	 * temporanei prima che
	 * venga letto l'ini file
	 * * * * * * * * * * * * */
	this->url ="http://www.cim.unito.it/website/private/fantacalcio/";
	this->formazioniUrl = this->url + "777/formazioni/";
	this->gazzettaUrl = this->url + "777/filesGazzetta/";
	this->debugStatus = FALSE;

#ifdef WIN32

	LOG(CMDLINE, "Platform WIN32");

	this->UserProfile = QString::fromLatin1(getenv("USERPROFILE"));

	this->fontVariableWidthSmall.setFamily(QString::fromUtf8("Segoe UI"));
	this->fontVariableWidthSmall.setPointSize(10);

	this->fontVariableWidthBig.setFamily(QString::fromUtf8("Segoe UI"));
	this->fontVariableWidthBig.setBold(true);
	this->fontVariableWidthBig.setPointSize(16);

	this->fontFixedWidth.setFamily(QString::fromUtf8("Lucida Console"));
	this->fontFixedWidth.setPointSize(8);
#else // ! def WIN32
#ifdef __MACH__
	LOG(CMDLINE, "Platform __MACH__");

	this->UserProfile = "/Users/" + QString::fromLatin1(getenv("USER"));

	this->fontVariableWidthSmall.setFamily(QString::fromUtf8("Segoe UI"));
	this->fontVariableWidthSmall.setPointSize(10);

	this->fontVariableWidthBig.setFamily(QString::fromUtf8("Segoe UI"));
	this->fontVariableWidthBig.setBold(true);
	this->fontVariableWidthBig.setPointSize(16);

	this->fontFixedWidth.setFamily(QString::fromUtf8("Lucida Console"));
	this->fontFixedWidth.setPointSize(8);
#else // ! def __MACH__ ! def WIN32 -->  LINUX?
	LOG(CMDLINE, "Platform LINUX (?)");

	this->UserProfile = "/home/" + QString::fromLatin1(getenv("USER"));

	this->fontVariableWidthSmall.setFamily(QString::fromUtf8("Ubuntu"));
	this->fontVariableWidthSmall.setPointSize(10);

	this->fontVariableWidthBig.setFamily(QString::fromUtf8("Ubuntu"));
	this->fontVariableWidthBig.setBold(true);
	this->fontVariableWidthBig.setPointSize(16);

	this->fontFixedWidth.setFamily(QString::fromUtf8("Ubuntu Mono"));
	this->fontFixedWidth.setPointSize(10);
#endif
#endif

	this->formazioniPath = this->UserProfile + "/FantaCalcGui/formazioni/";
	this->gazzettaPath = this->UserProfile + "/FantaCalcGui/gazzetta/";
	this->risultatiPath = this->UserProfile + "/FantaCalcGui/risultati/";
	this->downloadPath = this->UserProfile + "/FantaCalcGui/download/";
	this->listePath = this->UserProfile + "/FantaCalcGui/liste/";

	STR_MOD->fixSlashes(this->formazioniPath);
	STR_MOD->fixSlashes(this->gazzettaPath);
	STR_MOD->fixSlashes(this->risultatiPath);
	STR_MOD->fixSlashes(this->downloadPath);
	STR_MOD->fixSlashes(this->listePath);
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
	return this->getUrl() + "777/formazioni/listaFormazioni.txt";
}
QString Repository::getFileGazzettaUrl() {
	return this->getUrl() + "777/filesGazzetta/listaGazFiles.txt";
}
QString Repository::getUrl() {
	LOG(CMDLINE, "In QString Repository::getUrl()");
	return this->url;
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
