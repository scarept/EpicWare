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


#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define DEBUG 1

struct Estado{
	GLboolean   doubleBuffer;
	GLint       delay;
};

struct Horas{
	GLint       hor, min, seg;
};

struct Modelo{
	GLint       numLados;
	GLfloat     raio;
	GLfloat     tamLado;
	GLenum      tipoPoligono;
	Horas       hora;
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