#include <iostream> 
#include <fstream> 
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include "SOIL.h"

#include "Prolog.h"
#include "LoadImages.h"
#include "LoadExternalFiles.h"

using namespace std;


#define BUFSIZE 512

int teste = 0;

typedef struct {
	GLboolean   a, w, s, d, h, p;
}Teclas;

typedef struct{
	GLint	x, y;
	GLint xi, yi;
	GLint dimensao;
	GLint **matrix;
}Quadrado;

typedef struct{
	int **matLabirinto;
	int *posGPS;
	bool gps;
	GLuint imagem;
	GLuint textura_paredes;
	GLuint caminho_text;
	GLuint menu;
}Modelo;

Teclas tecla;
Quadrado quad;
Modelo mod;

void pintarGPS()
{
	if (mod.gps == true)
	{
		cout << " true " << endl;
		int tamanho = mod.posGPS[0];
		int x, y;
		for (int i = 2; i < tamanho; i = i+2)
		{
			x = mod.posGPS[(i)];
			y = mod.posGPS[(i - 1)];
			glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA);
			glBegin(GL_POLYGON);
				glColor3f(100, 100, 100);
				glVertex2f(0 + (x*quad.dimensao), 0 + ((y - 1)*quad.dimensao));
				glVertex2f(0 + (x*quad.dimensao), quad.dimensao + ((y - 1)*quad.dimensao));
				glVertex2f(quad.dimensao + (x*quad.dimensao), quad.dimensao + ((y - 1)*quad.dimensao));
				glVertex2f(quad.dimensao + (x*quad.dimensao), 0 + ((y - 1)*quad.dimensao));
			glEnd();
		}
	}
	if (mod.gps == false)
	{
		cout << " false" << endl;
	}
}



void initMenu(void)

{
	/*  texturas  menu */
	mod.menu = carrega_texturas("menu.png");

}

void desenhaMenu(GLenum mode){
	
	/* carregar fundo */
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, mod.menu);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 0.5); //transparencias 
	glBegin(GL_POLYGON);
		//glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 1.0);
		glVertex2f(0, 0);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(100, 0);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(100, 100);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(0, 100);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();
	
	/* botões   */
	
	glPushMatrix();
	if (mode == GL_SELECT)
		glLoadName(1);
		GLuint imagem = carrega_texturas("bt10.png");
		glBindTexture(GL_TEXTURE_2D, imagem);
		glBegin(GL_POLYGON);
		//glColor3f(1, 1, 1);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(25, 30);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(75, 30);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(75, 37);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(25, 37);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();

	glPushMatrix();
	if (mode == GL_SELECT)
		glLoadName(2);
		GLuint imagem20 = carrega_texturas("bt20.png");
		glBindTexture(GL_TEXTURE_2D, imagem20);
		glBegin(GL_POLYGON);
		//glColor3f(1, 1, 1);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(25, 40);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(75, 40);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(75, 47);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(25, 47);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	if (mode == GL_SELECT)
		glLoadName(3);
		GLuint imagem30 = carrega_texturas("bt30.png");
		glBindTexture(GL_TEXTURE_2D, imagem30);
		glBegin(GL_POLYGON);
		//glColor3f(1, 1, 1);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(25, 50);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(75, 50);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(75, 57);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(25, 57);
		glEnd();
	glPopMatrix();
	

	/*  sair btn  */
	glPushMatrix();
	if (mode == GL_SELECT)
		glLoadName(4);
		GLuint imagemExit = carrega_texturas("btExit.png");
		glBindTexture(GL_TEXTURE_2D, imagemExit);
		glBegin(GL_POLYGON);
		//glColor3f(1, 1, 1);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(25, 80);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(75, 80);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(75, 87);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(25, 87);
		glEnd();
	glPopMatrix();

}



/* desenha o jogador e coloca-o na sua posição inicial*/
void drawPlayer(int x, int y)
{
	
	
	glBindTexture(GL_TEXTURE_2D, mod.imagem);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 0.5); //transparencias 
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(0 + (x*quad.dimensao), 0 + ((y - 1)*quad.dimensao));
		glTexCoord2f(0.0, 1.0);
		glVertex2f(0 + (x*quad.dimensao), quad.dimensao + ((y - 1)*quad.dimensao));
		glTexCoord2f(1.0, 1.0);
		glVertex2f(quad.dimensao + (x*quad.dimensao), quad.dimensao + ((y - 1)*quad.dimensao));
		glTexCoord2f(1.0, 0.0);
		glVertex2f(quad.dimensao + (x*quad.dimensao), 0 + ((y - 1)*quad.dimensao));
	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);

}



