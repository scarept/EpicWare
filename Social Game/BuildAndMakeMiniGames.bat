echo off

SET BINARIES_PATH=MiniGames
SET SOCIAL_PATH=SocialGame\SocialGame\images
SET HANGMAN_RES_PATH=HangMan\WCFProlog\WCFProlog\images
SET HANGMAN_RES_PATH2=HangMan\WCFProlog\WCFProlog\pl
SET LABYRINTH_RES_PATH=Labyrinth\labyrinth\labyrinth\images
SET LABYRINTH_RES_PATH2=Labyrinth\labyrinth\labyrinth\pl
SET TICTACTOE_RES_PATH=TicTacToe\TicTacToe\images
SET TICTACTOE_RES_PATH2=TicTacToe\TicTacToe\pl

SET HANGMAN_RELEASE_IMG=HangMan\WCFProlog\Release\images
SET HANGMAN_RELEASE_PL=HangMan\WCFProlog\Release\pl
SET HANGMAN_RELEASE2_IMG=HangMan\WCFProlog\Debug\images
SET HANGMAN_RELEASE2_PL=HangMan\WCFProlog\Debug\pl

SET LABYRINTH_RELEASE_IMG=Labyrinth\labyrinth\Release\images
SET LABYRINTH_RELEASE_PL=Labyrinth\labyrinth\Release\pl
SET LABYRINTH_RELEASE2_IMG=Labyrinth\labyrinth\Debug\images
SET LABYRINTH_RELEASE2_PL=Labyrinth\labyrinth\Debug\pl

SET TICTACTOE_RELEASE_IMG=TicTacToe\Release\images
SET TICTACTOE_RELEASE_PL=TicTacToe\Release\pl
SET TICTACTOE_RELEASE2_IMG=TicTacToe\Debug\images
SET TICTACTOE_RELEASE2_PL=TicTacToe\Debug\pl

SET HANGMAN_PATH=HangMan\WCFProlog\Release
SET LABYRINTH_PATH=Labyrinth\labyrinth\Release
SET TICTACTOE_PATH=TicTacToe\Release
SET HANGMAN_PATH_D=HangMan\WCFProlog\Debug
SET LABYRINTH_PATH_D=Labyrinth\labyrinth\Debug
SET TICTACTOE_PATH_D=TicTacToe\Debug

MD %BINARIES_PATH%\%HANGMAN_PATH_D%
MD %BINARIES_PATH%\%LABYRINTH_PATH_D%
MD %BINARIES_PATH%\%TICTACTOE_PATH_D%

SET OUTPUT_PATH=SocialGame\Release
SET OUTPUT_PATH2=SocialGame\Debug

MD %OUTPUT_PATH%
MD %OUTPUT_PATH%\images
MD %OUTPUT_PATH%\pl

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

xcopy /Y /E ".\%BINARIES_PATH%\%HANGMAN_RES_PATH%" ".\%BINARIES_PATH%\%HANGMAN_RELEASE_IMG%"
xcopy /Y /E ".\%BINARIES_PATH%\%HANGMAN_RES_PATH2%" ".\%BINARIES_PATH%\%HANGMAN_RELEASE_PL%"
xcopy /Y /E ".\%BINARIES_PATH%\%HANGMAN_RES_PATH%" ".\%BINARIES_PATH%\%HANGMAN_RELEASE2_IMG%"
xcopy /Y /E ".\%BINARIES_PATH%\%HANGMAN_RES_PATH2%" ".\%BINARIES_PATH%\%HANGMAN_RELEASE2_PL%"

xcopy /Y /E ".\%BINARIES_PATH%\%LABYRINTH_RES_PATH%" ".\%BINARIES_PATH%\%LABYRINTH_RELEASE_IMG%"
xcopy /Y /E ".\%BINARIES_PATH%\%LABYRINTH_RES_PATH2%" ".\%BINARIES_PATH%\%LABYRINTH_RELEASE_PL%"
xcopy /Y /E ".\%BINARIES_PATH%\%LABYRINTH_RES_PATH%" ".\%BINARIES_PATH%\%LABYRINTH_RELEASE2_IMG%"
xcopy /Y /E ".\%BINARIES_PATH%\%LABYRINTH_RES_PATH2%" ".\%BINARIES_PATH%\%LABYRINTH_RELEASE2_PL%"

xcopy /Y /E ".\%BINARIES_PATH%\%TICTACTOE_RES_PATH%" ".\%BINARIES_PATH%\%TICTACTOE_RELEASE_IMG%"
xcopy /Y /E ".\%BINARIES_PATH%\%TICTACTOE_RES_PATH2%" ".\%BINARIES_PATH%\%TICTACTOE_RELEASE_PL%"
xcopy /Y /E ".\%BINARIES_PATH%\%TICTACTOE_RES_PATH%" ".\%BINARIES_PATH%\%TICTACTOE_RELEASE2_IMG%"
xcopy /Y /E ".\%BINARIES_PATH%\%TICTACTOE_RES_PATH2%" ".\%BINARIES_PATH%\%TICTACTOE_RELEASE2_PL%"

pause