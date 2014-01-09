#include <iostream> 
#include <fstream> 
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
//#include "SOIL.h"
#include <External images for OpenGl\Loadimages.h>
//#include "LoadExternalFiles.h"

#include <iostream>
#include <SWI-Prolog.h>
#include <SWI-Stream.h>
#include <SWI-cpp.h>
//#include "Prolog" 
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
	mod.imagem_circle = load2D("CIRCLE.png");
	mod.imagem_cruz = load2D("CRUZ.png");
	mod.textura_paredes = load2D("PAREDE.png");
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
		mod.textura_quadrado[i][j] = load2D("PAREDE.png");
		}
	}

	//if true PLAYER NON PC a jogar, if false PC a jogar
	player = true;

	glShadeModel(GL_FLAT);
}

void initMenu(void)
{
	/*  texturas  menu */
	//mod.menu = load2D("menu.png");
	mod.menu = load2D("MENU.png");

	mod.exit = load2D("EXIT.png");
	mod.play = load2D("PLAY.png");
}




/*
Responsavel por inserir os valores que lhe são passados na base de conhecimento dinamica PROLOG.
Formato liga('(0,0)','(0,0)').
*/
void joinConection(string envio){

	PlTermv bv(1);

	PlTermv az(&envio);
	bv[0] = PlCompound("board", az);
	cout << (char*)bv[0] << endl;
	PlQuery p("asserta", bv);
	p.next_solution();


}
/*
Recebe a matriz usada para desenhar o labirinto, e sempre que existe uma ligação entre 2 blocos é chamada a "joinConection" para criar o perdicado dinamico.
*/
void assertData(string* arr){
	string envio = "[";
	for (int i = 0; i = 9; i++)
	{
		envio = envio + arr[i];
		if (i < 8)
		{
			envio = envio + ",";
		}
		else{
			envio = envio + "]";
		}
	}
	joinConection(envio);
}

/* FUNÇÕES PROLOG */
int* fastestWayAvailable(string* arr){

	_putenv("SWI_HOME_DIR=C:\\Program Files (x86)\\swipl");
	char* argv[] = { "", "-s", "tictactoe.pl", NULL };

	PlEngine e(3, argv);

	/* Colocar informação da matriz na base de conhecimento*/
	assertData(arr);

	//char solution[255];

	PlTermv av(1);

	char *pointerInicial;
	char tempArr1[10];
	//sprintf(tempArr1, "'(%d,%d)'", x, y);
	pointerInicial = tempArr1;
	//PlTermv az(pointerVal1, pointerVal2);
	av[0] = PlCompound(tempArr1);

	char *pointerFinal;
	char tempArr2[10];
	//sprintf(tempArr2, "'(%d,%d)'", xFinal, yFinal);
	pointerFinal = tempArr2;
	//PlTermv az(pointerVal1, pointerVal2);
	av[1] = PlCompound(tempArr2);

	/*                                      */

	char *resTemp;//temporary pointer to solution output (prolog ouput)
	PlQuery q("path", av);
	while (q.next_solution())
	{
		//q.next_solution();
		resTemp = (char*)av[2];
		cout << (char*)av[2] << endl;
	}
	int valor = 0;
	int finalSize = 0;
	int *solution = new int[300];
	int segundo = 0;
	while (*resTemp != '\0')
	{
		if (*resTemp != '[' && *resTemp != '\''){
			//if (*resTemp != ',' && *resTemp != ']'){ //garante que o ultimo valor é escrito no array.
			//solution[finalSize] = *resTemp;
			//cout << solution[finalSize] << endl;
			if (*resTemp == '('){
				segundo = 1;
				resTemp++;
				int num = atoi(resTemp);
				//valor = valor * 10;
				//valor = valor + num;
				valor = num;

				finalSize++;
				solution[finalSize] = valor;
				cout << valor << endl;


				//finalSize++;
			}
			else if (*resTemp == ',' && segundo == 1){
				segundo = 0;
				resTemp++;
				int num = atoi(resTemp);
				//valor = valor * 10;
				//valor = valor + num;
				valor = num;

				finalSize++;
				solution[finalSize] = valor;
				cout << valor << endl;

			}
			else {

				valor = 0;
			}
		}

		resTemp++;
	}
	solution[0] = finalSize;
	return solution;
	//solution[finalSize] = '/0';

	/*
	for (int i = 0; i < finalSize; i++){

	cout << solution[i];
	}
	cout << endl;
	*/
}





/* LOGICA DE JOGO */
void converterMatrixEmArray(string* arrRet)
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (mod.matJogo[i][j] == 0)
			{
				stringstream ss;
				ss << count + 1;
				string z = "_Z"+ss.str();
				arrRet[count] = z;
			}
			else if (mod.matJogo[i][j] == 1)
			{
				arrRet[count] = "x";
			}
			else{
				arrRet[count] = "o";
			}
			count++;
		}
	}
}

int jogadaComputador()
{
	string arrProlog[9];
	converterMatrixEmArray(arrProlog);
	fastestWayAvailable(arrProlog);

	return -1;
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
				mod.textura_quadrado[0][0] = load2D("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 2){
				printf("2");
				mod.textura_quadrado[0][1] = load2D("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 3){
				printf("3");
				mod.textura_quadrado[0][2] = load2D("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 4){
				printf("4");
				mod.textura_quadrado[1][0] = load2D("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 5){
				printf("5");
				mod.textura_quadrado[1][1] = load2D("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 6){
				printf("6");
				mod.textura_quadrado[1][2] = load2D("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 7){
				printf("7");
				mod.textura_quadrado[2][0] = load2D("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 8){
				printf("8");
				mod.textura_quadrado[2][1] = load2D("CRUZ.png");
				glutPostRedisplay();
			}
			else if (*ptr == 9){
				printf("9");
				mod.textura_quadrado[2][2] = load2D("CRUZ.png");
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
	/* Teste */
	resetMatriz();
	jogadaComputador();

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

