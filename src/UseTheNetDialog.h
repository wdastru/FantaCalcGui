#ifndef USE_THE_NET_DIALOG_H
#define USE_THE_NET_DIALOG_H

#include <QtGui/QDialog>
#include <QUrl>
#include <QDir>
#include <QString>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include "ui_UseTheNetDialog.h"

#include "singletonQtLogger.h"
#include "defines.h"

#include "NoNetFileDialog.h"
#include "httpwindow.h"
#include "toString.h"

class UseTheNetDialog: public QDialog {
Q_OBJECT

public:
	UseTheNetDialog(QWidget *parent);
	~UseTheNetDialog();
	void setQuestion(const std::string question);
	QString getNoNetSquadreFile();
	QString getNoNetGazzettaFile();
	bool getYesClicked();
	bool getNoClicked();
	bool getDownloadSuccess();
	bool hasFinished;
	bool hasBeenAborted;

private slots:
	void yesClicked();
	void noClicked();
	void abortClicked();
	void configClicked();

private:
	Ui::UseTheNetDialogClass ui;
	NoNetFileDialog * noNetFileDialog;
	QString noNetSquadreFile;
	QString noNetGazzettaFile;
	bool yesHasBeenClicked;
	bool noHasBeenClicked;
	bool downloadSuccess;
};

#endif // USE_THE_NET_DIALOG_H
