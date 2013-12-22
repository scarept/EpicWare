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
#include <vector>

using namespace std;

struct Word
{
	char text[80], topic[80], language[80];
};

class CCreateStatement{
public:
	CCreateStatement();
	~CCreateStatement();

	void assertData(vector<Word> *);
	void joinConnection(char *, char *, char *); //CHANGE HERE!
};

#endif