echo off

SET BINARIES_PATH=MiniGames
SET SOCIAL_PATH=SocialGame\SocialGame\images
SET HANGMAN_RES_PATH=HangMan\WCFProlog\WCFProlog\images
SET HANGMAN_RES_PATH2=HangMan\WCFProlog\WCFProlog\pl
SET LABYRINTH_RES_PATH=Labyrinth\labyrinth\labyrinth\images
SET LABYRINTH_RES_PATH2=Labyrinth\labyrinth\labyrinth\pl
SET TICTACTOE_RES_PATH=TicTacToe\TicTacToe\images
SET TICTACTOE_RES_PATH2=TicTacToe\TicTacToe\pl



SET HANGMAN_PATH=HangMan\WCFProlog\Release
SET LABYRINTH_PATH=Labyrinth\labyrinth\Release
SET TICTACTOE_PATH=TicTacToe\Release
SET OUTPUT_PATH=SocialGame\Release
SET OUTPUT_PATH2=SocialGame\Debug

MD %OUTPUT_PATH%
MD %OUTPUT_PATH%\images
MD %OUTPUT_PATH%\pl
pause
MD %OUTPUT_PATH2%
MD %OUTPUT_PATH2%\images
MD %OUTPUT_PATH2%\pl

xcopy /I /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%HANGMAN_PATH%" ".\%OUTPUT_PATH%"
xcopy /I /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%HANGMAN_PATH%" ".\%OUTPUT_PATH2%"
xcopy /I /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%LABYRINTH_PATH%" ".\%OUTPUT_PATH%"
xcopy /I /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%LABYRINTH_PATH%" ".\%OUTPUT_PATH2%"
xcopy /I /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%TICTACTOE_PATH%" ".\%OUTPUT_PATH%"
xcopy /I /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%TICTACTOE_PATH%" ".\%OUTPUT_PATH2%"
xcopy /I /Y /E /exclude:excludedfileslist2.txt ".\%SOCIAL_PATH%" ".\%OUTPUT_PATH%\images"
xcopy /I /Y /E /exclude:excludedfileslist2.txt ".\%SOCIAL_PATH%" ".\%OUTPUT_PATH2%\images"

xcopy /I /Y /E ".\%BINARIES_PATH%\%HANGMAN_RES_PATH%" ".\%OUTPUT_PATH%\images"
xcopy /I /Y /E ".\%BINARIES_PATH%\%HANGMAN_RES_PATH%" ".\%OUTPUT_PATH2%\images"
xcopy /I /Y /E ".\%BINARIES_PATH%\%HANGMAN_RES_PATH2%" ".\%OUTPUT_PATH%\pl"
xcopy /I /Y /E ".\%BINARIES_PATH%\%HANGMAN_RES_PATH2%" ".\%OUTPUT_PATH2%\pl"

xcopy /I /Y /E ".\%BINARIES_PATH%\%LABYRINTH_RES_PATH%" ".\%OUTPUT_PATH%\images"
xcopy /I /Y /E ".\%BINARIES_PATH%\%LABYRINTH_RES_PATH%" ".\%OUTPUT_PATH2%\images"
xcopy /I /Y /E ".\%BINARIES_PATH%\%LABYRINTH_RES_PATH2%" ".\%OUTPUT_PATH%\pl"
xcopy /I /Y /E ".\%BINARIES_PATH%\%LABYRINTH_RES_PATH2%" ".\%OUTPUT_PATH2%\pl"

xcopy /I /Y /E ".\%BINARIES_PATH%\%TICTACTOE_RES_PATH%" ".\%OUTPUT_PATH%\images"
xcopy /I /Y /E ".\%BINARIES_PATH%\%TICTACTOE_RES_PATH%" ".\%OUTPUT_PATH2%\images"
xcopy /I /Y /E ".\%BINARIES_PATH%\%TICTACTOE_RES_PATH2%" ".\%OUTPUT_PATH%\pl"
xcopy /I /Y /E ".\%BINARIES_PATH%\%TICTACTOE_RES_PATH2%" ".\%OUTPUT_PATH2%\pl"

xcopy /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%HANGMAN_PATH%" ".\%OUTPUT_PATH%"
xcopy /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%HANGMAN_PATH%" ".\%OUTPUT_PATH2%"

xcopy /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%LABYRINTH_PATH%" ".\%OUTPUT_PATH%"
xcopy /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%LABYRINTH_PATH%" ".\%OUTPUT_PATH2%"
xcopy /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%TICTACTOE_PATH%" ".\%OUTPUT_PATH%"
xcopy /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%TICTACTOE_PATH%" ".\%OUTPUT_PATH2%"
xcopy /Y /E /exclude:excludedfileslist2.txt ".\%SOCIAL_PATH%" ".\%OUTPUT_PATH%\images"
xcopy /Y /E /exclude:excludedfileslist2.txt ".\%SOCIAL_PATH%" ".\%OUTPUT_PATH2%\images"
pause