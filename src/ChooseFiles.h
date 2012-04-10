#ifndef CHOOSEFILES_H
#define CHOOSEFILES_H

#include <QtGui/QWidget>
#include <QtGui/QRadioButton>
#include <QtGui/QLabel>
#include "ui_ChooseFiles.h"

class ChooseFiles: public QWidget {
Q_OBJECT

public:
	ChooseFiles(QString, QString, QWidget *parent = 0);
	~ChooseFiles();

private slots:
	void on_okButton_clicked();
	void on_cancelButton_clicked();
	void enableOkButton();
	//void quit();
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
	int nGazFiles;
	int nFiles;
	bool cancelClicked;
	void setupFormazioniTab(QString);
	void setupGazzettaTab(QString);
	int height;
};

#endif // CHOOSEFILES_H
