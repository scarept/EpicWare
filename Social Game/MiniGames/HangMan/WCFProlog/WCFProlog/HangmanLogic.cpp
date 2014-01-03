#include "HangmanLogic.h"
#include "SocialGameService.xsd.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

HangmanLogic::HangmanLogic(){}

HangmanLogic::~HangmanLogic(){}

vector<int> HangmanLogic::validateGuess(char* guess, string word){

	PlTermv av(3);

	//Define the input variables
	av[0] = guess;
	av[1] = word.c_str();

	//Define the query
	PlQuery q("validateGuess", av);

	vector<int> indexList;

	while (q.next_solution()){

		//Define string to be tokenized and it's delimiters
		char * pch = strtok((char*)av[2], " ,'[]");

		while (pch != NULL)
		{
			//Add index to vector
			indexList.push_back((int)*pch);

			pch = strtok(NULL, " ,'[]");
		}
	}

	return indexList;
}

bool HangmanLogic::isGameWon(string word, char* guessList){

	//Get list length
	int n = strlen(guessList);

	//Conjure up a list from guesses
	string guesses = "[";
	for (int i = 0; i < n; i++){
		if (i == (n - 1)){
			guesses.push_back(guessList[i]);
			guesses.push_back(']');
		}
		else{
			guesses.push_back(guessList[i]); 
			guesses.push_back(',');
		}
	}

	PlTermv av(2);

	//Define the input, Word and GuessList
	av[0] = PlCompound(word.c_str());
	av[1] = PlCompound(guesses.c_str());

	//Define the query
	PlQuery q("gameWon", av);

	//Initialize the return variable
	bool state = false;
	
	//Summom predicate
	state = q.next_solution();

	return state;
}

vector<string> HangmanLogic::getTopicsByLanguage(string language){

	//Topic vector to fill and return
	vector<string> topics;

	PlTermv av(2);

	//Define input, the language
	av[0] = PlCompound(language.c_str());

	//Define the query
	PlQuery q("getTopicsByLanguage", av);
	
	while (q.next_solution()){
		
		//Define string to be tokenized and it's delimiters
		char * pch = strtok((char*)av[1], " ,'[]");

		while (pch != NULL)
		{
			//Add topic to vector
			topics.push_back((string) pch);

			pch = strtok(NULL, " ,'[]");
		}
	}

	return topics;
}

string HangmanLogic::chooseWord(string topic, string language){

	PlTermv av(3);
	
	//Define the input variables
	av[0] = topic.c_str();
	av[1] = language.c_str();

	//Define the query
	PlQuery q("getWordByTopicAndLanguage", av);

	string word;

	while (q.next_solution())
		word = (string)(char *)av[2];

	return word;
}

char* HangmanLogic::processWideChar(WCHAR* wc){

	int size;
	char DefChar = ' ';

	size = wcslen(wc);
	char *text = (char *)malloc(size);
	DefChar = ' ';
	WideCharToMultiByte(CP_ACP, 0, wc, -1, text, 260, &DefChar, NULL);

	return text;
}

void HangmanLogic::assertData(vector<Word> words){

	for each (Word w in words){

		char *text = processWideChar(w.text);
		char *topic = processWideChar(w.topic);
		char *language = processWideChar(w.language);

		joinConnection(text, topic, language);
	}
}

void HangmanLogic::joinConnection(char *text, char *category, char *language){

	PlTermv term(2);
	PlTermv stats(text, category, language);

	term[0] = PlCompound("word", stats);

	//cout << (char *)term[0] << endl;

	PlQuery query("asserta", term);
	query.next_solution();
}