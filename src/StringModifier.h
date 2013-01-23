/*
 * StringModifier.h
 *
 *  Created on: 29/lug/2011
 *      Author: WAleViolaeIvan
 */

#ifndef STRINGMODIFIER_H_
#define STRINGMODIFIER_H_

#include "string"
#include <QtCore/QString>
#include "vector"

class StringModifier {
public:
	StringModifier();
	virtual ~StringModifier();
	static StringModifier * Inst();
	void onlyLettersBegin(std::string & str);
	void onlyLettersEnd(std::string & str);
	void onlyLettersAndNumbersBegin(std::string & str);
	void onlyLettersAndNumbersEnd(std::string & str);
	void removeNotAllowedChars(std::string & str);
	std::string onlySurname(std::string str);
	std::string onlyCapitalLetters(std::string str);
	std::string centerString(std::string str, unsigned int i);
	std::string leftString(std::string str, size_t i);
	QString leftQString(QString str, size_t i);
	std::string rightString(std::string str, size_t i);
	QString rightQString(QString str, size_t i);
	void modifyAccents(std::string & str);
	void modifyCommas(std::string & str);
	void toUpperCase(std::string &);
	void toLowerCase(std::string &);
	std::string msk(std::string riga, std::string delim, size_t idx);
	void fixSlashes(QString & qString);

private:
	static StringModifier * pInstance;

};

#endif /* STRINGMODIFIER_H_ */
