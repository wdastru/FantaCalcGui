#include "FileFormazioniViewer.h"

FileFormazioniViewer::FileFormazioniViewer(QWidget *parent) :
	QDialog(parent) {
	ui.setupUi(this);
}

FileFormazioniViewer::~FileFormazioniViewer() {

}

void FileFormazioniViewer::setDocument(QString document) {
	this->ui.plainTextEdit->setPlainText(document);
	QFont f("Courier");
	this->ui.plainTextEdit->setFont(f);
}

void FileFormazioniViewer::saveFileAndClose() {

}
