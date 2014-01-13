wordPT(computador).
wordPT(portatil).
wordPT(enforcado).

wordEN(computer).
wordEN(laptop).
wordEN(hangman).

gameWon(Word, GuessList):-

	%%Get GuessList length
	length(GuessList, N),

	%%Get Word as a list of codes
	string_to_list(Word, WordAsList),

	%%Initialize TempIndexList
	TempIndexList = [],

	%%Find all indexes
	gameWonLoop(GuessList, WordAsList, 0, N, TempIndexList, FinalIndexList),

	%%Discard repeated
	sort(FinalIndexList, ReallyFinalIndexList),

	%%Get Word length
	atom_length(Word, N1),

	NN1 is N1-1,
	%%Generate number list
	numlist(0, NN1, NumList),

	%%Check if game is won
	!, NumList = ReallyFinalIndexList.

gameWonLoop(GuessList, Word, N, N, IndexList, IndexList).
gameWonLoop(GuessList, Word, X, N, IndexList, FinalIndexList):-

        %%Get the guess, a char
	nth0(X, GuessList, Char),

	%%Obtain the indexes for which guess is valid
	validateGuess(Char, Word, NewIndexList),

	%%Add it to existing List
	append(NewIndexList, IndexList, TempIndexList),

	%%Increase guess counter
	Y is X + 1,

	gameWonLoop(GuessList, Word, Y, N, TempIndexList, FinalIndexList).



getTopicsByLanguage(Language,Topics):-findall(X, word(_,X,Language), TopicList),
	sort(TopicList, Topics).

getWordByTopicAndLanguage(Topic, Language, Word):-
		findall(X, word(X,Topic,Language), WordList),
		chooseWordFromList(WordList, Word).

%%Validates a user's guess
%% True if the Guess character is found (on the Word) in every index in IndexList
validateGuess(Guess, Word, IndexList):-

	        %%Get Word length
	        atom_length(Word, N),

		%%Get Word as a list of codes
		string_to_list(Word, WordAsList),

		%%Obtain Guess code
		atom_codes(Guess, GuessCode),

		%%Initialize list to store indexes
		TempIndexList = [],

		%%Retrieve IndexList
		checkWordForGuess(WordAsList, GuessCode, 0, N, TempIndexList, IndexList).

checkWordForGuess(_, _, N, N, IndexList, IndexList):-true.
checkWordForGuess(Word, Guess, X, N, TempIndexList, IndexList):-
	%%Get the Char that is at the Xth position of Word
	nth0(X, Word, Char),

	%%Write the Char
	%%put(Char),

	(
	    %%If Char at X is Guess
	    (
	      member(Char, Guess), !,
              append(TempIndexList, [X], NewIndexList),
	      Y is X + 1,
	      checkWordForGuess(Word, Guess, Y, N, NewIndexList, IndexList)
	    );
	    %%Else
	      Y is X + 1,
	      checkWordForGuess(Word, Guess, Y, N, TempIndexList, IndexList)
	).

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
