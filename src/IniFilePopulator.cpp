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
	LOG(DEBUG, "In IniFilePopulator::IniFilePopulator(...).");
	this->startDir = "";
	ui.setupUi(this);
}
IniFilePopulator::~IniFilePopulator() {

}
void IniFilePopulator::updateInternalData() {
	THE_REPO->formazioniPath = ui.formazioniLineEdit->text();
	THE_REPO->gazzettaPath = ui.gazzettaLineEdit->text();
	THE_REPO->risultatiPath = ui.risultatiLineEdit->text();
	THE_REPO->downloadPath = ui.downloadLineEdit->text();
	THE_REPO->listePath = ui.listeLineEdit->text();
	THE_REPO->formazioniUrl = ui.formazioniUrlLineEdit->text();
	THE_REPO->gazzettaUrl = ui.gazzettaUrlLineEdit->text();

	if (this->ui.trueCheckBox->isChecked()) {
		THE_REPO->debugStatus = true;
	} else if (this->ui.falseCheckBox->isChecked()) {
		THE_REPO->debugStatus = false;
	} else {
		THE_REPO->debugStatus = true;
	}

	this->createDirs();

	this->close();
}
bool IniFilePopulator::createDirs() {
	LOG(DEBUG, "In IniFilePopulator::createDirs().");

	bool retVal = true;

	QDir * dir = new QDir;

	if (dir->mkdir(THE_REPO->formazioniPath)) {
		LOG(
				DEBUG,
				"In IniFilePopulator::createDirs() --> "
						+ THE_REPO->formazioniPath + " has been created.");
		retVal = retVal && true;
	} else {
		LOG(
				DEBUG,
				"In IniFilePopulator::createDirs() --> "
						+ THE_REPO->formazioniPath + " has not been created.");
		retVal = retVal && false;
	}

	if (dir->mkdir(THE_REPO->gazzettaPath)) {
		LOG(
				DEBUG,
				"In IniFilePopulator::createDirs() --> "
						+ THE_REPO->gazzettaPath + " has been created.");
		retVal = retVal && true;
	} else {
		LOG(
				DEBUG,
				"In IniFilePopulator::createDirs() --> "
						+ THE_REPO->gazzettaPath + " has not been created.");
		retVal = retVal && false;
	}

	if (dir->mkdir(THE_REPO->risultatiPath)) {
		LOG(
				DEBUG,
				"In IniFilePopulator::createDirs() --> "
						+ THE_REPO->risultatiPath + " has been created.");
		retVal = retVal && true;
	} else {
		LOG(
				DEBUG,
				"In IniFilePopulator::createDirs() --> "
						+ THE_REPO->risultatiPath + " has not been created.");
		retVal = retVal && false;
	}

	if (dir->mkdir(THE_REPO->downloadPath)) {
		LOG(
				DEBUG,
				"In IniFilePopulator::createDirs() --> "
						+ THE_REPO->downloadPath + " has been created.");
		retVal = retVal && true;
	} else {
		LOG(
				DEBUG,
				"In IniFilePopulator::createDirs() --> "
						+ THE_REPO->downloadPath + " has not been created.");
		retVal = retVal && false;
	}

	if (dir->mkdir(THE_REPO->listePath)) {
		LOG(
				DEBUG,
				"In IniFilePopulator::createDirs() --> " + THE_REPO->listePath
						+ " has been created.");
		retVal = retVal && true;
	} else {
		LOG(
				DEBUG,
				"In IniFilePopulator::createDirs() --> " + THE_REPO->listePath
						+ " has not been created.");
		retVal = retVal && false;
	}

	return retVal;
}
void IniFilePopulator::chooseFormazioniPath() {
	QString directory = this->getDir("Formazioni Path", this->startDir);
	if (!directory.isEmpty()) {
		this->ui.formazioniLineEdit->setText(directory);
		THE_REPO->formazioniPath = directory;
		QDir * dir = new QDir(directory);
		dir->cdUp();
		this->startDir = dir->absolutePath();
	}
}
void IniFilePopulator::chooseGazzettaPath() {
	QString directory = this->getDir("Gazzetta Path", this->startDir);
	if (!directory.isEmpty()) {
		this->ui.gazzettaLineEdit->setText(directory);
		THE_REPO->gazzettaPath = directory;
		QDir * dir = new QDir(directory);
		dir->cdUp();
		this->startDir = dir->absolutePath();
	}
}
void IniFilePopulator::chooseDownloadPath() {
	QString directory = this->getDir("Download Path", this->startDir);
	if (!directory.isEmpty()) {
		this->ui.downloadLineEdit->setText(directory);
		THE_REPO->downloadPath = directory;
		QDir * dir = new QDir(directory);
		dir->cdUp();
		this->startDir = dir->absolutePath();
	}
}
void IniFilePopulator::chooseRisultatiPath() {
	QString directory = this->getDir("Risultati Path", this->startDir);
	if (!directory.isEmpty()) {
		this->ui.risultatiLineEdit->setText(directory);
		THE_REPO->risultatiPath = directory;
		QDir * dir = new QDir(directory);
		dir->cdUp();
		this->startDir = dir->absolutePath();
	}
}
void IniFilePopulator::chooseListePath() {
	QString directory = this->getDir("Liste Path", this->startDir);
	if (!directory.isEmpty()) {
		this->ui.listeLineEdit->setText(directory);
		THE_REPO->listePath = directory;
		QDir * dir = new QDir(directory);
		dir->cdUp();
		this->startDir = dir->absolutePath();
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
				"In void IniFilePopulator::setDebugStatus(bool status) --> status is TRUE.");
		this->ui.trueCheckBox->setChecked(TRUE);
	} else {
		LOG(DEBUG,
				"void IniFilePopulator::setDebugStatus(bool status) --> status is FALSE.");
		this->ui.falseCheckBox->setChecked(TRUE);
	}
}
void IniFilePopulator::toggleDebugStatus() {
	if (this->ui.trueCheckBox->isChecked()) {
		THE_REPO->debugStatus = TRUE;
		LOG(DEBUG,
				"void IniFilePopulator::toggleDebugStatus() --> TRUE is checked.");

	} else if (this->ui.falseCheckBox->isChecked()) {
		LOG(DEBUG,
				"void IniFilePopulator::toggleDebugStatus() --> FALSE is checked.");
		THE_REPO->debugStatus = FALSE;
	} else {
		LOG(
				ERROR,
				"void IniFilePopulator::toggleDebugStatus() --> status is not defined: set to FALSE.");
		THE_REPO->debugStatus = FALSE;
	}
}

