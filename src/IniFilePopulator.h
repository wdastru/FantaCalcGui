#ifndef INIFILEPOPULATOR_H
#define INIFILEPOPULATOR_H

#include "Logger.h"
#include "IniFileManager.h"
#include "defines.h"

#include <QtGui/QDialog>
#include <QtGui/QFileDialog>
#include "ui_IniFilePopulator.h"

class IniFilePopulator: public QDialog {
Q_OBJECT

public:
	static IniFilePopulator * Inst();
	IniFilePopulator(QWidget *parent = 0);
	virtual ~IniFilePopulator();
	void setStartDir(QString);
	QString getFormazioniPath();
	QString getGazzettaPath();
	QString getRisultatiPath();
	QString getDownloadPath();
	QString getListePath();
	QString getFormazioniUrl();
	QString getGazzettaUrl();
	bool getDebugStatus();
	void setFormazioniPath(QString);
	void setGazzettaPath(QString);
	void setRisultatiPath(QString);
	void setDownloadPath(QString);
	void setListePath(QString);
	void setFormazioniUrl(QString);
	void setGazzettaUrl(QString);
	void setDebugStatus(bool);

private slots:
	void chooseFormazioniPath();
	void chooseGazzettaPath();
	void chooseRisultatiPath();
	void chooseDownloadPath();
	void chooseListePath();

private:
	static IniFilePopulator* pInstance;
	Ui::IniFilePopulatorClass ui;
	QString getDir(QString, QString);
	QString startDir;

};

#endif // INIFILEPOPULATOR_H
