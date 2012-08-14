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

class Test: public QObject {
Q_OBJECT
private slots:
	void onlyLettersBegin();
	void onlyLettersEnd();
	void onlyLettersAndNumbersBegin();
	void onlyLettersAndNumbersEnd();
	void removeNotAllowedChars();

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
	std::string str = str1 + str2;
	QCOMPARE(QString::fromStdString(str), QString("1HelloHello"));
}
void Test::onlyLettersAndNumbersEnd() {
	std::string str1 = "Hello1.. //";
	std::string str2 = "Hello.. //";
	STR_MOD->onlyLettersAndNumbersEnd(str1);
	STR_MOD->onlyLettersAndNumbersEnd(str2);
	std::string str = str1 + str2;
	QCOMPARE(QString::fromStdString(str), QString("Hello1Hello"));
}
void Test::removeNotAllowedChars() {
	std::string str = "\\/:*?\"<>|";
	STR_MOD->removeNotAllowedChars(str);
	QCOMPARE(QString::fromStdString(str), QString(""));
}

QTEST_MAIN(Test)
#include "test.moc"

