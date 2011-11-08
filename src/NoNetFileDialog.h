/*
 * Generated by StarUML(tm) C++ Add-In
 *
 * @ Project : FantaCalcGuiNew
 * @ File Name : NoNetFileDialog.h
 * @ Date : 16/07/2011
 * @ Author : Walter Dastr�
 *
 */

#ifndef _NONETFILEDIALOG_H
#define _NONETFILEDIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QFileDialog>

#include "ui_NoNetFileDialog.h"
#include "IniFileManager.h"

class NoNetFileDialog: public QDialog {
Q_OBJECT

public:
	NoNetFileDialog(QWidget *parent);
	virtual ~NoNetFileDialog();
	QString getFileNameSquadre();
	QString getFileNameGazzetta();
	bool hasFinished;
	bool hasBeenAborted;

private slots:
	void setOpenFileNameSquadre();
	void setOpenFileNameGazzetta();
	void createEmptyFile();
	void okClicked();
	void cancelClicked();

private:
	Ui::NoNetFileDialogClass ui;
	QString fileNameSquadre;
	QString fileNameGazzetta;
	void enableOkButton();
};

#endif  //_NONETFILEDIALOG_H
