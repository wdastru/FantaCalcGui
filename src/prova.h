#ifndef PROVA_H
#define PROVA_H

#include <QtGui/QWidget>
#include "ui_prova.h"

class prova : public QWidget
{
    Q_OBJECT

public:
    prova(QWidget *parent = 0);
    ~prova();

private:
    Ui::provaClass ui;
};

#endif // PROVA_H
