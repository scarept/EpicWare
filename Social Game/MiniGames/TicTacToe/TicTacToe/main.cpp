#include <iostream> 
#include <fstream> 
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <freeGLUT\include\GL\freeglut.h>
#include <vector>
#include <External images for OpenGl\Loadimages.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <SWI-Prolog\include\SWI-Prolog.h>
#include <SWI-Prolog\include\SWI-Stream.h>
#include <SWI-Prolog\include\SWI-cpp.h>

#pragma comment(linker, "/subsystem:\"windows\" \
	/entry:\"mainCRTStartup\"")

using namespace std;

#define BUFSIZE 512
#define WIDTH 300
#define HEIGHT 300

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
	GLuint win;
	GLuint lose;
	GLuint deuce;
	int pontos;
}Modelo;

typedef struct{
	int l;
	int c;
} Cordenadas;
Quadrado quad;
Modelo mod;
//if true PLAYER NON PC a jogar, if false PC a jogar
bool player;
bool terminouJogo;
bool repetirJogada;
int vencedor = -1;


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
	mod.imagem_circle = load2D("./images/tictactoe/CIRCLE.png");
	mod.imagem_cruz = load2D("./images/tictactoe/CRUZ.png");
	mod.textura_paredes = load2D("./images/tictactoe/PAREDE.png");
	mod.win = load2D("./images/tictactoe/WIN.png");
	mod.lose = load2D("./images/tictactoe/LOSE.png");
	mod.deuce = load2D("./images/tictactoe/DEUCE.png");
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
		mod.textura_quadrado[i][j] = load2D("./images/tictactoe/PAREDE.png");
		}
	}

	//if true PLAYER NON PC a jogar, if false PC a jogar
	player = true;
	terminouJogo = false;
	repetirJogada = false;
	mod.pontos = -1;
	glShadeModel(GL_FLAT);
}

void initMenu(void)
{
	/*  texturas  menu */
	mod.menu = load2D("./images/tictactoe/MENU.png");
	mod.exit = load2D("./images/tictactoe/EXIT.png");
	mod.play = load2D("./images/tictactoe/PLAY.png");
}


/* PROLOG */
void addBase(char c)
{
	PlTermv bv1(1);
	char *pointerVal1;
	char tempArr1[10];
	sprintf_s(tempArr1, "%c", c);
	pointerVal1 = tempArr1;

	PlTermv az1(pointerVal1);
	bv1[0] = PlCompound("base", az1);
	//cout << (char*)bv1[0] << endl;
	PlQuery p1("assertz", bv1);
	p1.next_solution();
}

void addAllBase(char *arr){
	char b0 = arr[0];
	char b1 = arr[1];
	char b2 = arr[2];
	char b3 = arr[3];
	char b4 = arr[4];
	char b5 = arr[5];
	char b6 = arr[6];
	char b7 = arr[7];
	char b8 = arr[8];

	addBase(b0);
	addBase(b1);
	addBase(b2);
	addBase(b3);
	addBase(b4);
	addBase(b5);
	addBase(b6);
	addBase(b7);
	addBase(b8);
}

/*
 Transforma a matriz do jogo num array com elementos a inserir na base de conhecimento do prolog
*/
void assertData(){
	char arr[9];
	int posArray = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++){
			if (mod.matJogo[i][j] == 1)
			{
				arr[posArray] = 'x';
			}
			else if (mod.matJogo[i][j] == 2)
			{
				arr[posArray] = 'o';
			}
			else{
				arr[posArray] = 'N';
			}
			posArray++;
		}
		
	}
	addAllBase(arr);
}

Cordenadas fastestWayAvailable(){

	assertData();

	PlTermv av(2);



	char *res = 0;
	char *res2 = 0;

	/* Obtem as cordenadas da jogado do computador*/
	PlQuery q("c", av);
	while (q.next_solution())
	{
		res = (char *)av[0];
		res2 = (char *)av[1];
	}

	Cordenadas cord;
	cord.l = atoi(res2) - 1;
	cord.c = atoi(res) - 1;

	return cord;
}

