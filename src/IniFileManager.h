/*
 * IniFileManager.h
 *
 *  Created on: 13/lug/2011
 *      Author: WAleViolaeIvan
 */

#ifndef INIFILEMANAGER_H_
#define INIFILEMANAGER_H_

#include <QtCore/QString>

#include "singletonQtLogger.h"
#include "defines.h"

class IniFileManager {
public:
	IniFileManager();
	virtual ~IniFileManager();
	static IniFileManager* Inst();

	void writeIniFile();
	void readIniFile();
	QString getListaFormazioni();
	QString getListaGazFiles();
	QString getFormazioniPath();
	QString getGazzettaPath();
	QString getFileNameOutputPath();
	QString getRisultatiPath();
	QString getDownloadPath();
	QString getListePath();
	QString getFileFormazioniUrl();
	QString getFileGazzettaUrl();
	QString showIniFile();
	QString getIniFilePath();
	QString getWorkDir();
	QString getFormazioniUrl();
	QString getGazzettaUrl();
	bool getDebugStatus();

private:
	static IniFileManager* pInstance;
	QString iniFileName;
	QString workDir;
	QString formazioniPath;
	QString gazzettaPath;
	QString risultatiPath;
	QString listePath;
	QString downloadPath;
	QString formazioniUrl;
	QString gazzettaUrl;
	bool debugStatus;
};

#endif /* INIFILEMANAGER_H_ */
