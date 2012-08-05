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

#ifndef ERROR_STYLE
#define ERROR_STYLE(msg) <span style='color:#FF0000;'> ERROR : msg</span>
#endif /* ERROR_STYLE */

#ifndef UPDATE_STYLE
#define UPDATE_STYLE(msg) <span style='color:#00CC00; font-weight:bold'> UPDATE : msg</span>
#endif /* UPDATE_STYLE */

#ifndef WARNING_STYLE
#define WARNING_STYLE(msg) <span style='color:#FF8800;'> WARNING : msg</span>
#endif /* WARNING_STYLE */

#ifndef FATAL_STYLE
#define FATAL_STYLE(msg) <span style='color:#FF0000; font-weight:bold'> FATAL ERROR : msg</span>
#endif /* FATAL_STYLE */

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
#define UPDATE "UPDATE"
#define TOFILE  "FILE"
#endif /* TYPE_OF_LOG_MSG */

#ifndef THE_LOGGER
#define THE_LOGGER singletonQtLogger::Inst()
#endif /* THE_LOGGER */

#ifndef THE_MANAGER
#define THE_MANAGER IniFileManager::Inst()
#endif /* THE_MANAGER */

#ifndef THE_CONFIGURATOR
#define THE_CONFIGURATOR IniFilePopulator::Inst()
#endif /* THE_POPULATOR */

#ifndef THE_REPO
#define THE_REPO Repository::Inst()
#endif /* THE_REPO */

#ifndef THE_VIEWER
#define THE_VIEWER FileFormazioniViewer::Inst()
#endif /* THE_VIEWER */

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
#define PLAYER_OK 			    0
#define PLAYER_REPEATED 	    1
#define PLAYER_GDV_NO_GOAL 	    2
#define PLAYER_GDP_NO_GOAL 	    3
#define PLAYER_GDV_NOT_PLAYED 	4
#define PLAYER_GDP_NOT_PLAYED 	5
#define PLAYER_ERROR 			99
#endif /* ADDPLAYER_RETURN_CODES */

#ifndef FILEFORMREADER_RETURN_CODE
#define FILEFORMREADER_RETURN_CODE
#define FILEFORMREADER_OK					0
#define FILEFORMREADER_REPEATED				1
#define FILEFORMREADER_GDV_NO_GOAL			2
#define FILEFORMREADER_GDP_NO_GOAL			3
#define FILEFORMREADER_BAD_GAZ_FILE			4
#define FILEFORMREADER_NO_FORM_FILE			5
#define FILEFORMREADER_NO_PLAYER_FOUND		6
#define FILEFORMREADER_GENERIC_ERROR		7
#define FILEFORMREADER_GDV_NOT_PLAYED 		8
#define FILEFORMREADER_GDP_NOT_PLAYED 		9
#define FILEFORMREADER_GETITEMERR			10
#endif /* FILEFORMREADER_RETURN_CODE */

#ifndef FORMFILEVIEWER_RETURN_CODE
#define FORMFILEVIEWER_RETURN_CODE
#define FORMFILEVIEWER_CANCEL			0
#define FORMFILEVIEWER_OK				1
#endif /* FORMFILEVIEWER_RETURN_CODE */

#endif /* DEFINES_H_ */
