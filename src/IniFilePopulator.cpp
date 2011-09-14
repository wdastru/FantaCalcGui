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
	ui.formazioniUrlLineEdit->setText(
			"http://nmr.ch.unito.it/lab/Fantasito/777/formazioni/");
	ui.gazzettaUrlLineEdit->setText(
			"http://nmr.ch.unito.it/lab/Fantasito/777/filesGazzetta/");
	ui.falseCheckBox->setChecked(TRUE);
}

IniFilePopulator::~IniFilePopulator() {

}

void IniFilePopulator::chooseFormazioniPath() {
	QString directory = this->getDir("Formazioni Path", this->startDir);
	if (!directory.isEmpty())
		this->ui.formazioniLineEdit->setText(directory);
}
void IniFilePopulator::chooseGazzettaPath() {
	QString directory = this->getDir("Gazzetta Path", this->startDir);
	if (!directory.isEmpty())
		this->ui.gazzettaLineEdit->setText(directory);
}
void IniFilePopulator::chooseDownloadPath() {
	QString directory = this->getDir("Download Path", this->startDir);
	if (!directory.isEmpty())
		this->ui.downloadLineEdit->setText(directory);
}
void IniFilePopulator::chooseRisultatiPath() {
	QString directory = this->getDir("Risultati Path", this->startDir);
	if (!directory.isEmpty())
		this->ui.risultatiLineEdit->setText(directory);
}
void IniFilePopulator::chooseListePath() {
	QString directory = this->getDir("Liste Path", this->startDir);
	if (!directory.isEmpty())
		this->ui.listeLineEdit->setText(directory);
}
QString IniFilePopulator::getDir(QString caption, QString startDir) {

	LOG(DEBUG, "In IniFilePopulator::getDir()");

	QFileDialog::Options options = QFileDialog::DontResolveSymlinks
			| QFileDialog::ShowDirsOnly;
	options |= QFileDialog::DontUseNativeDialog;

	QString directory = QFileDialog::getExistingDirectory(this, caption,
			startDir, options);
	return directory;
}
void IniFilePopulator::setStartDir(QString _startDir) {
	this->startDir = _startDir;
	LOG(DEBUG,
			"In IniFilePopulator::setStartDir(QString) --> " + this->startDir);
}
QString IniFilePopulator::getFormazioniPath(){
	return this->ui.formazioniLineEdit->text();
}
QString IniFilePopulator::getGazzettaPath(){
	return this->ui.gazzettaLineEdit->text();
}
QString IniFilePopulator::getRisultatiPath(){
	return this->ui.risultatiLineEdit->text();
}
QString IniFilePopulator::getListePath(){
	return this->ui.listeLineEdit->text();
}
QString IniFilePopulator::getDownloadPath(){
	return this->ui.downloadLineEdit->text();
}
QString IniFilePopulator::getFormazioniUrl(){
	return this->ui.formazioniUrlLineEdit->text();
}
QString IniFilePopulator::getGazzettaUrl(){
	return this->ui.gazzettaUrlLineEdit->text();
}
QString IniFilePopulator::getDebugStatus(){
	if (this->ui.trueCheckBox->isChecked())
		return "TRUE";
	else if (this->ui.falseCheckBox->isChecked())
		return "FALSE";
	else {
		LOG(DEBUG, "In QString IniFilePopulator::getDebugStatus() --> no checkBox is selected!");
		return "FALSE";
	}

}
