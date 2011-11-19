/*
 * defines.h
 *
 *  Created on: 25/dic/2010
 *      Author: Cretino
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#include <QtCore/QTime>
#include "toString.h"

#ifndef UPDATE_LOG_INFO
#define UPDATE_LOG_INFO(msg) pLogger->ui.plainTextEdit->appendHtml(" [&nbsp&nbspINFO] "+QTime::currentTime().toString("hh:mm:ss.zzz")+" : "+msg)
#endif /* UPDATE_LOG_INFO */

#ifndef UPDATE_LOG_FATAL
#define UPDATE_LOG_FATAL(msg) pLogger->ui.plainTextEdit->appendHtml("<span style='color:#FF0000'>[&nbspFATAL]</span> "+QTime::currentTime().toString("hh:mm:ss.zzz")+" : "+msg)
#endif /* UPDATE_LOG_FATAL */

#ifndef HOMEAWAY_BOX_IS_CHECKED
#define HOMEAWAY_BOX_IS_CHECKED		0
#endif /* HOMEAWAY_BOX_IS_CHECKED */

#ifndef NEUTRO_BOX_IS_CHECKED
#define NEUTRO_BOX_IS_CHECKED		1
#endif /* NEUTRO_BOX_IS_CHECKED */

#ifndef NO_BOX_IS_CHECKED
#define NO_BOX_IS_CHECKED			-1
#endif /* NO_BOX_IS_CHECKED */

#ifndef LOG
#define LOG singletonQtLogger::Inst()->Logging
#endif /* LOG */

#ifndef TYPE_OF_LOG_MSG
#define TYPE_OF_LOG_MSG
#define INFO  "INFO"
#define ERROR "ERROR"
#define FATAL "FATAL"
#define WARN  "WARN"
#define DEBUG "DEBUG"
#define TOFILE  "FILE"
#endif /* TYPE_OF_LOG_MSG */

#ifndef THE_LOGGER
//#define THE_LOGGER singletonQtLogger::Inst()
#define THE_LOGGER Logger::Inst()
#endif /* THE_LOGGER */

#ifndef STR_MOD
#define STR_MOD StringModifier::Inst()
#endif /* STR_MOD */

#ifndef FANTA
#define FANTA Fanta::Inst()
#endif /* FANTA */

#ifndef INI_FILE_MGR
#define INI_FILE_MGR IniFilemanager::Inst()
#endif /* INI_FILE_MGR */

#ifndef DELIM
#define DELIM "\t"
#endif /* DELIM */

#ifndef COLUMNS
#define COLUMNS
#define ColNomeCognome			1
#define ColSquadra 				2
#define ColRuolo 				3
#define ColFantaVotoGazzetta 	6
#define ColVotoGazzetta 		7
#define ColGoalFatti 			8
#define ColGoalSubiti 			8
#define ColAmm 					9
#define ColEsp 					10
#define ColRigore 				11
#define ColAutoreti 			12
#define ColAssist 				13
#define ColGoalDecVitt  		14 // non presente nel file gazzetta, ma aggiunto dal programma
#define ColGoalDecPar 			15 // non presente nel file gazzetta, ma aggiunto dal programma
#endif /* COLUMNS */

#ifndef ADDPLAYER_RETURN_CODES
#define ADDPLAYER_RETURN_CODES
#define PLAYER_OK 			0
#define PLAYER_REPEATED 	1
#define PLAYER_GDV_NO_GOAL 	2
#define PLAYER_GDP_NO_GOAL 	3
#endif /* ADDPLAYER_RETURN_CODES */

#ifndef FORMFILEREAD_RETURN_CODE
#define FORMFILEREAD_RETURN_CODE
#define FORMFILEREAD_OK					0
#define FORMFILEREAD_REPEATED			1
#define FORMFILEREAD_GDV_NO_GOAL		2
#define FORMFILEREAD_GDP_NO_GOAL		3
#define FORMFILEREAD_BAD_GAZ_FILE		4
#define FORMFILEREAD_NO_FORM_FILE		5
#define FORMFILEREAD_NO_PLAYER_FOUND	6
#endif /* FORMFILEREAD_RETURN_CODE */

#endif /* DEFINES_H_ */
