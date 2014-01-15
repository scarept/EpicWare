echo off

SET DEPENDENCIES_PATH=ExternalDependencies
SET FREEGLUT=freeGLUT\bin\freeglut.dll
SET PROLOG=SWI-Prolog\bin
SET OUTPUT_PATH=Social Game\SocialGame\Release
SET MINIGAMES_SCRIPT=BuildAndMakeMiniGames.bat
MD "%OUTPUT_PATH%"

xcopy /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%OUTPUT_PATH%"
xcopy /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%" ".\%OUTPUT_PATH%"
CD ".\Social Game"
CALL %MINIGAMES_SCRIPT%