void desenhaLabirinto(int **matLabirinto)
{

	int nivel = matLabirinto[0][0];
	
	int x = 0, y = 0;
	if (nivel == 1)
	{
		x = y = 10;
		matLabirinto[0][5] = 10;
		matLabirinto[0][6] = 10;
	}
	else if (nivel == 2)
	{
		x = y = 20;
		matLabirinto[0][5] = 20;
		matLabirinto[0][6] = 5;
	}
	else
	{
		x = y = 25;
		matLabirinto[0][5] = 25;
		matLabirinto[0][6] = 4;
	}

	for (int i = 1; i<(x + 1); i++)
	{
		for (int j = 0; j<y; j++)
		{
			if (matLabirinto[i][j] != 0 && x == 10)
			{
				glBindTexture(GL_TEXTURE_2D, mod.textura_paredes);

				glBegin(GL_POLYGON);
				//glColor3f(0, 0, 255);
				glTexCoord2f(0.0, 0.0);
				glVertex2f(0 + (j * 10), 0 + ((i - 1) * 10));
				glTexCoord2f(0.0, 1.0);
				glVertex2f(0 + (j * 10), 10 + ((i - 1) * 10));
				glTexCoord2f(1.0, 1.0);
				glVertex2f(10 + (j * 10), 10 + ((i - 1) * 10));
				glTexCoord2f(1.0, 0.0);
				glVertex2f(10 + (j * 10), 0 + ((i - 1) * 10));
				glEnd();
				glBindTexture(GL_TEXTURE_2D, NULL);
			}

			if (matLabirinto[i][j] != 0 && x == 20)
			{


				glBindTexture(GL_TEXTURE_2D, mod.textura_paredes);

				glBegin(GL_POLYGON);
				//glColor3f(0, 0, 255);
				glTexCoord2f(0.0, 0.0);
				glVertex2f(0 + (j * 5), 0 + ((i - 1) * 5));
				glTexCoord2f(0.0, 1.0);
				glVertex2f(0 + (j * 5), 5 + ((i - 1) * 5));
				glTexCoord2f(1.0, 1.0);
				glVertex2f(5 + (j * 5), 5 + ((i - 1) * 5));
				glTexCoord2f(1.0, 0.0);
				glVertex2f(5 + (j * 5), 0 + ((i - 1) * 5));
				glEnd();
				glBindTexture(GL_TEXTURE_2D, NULL);
			}
			if (matLabirinto[i][j] != 0 && x == 25)
			{
				glBindTexture(GL_TEXTURE_2D, mod.textura_paredes);

				glBegin(GL_POLYGON);
				//glColor3f(0, 0, 255);
				glTexCoord2f(0.0, 0.0);
				glVertex2f(0 + (j * 4), 0 + ((i - 1) * 4));
				glTexCoord2f(0.0, 1.0);
				glVertex2f(0 + (j * 4), 4 + ((i - 1) * 4));
				glTexCoord2f(1.0, 1.0);
				glVertex2f(4 + (j * 4), 4 + ((i - 1) * 4));
				glTexCoord2f(1.0, 0.0);
				glVertex2f(4 + (j * 4), 0 + ((i - 1) * 4));
				glEnd();
				glBindTexture(GL_TEXTURE_2D, NULL);
			}
		}
	}

	quad.dimensao = matLabirinto[0][6];
	//cout << " ola " << endl;
	//cout << matLabirinto[0][4] << endl;
	//cout << matLabirinto[0][3] << " -----" << endl;
	//quad.x = matLabirinto[0][3], quad.y = matLabirinto[0][1];
	//cout << matLabirinto[0][3] << ";" << matLabirinto[0][1];
	drawPlayer(quad.x = quad.x + 0, quad.y = quad.y + 0);
	quad.matrix = matLabirinto;
	//criarPerdicados(matLabirinto);
}



void reshape(int w, int h)

{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluOrtho2D(0, 100, 100, 0);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

}



void display(void)
{

	if (teste == 0){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		desenhaMenu(GL_SELECT);
		glutSwapBuffers();
	}
	else if (teste == 1){

		glClear(GL_COLOR_BUFFER_BIT);

		pintarGPS();
		desenhaLabirinto(mod.matLabirinto);
		
		
		glutSwapBuffers();

	}
	else if (teste == 2){
		//implementar pausa
	}

	glFlush();

}


