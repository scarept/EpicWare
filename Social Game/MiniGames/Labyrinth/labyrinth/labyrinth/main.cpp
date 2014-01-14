#include <iostream> 
#include <fstream> 
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <freeGLUT\include\GL\freeglut.h>
#include <vector>
#include <SOIL\src\SOIL.h>

#include "Labyrinth.h"
#include <External images for OpenGL\LoadImages.h>
#include "LoadExternalFiles.h"
#include <Windows.h>

#include <SWI-Prolog\include\SWI-Prolog.h>
#include <SWI-Prolog\include\SWI-Stream.h>
#include <SWI-Prolog\include\SWI-cpp.h>

#pragma comment(linker, "/subsystem:\"windows\" \
	/entry:\"mainCRTStartup\"")

int main(int argc, char** argv)
{
	//Dev purposes only, needs to be commented for release
	_putenv("SWI_HOME_DIR=C:\\Program Files (x86)\\swipl");

	char* dummy_args[] = { "libswipl.dll", "-s", ".\/pl\/labyrinthIA.pl", NULL };
	
	PlEngine e(3, dummy_args);

	Labyrinth s;
	s.startGame(argc, argv);

	return 1;
}