/*
VALORES DE RETORNO (PARA JÁ NÃO UTILIZADOS, PODERÁ SER UTIL NO FUTURO)
-1 Posição de jogada ocupada
0 Jogada válida
1 Jogador Ganhou
2 Jogo terminou sem vencedores
*/
int validaJogada(int player, int l, int c)
{
	//Verifica posição ocupada
	if (mod.matJogo[l][c] != 0)
	{
		repetirJogada = true;
		return -1;
	}
	else{
		repetirJogada = false;
		mod.matJogo[l][c] = player;

		/* VERIFICAÇÃO SE JOGADOR GANHOU COM A JOGADA EFETUADA*/

		//Verifica linha completa
		bool flag = true;
		for (int i = 0; i < 3; i++)
		{
			if (mod.matJogo[l][i] != player)
			{
				flag = false;
			}
		}
		if (flag)
		{
			terminouJogo = true;
			vencedor = player;
			mod.pontos = 1;
			teste = 2;
			return 1;
			
		}


		//Verifica coluna completa
		flag = true;
		for (int i = 0; i < 3; i++)
		{
			if (mod.matJogo[i][c] != player)
			{
				flag = false;
			}
		}
		if (flag)
		{
			terminouJogo = true;
			vencedor = player;
			mod.pontos = 1; 
			teste = 2;
			return 1;
			
		}


		//Verifica diagonal 1
		flag = true;
		for (int i = 0; i < 3; i++)
		{
			if (mod.matJogo[i][i] != player)
			{
				flag = false;
			}
		}
		if (flag)
		{
			terminouJogo = true;
			vencedor = player;
			mod.pontos = 1;
			teste = 2;
			return 1;
			
		}

		//Verifica diagonal 2
		flag = true;
		if (mod.matJogo[0][2] != player)
		{
			flag = false;
		}
		if (mod.matJogo[1][1] != player)
		{
			flag = false;
		}
		if (mod.matJogo[2][0] != player)
		{
			flag = false;
		}

		if (flag)
		{
			terminouJogo = true;
			vencedor = player;
			teste = 2;
			mod.pontos = 1;
			return 1;
			
		}

		/* VERIFICA SE JOGO TERMINOU SEM VENCEDOR*/
		bool terminou = true;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (mod.matJogo[i][j] == 0)
				{
					terminou = false;
				}
			}
		}
		if (terminou)
		{
			terminouJogo = true;
			vencedor = 0;
			mod.pontos = 0;
			teste = 2;
			return 2;
		}
		else{
			return 0;
		}
	}
}

int jogadaJogador(int l, int c)
{
	return validaJogada(1,l,c);
}


int jogadaComputador()
{
	if (!terminouJogo && !repetirJogada){
		player = false;
		Cordenadas cord;
		cord = fastestWayAvailable();
		player = true;
		return validaJogada(2, cord.l, cord.c);
	}
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
	//Analisa Matriz de Jogo
	for (int i = 0; i < 3; i++)
	{

		for (int j = 0; j < 3; j++)
		{
			if (mod.matJogo[i][j] == 0)
			{
				mod.textura_quadrado[i][j] = load2D("./images/tictactoe/PAREDE.png");
			}
			else if(mod.matJogo[i][j] == 1){
				mod.textura_quadrado[i][j] = load2D("./images/tictactoe/CRUZ.png");
			}
			else{
				mod.textura_quadrado[i][j] = load2D("./images/tictactoe/CIRCLE.png");
			}
		}
	}
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
				glTexCoord2f(0.0f, 0.0f);
				glVertex2f(0.0f + ((float)j * 33.0f), 0.0f + (float)i * 33.0f);
				glTexCoord2f(0.0f, 1.0f);
				glVertex2f(0.0f + ((float)j * 33.0f), 33.0f + (float)i * 33.0f);
				glTexCoord2f(1.0f, 1.0f);
				glVertex2f(33.0f + ((float)j * 33.0f), 33.0f + (float)i * 33.0f);
				glTexCoord2f(1.0f, 0.0f);
				glVertex2f(33.0f + ((float)j * 33.0f), 0.0f + (float)i * 33.0f);
				glEnd();
				glBindTexture(GL_TEXTURE_2D, NULL);
			}
			glPopMatrix();
		}
	}
}

