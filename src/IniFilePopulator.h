#ifndef INIFILEPOPULATOR_H
#define INIFILEPOPULATOR_H

#include <QtGui/QFileDialog>
#include <QtGui/QDialog>

#include "IniFileManager.h"
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
	QString getUrl();
	bool getDebugStatus();
	void setFormazioniPath(QString);
	void setGazzettaPath(QString);
	void setRisultatiPath(QString);
	void setDownloadPath(QString);
	void setListePath(QString);
	void setUrl(QString);
	void setDebugStatus(bool);

private slots:
	void chooseFormazioniPath();
	void chooseGazzettaPath();
	void chooseRisultatiPath();
	void chooseDownloadPath();
	void chooseListePath();
	void toggleDebugStatus();
	void updateInternalData();

private:
	static IniFilePopulator* pInstance;
	Ui::IniFilePopulatorClass ui;
	QString getDir(QString, QString);
	QString startDir;
	bool createDirs();

};

#endif // INIFILEPOPULATOR_H
