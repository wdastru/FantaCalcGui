/****************************************************************************
 **
 ** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:BSD$
 ** You may use this file under the terms of the BSD license as follows:
 **
 ** "Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 **   * Redistributions of source code must retain the above copyright
 **     notice, this list of conditions and the following disclaimer.
 **   * Redistributions in binary form must reproduce the above copyright
 **     notice, this list of conditions and the following disclaimer in
 **     the documentation and/or other materials provided with the
 **     distribution.
 **   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
 **     the names of its contributors may be used to endorse or promote
 **     products derived from this software without specific prior written
 **     permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include <iostream>

#include <QtTest/QtTest>
#include "../defines.h"
#include "../StringModifier.h"
#include "../Fanta.h"

class Test: public QObject {
Q_OBJECT
private slots:
	void onlyLettersBegin();
	void onlyLettersEnd();
	void onlyLettersAndNumbersBegin();
	void onlyLettersAndNumbersEnd();
	void removeNotAllowedChars();
	void onlySurname();
	void leftString();
	void leftQString();
	void LevenshteinDistance();
};

void Test::onlyLettersBegin() {
	std::string str = "123Hello";
	STR_MOD->onlyLettersBegin(str);
	QCOMPARE(QString::fromStdString(str), QString("Hello"));
}
void Test::onlyLettersEnd() {
	std::string str = "Hello:123";
	STR_MOD->onlyLettersEnd(str);
	QCOMPARE(QString::fromStdString(str), QString("Hello"));
}
void Test::onlyLettersAndNumbersBegin() {
	std::string str1 = ",, //1Hello";
	std::string str2 = ",, //Hello";
	STR_MOD->onlyLettersAndNumbersBegin(str1);
	STR_MOD->onlyLettersAndNumbersBegin(str2);
	QCOMPARE(QString::fromStdString(str1), QString("1Hello"));
	QCOMPARE(QString::fromStdString(str2), QString("Hello"));
}
void Test::onlyLettersAndNumbersEnd() {
	std::string str1 = "Hello1.. //";
	std::string str2 = "Hello.. //";
	STR_MOD->onlyLettersAndNumbersEnd(str1);
	STR_MOD->onlyLettersAndNumbersEnd(str2);
	QCOMPARE(QString::fromStdString(str1), QString("Hello1"));
	QCOMPARE(QString::fromStdString(str2), QString("Hello"));
}
void Test::removeNotAllowedChars() {
	std::string str = "\\/:*?\"<>|";
	STR_MOD->removeNotAllowedChars(str);
	QCOMPARE(QString::fromStdString(str), QString(""));
}
void Test::onlySurname() {
	std::string str1 = "824	DEL PIERO	JUVENTUS	A	1	19	6	6	0	0	0	0	0	0";
	std::string str2 = "204	ALVAREZ P.S.	CATANIA	D	1	6	5.5	6	0	-0.5	0	0	0	0";
	std::string str3 = "124	FREY S.	GENOA	P	1	11	4.5	6	-1	-0.5	0	0	0	0";
	std::string surname1 = STR_MOD->onlySurname(STR_MOD->msk(str1, DELIM, ColNomeCognome));
	std::string surname2 = STR_MOD->onlySurname(STR_MOD->msk(str2, DELIM, ColNomeCognome));
	std::string surname3 = STR_MOD->onlySurname(STR_MOD->msk(str3, DELIM, ColNomeCognome));
	QCOMPARE(QString::fromStdString(surname1), QString("DEL PIERO"));
	QCOMPARE(QString::fromStdString(surname2), QString("ALVAREZ"));
	QCOMPARE(QString::fromStdString(surname3), QString("FREY"));
}
void Test::leftString() {
	std::string str = "pippo";
	str = STR_MOD->leftString(str, 10);
	QCOMPARE(QString::fromStdString(str), QString("pippo     "));
}
void Test::leftQString() {
	QString qStr = "pippo";
	qStr = STR_MOD->leftQString(qStr, 10);
	QCOMPARE(qStr, QString("pippo     "));
}
void Test::LevenshteinDistance() {
	unsigned int distance = FANTA->LevenshteinDistance("pippo", "pippo");
	QCOMPARE(distance, 0);
}

QTEST_MAIN(Test)
#include "test.moc"

