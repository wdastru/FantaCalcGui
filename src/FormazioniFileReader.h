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

#include "Fanta.h"
#include "Logger.h"
#include "StringModifier.h"
#include "WhichOfTheseDialog.h"
#include "WhichOfLevenshteinDialog.h"
#include "toString.h"
#include "defines.h"

using namespace std;


class FormazioniFileReader {
public:
	FormazioniFileReader(QString);
	virtual ~FormazioniFileReader();
	void setPlayers(
			std::vector<std::vector<std::string> >);
	unsigned int execute();
//	void printTitolo2(std::string);
//	void printTitolo3(std::string);

private:
	QString fileFormazioni;
	std::vector<std::vector<std::string> > allThePlayers;
	std::vector < std::string > findLevenstheins(std::string);
	std::string prepareStringToPresent(std::string, signed int);
};

#endif /* FORMAZIONIFILEREADER_H_ */
