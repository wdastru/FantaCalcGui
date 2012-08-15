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
        src/ChooseFiles.cpp
        src/Downloader.cpp
        src/NoNetFileDialog.cpp 
        src/GazzettaFileReader.cpp 
        src/FileFormazioniViewer.cpp 
        src/FileFormazioniReader.cpp 
        src/Fanta.cpp        
        src/IniFilePopulator.cpp
        src/Repository.cpp 
        src/StringModifier.cpp 
        src/httpwindow.cpp
        src/singletonQtLogger.cpp
        src/resources.rc )
		
SET( HDRS 
        src/ChooseFiles.h
        src/Downloader.h
        src/NoNetFileDialog.h  
        src/FileFormazioniViewer.h
        src/FileFormazioniReader.h
        src/IniFilePopulator.h
        src/httpwindow.h
        src/singletonQtLogger.h )
SET( UIS  
        src/authenticationdialog.ui
    	src/ChooseFiles.ui
        src/IniFilePopulator.ui
    	src/FileFormazioniViewer.ui
        src/NoNetFileDialog.ui
        src/singletonQtLogger.ui )

SET( TEST_SRCS 
		src/Test/test.cpp
        src/singletonQtLogger.cpp
        src/Fanta.cpp        
        src/Repository.cpp 
        src/StringModifier.cpp )

QT4_WRAP_UI( UI_HDRS ${UIS} )
QT4_WRAP_CPP( MOC_SRCS ${HDRS} )

QT4_WRAP_CPP( MOC_TEST_SRCS ${TEST_HDRS} )

INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} )

ADD_EXECUTABLE( FantaCalcGui ${SRCS} ${MOC_SRCS} ${UI_HDRS} )
TARGET_LINK_LIBRARIES( FantaCalcGui ${QT_LIBRARIES} ${QT_QTNETWORK_LIBRARIES} ${QT_QTXML_LIBRARIES} )

ADD_EXECUTABLE( test ${TEST_SRCS} ${MOC_TEST_SRCS} )
TARGET_LINK_LIBRARIES( test ${QT_LIBRARIES} ${QT_QTTEST_LIBRARIES} )
