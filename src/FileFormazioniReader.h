#ifndef FILEFORMAZIONIREADER_H
#define FILEFORMAZIONIREADER_H

#include <QtGui/QDialog>

#include "defines.h"

using namespace std;

class FileFormazioniReader: public QDialog {
Q_OBJECT

public:
	FileFormazioniReader(QString, QWidget *parent = 0);
	virtual ~FileFormazioniReader();
	void setPlayers( vector< vector< string > >);
	unsigned int execute();

private:
	QString fileFormazioni;
	void init();
	vector< vector< string > > allThePlayers;
	vector < string > findLevenstheins(string);
	string prepareStringToPresent(string, signed int);

};

#endif
