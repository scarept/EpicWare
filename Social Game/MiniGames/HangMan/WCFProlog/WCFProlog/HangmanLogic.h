#ifndef CREATESTATEMENT_H
#define CREATESTATEMENT_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <SWI-Prolog.h>
#include <SWI-Stream.h>
#include <SWI-cpp.h>
#include <string>
#include "WebServices.h"
#include <EpicService\schemas.microsoft.com.2003.10.Serialization.xsd.h>
#include <EpicService\schemas.microsoft.com.2003.10.Serialization.Arrays.xsd.h>
#include <EpicService\tempuri.org.xsd.h>
#include <EpicService\tempuri.org.wsdl.h>
#include <EpicService\EpicWareWeb.xsd.h>
#include <EpicService\EpicWareWeb.Models.xsd.h>
#include <vector>

using namespace std;

class HangmanLogic{
public:
	HangmanLogic();
	~HangmanLogic();
	/*
	Validates a user's guess, returns the indexes in Word where Guess is found
	Index starts at 0
	*/
	vector<int> validateGuess(char* guess, string word);

	/*
	Treats and then asserts word facts into the prolog engine from a Word vector
	*/
	void assertData(vector<Word> words);

	/*
	Assert a single word fact into the prolog engine from the provided text, category and language
	*/
	void joinConnection(char *text, char *category, char *language);

	/*
	Request a new random word from the topic and language in play
	*/
	string chooseWord(string language, string topic);

	/*
	Auxiliary method that provides easy conversion from a WCHAR* to a char*
	*/
	char* processWideChar(WCHAR* wc);

	/*
	Retrieve every topic from a specified language
	*/
	vector<string> getTopicsByLanguage(string language);

	/*
	Determine whether the game is won from the word and guesses in play
	*/
	bool isGameWon(string word, char* guessList);
};

#endif