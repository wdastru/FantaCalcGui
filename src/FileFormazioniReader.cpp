#include <QtGui>

#include "FileFormazioniReader.h"
#include <sstream>

FileFormazioniReader::FileFormazioniReader(QString _fileFormazioni,
		QWidget *parent) :
		QDialog(parent) {
	this->fileFormazioni = _fileFormazioni;

	QString a = "pippo";
	QString b = "pluto";
	QString c = "cicci";

	QStringList items;

	items.push_back(a);
	items.push_back(b);
	items.push_back(c);

	bool ok;
	QString item = QInputDialog::getItem(this, tr("Scegli"),
			"Gugu non trovato. Giocatori con nome simile:", items, 0,
			false, &ok);
}
