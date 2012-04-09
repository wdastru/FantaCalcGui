#ifndef CHOOSEFILES_H
#define CHOOSEFILES_H

#include <QtGui/QWidget>
#include "ui_ChooseFiles.h"

class ChooseFiles : public QWidget
{
    Q_OBJECT

public:
    ChooseFiles(QWidget *parent = 0);
    ~ChooseFiles();

private slots:
	void on_okButton_clicked();
	void on_cancelButton_clicked();
	//void enableOkButton();
	//void quit();
	//void toggle1();
	//void toggle2();
	//void execute();

private:
    Ui::ChooseFilesClass ui;
};

#endif // CHOOSEFILES_H
