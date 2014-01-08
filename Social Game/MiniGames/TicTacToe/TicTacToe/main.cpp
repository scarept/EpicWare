#include <iostream> 
#include <fstream> 
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
//#include "SOIL.h"

//#include "Prolog.h"
#include "LoadImages.h"
//#include "LoadExternalFiles.h"

using namespace std;

#define BUFSIZE 512

int teste = 0;

typedef struct{
	GLint	x, y;
	GLint xi, yi;
	GLint dimensao;
	GLint **matrix;
}Quadrado;

typedef struct{
	int matJogo[3][3];
	GLuint imagem_circle;
	GLuint imagem_cruz;
	GLuint textura_paredes;
	GLuint play;
	GLuint exit;
	GLuint menu;
	GLuint textura_quadrado[3][3];
}Modelo;

Quadrado quad;
Modelo mod;
//if true PLAYER NON PC a jogar, if false PC a jogar
bool player;


/* INICIALIZAÇÃO DE JOGO */

void resetMatriz(){
	mod.matJogo[0][0] = 0;
	mod.matJogo[0][1] = 0;
	mod.matJogo[0][2] = 0;

	mod.matJogo[1][0] = 0;
	mod.matJogo[1][1] = 0;
	mod.matJogo[1][2] = 0;

	mod.matJogo[2][0] = 0;
	mod.matJogo[2][1] = 0;
	mod.matJogo[2][2] = 0;
}

void initGame(){
	resetMatriz();

	/* carregar imagens */
	mod.imagem_circle = carrega_texturas("CIRCLE.png");
	mod.imagem_cruz = carrega_texturas("CRUZ.png");
	mod.textura_paredes = carrega_texturas("PAREDE.png");
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
		mod.textura_quadrado[i][j] = carrega_texturas("PAREDE.png");
		}
	}

	//if true PLAYER NON PC a jogar, if false PC a jogar
	player = true;

	glShadeModel(GL_FLAT);
}

void initMenu(void)
{
	/*  texturas  menu */
	//mod.menu = carrega_texturas("menu.png");
	mod.menu = carrega_texturas("MENU.png");

	mod.exit = carrega_texturas("EXIT.png");
	mod.play = carrega_texturas("PLAY.png");
}



/* DESNHOS NO ECRA */

void desenhaMenu(GLenum mode){

	/* carregar fundo */
	glPushMatrix();
	if (mode == GL_SELECT){
		glLoadName(20);
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
	}
	glPopMatrix();

	/* botões   */

	glPushMatrix();
	if (mode == GL_SELECT){
		glLoadName(1);
		glBindTexture(GL_TEXTURE_2D, mod.play);
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
	}
	glPopMatrix();

	/*  sair btn  */
	glPushMatrix();
	if (mode == GL_SELECT){
		glLoadName(4);
		glBindTexture(GL_TEXTURE_2D, mod.exit);
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
	}
	glPopMatrix();

}

void desenhaJogo(GLenum mode)
{
	int x = 0, y = 0;
	x = y = 3;
	int count = 0;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			glPushMatrix();
			count++;
			if (mode == GL_SELECT){
				glLoadName(count);
				glBindTexture(GL_TEXTURE_2D, mod.textura_quadrado[i][j]);
				glBegin(GL_POLYGON);
				glColor3f(128, 0, 255);
				glTexCoord2f(0.0, 0.0);
				glVertex2f(0 + (j * 33), 0 + i * 33);
				glTexCoord2f(0.0, 1.0);
				glVertex2f(0 + (j * 33), 33 + i * 33);
				glTexCoord2f(1.0, 1.0);
				glVertex2f(33 + (j * 33), 33 + i * 33);
				glTexCoord2f(1.0, 0.0);
				glVertex2f(33 + (j * 33), 0 + i * 33);
				glEnd();
				glBindTexture(GL_TEXTURE_2D, NULL);
			}
			glPopMatrix();
		}
	}
}

void reshape(int w, int h)

{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluOrtho2D(0, 99, 99, 0);

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
		desenhaJogo(GL_SELECT);
		glutSwapBuffers();
	}
	glFlush();

}

/* PIKING */
void clickEvent(GLint hits, GLuint buffer[])
{
	int i;
	unsigned int j;
	GLuint names, *ptr;
	ptr = (GLuint *)buffer;
	for (i = 0; i < hits; i++) {
		names = *ptr;
		ptr = ptr + 3;
		for (j = 0; j < names; j++) { /* for each name */
			if (*ptr == 1){
				initGame();
				teste = 1;
				glutPostRedisplay();
			}
			else if (*ptr == 4){
				exit(0);
			}
			ptr++;
		}
	}
}

void clickEventMatrix(GLint hits, GLuint buffer[])
{
	int i;
	unsigned int j;
	GLuint names, *ptr;
	ptr = (GLuint *)buffer;
	for (i = 0; i < hits; i++) {
		names = *ptr;
		ptr = ptr + 3;
		for (j = 0; j < names; j++) { /* for each name */
			if (*ptr == 1){
				printf("1");
				mod.textura_quadrado[0][0] = carrega_texturas("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 2){
				printf("2");
				mod.textura_quadrado[0][1] = carrega_texturas("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 3){
				printf("3");
				mod.textura_quadrado[0][2] = carrega_texturas("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 4){
				printf("4");
				mod.textura_quadrado[1][0] = carrega_texturas("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 5){
				printf("5");
				mod.textura_quadrado[1][1] = carrega_texturas("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 6){
				printf("6");
				mod.textura_quadrado[1][2] = carrega_texturas("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 7){
				printf("7");
				mod.textura_quadrado[2][0] = carrega_texturas("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 8){
				printf("8");
				mod.textura_quadrado[2][1] = carrega_texturas("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 9){
				printf("9");
				mod.textura_quadrado[2][2] = carrega_texturas("CRUZ.png");
				glutPostRedisplay();
			}
			//else if (*ptr == 4){
			//	exit(0);
			//}
			ptr++;
		}
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
	gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y), 0.5, 0.5, viewport);
	gluOrtho2D(0, 100, 100, 0);
	desenhaMenu(GL_SELECT);

	glPopMatrix();
	glFlush();
	hits = glRenderMode(GL_RENDER);
	clickEvent(hits, selectBuf);

}


void pickMatriz(int button, int state, int x, int y)
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
	gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y), 0.5, 0.5, viewport);
	gluOrtho2D(0, 100, 100, 0);
	desenhaJogo(GL_SELECT);

	glPopMatrix();
	glFlush();
	hits = glRenderMode(GL_RENDER);
	clickEventMatrix(hits, selectBuf);

}

void picking(int button, int state, int x, int y)
{
	if (teste == 0){
		pickRects(button, state, x, y);
	}
	else if (teste == 1){
		pickMatriz(button, state, x, y);
	}
}

/* MAIN */

int main(int argc, char** argv)
{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(300, 300); //tamanho da janela

	glutInitWindowPosition(99, 99); //posição inicial da janela

	glutCreateWindow(argv[0]); //linha de comandos

	glutMouseFunc(picking); //funcionalidade de picking do rato

	glutDisplayFunc(display); //função display actualizada a cada instante

	glutReshapeFunc(reshape);

	initMenu(); //começa por carregar o menu

	glutMainLoop();

	return 0;

}

