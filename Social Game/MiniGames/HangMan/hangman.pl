wordPT(computador).
wordPT(portatil).
wordPT(enforcado).

wordEN(computer).
wordEN(laptop).
wordEN(hangman).

%%Picks word dictionary from specified language
%%English
getWordListByLanguage('EN', WordList):-
	findall(X, wordEN(X), WordList).
%%Portuguese
getWordListByLanguage('PT', WordList) :-
	findall(X, wordPT(X), WordList).
%%Default (English)
getWordListByLanguage(_, WordList) :-
	findall(X, wordEN(X), WordList).

%%Chooses a random word from a specified language
chooseWordByLanguage(Language, Word):-
	getWordListByLanguage(Language, WordList), !,
	chooseWordFromList(WordList, Word).

chooseWordFromList([], []).
chooseWordFromList(List, Word):-
	length(List, N),
	random(0, N, Index),
	nth0(Index, List, Word).

%%Draws word from guesses made
%TODO
drawWordStatus(W, G):-atom_length(W, N), ciclo(W, N).

ciclo(W, N):-ciclo(W, 0, N).
ciclo(_, N, N):-nl.
ciclo(W, X, N):-Y is X+1, write(' _ '), ciclo(W, Y, N).

processInput(X):-atom_length(X,1),
	(X >= 'A', X =< 'Z');(X >= 'a', X =< 'z').

%%The game loop
%TODO
gameLoop(Word, GuessList):-read(Guess).

%%The game itself, needs language specified
beginGame(Language):-chooseWordByLanguage(Language, Word),
	write(Word), nl,
	GuessList = [],
	drawWordStatus(Word, GuessList),
	gameLoop(Word, GuessList).

