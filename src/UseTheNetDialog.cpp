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

	LOG(DEBUG,
			"In UseTheNetDialog::UseTheNetDialog(QWidget *parent) -> object created.");
}
UseTheNetDialog::~UseTheNetDialog() {
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
	LOG(DEBUG,
			"In void UseTheNetDialog::yesClicked() : network will be accessed.");
	this->yesHasBeenClicked = TRUE;
	this->noHasBeenClicked = FALSE;

	std::vector<QUrl> * urls = new std::vector<QUrl>;
	urls->push_back(THE_MANAGER->getFileFormazioniUrl());
	urls->push_back(THE_MANAGER->getFileGazzettaUrl());

	std::vector<QString> * savePaths = new std::vector<QString>;
	savePaths->push_back(THE_MANAGER->getListePath());
	savePaths->push_back(THE_MANAGER->getListePath());

	HttpWindow httpWin(THE_LOGGER, urls, savePaths);
	httpWin.exec();

	if (httpWin.requestSucceded()) {
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
		return;
	}
}
void UseTheNetDialog::noClicked() {
	LOG(DEBUG,
			"In UseTheNetDialog::noClicked() --> Network will not be accessed.");

	this->yesHasBeenClicked = FALSE;
	this->noHasBeenClicked = TRUE;

	noNetFileDialog = new NoNetFileDialog(this);
	noNetFileDialog->exec();

	if (!noNetFileDialog->hasBeenAborted) {
		this->noNetSquadreFile = noNetFileDialog->getFileNameSquadre();
		LOG(
				DEBUG,
				"In void UseTheNetDialog::noClicked() -> fileNameSquadre : "
						+ this->noNetSquadreFile);
		this->noNetGazzettaFile = noNetFileDialog->getFileNameGazzetta();
		this->hasFinished = TRUE;
		this->close();
	} else {
		this->hasFinished = FALSE;
		return;
	}
}
void UseTheNetDialog::abortClicked() {
	this->hasBeenAborted = true;
	this->hasFinished = true;
	LOG(DEBUG, "UseTheNetDialog::abortClicked()");
	this->close();
}
void UseTheNetDialog::configClicked() {
	THE_CONFIGURATOR->setFormazioniPath(THE_REPO->getFormazioniPath());
	THE_CONFIGURATOR->setGazzettaPath(THE_REPO->getGazzettaPath());
	THE_CONFIGURATOR->setRisultatiPath(THE_REPO->getRisultatiPath());
	THE_CONFIGURATOR->setListePath(THE_REPO->getListePath());
	THE_CONFIGURATOR->setDownloadPath(THE_REPO->getDownloadPath());
	THE_CONFIGURATOR->setFormazioniUrl(THE_REPO->getFormazioniUrl());
	THE_CONFIGURATOR->setGazzettaUrl(THE_REPO->getGazzettaUrl());
	THE_CONFIGURATOR->setDebugStatus(THE_REPO->getDebugStatus());
	THE_CONFIGURATOR->exec();
}
QString UseTheNetDialog::getNoNetSquadreFile() {
	return this->noNetSquadreFile;
}
QString UseTheNetDialog::getNoNetGazzettaFile() {
	return this->noNetGazzettaFile;
}
bool UseTheNetDialog::getYesClicked() {
	LOG(DEBUG, "In UseTheNetDialog::getYesClicked()");
	return this->yesHasBeenClicked;
}
bool UseTheNetDialog::getNoClicked() {
	LOG(DEBUG, "In UseTheNetDialog::getNoClicked()");
	return this->noHasBeenClicked;
}
bool UseTheNetDialog::getDownloadSuccess() {
	LOG(DEBUG, "In UseTheNetDialog::getDownloadSuccess()");
	return this->downloadSuccess;
}
