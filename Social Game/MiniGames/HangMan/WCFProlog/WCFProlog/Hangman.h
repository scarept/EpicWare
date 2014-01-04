#ifndef HANGMAN_H
#define HANGMAN_H

#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include "C:\Users\Vítor\Desktop\EpicWare\Social Game\MiniGames\Labyrinth\labyrinth\labyrinth\LoadImages.h"

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif

using namespace std;

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#ifndef BUFSIZE
#define BUFSIZE 512
#endif
#define WIDTH 800
#define HEIGHT 600

#define DEBUG 1

struct Estado{
	GLboolean   doubleBuffer;
	GLint       delay;
};

struct Horas{
	GLint       hor, min, seg;
};

struct Modelo{
	GLfloat     raio; //Stickman's head size
	Horas       hora;
	bool		onGame; //false for categories, true for play
	int			numErrors; //number of times user failed a guess
	char		word[80]; //word picked randomly
	char		guesses[27]; //letters already guessed by user
	char		partialWord[80]; //word with letters already guessed in correct place
	char		category[80]; //Selected word's category
};


class CHangman
{
private:
public:
	CHangman();
	~CHangman();
	void startGame(int, char **);
};

#endif