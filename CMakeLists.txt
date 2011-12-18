CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (FantaCalcGuiNew)

SET( SRCS src/main.cpp 
        src/IniFileManager.cpp
        src/CVersion.cpp
		src/ChooseFileFromAListDialog.cpp
		src/Downloader.cpp
		src/NoNetFileDialog.cpp 
        src/GazzettaFileReader.cpp 
        src/FormazioniFileReader.cpp 
        src/FileFormazioniViewer.cpp 
        src/Fanta.cpp        
        src/WhichOfTheseDialog.cpp
        src/WhichOfLevenshteinDialog.cpp
        src/Less25MinDialog.cpp
        src/IniFilePopulator.cpp
        src/Repository.cpp 
        src/StringModifier.cpp 
        src/httpwindow.cpp
        src/singletonQtLogger.cpp )
SET( HDRS src/CVersion.h
        src/IniFileManager.h
		src/ChooseFileFromAListDialog.h
		src/Downloader.h
		src/NoNetFileDialog.h 
        src/GazzettaFileReader.h
        src/FormazioniFileReader.h 
        src/FileFormazioniViewer.h
        src/Fanta.h        
        src/WhichOfTheseDialog.h
        src/Less25MinDialog.h
        src/WhichOfLevenshteinDialog.h
        src/IniFilePopulator.h
        src/Repository.h
        src/StringModifier.h 
        src/httpwindow.h
        src/singletonQtLogger.h )
SET( UIS  src/authenticationdialog.ui
		src/IniFilePopulator.ui
		src/FileFormazioniViewer.ui
        src/NoNetFileDialog.ui 
		src/singletonQtLogger.ui )
SET( RCS src/resources.qrc )

# enable warnings
ADD_DEFINITIONS( -Wall )

FIND_PACKAGE(Qt REQUIRED)
INCLUDE( ${QT_USE_FILE} )

#QT4_ADD_RESOURCES( RC_SRCS ${RCS} )
QT4_WRAP_UI( UI_HDRS ${UIS} )
QT4_WRAP_CPP( MOC_SRCS ${HDRS} )

INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} 
    C:/Qt/4.7.3/include/
    C:/Qt/4.7.3/include/QtNetwork 
    D:/Sorgenti/FantaCalcGuiNew/src  )
LINK_DIRECTORIES( C:/Qt/4.7.3/bin/ )

ADD_EXECUTABLE( FantaCalcGui ${SRCS} ${MOC_SRCS} ${UI_HDRS} ${RC_SRCS} )
TARGET_LINK_LIBRARIES( FantaCalcGui ${QT_LIBRARIES} QtNetwork4 QtTest4 )

