/*
 * boolToString.h
 *
 *  Created on: 12/gen/2011
 *      Author: Cretino
 */

#ifndef BOOLTOQSTRING_H_
#define BOOLTOQSTRING_H_

#include <QString>

namespace my {
std::string boolToString(bool boolean) {
	if (boolean)
		return "TRUE";
	else
		return "FALSE";
}

QString boolToQString(bool boolean) {
	if (boolean)
		return "TRUE";
	else
		return "FALSE";
}
}
#endif /* BOOLTOQSTRING_H_ */
