#define DO_DEBUG

#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtCore/QDir>

#include "Repository.h"
#include "IniFileManager.h"
#include "IniFilePopulator.h"
#include "StringModifier.h"
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
	//LOG(DEB, "In IniFilePopulator() constructor.");
	this->startDir = "";
	ui.setupUi(this);
	this->setFont(THE_REPO->fontVariableWidthSmall);
	this->setWindowTitle("FantaCalcGui - Configurazione");
}
IniFilePopulator::~IniFilePopulator() {

}
void IniFilePopulator::updateInternalData() {
	THE_REPO->formazioniPath = ui.formazioniLineEdit->text();
	THE_REPO->gazzettaPath = ui.gazzettaLineEdit->text();
	THE_REPO->risultatiPath = ui.risultatiLineEdit->text();
	THE_REPO->downloadPath = ui.downloadLineEdit->text();
	THE_REPO->listePath = ui.listeLineEdit->text();
	THE_REPO->url = ui.urlLineEdit->text();
	THE_REPO->formazioniUrl = ui.urlLineEdit->text() + "777/formazioni/";
	THE_REPO->gazzettaUrl = ui.urlLineEdit->text() + "777/filesGazzetta/";

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
	//	LOG(DEB, "In IniFilePopulator::createDirs().");

	bool retVal = true;

	QDir * dir = new QDir;

	QVector<QString> * paths = new QVector<QString>();
	paths->push_back(THE_REPO->formazioniPath);
	paths->push_back(THE_REPO->risultatiPath);
	paths->push_back(THE_REPO->gazzettaPath);
	paths->push_back(THE_REPO->listePath);
	paths->push_back(THE_REPO->downloadPath);

	for (int i = 0; i < paths->size(); ++i) {
		if (!dir->exists(paths->at(i))) {
			if (dir->mkdir(paths->at(i))) {
				LOG(DEB, QObject::tr("Creata cartella %1").arg(paths->at(i)));
				retVal = retVal && true;
			} else {
				LOG(ERR,
						QObject::tr(
								"Non e' stato possibile creare la cartella %1").arg(
								paths->at(i)));
			}
		}
	}

	return retVal;
}
void IniFilePopulator::chooseFormazioniPath() {

	QString directory = this->getDir("Formazioni Path", THE_REPO->formazioniPath);
	if (!directory.isEmpty()) {

		LOG(DEB,
				QObject::tr("Percorso di salvataggio file formazioni : %1").arg(
						directory));

		this->ui.formazioniLineEdit->setText(directory);
		THE_REPO->formazioniPath = directory;
		QDir * dir = new QDir(directory);
		dir->cdUp();
		this->startDir = dir->absolutePath();
	}
}
void IniFilePopulator::chooseGazzettaPath() {
	QString directory = this->getDir("Gazzetta Path", THE_REPO->gazzettaPath);
	if (!directory.isEmpty()) {

		LOG(DEB,
				QObject::tr("Percorso di salvataggio file gazzetta : %1").arg(
						directory));

		this->ui.gazzettaLineEdit->setText(directory);
		THE_REPO->gazzettaPath = directory;
		QDir * dir = new QDir(directory);
		dir->cdUp();
		this->startDir = dir->absolutePath();
	}
}
void IniFilePopulator::chooseDownloadPath() {
	QString directory = this->getDir("Download Path", THE_REPO->downloadPath);
	if (!directory.isEmpty()) {

		LOG(DEB,
				QObject::tr("Percorso di salvataggio downloads : %1").arg(
						directory));

		this->ui.downloadLineEdit->setText(directory);
		THE_REPO->downloadPath = directory;
		QDir * dir = new QDir(directory);
		dir->cdUp();
		this->startDir = dir->absolutePath();
	}
}
void IniFilePopulator::chooseRisultatiPath() {
	QString directory = this->getDir("Risultati Path", THE_REPO->risultatiPath);
	if (!directory.isEmpty()) {

		LOG(DEB,
				QObject::tr("Percorso di salvataggio risultati : %1").arg(
						directory));

		this->ui.risultatiLineEdit->setText(directory);
		THE_REPO->risultatiPath = directory;
		QDir * dir = new QDir(directory);
		dir->cdUp();
		this->startDir = dir->absolutePath();
	}
}
void IniFilePopulator::chooseListePath() {
	QString directory = this->getDir("Liste Path", THE_REPO->listePath);
	if (!directory.isEmpty()) {

		LOG(DEB,
				QObject::tr("Percorso di salvataggio file liste : %1").arg(
						directory));

		this->ui.listeLineEdit->setText(directory);
		THE_REPO->listePath = directory;
		QDir * dir = new QDir(directory);
		dir->cdUp();
		this->startDir = dir->absolutePath();
	}
}
QString IniFilePopulator::getDir(QString caption, QString startDir) {

	//	LOG(DEB, "In IniFilePopulator::getDir()");

	QFileDialog::Options options = QFileDialog::DontResolveSymlinks
			| QFileDialog::ShowDirsOnly;
	options |= QFileDialog::DontUseNativeDialog;

	QString dir = QFileDialog::getExistingDirectory(this, caption, startDir,
			options);

	LOG(DEB, "In IniFilePopulator::getDir() --> returning " + dir);

	return dir;
}
void IniFilePopulator::setStartDir(QString _startDir) {
	this->startDir = _startDir;
	//	LOG(DEB,
	//			"In IniFilePopulator::setStartDir(QString) --> " + this->startDir);
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
QString IniFilePopulator::getUrl() {
	return this->ui.urlLineEdit->text();
}
bool IniFilePopulator::getDebugStatus() {
	if (this->ui.trueCheckBox->isChecked())
		return TRUE;
	else if (this->ui.falseCheckBox->isChecked())
		return FALSE;
	else {
		LOG(DEB,
				"In QString IniFilePopulator::getDebugStatus() --> no checkBox is selected!");
		return FALSE;
	}
}
void IniFilePopulator::setFormazioniPath(QString str) {
	//	LOG(
	//			DBG,
	//			"In void IniFilePopulator::setFormazioniPath(QString str ) --> str : "
	//					+ str);
	this->ui.formazioniLineEdit->setText(str);
}
void IniFilePopulator::setGazzettaPath(QString str) {
	//	LOG(
	//			DBG,
	//			"In void IniFilePopulator::setGazzettaPath(QString str ) --> str : "
	//					+ str);
	this->ui.gazzettaLineEdit->setText(str);
}
void IniFilePopulator::setRisultatiPath(QString str) {
	//	LOG(
	//			DBG,
	//			"In void IniFilePopulator::setRisultatiPath(QString str ) --> str : "
	//					+ str);
	this->ui.risultatiLineEdit->setText(str);
}
void IniFilePopulator::setListePath(QString str) {
	//	LOG(
	//			DBG,
	//			"In void IniFilePopulator::setListePath(QString str ) --> str : "
	//					+ str);
	this->ui.listeLineEdit->setText(str);
}
void IniFilePopulator::setDownloadPath(QString str) {
	//	LOG(
	//			DBG,
	//			"In void IniFilePopulator::setDownloadPath(QString str ) --> str : "
	//					+ str);
	this->ui.downloadLineEdit->setText(str);
}
void IniFilePopulator::setUrl(QString str) {
	//	LOG(
	//			DBG,
	//			"In void IniFilePopulator::setUrl(QString str ) --> str : "
	//					+ str);
	this->ui.urlLineEdit->setText(str);
}
void IniFilePopulator::setDebugStatus(bool status) {
	if (status) {
		//		LOG(DEB,
		//				"In void IniFilePopulator::setDebugStatus(bool status) --> status is TRUE.");
		this->ui.trueCheckBox->setChecked(TRUE);
	} else {
		//		LOG(DEB,
		//				"void IniFilePopulator::setDebugStatus(bool status) --> status is FALSE.");
		this->ui.falseCheckBox->setChecked(TRUE);
	}
}
void IniFilePopulator::toggleDebugStatus() {
	if (this->ui.trueCheckBox->isChecked()) {
		THE_REPO->debugStatus = TRUE;
		//THE_LOGGER->ui.plainTextEdit->setPlainText(THE_LOGGER->fileContent.replace("&nbsp;", " "));
		DEBUG("void IniFilePopulator::toggleDebugStatus() --> TRUE is checked.");
	} else if (this->ui.falseCheckBox->isChecked()) {
		THE_REPO->debugStatus = FALSE;
		//THE_LOGGER->ui.plainTextEdit->setPlainText(THE_LOGGER->fileContent.replace("&nbsp;", " "));
		DEBUG("void IniFilePopulator::toggleDebugStatus() --> FALSE is checked.");
	} else {
		LOG(ERR,
				"void IniFilePopulator::toggleDebugStatus() --> status is not defined: set to FALSE.");
		THE_REPO->debugStatus = FALSE;
	}
}

