#ifndef _TOSTRING_H
#define _TOSTRING_H

#include <sstream>
#include <QtCore/QString>

namespace my {
template<typename T> std::string toString(const T & value) {
	std::ostringstream oss;
	oss << value;
	return oss.str();
}
template<typename T> QString toQString(const T & value) {
	std::ostringstream oss;
	oss << value;
	return QString::fromStdString(oss.str());
}
}
#endif
