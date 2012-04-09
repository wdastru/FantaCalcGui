#include "ChooseFiles.h"

#include "defines.h"
#include "singletonQtLogger.h"

ChooseFiles::ChooseFiles(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
}

ChooseFiles::~ChooseFiles()
{

}

void ChooseFiles::on_okButton_clicked() {
	LOG(DEBUG, "In void ChooseFiles::on_okButton_clicked().");
	//this->doDownload();
	//if (this->downloadSuccess) {
	//	this->createFileSquadreFromWebFiles();
	//	this->fileGazzetta = THE_REPO->getGazzettaPath() + "/"
	//			+ this->getGazFile();
	//	this->accept();
	//} else {
	//	LOG(DEBUG,
	//			"In void ChooseFiles::execute() --> download of file was not successful.");
	//	/* TODO
	//	 * completare
	//	 */
	//}

	this->close();
}

void ChooseFiles::on_cancelButton_clicked() {
	LOG(DEBUG, "In void ChooseFiles::on_okButton_clicked().");

	//for (int i = 0; i < this->nFiles; i++) {
	//	home.at(i)->setChecked(false);
	//	away.at(i)->setChecked(false);
	//	neutro1.at(i)->setChecked(false);
	//	neutro2.at(i)->setChecked(false);
	//}
	//for (int i = 0; i < this->nGazFiles; i++)
	//	gaz.at(i)->setChecked(false);
    //
	//this->cancelClicked = TRUE;
	this->close();
}

