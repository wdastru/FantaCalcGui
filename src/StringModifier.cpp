/*
 * StringModifier.cpp
 *
 *  Created on: 29/lug/2011
 *      Author: WAleViolaeIvan
 */

#include "StringModifier.h"
#include <QtCore/QDebug>

StringModifier * StringModifier::Inst() {
	if (pInstance == NULL) {
		pInstance = new StringModifier();
	}
	return pInstance;
}
StringModifier * StringModifier::pInstance = NULL;
StringModifier::StringModifier() {
}
StringModifier::~StringModifier() {
}
void StringModifier::onlyLettersBegin(std::string & str) {
	while ((str.at(0) < 'A' || (str.at(0) > 'Z' && str.at(0) < 'a')
			|| str.at(0) > 'z') && str.size() > 1)
		str.erase(0, 1);
}
void StringModifier::onlyLettersEnd(std::string & str) {
	while ((str.at(str.size() - 1) < 'A'
			|| (str.at(str.size() - 1) > 'Z' && str.at(str.size() - 1) < 'a')
			|| str.at(str.size() - 1) > 'z') && str.size() > 1
			&& str.at(str.size() - 1) != '\'')
		str.erase(str.size() - 1, 1);
}
void StringModifier::onlyLettersAndNumbersBegin(std::string & str) {
	//qDebug() << "In void StringModifier::onlyLettersAndNumbersBegin(std::string & str): str = #" + QString::fromStdString(str) + "#";
	while ( \
			(str.at(0) < '0' \
			|| (str.at(0) > '9' && str.at(0) < 'A') \
			|| (str.at(0) > 'Z' && str.at(0) < 'a') \
			|| str.at(0) > 'z') \
			&& str.size() >1
			) str.erase(0, 1);
	//qDebug() << "Out of void StringModifier::onlyLettersAndNumbersBegin(std::string & str): str = #" + QString::fromStdString(str) + "#";
}
void StringModifier::onlyLettersAndNumbersEnd(std::string & str) {
	//qDebug() << "In void void StringModifier::onlyLettersAndNumbersEnd(std::string & str): str = #" + QString::fromStdString(str) + "#";
	while ( \
			(str.at(str.size() - 1) < '0' \
			|| (str.at(str.size() - 1) > '9' && str.at(str.size() - 1) < 'A') \
			|| (str.at(str.size() - 1) > 'Z' && str.at(str.size() - 1) < 'a') \
			|| str.at(str.size() - 1) > 'z') \
			&& str.size() > 1
			) str.erase(str.size() - 1, 1);
	//qDebug() << "Out of void void StringModifier::onlyLettersAndNumbersEnd(std::string & str): str = #" + QString::fromStdString(str) + "#";
}
void StringModifier::removeNotAllowedChars(std::string & str) {
	for (size_t i = 0; i < str.size(); i++) {
		if (str.at(i) == '\\' || str.at(i) == '/' || str.at(i) == ':'
				|| str.at(i) == '*' || str.at(i) == '?' || str.at(i) == '\"'
				|| str.at(i) == '<' || str.at(i) == '>' || str.at(i) == '|')
			str.erase(i, 1);
	}
}
std::string StringModifier::onlySurname(std::string str) {
	while (((str.at(str.size() - 1) < 'A' || str.at(str.size() - 1) > 'Z')
			|| (str.at(str.size() - 2) < 'A' || str.at(str.size() - 2) > 'Z'))
			&& str.size() > 1 && str.at(str.size() - 1) != '\'')
		str.erase(str.size() - 1, 1);
	return str;
}
std::string StringModifier::onlyCapitalLetters(std::string str) {
	while ((str.at(0) < 'A' || str.at(0) > 'Z') && str.size() > 1)
		str.erase(0, 1);
	return str;
}
std::string StringModifier::centerString(std::string str, unsigned int i) {
	std::string centeredString = "";

	if (str.size() >= i) {
		centeredString = str;
		return centeredString;
	} else {
		centeredString = str;
		while (1) {
			centeredString = " " + centeredString;
			if (centeredString.size() == i)
				return centeredString;
			centeredString = centeredString + " ";
			if (centeredString.size() == i)
				return centeredString;
		}
	}
}
std::string StringModifier::leftString(std::string str, size_t i) {
	std::string leftString = "";

	if (str.size() >= i) {
		leftString = str;
		return leftString;
	} else {
		leftString = str;
		while (1) {
			leftString = leftString + " ";
			if (leftString.size() == i)
				return leftString;
		}
	}
}
QString StringModifier::leftQString(QString str, size_t i) {
	QString leftString = "";

	if (str.size() >= i) {
		leftString = str;
		return leftString;
	} else {
		leftString = str;
		while (1) {
			leftString = leftString + " ";
			if (leftString.size() == i)
				return leftString;
		}
	}
}
std::string StringModifier::rightString(std::string str, size_t i) {
	std::string rightString = "";

	if (str.size() >= i) {
		rightString = str;
		return rightString;
	} else {
		rightString = str;
		while (1) {
			rightString = " " + rightString;
			if (rightString.size() == i)
				return rightString;
		}
	}
}
QString StringModifier::rightQString(QString str, size_t i) {
	QString rightString = "";

	if (str.size() >= i) {
		rightString = str;
		return rightString;
	} else {
		rightString = str;
		while (1) {
			rightString = " " + rightString;
			if (rightString.size() == i)
				return rightString;
		}
	}
}
void StringModifier::modifyAccents(std::string & str) {
	for (unsigned int i = 0; i < str.size(); i++) {
		if (str.at(i) == -32 /* � */|| str.at(i) == -123) // il primo � il valore x word, notepad, scite
			str.replace(i, 1, "a'"); // il secondo il valore per l'editor di DOS

		else if (str.at(i) == -24 /* � */|| str.at(i) == -118)
			str.replace(i, 1, "e'");

		else if (str.at(i) == -20 /* � */|| str.at(i) == -115)
			str.replace(i, 1, "i'");

		else if (str.at(i) == -14 /* � */|| str.at(i) == -107)
			str.replace(i, 1, "o'");

		else if (str.at(i) == -7 /* � */|| str.at(i) == -105)
			str.replace(i, 1, "u'");
	}
}
void StringModifier::modifyCommas(std::string & str) {
	for (unsigned int i = 0; i < str.size(); i++) {
		if (str.at(i) == ',')
			str.replace(i, 1, ".");
	}
}
void StringModifier::toUpperCase(std::string & strToConvert) {
	//change each element of the string to upper case
	for (unsigned int i = 0; i < strToConvert.length(); i++) {
		strToConvert[i] = toupper(strToConvert[i]);
	}
}
void StringModifier::toLowerCase(std::string & strToConvert) {
	//change each element of the string to lower case
	for (unsigned int i = 0; i < strToConvert.length(); i++) {
		strToConvert[i] = tolower(strToConvert[i]);
	}
}
std::string StringModifier::msk(std::string riga, std::string delim,
		size_t idx) {
	size_t old_pos = 0;
	size_t new_pos;

	std::vector<std::string> v;
	v.clear();

	std::string token;

	while (1) {
		new_pos = riga.find_first_of(delim, old_pos); // trova la nuova posizione di uno dei delimitatori

		if (new_pos == std::string::npos) {
			token.assign(riga, old_pos, riga.size()); // se il delimitatore non viene trovato metti in token
			v.push_back(token); // tutto ci� che rimane della riga e vai alla prossima riga

			break;
		}

		if (new_pos == old_pos) // se la nuova posizione e' contigua alla vecchia incrementa la posizione e continua
				{
			old_pos++; //                  ^
			continue; //                  |
		} //                  |
		  //                  |
		token.assign(riga, old_pos, new_pos - old_pos); //                  |
		v.push_back(token); //                  |
							//                  |
		old_pos = ++new_pos; // la "nuova" vecchia posizione e' 1 in piu' della nuova attuale

	}

	if ((idx < 0) || (idx > v.size() - 1))
		return "TnotF!";

	else
		return v.at(idx);

}

void StringModifier::fixSlashes(QString & qString) {
#ifdef WIN32
	qString.replace("/", "\\");
#endif
#ifdef LINUX
	qString.replace("\\", "/");
#endif
}
