#ifndef _TOSTRING_H
#define _TOSTRING_H

#include <sstream>

namespace my {
	template<typename T> std::string toString(const T & value) {
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}
}
#endif
