#include "Repository.h"
#include "IniFileManager.h"
#include "IniFilePopulator.h"
#include "defines.h"

IniFilePopulator* IniFilePopulator::Inst() {
	if (pInstance == NULL) {
		pInstance = new IniFilePopulator();
	}
	return pInstance;
}
IniFilePopulator* IniFilePopulator::pInstance = NULL;
IniFilePopulator::IniFilePopulator(QWidget *parent) :
	QDialog(parent) {
	LOG(DEBUG, "In IniFilePopulator() constructor.");
	ui.setupUi(this);
}
IniFilePopulator::~IniFilePopulator() {

}
void IniFilePopulator::chooseFormazioniPath() {
	QString directory = THE_REPO->getFormazioniPath();
	QString startDir = THE_MANAGER->getWorkDir();
	if (!directory.isEmpty()) {
		startDir = directory;
	}
	directory = this->getDir("Formazioni Path", startDir);
	if (!directory.isEmpty()) {
		this->ui.formazioniLineEdit->setText(directory);
		THE_REPO->formazioniPath = directory;
	}
}
void IniFilePopulator::chooseGazzettaPath() {
	QString directory = THE_REPO->getGazzettaPath();
	QString startDir = THE_MANAGER->getWorkDir();
	if (!directory.isEmpty()) {
		startDir = directory;
	}
	directory = this->getDir("Gazzetta Path", startDir);
	if (!directory.isEmpty()) {
		this->ui.gazzettaLineEdit->setText(directory);
		THE_REPO->gazzettaPath = directory;
	}
}
void IniFilePopulator::chooseDownloadPath() {
	QString directory = THE_REPO->getDownloadPath();
	QString startDir = THE_MANAGER->getWorkDir();
	if (!directory.isEmpty()) {
		startDir = directory;
	}
	directory = this->getDir("Download Path", startDir);
	if (!directory.isEmpty()) {
		this->ui.downloadLineEdit->setText(directory);
		THE_REPO->downloadPath = directory;
	}
}
void IniFilePopulator::chooseRisultatiPath() {
	QString directory = THE_REPO->getRisultatiPath();
	QString startDir = THE_MANAGER->getWorkDir();
	if (!directory.isEmpty()) {
		startDir = directory;
	}
	directory = this->getDir("Risultati Path", startDir);
	if (!directory.isEmpty()) {
		this->ui.risultatiLineEdit->setText(directory);
		THE_REPO->risultatiPath = directory;
	}
}
void IniFilePopulator::chooseListePath() {
	QString directory = THE_REPO->getListePath();
	QString startDir = THE_MANAGER->getWorkDir();
	if (!directory.isEmpty()) {
		startDir = directory;
	}
	directory = this->getDir("Liste Path", startDir);
	if (!directory.isEmpty()) {
		this->ui.listeLineEdit->setText(directory);
		THE_REPO->listePath = directory;
	}
}
QString IniFilePopulator::getDir(QString caption, QString startDir) {

	LOG(DEBUG, "In IniFilePopulator::getDir()");

	QFileDialog::Options options = QFileDialog::DontResolveSymlinks
			| QFileDialog::ShowDirsOnly;
	options |= QFileDialog::DontUseNativeDialog;

	QString dir = QFileDialog::getExistingDirectory(this, caption, startDir,
			options);

	LOG(DEBUG, "In IniFilePopulator::getDir() --> returning " + dir);

	return dir;
}
void IniFilePopulator::setStartDir(QString _startDir) {
	this->startDir = _startDir;
	LOG(DEBUG,
			"In IniFilePopulator::setStartDir(QString) --> " + this->startDir);
}
QString IniFilePopulator::getFormazioniPath() {
	return this->ui.formazioniLineEdit->text();
}
QString IniFilePopulator::getGazzettaPath() {
	return this->ui.gazzettaLineEdit->text();
}
QString IniFilePopulator::getRisultatiPath() {
	return this->ui.risultatiLineEdit->text();
}
QString IniFilePopulator::getListePath() {
	return this->ui.listeLineEdit->text();
}
QString IniFilePopulator::getDownloadPath() {
	return this->ui.downloadLineEdit->text();
}
QString IniFilePopulator::getFormazioniUrl() {
	return this->ui.formazioniUrlLineEdit->text();
}
QString IniFilePopulator::getGazzettaUrl() {
	return this->ui.gazzettaUrlLineEdit->text();
}
bool IniFilePopulator::getDebugStatus() {
	if (this->ui.trueCheckBox->isChecked())
		return TRUE;
	else if (this->ui.falseCheckBox->isChecked())
		return FALSE;
	else {
		LOG(DEBUG,
				"In QString IniFilePopulator::getDebugStatus() --> no checkBox is selected!");
		return FALSE;
	}
}
void IniFilePopulator::setFormazioniPath(QString str) {
	LOG(
			DEBUG,
			"In void IniFilePopulator::setFormazioniPath(QString str ) --> str : "
					+ str);
	this->ui.formazioniLineEdit->setText(str);
}
void IniFilePopulator::setGazzettaPath(QString str) {
	LOG(
			DEBUG,
			"In void IniFilePopulator::setGazzettaPath(QString str ) --> str : "
					+ str);
	this->ui.gazzettaLineEdit->setText(str);
}
void IniFilePopulator::setRisultatiPath(QString str) {
	LOG(
			DEBUG,
			"In void IniFilePopulator::setRisultatiPath(QString str ) --> str : "
					+ str);
	this->ui.risultatiLineEdit->setText(str);
}
void IniFilePopulator::setListePath(QString str) {
	LOG(
			DEBUG,
			"In void IniFilePopulator::setListePath(QString str ) --> str : "
					+ str);
	this->ui.listeLineEdit->setText(str);
}
void IniFilePopulator::setDownloadPath(QString str) {
	LOG(
			DEBUG,
			"In void IniFilePopulator::setDownloadPath(QString str ) --> str : "
					+ str);
	this->ui.downloadLineEdit->setText(str);
}
void IniFilePopulator::setFormazioniUrl(QString str) {
	LOG(
			DEBUG,
			"In void IniFilePopulator::setFormazioniUrl(QString str ) --> str : "
					+ str);
	this->ui.formazioniUrlLineEdit->setText(str);
}
void IniFilePopulator::setGazzettaUrl(QString str) {
	LOG(
			DEBUG,
			"In void IniFilePopulator::setGazzettaUrl(QString str ) --> str : "
					+ str);
	this->ui.gazzettaUrlLineEdit->setText(str);
}
void IniFilePopulator::setDebugStatus(bool status) {
	if (status) {
		LOG(DEBUG,
				"In void IniFilePopulator::setDebugStatus(bool status) --> status is TRUE");
		this->ui.trueCheckBox->setChecked(true);
	} else {
		LOG(DEBUG,
				"void IniFilePopulator::setDebugStatus(bool status) --> status is FALSE");
		this->ui.falseCheckBox->setChecked(true);
	}
}
void IniFilePopulator::toggleDebugStatus() {
	if (THE_REPO->debugStatus) {
		THE_REPO->debugStatus = FALSE;
		LOG(DEBUG,
				"void IniFilePopulator::toggleDebugStatus() --> status is now FALSE");
	} else {
		THE_REPO->debugStatus = TRUE;
		LOG(DEBUG,
				"void IniFilePopulator::toggleDebugStatus() --> status is now TRUE");
	}
}
