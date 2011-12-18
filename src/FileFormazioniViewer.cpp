#include "FileFormazioniViewer.h"

FileFormazioniViewer::FileFormazioniViewer(QWidget *parent) :
	QDialog(parent) {
	ui.setupUi(this);
}

FileFormazioniViewer::~FileFormazioniViewer() {

}

void FileFormazioniViewer::setFile(QString filename) {

	QFile *file = new QFile(filename);
	if (file->exists()) {
		file->open(QIODevice::ReadWrite);
		if (file->isOpen()) {
			if (file->isReadable()) {
//				QByteArray data = file->readAll();
//				QString str = QString::fromLocal8Bit(data);
				this->ui.plainTextEdit->setPlainText(QString::fromLocal8Bit(file->readAll()));
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

}
