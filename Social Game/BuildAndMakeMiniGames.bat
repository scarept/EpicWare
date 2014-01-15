echo off

SET SOCIAL_PATH=SocialGame\SocialGame\images
SET BINARIES_PATH=MiniGames
SET HANGMAN_PATH=HangMan\WCFProlog\Release
SET LABYRINTH_PATH=Labyrinth\labyrinth\Release
SET TICTACTOE_PATH=TicTacToe\Release
SET OUTPUT_PATH=SocialGame\Release
SET OUTPUT_PATH2=SocialGame\Debug

MD %OUTPUT_PATH%
MD %OUTPUT_PATH2%

xcopy /I /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%HANGMAN_PATH%" ".\%OUTPUT_PATH%"
xcopy /I /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%HANGMAN_PATH%" ".\%OUTPUT_PATH2%"
xcopy /I /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%LABYRINTH_PATH%" ".\%OUTPUT_PATH%"
xcopy /I /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%LABYRINTH_PATH%" ".\%OUTPUT_PATH2%"
xcopy /I /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%TICTACTOE_PATH%" ".\%OUTPUT_PATH%"
xcopy /I /Y /E /exclude:excludedfileslist.txt ".\%BINARIES_PATH%\%TICTACTOE_PATH%" ".\%OUTPUT_PATH2%"
xcopy /I /Y /E /exclude:excludedfileslist2.txt ".\%SOCIAL_PATH%" ".\%OUTPUT_PATH%\images"
xcopy /I /Y /E /exclude:excludedfileslist2.txt ".\%SOCIAL_PATH%" ".\%OUTPUT_PATH2%\images"
pause