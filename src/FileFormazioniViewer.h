#ifndef FILEFORMAZIONIVIEWER_H
#define FILEFORMAZIONIVIEWER_H

#include <QtGui/QDialog>
#include <QtCore/QFile>

#include "ui_FileFormazioniViewer.h"

class FileFormazioniViewer: public QDialog {
Q_OBJECT

public:

	static FileFormazioniViewer* Inst();
	FileFormazioniViewer(QWidget *parent = 0);
	virtual ~FileFormazioniViewer();
	void setFile(QString);
	unsigned int getResult();

private slots:
	void saveFileAndClose();
	void quit();

private:
	static FileFormazioniViewer* pInstance;
	Ui::FileFormazioniViewerClass ui;
	QString filename;
	unsigned int result;
};

#endif // FILEFORMAZIONIVIEWER_H
