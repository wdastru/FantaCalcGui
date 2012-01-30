#ifndef _STRINGMODIFIERS_H
#define _STRINGMODIFIERS_H

void onlyLettersBegin(std::string & str) {
	while ((str.at(0) < 'A' || (str.at(0) > 'Z' && str.at(0) < 'a')
			|| str.at(0) > 'z') && str.size() > 1)
		str.erase(0, 1);
}

void onlyLettersEnd(std::string & str) {
	while ((str.at(str.size() - 1) < 'A' || (str.at(str.size() - 1) > 'Z'
			&& str.at(str.size() - 1) < 'a') || str.at(str.size() - 1) > 'z')
			&& str.size() > 1 && str.at(str.size() - 1) != '\'')
		str.erase(str.size() - 1, 1);
}

void onlyLettersAndNumbersBegin(std::string & str) {
	while ((str.at(0) < '0' || (str.at(0) > '9' && str.at(0) < 'A') || (str.at(
			0) > 'Z' && str.at(0) < 'a') || str.at(0) > 'z') && str.size() > 1)
		str.erase(0, 1);
}

void onlyLettersAndNumbersEnd(std::string & str) {
	while ((str.at(str.size() - 1) < '0' || (str.at(str.size() - 1) > '9'
			&& str.at(str.size() - 1) < 'A') || (str.at(str.size() - 1) > 'Z'
			&& str.at(str.size() - 1) < 'a') || str.at(str.size() - 1) > 'z')
			&& str.size() > 1)
		str.erase(str.size() - 1, 1);
}

void removeNotAllowedChars(std::string & str) {
	for (size_t i = 0; i < str.size(); i++) {
		if (str.at(i) == '\\' || str.at(i) == '/' || str.at(i) == ':'
				|| str.at(i) == '*' || str.at(i) == '?' || str.at(i) == '\"'
				|| str.at(i) == '<' || str.at(i) == '>' || str.at(i) == '|')
			str.erase(i, 1);
	}
}

std::string onlySurname(std::string str) {
	while (((str.at(str.size() - 1) < 'A' || str.at(str.size() - 1) > 'Z')
			|| (str.at(str.size() - 2) < 'A' || str.at(str.size() - 2) > 'Z'))
			&& str.size() > 1 && str.at(str.size() - 1) != '\'')
		str.erase(str.size() - 1, 1);
	return str;
}

std::string onlyCapitalLetters(std::string str) {
	while ((str.at(0) < 'A' || str.at(0) > 'Z') && str.size() > 1)
		str.erase(0, 1);
	return str;
}

std::string centerString(std::string str, size_t i) {
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

std::string leftString(std::string str, size_t i) {
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

std::string rightString(std::string str, size_t i) {
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

void modifyAccents(std::string & str) {
	for (unsigned int i = 0; i < str.size(); i++) {
		if (str.at(i) == -32 /* à */|| str.at(i) == -123) // il primo è il valore x word, notepad, scite
			str.replace(i, 1, "a'"); // il secondo il valore per l'editor di DOS

		else if (str.at(i) == -24 /* è */|| str.at(i) == -118)
			str.replace(i, 1, "e'");

		else if (str.at(i) == -20 /* ì */|| str.at(i) == -115)
			str.replace(i, 1, "i'");

		else if (str.at(i) == -14 /* ò */|| str.at(i) == -107)
			str.replace(i, 1, "o'");

		else if (str.at(i) == -7 /* ù */|| str.at(i) == -105)
			str.replace(i, 1, "u'");
	}
}

void modifyCommas(std::string & str) {
	for (unsigned int i = 0; i < str.size(); i++) {
		if (str.at(i) == ',')
			str.replace(i, 1, ".");
	}
}

#endif // _STRINGMODFIERS_H
