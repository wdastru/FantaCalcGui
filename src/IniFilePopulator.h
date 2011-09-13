#ifndef INIFILEPOPULATOR_H
#define INIFILEPOPULATOR_H

#include "singletonQtLogger.h"
#include "defines.h"

#include <QtGui/QDialog>
#include "ui_IniFilePopulator.h"

class IniFilePopulator : public QDialog
{
    Q_OBJECT

public:
    IniFilePopulator(QWidget *parent = 0);
    ~IniFilePopulator();

private:
    Ui::IniFilePopulatorClass ui;
};

#endif // INIFILEPOPULATOR_H
