@ECHO OFF
IF EXIST "C:\Program Files\toidua\toidua.exe" (
    DEL "C:\Program Files\toidua\toidua.exe"
    RMDIR "C:\Program Files\toidua"
    ECHO toidua has been uninstalled.
) ELSE (
    ECHO toidua is not installed.
)

SET /P DUMMY=Press ENTER to exit...
EXIT /b 0