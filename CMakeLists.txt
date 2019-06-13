CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (FantaCalcGuiNew)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

SET (QT_USE_QTNETWORK TRUE)
SET (QT_USE_QTXML TRUE)

# Get the latest abbreviated commit hash of the working branch
EXECUTE_PROCESS(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the tag of the current commit (if any)
EXECUTE_PROCESS(
  COMMAND git describe --tags --exact-match
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_TAG
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

SET (REVISION ${GIT_COMMIT_HASH})
SET (VERSION ${GIT_TAG})

CONFIGURE_FILE(src/revision.h.in revision.h @ONLY)
CONFIGURE_FILE(src/version.h.in version.h @ONLY)

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
        src/MatchChooserCamp.cpp
        src/MatchChooserCoppa.cpp
        src/UpdatesChooser.cpp
        src/RinviateDialog.cpp
        src/resources.rc )
		
SET( HDRS 
        src/ChooseFiles.h
        src/Downloader.h
        src/NoNetFileDialog.h  
        src/FileFormazioniViewer.h
        src/FileFormazioniReader.h
        src/IniFilePopulator.h
        src/httpwindow.h
        src/MatchChooserCamp.h
        src/MatchChooserCoppa.h
        src/UpdatesChooser.h
        src/RinviateDialog.h
        src/singletonQtLogger.h )
        
SET( UIS  
        src/authenticationdialog.ui
        src/ChooseFiles.ui
        src/IniFilePopulator.ui
        src/FileFormazioniViewer.ui
        src/NoNetFileDialog.ui
        src/MatchChooserCamp.ui
        src/MatchChooserCoppa.ui
        src/UpdatesChooser.ui
        src/singletonQtLogger.ui
		src/RinviateDialog.ui )

SET( TEST_SRCS 
        src/FCGTest.cpp
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
        src/MatchChooserCamp.cpp
        src/MatchChooserCoppa.cpp
        src/UpdatesChooser.cpp
        src/singletonQtLogger.cpp )

QT4_WRAP_UI( UI_HDRS ${UIS} )
QT4_WRAP_CPP( MOC_SRCS ${HDRS} )

INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} )

ADD_EXECUTABLE( FantaCalcGui ${SRCS} ${MOC_SRCS} ${UI_HDRS} )
TARGET_LINK_LIBRARIES( FantaCalcGui ${QT_LIBRARIES} ${QT_QTNETWORK_LIBRARIES} ${QT_QTXML_LIBRARIES} )

ADD_EXECUTABLE( FCGTest ${TEST_SRCS}  ${MOC_SRCS} ${UI_HDRS} )
TARGET_LINK_LIBRARIES( FCGTest ${QT_LIBRARIES} ${QT_QTTEST_LIBRARIES} ${QT_QTNETWORK_LIBRARIES} ${QT_QTXML_LIBRARIES} )

