#ifndef SINGLETONQTLOGGER_H
#define SINGLETONQTLOGGER_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QTime>
#include <QFile>
#include "ui_singletonQtLogger.h"

class singletonQtLogger: public QDialog {
Q_OBJECT

public:
	static singletonQtLogger* Inst();
	void Logging(QString type, QString message);
	void Initialize();
	singletonQtLogger(QDialog *parent = 0);
	virtual ~singletonQtLogger();
	void setTitle(QString title);
	void setDebugStatus(bool status);
	void setLogFileName(QString);

private slots:
	void saveLogAndClose();
	void configClicked();
	void onlineClicked();
	void offlineClicked();

private:
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
