#ifndef SINGLETONQTLOGGER_H
#define SINGLETONQTLOGGER_H

#include <QtWidgets/QWidget>

#include <QtCore/QString>
#include "ui_singletonQtLogger.h"

class IniFilePopulator;

class singletonQtLogger: public QWidget {
Q_OBJECT

friend class IniFilePopulator;

public:
	static singletonQtLogger* Inst();
	void Logging(QString type, QString message);
	void Initialize();
	singletonQtLogger(QWidget *parent = 0);
	virtual ~singletonQtLogger();
	void setTitle(QString);
	void setVersion(QString);
	void setRevision(QString);
	QString getTitle(void);
	QString getVersion(void);
	QString getRevision(void);
	void setLogFileName(QString);
	//bool checkForUpdates_old();

private slots:
	void saveLogAndClose();
	void configClicked();
	void onlineClicked();
	void offlineClicked();
	void goOn();
	void on_uploadCampButton_clicked();
	void on_uploadCoppaButton_clicked();

public slots:
	bool checkForUpdates();

signals:
	void onOffClickedFinished();
	void restart();

private:
	void init();
	void saveLogFile();
	QString title;
	Ui::singletonQtLoggerClass ui;
	static singletonQtLogger* pInstance;
	QString fileContent;
	QString logFileName;
	QString version;
	QString revision;
	QString fileGazzetta;
	QString fileFormazioni;
};

#endif //
SINGLETONQTLOGGER_H
