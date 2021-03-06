/*
 * GazzettaFileReader.cpp
 *
 *  Created on: 28/lug/2011
 *      Author: WAleViolaeIvan
 */

#define DO_DEBUG

#include <QtCore/QDebug>

#include "Fanta.h"
#include "GazzettaFileReader.h"
#include "StringModifier.h"

GazzettaFileReader::GazzettaFileReader(QString _fileGazzetta) {
//	LOG(DEB, "In GazzettaFileReader::GazzettaFileReader( ... ).");
	this->fileGazzetta = _fileGazzetta;
//	FANTA->setFileGazzetta(_fileGazzetta);
}

GazzettaFileReader::~GazzettaFileReader() {

}

std::vector<std::vector<std::string> > GazzettaFileReader::getOutput() {
	DEBUG(this->fileGazzetta.toStdString().c_str());

	std::ifstream fGaz(this->fileGazzetta.toStdString().c_str());

	if (!fGaz) {
		DEBUG("il file gazzetta  : " << this->fileGazzetta.toStdString().c_str() << " non esiste!");
		LOG(
				FATAL,
				"In GazzettaFileReader::getOutput() --> il file gazzetta  : "
						+ this->fileGazzetta + " non esiste!");
	}

	std::vector<std::vector<std::string> > Gazzetta;
	Gazzetta.resize(26);

	while (!fGaz.eof()) {
		std::string line;
		getline(fGaz, line);
		STR_MOD->modifyCommas(line);
		std::string tmpString;
		tmpString = line;

		for (signed int i = 0; i < 26; i++) {
			if (line.size() > 0) {
				STR_MOD->onlyLettersBegin(tmpString);
				if (tmpString[0] == (65 + i)) // separa in 26 vettori ( uno per ogni lettera iniziale del cognome del giocatore )
				{
					Gazzetta.at(i).push_back(line);
					break;
				}
			}
		}
	}
	fGaz.close();

	DEBUG("Out");

	return Gazzetta;
}
