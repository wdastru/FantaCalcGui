#ifndef LOGGER_H
#define LOGGER_H

#include <QtGui/QDialog>
#include "ui_Logger.h"

class Logger : public QDialog
{
    Q_OBJECT

public:
    Logger(QWidget *parent = 0);
    virtual ~Logger();
    Ui::LoggerClass ui;

private:
};

#endif // LOGGER_H
