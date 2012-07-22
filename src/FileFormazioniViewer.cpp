#include "FileFormazioniViewer.h"
#include "Repository.h"
#include "defines.h"
#include "singletonQtLogger.h"

#include <QTextDocumentWriter>
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

				this->setFont(THE_REPO->fontFixedWidth);

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

	this->ui.plainTextEdit->setFont(THE_REPO->fontFixedWidth);
}
void FileFormazioniViewer::saveFileAndClose() {
	//qDebug() << "In FileFormazioniViewer::saveFileAndClose().";

	this->result = FORMFILEVIEWER_OK;

	QTextDocumentWriter writer(this->filename);
	if (writer.write(this->ui.plainTextEdit->document())) {
		//qDebug() << "In FileFormazioniViewer::saveFileAndClose() --> write of " + this->filename + " was successful.";
	} else {
		qDebug() << "In FileFormazioniViewer::saveFileAndClose() --> write of " + this->filename + " was not successful.";
		LOG(
				ERROR,
				"Writing of " + this->filename + " was not successful.");
	}

	this->close();
}
void FileFormazioniViewer::quit() {
	//qDebug() << "In FileFormazioniViewer::quit().";
	this->result = FORMFILEVIEWER_CANCEL;
	this->close();
}
unsigned int FileFormazioniViewer::getResult() {
	return this->result;
}
