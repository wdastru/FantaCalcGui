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
#include "singletonQtLogger.h"
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
			std::vector<std::vector<std::string> > &);
	void execute();
	void printTitolo2(std::string);
	void printTitolo3(std::string);

private:
	QString fileFormazioni;
	std::vector<std::vector<std::string> > allThePlayers;
};

#endif /* FORMAZIONIFILEREADER_H_ */
