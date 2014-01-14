#include <iostream> 
#include <fstream> 
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <freeGLUT\include\GL\freeglut.h>
#include <vector>
#include <SOIL\SOIL.h>

#include "Labyrinth.h"
#include <External images for OpenGL\LoadImages.h>
#include "LoadExternalFiles.h"
#include <Windows.h>

#pragma comment(linker, "/subsystem:\"windows\" \
	/entry:\"mainCRTStartup\"")

int main(int argc, char** argv)
{
	Labyrinth s;
	s.startGame(argc, argv);

	return 1;
}

