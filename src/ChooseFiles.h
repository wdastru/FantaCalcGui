#ifndef CHOOSEFILES_H
#define CHOOSEFILES_H

#include <QtGui/QDialog>
#include <QtGui/QRadioButton>
#include <QtGui/QLabel>

#include "ui_ChooseFiles.h"

#include "Downloader.h"

class ChooseFiles: public QDialog {
Q_OBJECT

public:
	ChooseFiles(QString, QString, QWidget *parent = 0);
	~ChooseFiles();
	bool wasCancelClicked();
	QString getFileGazzetta(void);
	QString getFileFormazioni(void);
	QString getGazFile();
	QString getHomeFile();
	QString getAwayFile();

private slots:
	void on_okButton_clicked();
	void on_cancelButton_clicked();
	void on_HomeAwayBox_toggled(bool);
	void on_CampoNeutroBox_toggled(bool);
	void enableOkButton();
	//void toggle1();
	//void toggle2();
	//void execute();

private:
	Ui::ChooseFilesClass ui;
	std::vector<QRadioButton *> home;
	std::vector<QRadioButton *> away;
	std::vector<QRadioButton *> neutro1;
	std::vector<QRadioButton *> neutro2;
	std::vector<QRadioButton *> gaz;
	std::vector<QLabel *> labelFormazioni;
	std::vector<QLabel *> labelGazzetta;
	QString fileGazzetta;
	QString fileFormazioni;
	int nGazFiles;
	int nFiles;
	bool cancelClicked;
	void setupFormazioniTab(QString);
	void setupGazzettaTab(QString);
	int height;
	void doDownload();
	bool downloadSuccess;
	bool createFileSquadreFromWebFiles();
	Downloader* filesDownloader;

};

#endif // CHOOSEFILES_H
