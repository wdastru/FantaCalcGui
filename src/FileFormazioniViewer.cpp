#define DO_DEBUG

#include "FileFormazioniViewer.h"
#include "Repository.h"
#include "defines.h"
#include "singletonQtLogger.h"

#include <QtGui/QTextDocumentWriter>
#include <QtCore/QDebug>

FileFormazioniViewer* FileFormazioniViewer::pInstance = NULL;

FileFormazioniViewer* FileFormazioniViewer::Inst() {
	if (pInstance == NULL) {
		pInstance = new FileFormazioniViewer(THE_LOGGER);
	}
	return pInstance;
}
FileFormazioniViewer::FileFormazioniViewer(QWidget *parent) :
	QDialog(parent) {
	ui.setupUi(this);
	this->setFont(THE_REPO->fontVariableWidthSmall);
	this->ui.plainTextEdit->setFont(THE_REPO->fontFixedWidth);
	this->setWindowTitle("FantaCalcGui - Formazioni");
}
FileFormazioniViewer::~FileFormazioniViewer() {

}
void FileFormazioniViewer::setFile(QString filename) {
	this->filename = filename;
	QFile *file = new QFile(filename);
	if (file->exists()) {
		file->open(QIODevice::ReadWrite);
		if (file->isOpen()) {
			if (file->isReadable()) {

				//this->setFont(THE_REPO->fontFixedWidth);

				this->ui.plainTextEdit->setPlainText(
						QString::fromLocal8Bit(file->readAll()));
			} else {
				/* TODO
				 * completare:
				 * if file is not readable
				 * * * * * * * * * * * * * */
			}
		} else {
			/* TODO
			 * completare:
			 * if file is not open
			 * * * * * * * * * * * */
		}

	} else {
		/* TODO
		 * completare:
		 * if file does not exists
		 * * * * * * * * * * * * * */
	}

	//this->ui.plainTextEdit->setFont(THE_REPO->fontFixedWidth);
}
void FileFormazioniViewer::saveFileAndClose() {
	DEBUG("");

	this->result = FORMFILEVIEWER_OK;

	QTextDocumentWriter writer(this->filename);
	if (writer.write(this->ui.plainTextEdit->document())) {
		DEBUG("write of " << this->filename.toStdString().c_str() << " was successful.");
	} else {
		DEBUG("write of " << this->filename.toStdString().c_str() << " was not successful.");
		LOG(
				ERR,
				"Writing of " + this->filename + " was not successful.");
	}

	this->close();
}
void FileFormazioniViewer::quit() {
	DEBUG("");
	this->result = FORMFILEVIEWER_CANCEL;
	this->close();
}
unsigned int FileFormazioniViewer::getResult() {
	return this->result;
}
