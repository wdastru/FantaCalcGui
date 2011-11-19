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
	singletonQtLogger(QWidget *parent = 0);
	virtual ~singletonQtLogger();

	static singletonQtLogger* Inst();
	void Logging(QString type, QString message);
	void Initialize();
	void setDebugStatus(bool status);
	void setLogFileName(QString);

private slots:
	void saveLogAndClose();

public:
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
