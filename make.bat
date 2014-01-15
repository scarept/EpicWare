echo off

SET DEPENDENCIES_PATH=ExternalDependencies
SET FREEGLUT=freeGLUT\bin\freeglut.dll
SET PROLOG=SWI-Prolog
SET OUTPUT_PATH=Social Game\SocialGame\Release
SET OUTPUT_PATH2=Social Game\SocialGame\Debug

SET HANGMAN_PATH=Social Game\MiniGames\HangMan\WCFProlog\Release
SET HANGMAN_PATH2=Social Game\MiniGames\HangMan\WCFProlog\Debug
SET LABYRINTH_PATH=Social Game\MiniGames\Labyrinth\labyrinth\Release
SET LABYRINTH_PATH2=Social Game\MiniGames\Labyrinth\labyrinth\Debug
SET TICTACTOE_PATH=Social Game\MiniGames\TicTacToe\Release
SET TICTACTOE_PATH2=Social Game\MiniGames\TicTacToe\Debug

SET MINIGAMES_SCRIPT=BuildAndMakeMiniGames.bat

MD ".\%OUTPUT_PATH%"
MD ".\%OUTPUT_PATH2%"
MD ".\%OUTPUT_PATH%\library"
MD ".\%OUTPUT_PATH2%\library"
MD ".\%LABYRINTH_PATH%"
MD ".\%LABYRINTH_PATH2%"
MD ".\%LABYRINTH_PATH%\library"
MD ".\%LABYRINTH_PATH2%\library"
MD ".\%HANGMAN_PATH%"
MD ".\%HANGMAN_PATH2%"
MD ".\%HANGMAN_PATH%\library"
MD ".\%HANGMAN_PATH2%\library"
MD ".\%TICTACTOE_PATH%"
MD ".\%TICTACTOE_PATH2%"
MD ".\%TICTACTOE_PATH%\library"
MD ".\%TICTACTOE_PATH2%\library"

xcopy /D /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%OUTPUT_PATH%"
xcopy /D /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%OUTPUT_PATH2%"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\bin" ".\%OUTPUT_PATH%"
xcopy /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\bin" ".\%OUTPUT_PATH2%"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\library" ".\%OUTPUT_PATH%\library"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\library" ".\%OUTPUT_PATH2%\library"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\boot32.prc" ".\%OUTPUT_PATH%"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\boot32.prc" ".\%OUTPUT_PATH2%"

xcopy /D /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%LABYRINTH_PATH%"
xcopy /D /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%LABYRINTH_PATH2%"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\bin" ".\%LABYRINTH_PATH%"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\bin" ".\%LABYRINTH_PATH2%"
xcopy /D /Y ".\%DEPENDENCIES_PATH%\%PROLOG%\boot32.prc" ".\%LABYRINTH_PATH%"
xcopy /D /Y ".\%DEPENDENCIES_PATH%\%PROLOG%\boot32.prc" ".\%LABYRINTH_PATH2%"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\library" ".\%LABYRINTH_PATH%\library"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\library" ".\%LABYRINTH_PATH2%\library"

xcopy /D /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%HANGMAN_PATH%"
xcopy /D /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%HANGMAN_PATH2%"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\bin" ".\%HANGMAN_PATH%"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\bin" ".\%HANGMAN_PATH2%"
xcopy /D /Y ".\%DEPENDENCIES_PATH%\%PROLOG%\boot32.prc" ".\%HANGMAN_PATH%"
xcopy /D /Y ".\%DEPENDENCIES_PATH%\%PROLOG%\boot32.prc" ".\%HANGMAN_PATH2%"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\library" ".\%HANGMAN_PATH%\library"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\library" ".\%HANGMAN_PATH2%\library"

xcopy /D /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%TICTACTOE_PATH%"
xcopy /D /Y ".\%DEPENDENCIES_PATH%\%FREEGLUT%" ".\%TICTACTOE_PATH2%"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\bin" ".\%TICTACTOE_PATH%"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\bin" ".\%TICTACTOE_PATH2%"
xcopy /D /Y ".\%DEPENDENCIES_PATH%\%PROLOG%\boot32.prc" ".\%TICTACTOE_PATH%"
xcopy /D /Y ".\%DEPENDENCIES_PATH%\%PROLOG%\boot32.prc" ".\%TICTACTOE_PATH2%"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\library" ".\%TICTACTOE_PATH%\library"
xcopy /D /Y /E ".\%DEPENDENCIES_PATH%\%PROLOG%\library" ".\%TICTACTOE_PATH%\library"

CD ".\Social Game"
CALL %MINIGAMES_SCRIPT%