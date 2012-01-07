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
//#include "IniFilePopulator.h"

#include "defines.h"

class IniFileManager {

public:
	IniFileManager();
	virtual ~IniFileManager();
	static IniFileManager* Inst();
//	void updateAndWriteIniFile();
	void writeIniFile();
	void readIniFile();
	QString getIniFilePath();
	QString getWorkDir();
	void setWorkDir(QString);
	QString showIniFile();

private:
	static IniFileManager* pInstance;
	QString iniFileName;
	QString workDir;
};

#endif /* INIFILEMANAGER_H_ */
