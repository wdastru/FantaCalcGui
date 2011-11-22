#ifndef SINGLETONQTLOGGER_H
#define SINGLETONQTLOGGER_H

#include <QWidget>
#include <QMessageBox>
#include <QString>
#include <QTime>
#include <QFile>
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
	void setDebugStatus(bool);
	void setLogFileName(QString);

private slots:
	void saveLogAndClose();
	void configClicked();
	void onlineClicked();
	void offlineClicked();

private:
	void init();
	void saveLogFile();
	QString title;
	static bool debugStatus;
	Ui::singletonQtLoggerClass ui;
	static singletonQtLogger* pInstance;
	QString fileContent;
	QString logFileName;
	QString version;
};

#endif //
SINGLETONQTLOGGER_H
