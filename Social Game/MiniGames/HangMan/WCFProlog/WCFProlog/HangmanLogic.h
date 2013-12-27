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
#include "schemas.microsoft.com.2003.10.Serialization.xsd.h"
#include "tempuri.org.xsd.h"
#include "tempuri.org.wsdl.h"
#include "SocialGameService.xsd.h"
#include <vector>

using namespace std;

class HangmanLogic{
public:
	HangmanLogic();
	~HangmanLogic();

	void assertWord(char *text, char *category, char *language);
	void assertData(vector<Word> words);
	void joinConnection(char *, char *, char *);
	void chooseWord(string language, string topic);
};

#endif