#include "Repository.h"
#include "IniFilePopulator.h"

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
	ui.falseCheckBox->setChecked(TRUE);
}
IniFilePopulator::~IniFilePopulator() {

}
void IniFilePopulator::chooseFormazioniPath() {
	QString directory = this->getDir("Formazioni Path",
			THE_REPO->getFormazioniPath());
	if (!directory.isEmpty())
		this->ui.formazioniLineEdit->setText(directory);
}
void IniFilePopulator::chooseGazzettaPath() {
	QString directory = this->getDir("Gazzetta Path",
			THE_REPO->getGazzettaUrl());
	if (!directory.isEmpty())
		this->ui.gazzettaLineEdit->setText(directory);
}
void IniFilePopulator::chooseDownloadPath() {
	QString directory = this->getDir("Download Path",
			THE_REPO->getDownloadPath());
	if (!directory.isEmpty())
		this->ui.downloadLineEdit->setText(directory);
}
void IniFilePopulator::chooseRisultatiPath() {
	QString directory = this->getDir("Risultati Path",
			THE_REPO->getRisultatiPath());
	if (!directory.isEmpty())
		this->ui.risultatiLineEdit->setText(directory);
}
void IniFilePopulator::chooseListePath() {
	QString directory = this->getDir("Liste Path", THE_REPO->getListePath());
	if (!directory.isEmpty())
		this->ui.listeLineEdit->setText(directory);
}
QString IniFilePopulator::getDir(QString caption, QString startDir) {

	LOG(DEBUG, "In IniFilePopulator::getDir()");

	QFileDialog::Options options = QFileDialog::DontResolveSymlinks
			| QFileDialog::ShowDirsOnly;
	options |= QFileDialog::DontUseNativeDialog;

	return QFileDialog::getExistingDirectory(this, caption, startDir, options);
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
