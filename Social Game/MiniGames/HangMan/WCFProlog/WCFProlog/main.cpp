#include <stdlib.h>
#include <string>
#include <iostream>
#include "Hangman.h"
#include <WCF\WCF.h>
#include <SWI-Prolog\include\SWI-Prolog.h>
#include <SWI-Prolog\include\SWI-Stream.h>
#include <SWI-Prolog\include\SWI-cpp.h>
#include <thread>

#pragma comment(linker, "/subsystem:\"windows\" \
	/entry:\"mainCRTStartup\"")

int main(int argc, char** argv)
{
	CHangman hm;
	hm.startGame(argc, argv);

	return 1;
}