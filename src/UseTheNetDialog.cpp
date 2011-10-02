#include <QtGui/QApplication>

#include <QtCore/QFileInfo>
#include <QtTest/QTest>
#include "UseTheNetDialog.h"
#include "IniFileManager.h"
#include "IniFilePopulator.h"

UseTheNetDialog::UseTheNetDialog(QWidget *parent) :
	QDialog(parent) {
	ui.setupUi(this);
	hasFinished = FALSE;
	hasBeenAborted = FALSE;
	yesHasBeenClicked = FALSE;
	downloadSuccess = FALSE;

	noNetFileDialog = new NoNetFileDialog(this);

	LOG(DEBUG, "UseTheNetDialog object created.");
}
virtual UseTheNetDialog::~UseTheNetDialog() {
	delete noNetFileDialog;
}
void UseTheNetDialog::setQuestion(const std::string question) {
	const std::string
			richText =
					"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
						"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
						"p, li { white-space: pre-wrap; }\n"
						"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
						"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
							+ question + "</p></body></html>";
	this->ui.UseTheNetDialogLabel->setText(
			QApplication::translate("UseTheNetDialogClass", richText.c_str(),
					0, QApplication::UnicodeUTF8));
}
void UseTheNetDialog::yesClicked() {
	LOG(DEBUG, "Network will be accessed.");
	this->yesHasBeenClicked = TRUE;
	this->noHasBeenClicked = TRUE;

	HttpWindow httpWin_1(singletonQtLogger::Inst(),
			IniFileManager::Inst()->getFileFormazioniUrl(),
			IniFileManager::Inst()->getListePath());
	httpWin_1.exec();
	HttpWindow httpWin_2(singletonQtLogger::Inst(),
			IniFileManager::Inst()->getFileGazzettaUrl(),
			IniFileManager::Inst()->getListePath());
	httpWin_2.exec();

	if (httpWin_1.requestSucceded() && httpWin_2.requestSucceded()) {
		LOG(
				DEBUG,
				"In UseTheNetDialog::yesClicked() --> the download of files succeded: closing useTheNetDialog.");
		this->hasFinished = TRUE;
		this->downloadSuccess = TRUE;
		this->close();
	} else {
		LOG(DEBUG,
				"In UseTheNetDialog::yesClicked() --> the download of files failed.");
		this->downloadSuccess = FALSE;
	}
}
void UseTheNetDialog::noClicked() {
	this->hasFinished = true;
	LOG(DEBUG, "Network will not be accessed.");
	noNetFileDialog->exec();
	this->noNetSquadreFile = noNetFileDialog->getFileNameSquadre();
	this->noNetGazzettaFile = noNetFileDialog->getFileNameGazzetta();
	this->yesHasBeenClicked = FALSE;
	this->noHasBeenClicked = TRUE;
	this->close();
}
void UseTheNetDialog::abortClicked() {
	this->hasBeenAborted = true;
	this->hasFinished = true;
	LOG(DEBUG, "UseTheNetDialog::abortClicked()");
	this->close();
}
void UseTheNetDialog::configClicked() {
	IniFilePopulator::Inst()->setFormazioniPath(
			IniFileManager::Inst()->getFormazioniPath());
	IniFilePopulator::Inst()->setGazzettaPath(
			IniFileManager::Inst()->getGazzettaPath());
	IniFilePopulator::Inst()->setRisultatiPath(
			IniFileManager::Inst()->getRisultatiPath());
	IniFilePopulator::Inst()->setListePath(
			IniFileManager::Inst()->getListePath());
	IniFilePopulator::Inst()->setDownloadPath(
			IniFileManager::Inst()->getDownloadPath());
	IniFilePopulator::Inst()->setFormazioniUrl(
			IniFileManager::Inst()->getFormazioniUrl());
	IniFilePopulator::Inst()->setGazzettaUrl(
			IniFileManager::Inst()->getGazzettaUrl());
	IniFilePopulator::Inst()->setDebugStatus(
			IniFileManager::Inst()->getDebugStatus());
	IniFilePopulator::Inst()->exec();

	IniFileManager::Inst()->updateAndWriteIniFile();
}
QString UseTheNetDialog::getNoNetSquadreFile() {
	return this->noNetSquadreFile;
}
QString UseTheNetDialog::getNoNetGazzettaFile() {
	return this->noNetGazzettaFile;
}
bool UseTheNetDialog::getYesClicked() {
	LOG(DEBUG, "In UseTheNetDialog::getYesClicked() : ");
	return this->yesHasBeenClicked;
}
bool UseTheNetDialog::getNoClicked() {
	LOG(DEBUG, "In UseTheNetDialog::getNoClicked() : ");
	return this->noHasBeenClicked;
}
bool UseTheNetDialog::getDownloadSuccess() {
	LOG(DEBUG, "In UseTheNetDialog::getDownloadSuccess() : ");
	return this->downloadSuccess;
}
