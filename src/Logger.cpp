/*
 * Logger.cpp
 *
 *  Created on: 19/nov/2011
 *      Author: WAleViolaeIvan
 */

#include "Logger.h"
#include "defines.h"

Logger::Logger() {
	// TODO Auto-generated constructor stub
	this->version = "v0.2 build 14";
	this->ui.label->setText(
			"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
				"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
				"p, li { white-space: pre-wrap; }\n"
				"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
				"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; color:#ff0000;\">FantaCalcGui</span></p><p>"
					+ this->version + "</p></body></html>");
	this->ui.setupUi(this);
	this->show();
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}
