CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (FantaCalcGuiNew)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

SET (QT_USE_QTNETWORK TRUE)
SET (QT_USE_QTXML TRUE)

SET( SRCS 
        src/main.cpp 
        src/IniFileManager.cpp
        src/ChooseFileFromAListDialog.cpp
        src/Downloader.cpp
        src/NoNetFileDialog.cpp 
        src/GazzettaFileReader.cpp 
        src/FormazioniFileReader.cpp 
        src/FileFormazioniViewer.cpp 
        src/Fanta.cpp        
        src/WhichOfTheseDialog.cpp
        src/WhichOfLevenshteinDialog.cpp
        src/IniFilePopulator.cpp
        src/Repository.cpp 
        src/StringModifier.cpp 
        src/httpwindow.cpp
        src/singletonQtLogger.cpp
        src/resources.rc )
SET( HDRS 
        src/ChooseFileFromAListDialog.h
        src/Downloader.h
        src/NoNetFileDialog.h  
        src/FileFormazioniViewer.h
        src/WhichOfTheseDialog.h
        src/WhichOfLevenshteinDialog.h
        src/IniFilePopulator.h
        src/httpwindow.h
        src/singletonQtLogger.h )
SET( UIS  
        src/authenticationdialog.ui
    		src/IniFilePopulator.ui
    		src/FileFormazioniViewer.ui
        src/NoNetFileDialog.ui
        src/singletonQtLogger.ui )

QT4_WRAP_UI( UI_HDRS ${UIS} )
QT4_WRAP_CPP( MOC_SRCS ${HDRS} )

INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} )

ADD_EXECUTABLE( FantaCalcGui ${SRCS} ${MOC_SRCS} ${UI_HDRS} )

TARGET_LINK_LIBRARIES( FantaCalcGui ${QT_LIBRARIES} ${QT_QTNETWORK_LIBRARIES} ${QT_QTXML_LIBRARIES} )
