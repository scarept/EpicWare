#include <iostream> 
#include <fstream> 
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include "Prolog.h"

using namespace std;

typedef struct {
	GLboolean   a, w, s, d, h;
}Teclas;

typedef struct{
	GLint	x, y;
	GLint xi, yi;
	GLint dimensao;
	GLint **matrix;
}Quadrado;

Teclas tecla;
Quadrado quad;



void init(void)

{
	/*pos inicioal*/
	ifstream ficheiro("teste2.txt", ios::in);
	string linha;
	getline(ficheiro, linha);
	char Seperator = ' ';
	istringstream StrStream(linha);
	string Token;
	int valor, i = 0;
	while (getline(StrStream, Token, Seperator))
	{
		cout << i << " : ttt" << endl;
		valor = atoi(Token.c_str());
		if (i == 1)
		{
			cout << "Valor A: " << valor << endl;
			quad.x = valor;
		}
		if (i == 2)
		{
			cout << "Valor B: " << valor << endl;
			quad.y = valor;
		}
		i++;
		//matLabirinto[0][i] = valor;
	}
	/*Fim pos inicial*/
	//quad.x = quad.xi;
	//quad.y = quad.yi;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	tecla.a = tecla.w = tecla.s = tecla.d = GL_FALSE;
}

void desenhaQuadrado(int x, int y)
{
	glBegin(GL_POLYGON);
	glColor3f(0, 100, 100);
	glVertex2f(0 + (x*quad.dimensao), 0 + ((y - 1)*quad.dimensao));
	glVertex2f(0 + (x*quad.dimensao), quad.dimensao + ((y - 1)*quad.dimensao));
	glVertex2f(quad.dimensao + (x*quad.dimensao), quad.dimensao + ((y - 1)*quad.dimensao));
	glVertex2f(quad.dimensao + (x*quad.dimensao), 0 + ((y - 1)*quad.dimensao));
	glEnd();

}
void criarPerdicados(int **matriz)
{
	int nivel = 0;
	nivel = matriz[0][0];
	int largura = 0, altura = 0;
	if (nivel == 1 || nivel == 2)
	{
		largura = nivel * 10;
		altura = nivel * 10 + 1;
	}
	else
	{
		largura = 25;
		altura = 26;
	}

	for (int i = 1; i<altura; i++)
	{
		for (int j = 1; j< largura; j++)
		{
			if (matriz[i][j] == 0 && matriz[i][(j - 1)] == 0)
			{
				//cout << " ta top ligou : (" << i << "," << (j-1) << ") , (" << i << "," << j << ")" << endl;
			}
			if (matriz[i][j] == 0 && matriz[(i - 1)][j] == 0)
			{
				//cout << " ta top ligou verti : (" << (i-1) << "," << j << ") , (" << i << "," << j << ")" << endl;
			}
		}
	}

}

//int** carregarMatriz(string nome){
int** carregarMatriz(string nome){
	ifstream ficheiro(nome, ios::in);
	//	char linhab[256];
	int** matLabirinto = NULL;
	int auxNumLinhaMat = 0;
	int nivel = 0;
	if (ficheiro)
	{
		string linha;
		int linhaMatriz = 1, colunaMatriz = 0;
		while (getline(ficheiro, linha))
		{
			if (nivel == 0)
			{
				//**********
				nivel = atoi(linha.c_str());
				//printf("Conteudo %d \n", nivel);

				/* Numero de linhas da matriz*/
				if (nivel == 1 || nivel == 2)
				{
					auxNumLinhaMat = (nivel * 10) + 1;
				}
				else
				{
					auxNumLinhaMat = 25 + 1;
				}
				matLabirinto = new int*[auxNumLinhaMat - 1];
				for (int i = 0; i < auxNumLinhaMat; i++)
				{
					matLabirinto[i] = new int[auxNumLinhaMat];
				}

				/*Posição de inicio e posição de fim*/
				char Seperator = ' ';
				istringstream StrStream(linha);
				string Token;
				int valor, i = 0;
				while (getline(StrStream, Token, Seperator))
				{
					valor = atoi(Token.c_str());
					matLabirinto[0][i] = valor;
					i++;
				}

			}
			else
			{
				//printf("linha seguinte \n");
				if (nivel == 1 || nivel == 2 || nivel == 3)
				{
					//**************continuar aqui
					char Seperator = ' ';
					istringstream StrStream(linha);
					string Token;
					int valor;
					while (getline(StrStream, Token, Seperator))
					{
						valor = atoi(Token.c_str());
						matLabirinto[linhaMatriz][colunaMatriz] = valor;
						colunaMatriz++;
					}
					linhaMatriz++;
					colunaMatriz = 0;
				}

			}
		}
	}
	else
	{
		printf("erro abertura ficheiro/n");
	}

	if (nivel == 1)
	{
		matLabirinto[0][0] = 1;
	}
	else if (nivel == 2)
	{
		matLabirinto[0][0] = 2;
	}
	else if (nivel == 3)
	{
		matLabirinto[0][0] = 3;
	}

	return matLabirinto;
}

