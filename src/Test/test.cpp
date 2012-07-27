/*
 * test.cpp
 *
 *  Created on: Jul 26, 2012
 *      Author: waleviolaeivan
 */

 #include "test.h"

Test::Test() {};

void Test::toUpper()
 {
     QString str = "Hello";
     QCOMPARE(str.toUpper(), QString("HELLO"));
 }





