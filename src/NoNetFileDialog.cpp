/*
 * Generated by StarUML(tm) C++ Add-In
 *
 * @ Project : FantaCalcGuiNew
 * @ File Name : NoNetFileDialog.cpp
 * @ Date : 16/07/2011
 * @ Author : Walter Dastr�
 *
 */

#define DO_DEBUG

#include "NoNetFileDialog.h"
#include "Repository.h"

NoNetFileDialog::NoNetFileDialog(QWidget *parent) :
	QDialog(parent) {

	this->setFont(THE_REPO->fontVariableWidthSmall);
	ui.setupUi(this);
	ui.okButton->setEnabled(false);
	this->setWindowTitle("FantaCalcGui - Scegli i file offline");
	hasBeenAborted = FALSE;
}
NoNetFileDialog::~NoNetFileDialog() {

}
void NoNetFileDialog::setOpenFileNameSquadre() {
	QString path =
			THE_REPO->getFormazioniPath().trimmed().replace("\\", "\\\\");

	this->fileNameSquadre = QFileDialog::getOpenFileName(this,
			tr("Scegli il file con le squadre."), path,
			tr("Text Files (*.txt);;All Files (*)"));

	if (!this->fileNameSquadre.isEmpty()) {
//		LOG(
//				DBG,
//				"In NoNetFileDialog::setOpenFileNameSquadre() --> fileNameSquadre is not empty: "
//						+ this->fileNameSquadre);
		/*
		 QByteArray ba = this->fileNameSquadre.toLatin1();

		 while (1) {
		 if (ba.at(ba.size() - 1) != '/') {
		 if (ba.size() > 1)
		 ba.remove(ba.size() - 1, 1);
		 else
		 break;
		 } else
		 break;
		 }

		 this->fileNameSquadrePath = ba.trimmed();
		 //		this->writeIniFile();
		 THE_REPO->writeIniFile();
		 */
	} else {
		LOG(ERR,
				"In NoNetFileDialog::setOpenFileNameSquadre() --> fileNameSquadre is empty.");
		this->fileNameSquadre = "";
		//		openFileNameSquadreLabel->setText("");
	}

	ui.fileSquadreLineEdit->setText(this->fileNameSquadre);
	this->enableOkButton();

	//	THE_MANAGER->writeIniFile();
}
void NoNetFileDialog::setOpenFileNameGazzetta() {
	QString path = THE_REPO->getGazzettaPath().trimmed().replace("\\", "\\\\");

	this->fileNameGazzetta = QFileDialog::getOpenFileName(this,
			tr("Scegli il file della gazzetta."), path,
			tr("Text Files (*.txt);;All Files (*)"));

	if (!this->fileNameGazzetta.isEmpty()) {
//		LOG(
//				DBG,
//				"In NoNetFileDialog::setOpenFileNameGazzetta() --> fileNameGazzetta is not empty: "
//						+ this->fileNameGazzetta);
		/*
		 openFileNameGazzettaLabel->setText(fileNameGazzetta);

		 QByteArray ba = fileNameGazzetta.toLatin1();

		 while (1) {
		 if (ba.at(ba.size() - 1) != '/') {
		 if (ba.size() > 1)
		 ba.remove(ba.size() - 1, 1);
		 else
		 break;
		 } else
		 break;
		 }

		 this->fileNameGazzettaPath = ba.trimmed();
		 //		this->writeIniFile();
		 THE_REPO->writeIniFile();
		 */
	} else {
		LOG(ERR,
				"In NoNetFileDialog::setOpenFileNameGazzetta() --> fileNameGazzetta is empty.");
		this->fileNameGazzetta = "";
	}

	ui.fileGazzettaLineEdit->setText(this->fileNameGazzetta);
	this->enableOkButton();

}
void NoNetFileDialog::enableOkButton() {
	if (ui.fileSquadreLineEdit->text().isEmpty()
			|| ui.fileGazzettaLineEdit->text().isEmpty())
		ui.okButton->setEnabled(false);
	else
		ui.okButton->setEnabled(true);
}
QString NoNetFileDialog::getFileNameSquadre() {
	return this->fileNameSquadre;
}
QString NoNetFileDialog::getFileNameGazzetta() {
	return this->fileNameGazzetta;
}
void NoNetFileDialog::okClicked() {
	this->hasBeenAborted = FALSE;
//	LOG(DEB, "In NoNetFileDialog::okClicked().");
	this->hide();
}
void NoNetFileDialog::cancelClicked() {
	this->hasBeenAborted = TRUE;
//	LOG(DEB, "In NoNetFileDialog::cancelClicked().");
	this->close();
}
void NoNetFileDialog::closeEvent(QCloseEvent *event) {
	this->cancelClicked();
}

