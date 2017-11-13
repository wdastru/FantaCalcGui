#ifndef RINVIATEDIALOG_H
#define RINVIATEDIALOG_H

//#include <QtWidgets/QDialog>
#include <QtGui/QDialog>
#include <QtCore/QFile>
#include <QtGui/QCheckBox>

#include "ui_RinviateDialog.h"

class RinviateDialog: public QDialog {
Q_OBJECT

public:

	static RinviateDialog* Inst();
	RinviateDialog(QWidget *parent = 0);
	virtual ~RinviateDialog();
	std::vector<std::string> partiteRinviate();

private slots:
	void quit();
	void enableOkButton();

private:
	static RinviateDialog* pInstance;
	Ui::RinviateDialogClass ui;

	QCheckBox *checkBox[20];

};

#endif // RINVIATE_H
