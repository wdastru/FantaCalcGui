/*
 * FormazioniFileReader.h
 *
 *  Created on: 29/lug/2011
 *      Author: WAleViolaeIvan
 */

#ifndef FORMAZIONIFILEREADER_H_
#define FORMAZIONIFILEREADER_H_

#include <fstream>
#include <string>
#include <vector>
#include "QtCore/QString"

#include "StringModifier.h"
#include "WhichOfTheseDialog.h"
#include "toString.h"
#include "defines.h"

using namespace std;

class FormazioniFileReader {

public:
	FormazioniFileReader(QString);
	virtual ~FormazioniFileReader();
	void setPlayers( vector< vector< string > >);
	unsigned int execute();

private:
	void init();
	QString fileFormazioni;
	vector< vector< string > > allThePlayers;
	vector < string > findLevenstheins(string);
	string prepareStringToPresent(string, signed int);
};

#endif /* FORMAZIONIFILEREADER_H_ */
