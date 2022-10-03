@ECHO OFF
ECHO compiling...
IF NOT  EXIST bin\ (
    MKDIR bin 
)
IF NOT EXIST obj\ (
    MKDIR obj
)

g++ src\main.cpp -o .\obj\toidua.o
g++ obj\toidua.o -o .\bin\toidua.exe
ECHO cloning into "C:\Program Files\toidua"

IF NOT EXIST "c:\Program Files\toidua\" (
    MKDIR "c:\Program Files\toidua"
)

COPY ".\bin\toidua.exe" "c:\Program Files\toidua\toidua.exe"
ECHO adding to path...
IF EXIST "c:\Program Files\toidua" SET PATH=%PATH%;"c:\Program Files\toidua"
ECHO done!
ECHO Clean Up? (y\n)
SET /P clean=""
GOTO :CHECK

:CLEAN_UP_FUNC
ECHO cleaning up...
DEL .\bin\toidua.exe
DEL .\obj\toidua.o
RMDIR .\bin
RMDIR .\obj
ECHO done cleaning up!
goto :END

:CHECK

IF %clean% == y (
    GOTO :CLEAN_UP_FUNC
)
IF %clean% == Y (
    GOTO :CLEAN_UP_FUNC
)

:END

SET /P DUMMY=Press ENTER to continue...
EXIT /b 0