#ifndef CHOOSEFILEFROMALISTDIALOG_H
#define CHOOSEFILEFROMALISTDIALOG_H

#include <QtGui/QDialog>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QUrl>

class QLabel;
class QPushButton;
class QGroupBox;
class QRadioButton;
class QScrollArea;
class QTabWidget;

class ChooseFileFromAListDialog: public QDialog {
Q_OBJECT

public:
	ChooseFileFromAListDialog(QString, QString, QWidget *parent = 0);
	void setFileFormazioni(QString);
	QString getFileFormazioni(void);
	QString getFileGazzetta(void);

	void setFileGazzetta(QString);
	QString getHomeFile();
	QString getGazFile();
	QString getAwayFile();
	bool wasCancelClicked();
	bool isFinished();
	bool getDownloadSuccess();
	QTabWidget *Tabs;
	QWidget *formazioniTab;
	QWidget *gazzettaTab;

private slots:
	void enableOkButton();
	void quit();
	void toggle1();
	void toggle2();
	void execute();

private:
	void doDownload();
	int groupBoxChecked();
	bool createFileSquadreFromWebFiles();
	QString fileFormazioni;
	QString fileGazzetta;
	std::vector<QRadioButton *> home;
	std::vector<QRadioButton *> away;
	std::vector<QRadioButton *> neutro1;
	std::vector<QRadioButton *> neutro2;
	std::vector<QRadioButton *> gaz;
	std::vector<QLabel *> labelFormazioni;
	std::vector<QLabel *> labelGazzetta;
	QLabel * label;
	QPushButton *okButton;
	QPushButton *cancelButton;
	QGroupBox * FilesBox;
	QGroupBox * HomeAwayBox;
	QGroupBox * CampoNeutroBox;
	QGroupBox * groupBoxLabelsFormazioni;
	QGroupBox * groupBoxHome;
	QGroupBox * groupBoxAway;
	QGroupBox * groupBoxGazzetta;
	QGroupBox * groupBoxNeutro1;
	QGroupBox * groupBoxNeutro2;
	QGroupBox * containerBoxFormazioni;
	QGroupBox * containerBoxGazzetta;
	QScrollArea * scrollArea;
	int nFiles;
	int nGazFiles;
	bool cancelClicked;
	bool hasFinished;
	bool downloadSuccess;

protected:
	void closeEvent(QCloseEvent *event);

};

#endif // CHOOSEFROMALISTDIALOG_H
