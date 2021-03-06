; Script generated by the HM NIS Edit Script Wizard.

; Qt
!define QT "C:\Qt\4.8.6\bin"
!define INSTALLER_PATH "D:\Sorgenti\FantaCalcGuiNew_Win32Build\installer"

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "FantaCalcGui"
!define PRODUCT_VERSION "v3.5.0"
!define PRODUCT_PUBLISHER "EPTADONE Software Inc."
!define PRODUCT_WEB_SITE "http://www.cim.unito.it/private/fantacalcio/"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\FantaCalcGui.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_STARTMENU_REGVAL "NSIS:StartMenuDir"
!define PRODUCT_OUTDIR "D:\Sorgenti\FantaCalcGuiNew\installer"

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\orange-install-nsis.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\orange-uninstall-nsis.ico"

; Language Selection Dialog Settings
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Start menu page
var ICONS_GROUP
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "FantaCalcGui ${PRODUCT_VERSION}"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_STARTMENU_REGVAL}"
!insertmacro MUI_PAGE_STARTMENU Application $ICONS_GROUP
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES

; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\FantaCalcGui.exe"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
;!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "Italian"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "${PRODUCT_OUTDIR}/${PRODUCT_NAME}_${PRODUCT_VERSION}_Setup.exe"
InstallDir "$PROGRAMFILES\FantaCalcGui"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite try
  File "${INSTALLER_PATH}\FantaCalcGui.exe"
  File "${INSTALLER_PATH}\libstdc++-6.dll"
  File "${INSTALLER_PATH}\libwinpthread-1.dll"
  File "${INSTALLER_PATH}\libgcc_s_dw2-1.dll"
  File "${INSTALLER_PATH}\QtCore4.dll"
  File "${INSTALLER_PATH}\QtGui4.dll"
  File "${INSTALLER_PATH}\QtNetwork4.dll"
  File "${INSTALLER_PATH}\QtXml4.dll"

; Shortcuts
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  CreateDirectory "$SMPROGRAMS\$ICONS_GROUP"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\FantaCalcGui.lnk" "$INSTDIR\FantaCalcGui.exe"
  CreateShortCut "$DESKTOP\FantaCalcGui.lnk" "$INSTDIR\FantaCalcGui.exe"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -AdditionalIcons
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Fantacalcio Home.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk" "$INSTDIR\uninst.exe"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\FantaCalcGui.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\FantaCalcGui.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
!insertmacro MUI_UNGETLANGUAGE
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  !insertmacro MUI_STARTMENU_GETFOLDER Application $ICONS_GROUP
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\QtNetwork4.dll"
  Delete "$INSTDIR\QtGui4.dll"
  Delete "$INSTDIR\QtCore4.dll"
  Delete "$INSTDIR\QtXml4.dll"
  Delete "$INSTDIR\libgcc_s_dw2-1.dll"
  Delete "$INSTDIR\libstdc++-6.dll"
  Delete "$INSTDIR\libwinpthread-1.dll"
  Delete "$INSTDIR\FantaCalcGui.exe"

; Windows XP
  Delete "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\Fantacalcio Home.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\FantaCalcGui.lnk"
  
; Windows 7
  Delete "%PROGRAMDATA%\Microsoft\Windows\Start Menu\Programs\$ICONS_GROUP\FantaCalcGui.lnk"
  Delete "%PROGRAMDATA%\Microsoft\Windows\Start Menu\Programs\$ICONS_GROUP\Uninstall.lnk"
  Delete "%PROGRAMDATA%\Microsoft\Windows\Start Menu\Programs\$ICONS_GROUP\Fantacalcio Home.lnk"

; Windows 8
  Delete "%PROGRAMDATA%\Microsoft\Windows\Start Menu\Programs\FantaCalcGui ${PRODUCT_VERSION}\FantaCalcGui.lnk"
  Delete "%PROGRAMDATA%\Microsoft\Windows\Start Menu\Programs\FantaCalcGui ${PRODUCT_VERSION}\Uninstall.lnk"
  Delete "%PROGRAMDATA%\Microsoft\Windows\Start Menu\Programs\FantaCalcGui ${PRODUCT_VERSION}\Fantacalcio Home.lnk"
  
  Delete "$DESKTOP\FantaCalcGui.lnk"

  RMDir "%PROGRAMDATA%\Microsoft\Windows\Start Menu\Programs\$ICONS_GROUP\"
  RMDir "$SMPROGRAMS\$ICONS_GROUP\"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd
