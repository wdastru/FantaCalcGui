#ifndef FILEFORMAZIONIVIEWER_H
#define FILEFORMAZIONIVIEWER_H

#include <QtGui/QDialog>
#include "ui_FileFormazioniViewer.h"

class FileFormazioniViewer : public QDialog {
    Q_OBJECT

public:
    FileFormazioniViewer(QWidget *parent = 0);
    virtual ~FileFormazioniViewer();

private:
    Ui::FileFormazioniViewerClass ui;
};

#endif // FILEFORMAZIONIVIEWER_H