void desenhaFinal(GLenum mode)
{
	/* carregar fundo */
	glPushMatrix();
	if (mode == GL_SELECT)
		glLoadName(99);
		glBindTexture(GL_TEXTURE_2D, mod.menu);
		//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 0.5); //transparencias 
		glBegin(GL_POLYGON);
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

	/* carrega painel  final */

	if (vencedor == 0){
		glBindTexture(GL_TEXTURE_2D, mod.deuce);
	}
	else if (vencedor == 1){
		glBindTexture(GL_TEXTURE_2D, mod.win);
	}
	else{
		glBindTexture(GL_TEXTURE_2D, mod.lose);
	}
	glPushMatrix();
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(15, 30);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(85, 30);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(85, 57);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(15, 57);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();

	///*  sair btn  */
	//glPushMatrix();
	//if (mode == GL_SELECT){
	//	glLoadName(4);
	//	glBindTexture(GL_TEXTURE_2D, mod.exit);
	//	glBegin(GL_POLYGON);
	//	glTexCoord2f(0.0, 1.0);
	//	glVertex2f(25, 80);
	//	glTexCoord2f(1.0, 1.0);
	//	glVertex2f(75, 80);
	//	glTexCoord2f(1.0, 0.0);
	//	glVertex2f(75, 87);
	//	glTexCoord2f(0.0, 0.0);
	//	glVertex2f(25, 87);
	//	glEnd();
	//}
	//glPopMatrix();


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
	if (!terminouJogo){
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
	}
	else{
		glClear(GL_COLOR_BUFFER_BIT);
		desenhaFinal(GL_SELECT);
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
			int aa = *ptr;
			cout << *ptr;
			if (*ptr == 1){
				initGame();
				teste = 1;
				glutPostRedisplay();
			}
			else if (*ptr == 4){
				glutLeaveMainLoop();
			}
			ptr++;
		}
	}
}

void clickEventMatrix(GLint hits, GLuint buffer[])
{
	if (player && !terminouJogo){

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
					glutPostRedisplay();
					jogadaJogador(0, 0);
				}
				else if (*ptr == 2){
					printf("2");
					glutPostRedisplay();
					jogadaJogador(0, 1);
				}
				else if (*ptr == 3){
					printf("3");
					glutPostRedisplay();
					jogadaJogador(0, 2);
				}
				else if (*ptr == 4){
					printf("4");
					glutPostRedisplay();
					jogadaJogador(1, 0);
				}
				else if (*ptr == 5){
					printf("5");
					glutPostRedisplay();
					jogadaJogador(1, 1);
				}
				else if (*ptr == 6){
					printf("6");
					glutPostRedisplay();
					jogadaJogador(1, 2);
				}
				else if (*ptr == 7){
					printf("7");
					glutPostRedisplay();
					jogadaJogador(2, 0);
				}
				else if (*ptr == 8){
					printf("8");
					glutPostRedisplay();
					jogadaJogador(2, 1);
				}
				else if (*ptr == 9){
					printf("9");
					glutPostRedisplay();
					jogadaJogador(2, 2);
				}
				else if (*ptr == 99){
					printf("99");
					glutLeaveMainLoop();
					
				}
				ptr++;
			}
		}
		jogadaComputador();
	}
	else{}
	
}

void clickEventFinal(GLint hits, GLuint buffer[])
{
		int i;
		unsigned int j;
		GLuint names, *ptr;
		ptr = (GLuint *)buffer;
		for (i = 0; i < hits; i++) {
			names = *ptr;
			ptr = ptr + 3;
			for (j = 0; j < names; j++) { /* for each name */
				if (*ptr == 99){
					printf("99");
					glutLeaveMainLoop();

				}
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

	//if (terminouJogo)
	//	desenhaFinal(GL_SELECT);

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


void pickFinal(int button, int state, int x, int y)
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
	desenhaFinal(GL_SELECT);

	glPopMatrix();
	glFlush();
	hits = glRenderMode(GL_RENDER);
	clickEventFinal(hits, selectBuf);

}

void picking(int button, int state, int x, int y)
{
	if (teste == 0){
		pickRects(button, state, x, y);
	}
	else if (teste == 1){
		pickMatriz(button, state, x, y);
	}
	else if (teste == 2){
		pickFinal(button, state, x, y);
	}
}

/* MAIN */

int main(int argc, char** argv)
{
	_putenv("SWI_HOME_DIR=.\\");

	char* dummy_args[] = { "libswipl.dll", "-s", "./pl/tictactoe.pl", NULL };

	PlEngine e(3, dummy_args);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	//posição inicial da janela
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WIDTH) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) / 2);

	glutInitWindowSize(WIDTH, HEIGHT); //tamanho da janela
	
	//glutSetIconTitle("./images/tictactoe/tictactoe.ico");

	glutCreateWindow("Tic-Tac-Toe"); //linha de comandos

	HANDLE icon = LoadImage(GetModuleHandle(NULL), L"./images/tictactoe/tictactoe.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE | LR_COLOR);
	HWND hwnd = FindWindow(NULL, L"Tic-Tac-Toe");
	SendMessage(hwnd, (UINT)WM_SETICON, ICON_BIG, (LPARAM)icon);

	glutMouseFunc(picking); //funcionalidade de picking do rato

	glutDisplayFunc(display); //função display actualizada a cada instante

	glutReshapeFunc(reshape);

	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
		);

	initMenu(); //começa por carregar o menu

	glutMainLoop();

	return mod.pontos;
}

