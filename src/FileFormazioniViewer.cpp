#include "FileFormazioniViewer.h"
#include "defines.h"
#include "singletonQtLogger.h"

#include <QTextDocumentWriter>

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
				this->ui.plainTextEdit->setPlainText(
						QString::fromLocal8Bit(file->readAll()));
			} else {
				/* TODO
				 * completare
				 */
			}
		} else {
			/* TODO
			 * completare
			 */
		}

	} else {
		/* TODO
		 * completare
		 */
	}

	QFont f("Courier");
	this->ui.plainTextEdit->setFont(f);
}

void FileFormazioniViewer::saveFileAndClose() {
	LOG(DEBUG, "In FileFormazioniViewer::saveFileAndClose().");
	QTextDocumentWriter writer(this->filename);
	if (writer.write(this->ui.plainTextEdit->document())) {
		LOG(
				DEBUG,
				"In FileFormazioniViewer::saveFileAndClose() --> write of "
						+ this->filename + " was successful.");
		this->close();
	} else {
		LOG(
				ERROR,
				"In FileFormazioniViewer::saveFileAndClose() --> write of "
						+ this->filename + " was not successful.");
		this->close();
	}
}
