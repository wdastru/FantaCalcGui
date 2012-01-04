/*
 * Repository.h
 *
 *  Created on: 22/nov/2011
 *      Author: WAleViolaeIvan
 */

#include <QString>
#include <QFont>

#ifndef REPOSITORY_H_
#define REPOSITORY_H_

class Repository {

	friend class IniFilePopulator;
	friend class IniFileManager;
	friend class singletonQtLogger;
	friend class ChooseFileFromAListDialog;
	friend class Downloader;
	friend class FileFormazioniViewer;
	friend class Less25MinDialog;

public:
	Repository();
	virtual ~Repository();
	static Repository* Inst();
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
	QString getFormazioniUrl();
	QString getGazzettaUrl();
	bool getDebugStatus();
//	void setFormazioniPath(QString dir);

private:
	static Repository* pInstance;
	QString formazioniPath;
	QString gazzettaPath;
	QString risultatiPath;
	QString listePath;
	QString downloadPath;
	QString formazioniUrl;
	QString gazzettaUrl;
	QString fileGazzetta;
	QString fileFormazioni;
	QString noNetSquadreFile;
	QString noNetGazzettaFile;
	QFont fontVariableWidthSmall;
	QFont fontVariableWidthBig;
	QFont fontFixedWidth;

	bool debugStatus;
};

#endif /* REPOSITORY_H_ */
