#include <stdlib.h>
#include <string>
#include <iostream>
#include "Hangman.h"
#include "WCF.h"
#include <SWI-Prolog.h>
#include <SWI-Stream.h>
#include <SWI-cpp.h>

int main(int argc, char **argv){

	_putenv("SWI_HOME_DIR=C:\\Program Files (x86)\\swipl");
	char* dummy_args[] = { argv[0], "-s", "hangman.pl", NULL };

	argv = dummy_args;
	argc = sizeof(dummy_args) / sizeof(dummy_args[0]) - 1;

	PlEngine e(3, argv);

	CHangman hm;

	hm.startGame(argc, argv);

	return 0;
}