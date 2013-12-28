wordPT(computador).
wordPT(portatil).
wordPT(enforcado).

wordEN(computer).
wordEN(laptop).
wordEN(hangman).

getWordByTopicAndLanguage(Topic, Language, Word):-
		findall(X, word(X,Topic,Language), WordList),
		chooseWordFromList(WordList, Word).

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
drawWordFromGuesses(Word, GuessList):-
	atom_length(Word, N),
	string_to_list(Word, WordL),
	drawWordFromGuesses(WordL, GuessList, N).
drawWordFromGuesses(W, GuessList, N):-
	drawWordFromGuesses(W, GuessList, 0, N).
drawWordFromGuesses(_, _, N, N):-nl.
drawWordFromGuesses(W, GuessList, X, N):-
	nth0(X, W, Char),
	(
	    (
	      member(Char, GuessList),
	      write(' '), put(Char), write(' ')
	    );
	    (
		write(' _ ')
	    )
	),
	Y is X+1,
	drawWordFromGuesses(W, GuessList, Y, N).

processInput(X):-
	atom_length(X,N), N =:= 1,
	atom_codes(X, [Y]),
	(
	    (Y =< 90, Y >= 65);
	    (Y =< 122, Y >= 97)
	).

%%The game loop
gameLoop(Word, GuessList):-
	gameLoop(Word, GuessList, 0).

gameLoop(Word, GuessList, 7):-
	write('You lost, hanged man!'),nl,
	write('The word was '), write(Word),nl,
	write('Your guesses: '), nl,
	string_to_list(Guesses,GuessList),
	write(Guesses).

gameLoop(Word, GuessList, N):-
	write('Please enter a letter: '),

	%%Read user input
	read(Guess),

	%%Check for valid input
	processInput(Guess),

	%%Obtain character code
	atom_codes(Guess, GuessCode),

	%%Add guess to list
	append(GuessList, GuessCode, NewGuessList),

	%%Convert word to list
	string_to_list(Word, WordAsList),

	%%Check if penalty applies
	(
	   \+subset(GuessCode, WordAsList)
	   -> Y is N+1;
	   Y is N
	),

	%%Draw word
	drawWordFromGuesses(Word, NewGuessList),

	%%Avoid backtracking
	!,

	%%Check if game is NOT won
	\+ subset(WordAsList, NewGuessList)
	%%If NOT won, try another guess
	-> nl, gameLoop(Word, NewGuessList, Y)
	%%If won
	; nl, write('You won!'), true.

%%The game itself, needs language specified
hangman(Language):-

	%%Choose a word by language
	chooseWordByLanguage(Language, Word),
	write('Word to guess: '),
	write(Word), nl,
	GuessList = [],
	!,
	gameLoop(Word, GuessList).
