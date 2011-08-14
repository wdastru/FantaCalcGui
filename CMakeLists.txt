CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (FantaCalcGuiNew)

SET( SRCS src/main.cpp 
        src/IniFileManager.cpp
        src/httpwindow.cpp
		src/CVersion.cpp
		src/ChooseFileFromAListDialog.cpp
		src/UseTheNetDialog.cpp
		src/NoNetFileDialog.cpp 
        src/GazzettaFileReader.cpp 
        src/FormazioniFileReader.cpp 
        src/Fanta.cpp        
        src/WhichOfTheseDialog.cpp
        src/WhichOfLevenshteinDialog.cpp
        src/Less25MinDialog.cpp
        src/StringModifier.cpp )
SET( HDRS src/CVersion.h
        src/IniFileManager.h
		src/httpwindow.h
        src/ChooseFileFromAListDialog.h
		src/UseTheNetDialog.h
		src/NoNetFileDialog.h 
        src/GazzettaFileReader.h
        src/FormazioniFileReader.h 
        src/Fanta.h        
        src/WhichOfTheseDialog.h
        src/Less25MinDialog.h
        src/WhichOfLevenshteinDialog.h
        src/StringModifier.h )
SET( UIS  src/authenticationdialog.ui
		src/UseTheNetDialog.ui
		src/NoNetFileDialog.ui  )
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
    D:/Sorgenti/FantaCalcGuiNew/src 
    D:/Sorgenti/singletonQtLogger_CMake/src 
    D:/Sorgenti/singletonQtLogger_CMake/build )
LINK_DIRECTORIES( C:/Qt/4.7.3/bin/
    D:/Sorgenti/singletonQtLogger_CMake/build )

ADD_EXECUTABLE( FantaCalcGui ${SRCS} ${MOC_SRCS} ${UI_HDRS} ${RC_SRCS} )
TARGET_LINK_LIBRARIES( FantaCalcGui ${QT_LIBRARIES} QtNetwork4 QtTest4 SingletonQtLoggerShared )

