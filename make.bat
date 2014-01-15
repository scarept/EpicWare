echo off

SET DEPENDENCIES_PATH=ExternalDependencies
SET FREEGLUT=freeGLUT\bin\freeglut.dll
SET PROLOG=SWI-Prolog\bin
SET OUTPUT_PATH=Social Game\SocialGame\Release
SET OUTPUT_PATH2=Social Game\SocialGame\Debug

SET HANGMAN_PATH=HangMan\WCFProlog\Release
SET HANGMAN_PATH2=HangMan\WCFProlog\Debug
SET LABYRINTH_PATH=Labyrinth\labyrinth\Release
SET LABYRINTH_PATH2=Labyrinth\labyrinth\Debug
SET TICTACTOE_PATH=TicTacToe\Release
SET TICTACTOE_PATH2=TicTacToe\Debug

SET MINIGAMES_SCRIPT=BuildAndMakeMiniGames.bat

MD "%OUTPUT_PATH%"
MD "%OUTPUT_PATH2%"

xcopy /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%OUTPUT_PATH%"
xcopy /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%OUTPUT_PATH2%"
xcopy /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%" ".\%OUTPUT_PATH%"
xcopy /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%" ".\%OUTPUT_PATH2%"

xcopy /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%LABYRINTH_PATH%"
xcopy /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%LABYRINTH_PATH2%"
xcopy /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%" ".\%LABYRINTH_PATH%"
xcopy /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%" ".\%LABYRINTH_PATH2%"

xcopy /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%HANGMAN_PATH%"
xcopy /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%HANGMAN_PATH2%"
xcopy /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%" ".\%HANGMAN_PATH%"
xcopy /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%" ".\%HANGMAN_PATH2%"

xcopy /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%TICTACTOE_PATH%"
xcopy /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%TICTACTOE_PATH2%"
xcopy /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%" ".\%TICTACTOE_PATH%"
xcopy /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%" ".\%TICTACTOE_PATH2%"
CD ".\Social Game"
CALL %MINIGAMES_SCRIPT%