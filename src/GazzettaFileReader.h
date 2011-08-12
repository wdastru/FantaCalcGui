/*
 * GazzettaFileReader.h
 *
 *  Created on: 28/lug/2011
 *      Author: WAleViolaeIvan
 */

#ifndef GAZZETTAFILEREADER_H_
#define GAZZETTAFILEREADER_H_

#include "singletonQtLogger.h"
#include "defines.h"

#include <fstream>
#include <QtCore/QString>
#include <vector>

class GazzettaFileReader {
public:
	GazzettaFileReader( QString );
	~GazzettaFileReader();
	std::vector < std::vector < std::string > > getOutput();
private:
	QString fileGazzetta;
};

#endif /* GAZZETTAFILEREADER_H_ */
