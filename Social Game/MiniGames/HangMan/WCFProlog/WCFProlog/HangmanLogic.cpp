#include "HangmanLogic.h"
#include "SocialGameService.xsd.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

HangmanLogic::HangmanLogic(){}


HangmanLogic::~HangmanLogic(){}

void HangmanLogic::chooseWord(string topic, string language){

	PlTermv av(3);
	
	av[0] = topic.c_str();
	av[1] = language.c_str();

	PlQuery q("getWordByTopicAndLanguage", av);
	while (q.next_solution())
		cout << (char *)av[2] << endl;
}

void HangmanLogic::assertData(vector<Word> words){

	for each (Word w in words){

		int size;
		char DefChar = ' ';

		size = wcslen(w.text);
		char *text = (char *)malloc(size);
		DefChar = ' ';
		WideCharToMultiByte(CP_ACP, 0, w.text, -1, text, 260, &DefChar, NULL);

		size = wcslen(w.topic);
		char *topic = (char *)malloc(size);
		DefChar = ' ';
		WideCharToMultiByte(CP_ACP, 0, w.topic, -1, topic, 260, &DefChar, NULL);

		size = wcslen(w.language);
		char *language = (char *)malloc(size);
		DefChar = ' ';
		WideCharToMultiByte(CP_ACP, 0, w.language, -1, language, 260, &DefChar, NULL);

		joinConnection(text, topic, language);
	}
}

void HangmanLogic::joinConnection(char *text, char *category, char *language){

	PlTermv term(2);
	PlTermv stats(text, category, language);
	term[0] = PlCompound("word", stats);
	cout << (char *)term[0] << endl;
	PlQuery query("asserta", term);
	query.next_solution();
}