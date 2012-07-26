/*
 * test.cpp
 *
 *  Created on: Jul 26, 2012
 *      Author: waleviolaeivan
 */

 #include <QtTest/QtTest>

 class TestQString: public QObject
 {
     Q_OBJECT
 private slots:
     void toUpper();
 };

 void TestQString::toUpper()
 {
     QString str = "Hello";
     QCOMPARE(str.toUpper(), QString("HELLO"));
 }

 QTEST_MAIN(TestQString)
 #include "testqstring.moc"





