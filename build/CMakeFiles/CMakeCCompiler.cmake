SET(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
SET(CMAKE_C_COMPILER_ARG1 "")
SET(CMAKE_C_COMPILER_ID "GNU")
SET(CMAKE_C_PLATFORM_ID "MinGW")

SET(CMAKE_AR "C:/MinGW/bin/ar.exe")
SET(CMAKE_RANLIB "C:/MinGW/bin/ranlib.exe")
SET(CMAKE_LINKER "C:/MinGW/bin/ld.exe")
SET(CMAKE_COMPILER_IS_GNUCC 1)
SET(CMAKE_C_COMPILER_LOADED 1)
SET(CMAKE_COMPILER_IS_MINGW 1)
SET(CMAKE_COMPILER_IS_CYGWIN )
IF(CMAKE_COMPILER_IS_CYGWIN)
  SET(CYGWIN 1)
  SET(UNIX 1)
ENDIF(CMAKE_COMPILER_IS_CYGWIN)

SET(CMAKE_C_COMPILER_ENV_VAR "CC")

IF(CMAKE_COMPILER_IS_MINGW)
  SET(MINGW 1)
ENDIF(CMAKE_COMPILER_IS_MINGW)
SET(CMAKE_C_COMPILER_ID_RUN 1)
SET(CMAKE_C_SOURCE_FILE_EXTENSIONS c)
SET(CMAKE_C_IGNORE_EXTENSIONS h;H;o;O;obj;OBJ;def;DEF;rc;RC)
SET(CMAKE_C_LINKER_PREFERENCE 10)

# Save compiler ABI information.
SET(CMAKE_C_SIZEOF_DATA_PTR "4")
SET(CMAKE_C_COMPILER_ABI "")

IF(CMAKE_C_SIZEOF_DATA_PTR)
  SET(CMAKE_SIZEOF_VOID_P "${CMAKE_C_SIZEOF_DATA_PTR}")
ENDIF(CMAKE_C_SIZEOF_DATA_PTR)

IF(CMAKE_C_COMPILER_ABI)
  SET(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_C_COMPILER_ABI}")
ENDIF(CMAKE_C_COMPILER_ABI)

SET(CMAKE_C_HAS_ISYSROOT "")


SET(CMAKE_C_IMPLICIT_LINK_LIBRARIES "mingw32;moldname;mingwex;msvcrt;user32;kernel32;advapi32;shell32;mingw32;moldname;mingwex;msvcrt")
SET(CMAKE_C_IMPLICIT_LINK_DIRECTORIES "c:/MinGW/lib/gcc/mingw32/4.4.0;c:/MinGW/lib/gcc;c:/MinGW/mingw32/lib;c:/MinGW/lib")