void desenhaLabirinto(int **matLabirinto)
{
	for (int i = 0; i< 10; i++)
	{
		for (int z = 0; z < 10 - 1; z++)
		{
			//cout << matLabirinto[i][z] << endl;
		}
	}
	int nivel = matLabirinto[0][0];
	//cout << "nivel: " << nivel << endl;
	//dimenção matriz
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
				glBegin(GL_POLYGON);
				glColor3f(0, 0, 255);
				glVertex2f(0 + (j * 10), 0 + ((i - 1) * 10));
				glVertex2f(0 + (j * 10), 10 + ((i - 1) * 10));
				glVertex2f(10 + (j * 10), 10 + ((i - 1) * 10));
				glVertex2f(10 + (j * 10), 0 + ((i - 1) * 10));
				glEnd();
			}

			if (matLabirinto[i][j] != 0 && x == 20)
			{
				glBegin(GL_POLYGON);
				glColor3f(0, 0, 255);
				glVertex2f(0 + (j * 5), 0 + ((i - 1) * 5));
				glVertex2f(0 + (j * 5), 5 + ((i - 1) * 5));
				glVertex2f(5 + (j * 5), 5 + ((i - 1) * 5));
				glVertex2f(5 + (j * 5), 0 + ((i - 1) * 5));
				glEnd();
			}
			if (matLabirinto[i][j] != 0 && x == 25)
			{
				glBegin(GL_POLYGON);
				glColor3f(0, 0, 255);
				glVertex2f(0 + (j * 4), 0 + ((i - 1) * 4));
				glVertex2f(0 + (j * 4), 4 + ((i - 1) * 4));
				glVertex2f(4 + (j * 4), 4 + ((i - 1) * 4));
				glVertex2f(4 + (j * 4), 0 + ((i - 1) * 4));
				glEnd();
			}
		}
	}
	/*
	glBegin(GL_POLYGON);
	glColor3f(0,0,255);
	glVertex2f(0, 0);
	glVertex2f(0, 10);
	glVertex2f(10, 10);
	glVertex2f(10, 0);
	glEnd();
	*/

	quad.dimensao = matLabirinto[0][6];
	//cout << " ola " << endl;
	//cout << matLabirinto[0][4] << endl;
	//cout << matLabirinto[0][3] << " -----" << endl;
	//quad.x = matLabirinto[0][3], quad.y = matLabirinto[0][1];
	//cout << matLabirinto[0][3] << ";" << matLabirinto[0][1];
	desenhaQuadrado(quad.x = quad.x + 0, quad.y = quad.y + 0);
	quad.matrix = matLabirinto;
	criarPerdicados(matLabirinto);
}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f (1.0, 1.0, 1.0);
	glLoadIdentity();
	/* clear the matrix */

	int **matLabirinto;
	matLabirinto = carregarMatriz("teste2.txt");
	//quad.matPos = matLabirinto;
	desenhaLabirinto(matLabirinto);

	glFlush();

}



void reshape(int w, int h)

{

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluOrtho2D(0, 100, 100, 0);

	glMatrixMode(GL_MODELVIEW);

}


void Key(unsigned char key, int x, int y)
{
	switch (key) {
	case 'A':
	case 'a': tecla.a = GL_TRUE;

		cout << quad.matrix[quad.y][quad.x] << endl;
		cout << "pos x: " << quad.x << " pos.y " << quad.y << endl;
		cout << "aaa" << endl;
		if (quad.matrix[quad.y][quad.x - 1] == 0)
		{
			cout << " ola aaa " << endl;
			quad.x = quad.x - 1;
		}

		//if(quad.matrix[quad.x][quad.y] == 0)
		//{

		//}

		//quad.y = 1;
		break;
	case 'W':
	case 'w': tecla.w = GL_TRUE;
		if (quad.matrix[quad.y - 1][quad.x] == 0)
		{
			quad.y = quad.y - 1;
		}
		//quad.x = quad.x;

		cout << quad.matrix[quad.y][quad.x] << endl;
		cout << "pos x: " << quad.x << " pos.y " << quad.y << endl;

		cout << "wwww" << endl;
		break;
	case 'S':
	case 's': tecla.s = GL_TRUE;
		//quad.x = quad.x;
		if (quad.matrix[quad.y + 1][quad.x] == 0)
		{
			cout << " diabooooo " << endl;
			quad.y = quad.y + 1;
		}


		cout << "sss" << endl;
		break;
	case 'D':
	case 'd': tecla.d = GL_TRUE;
		if (quad.matrix[quad.y][quad.x + 1] == 0)
		{
			cout << " Bom diaaaaaa " << endl;
			quad.x = quad.x + 1;
		}
		break;

	case 'H':
	case 'h': tecla.d = GL_TRUE;
		fastestWayAvailable(quad.matrix, quad.x, quad.y);
		break;

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
		desenhaQuadrado(5, 5);
		//sleep(100);

	}
	//cout << "olaaaaaaaa aaaaa sssssssss" << endl;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	//carregarMatriz("teste.txt");
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(500, 500);

	glutInitWindowPosition(100, 100);

	glutCreateWindow(argv[0]);

	//init ();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);
	glutTimerFunc(20, TimerTeclas, 0);

	init();
	glutMainLoop();

	return 0;



}
