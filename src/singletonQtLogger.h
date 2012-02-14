#ifndef SINGLETONQTLOGGER_H
#define SINGLETONQTLOGGER_H

#include <QWidget>
#include <QString>
#include "ui_singletonQtLogger.h"

class singletonQtLogger: public QWidget {
Q_OBJECT

public:
	static singletonQtLogger* Inst();
	void Logging(QString type, QString message);
	void Initialize();
	singletonQtLogger(QWidget *parent = 0);
	virtual ~singletonQtLogger();
	void setTitle(QString);
	void setVersion(QString);
	QString getTitle(void);
	QString getVersion(void);
	void setLogFileName(QString);
	bool checkForUpdates();
	bool checkForUpdates_old();

private slots:
	void saveLogAndClose();
	void configClicked();
	void onlineClicked();
	void offlineClicked();
	void goOn();

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
	QString fileGazzetta;
	QString fileFormazioni;
};

#endif //
SINGLETONQTLOGGER_H