void Key(unsigned char key, int x, int y)
{
	/*se estiver com o jogo aberto */
	if (teste == 1){
		switch (key) {
		case 'A':
		case 'a': tecla.a = GL_TRUE;

			if (quad.matrix[quad.y][quad.x - 1] == 0)
			{
				cout << " ola aaa " << endl;
				quad.x = quad.x - 1;
			}

			break;
		case 'W':
		case 'w': tecla.w = GL_TRUE;
			if (quad.matrix[quad.y - 1][quad.x] == 0)
			{
				quad.y = quad.y - 1;
			}

			break;
		case 'S':
		case 's': tecla.s = GL_TRUE;
			if (quad.matrix[0][3] == quad.y + 1 && quad.matrix[0][4] == quad.x){
				teste = 2;
			}

			if (quad.matrix[quad.y + 1][quad.x] == 0)
			{
				quad.y = quad.y + 1;
			}

			break;
		case 'D':
		case 'd': tecla.d = GL_TRUE;
			if (quad.matrix[quad.y][quad.x + 1] == 0)
			{
				quad.x = quad.x + 1;
			}
			break;

		case 'H':
		case 'h': tecla.d = GL_TRUE;
			mod.posGPS = fastestWayAvailable(quad.matrix, quad.x, quad.y);
			mod.gps = true;
			break;

		case 'P':
		case 'p': tecla.d = GL_TRUE;
			teste = 0;
			break;

		}
	}


	//glutPostRedisplay();
}



void KeyUp(unsigned char key, int x, int y)
{
	switch (key) {
		// ... accoes sobre largar teclas ... 

	case 'A':
	case 'a': tecla.a = GL_FALSE;
		break;
	case 'W':
	case 'w': tecla.w = GL_FALSE;
		break;
	case 'S':
	case 's': tecla.s = GL_FALSE;
		break;
	case 'D':
	case 'd': tecla.d = GL_FALSE;
		break;
	case 'H':
	case 'h': tecla.d = GL_FALSE;
		break;
	}

}

void TimerTeclas(int value)
{
	glutTimerFunc(20, TimerTeclas, 0);
	if (tecla.a)
	{
		//cout << "olaaaaaaaa aaaaa " << endl;
		//cout << quad.x << " ; " << quad.y << endl;
		drawPlayer(5, 5);
		//sleep(100);

	}
	//cout << "olaaaaaaaa aaaaa sssssssss" << endl;
	glutPostRedisplay();
}

void initGame(char * file){
	/* funcionalidades do teclado*/
	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);
	glutTimerFunc(20, TimerTeclas, 0);

	/*	garantir que a ajuda está off */
	mod.gps = false;

	mod.matLabirinto = carregarMatriz(file);

	/* carregar iamgens */
	mod.imagem = carrega_texturas("teste.png");
	mod.textura_paredes = carrega_texturas("parede.png");
	
	/* ver coordenadas jogador !!??*/
	/*Atribuir coordenadas iniciais ao jogador*/
	quad.y = mod.matLabirinto[0][1];
	quad.x = mod.matLabirinto[0][2];
	
	
	/* diogo ver */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	tecla.a = tecla.w = tecla.s = tecla.d = GL_FALSE;


}


void clickEvent(GLint hits, GLuint buffer[])
{
	int i;
	unsigned int j;
	GLuint names, *ptr;
	//printf("hits = %d\n", hits);
	ptr = (GLuint *)buffer;
	for (i = 0; i < hits; i++) { /* for each hit */
		names = *ptr;
		/*
		printf(" number of names for hit = %d\n", names);
		ptr++;
		printf(" z1 is %g;", (float)*ptr / 0xffffffff);
		ptr++;
		printf(" z2 is %g\n", (float)*ptr / 0xffffffff);
		ptr++;
		printf(" the name is ");
		*/
		ptr = ptr + 3;
		for (j = 0; j < names; j++) { /* for each name */
			if (*ptr == 1){
				initGame("teste.txt");
				teste = 1;

			}
			else if (*ptr == 2){
				initGame("teste2.txt");
				teste = 1;
			}
			else if (*ptr == 3){
				initGame("teste3.txt");
				teste = 1;
			}
			else if (*ptr == 4){
				exit(0);
			}
			
			//printf("%d ", *ptr);
			ptr++;
		}
		//printf("\n");
	}
}


void pickRects(int button, int state, int x, int y)
{
	
	GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint viewport[4];
	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(BUFSIZE, selectBuf);
	(void)glRenderMode(GL_SELECT);
	glInitNames();
	glPushName((GLuint)~0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	/* create 5x5 pixel picking region near cursor location */
	gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y),0.5, 0.5, viewport);
	gluOrtho2D(0, 100, 100, 0);
	desenhaMenu(GL_SELECT);

	glPopMatrix();
	glFlush();
	hits = glRenderMode(GL_RENDER);
	clickEvent(hits, selectBuf);
	
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500); //tamanho da janela

	glutInitWindowPosition(100, 100); //posição inicial da janela

	glutCreateWindow(argv[0]); //linha de comandos


	glutMouseFunc(pickRects); //funcionalidade de picking do rato

	glutDisplayFunc(display); //função display actualizada a cada instante

	glutReshapeFunc(reshape);

		
	initMenu(); //comaça por carregar o menu

	glutMainLoop();

	return 0;

}

