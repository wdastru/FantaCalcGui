#ifndef FILEFORMAZIONIREADER_H
#define FILEFORMAZIONIREADER_H

#include <QtGui/QDialog>

#include "defines.h"

class FileFormazioniReader: public QDialog {
Q_OBJECT

public:
	FileFormazioniReader(QString, QWidget *parent = 0);

private slots:

private:
	QString fileFormazioni;

protected:

};

#endif
