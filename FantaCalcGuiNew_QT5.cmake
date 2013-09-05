# FIND INCLUDES IN CORRESPONDING BUILD DIRECTORIES
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# INSTRUCT CMAKE TO RUN MOC AUTOMATICALLY WHEN NEEDED.
SET(CMAKE_AUTOMOC ON)

# FIND THE QTWIDGETS LIBRARY
FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Network)
FIND_PACKAGE(Qt5Xml)

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
        src/singletonQtLogger.ui )

SET( TEST_SRCS 
        src/test.cpp
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

# TELL CMAKE TO CREATE THE HELLOWORLD EXECUTABLE
ADD_EXECUTABLE(FantaCalcGui ${SRCS} ${MOC_SRCS} ${UI_HDRS})

# USE THE WIDGETS MODULE FROM QT 5.
QT5_USE_MODULES(FantaCalcGui Widgets Network Xml)

