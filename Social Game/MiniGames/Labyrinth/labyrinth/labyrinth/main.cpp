#include <iostream> 
#include <fstream> 
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include "Prolog.h"
#include "SOIL.h"

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

typedef struct{
	int *posGPS;
	bool gps;
	GLuint imagem;
	GLuint textura_paredes;
	GLuint caminho_text;
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

void init(void)

{
	/*
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	float pixels[] = {
		0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
	};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
	*/
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	mod.imagem = SOIL_load_OGL_texture
		(
		"teste.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);


	/* check for an error during the load process */
	if (0 == mod.imagem)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	mod.textura_paredes = SOIL_load_OGL_texture
		(
		"parede.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);


	/* check for an error during the load process */
	if (0 == mod.textura_paredes)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}


	/*      textura caminhos  */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	mod.caminho_text = SOIL_load_OGL_texture
		(
		"fundo.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);


	/* check for an error during the load process */
	if (0 == mod.caminho_text)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}





	/*pos inicioal*/
	ifstream ficheiro("teste.txt", ios::in);
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
	
	
	glBindTexture(GL_TEXTURE_2D, mod.imagem);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 0.5); //transparencias 
	glBegin(GL_POLYGON);
	//glColor3f(0, 100, 100);
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

	quad.dimensao = matLabirinto[0][6];
	//cout << " ola " << endl;
	//cout << matLabirinto[0][4] << endl;
	//cout << matLabirinto[0][3] << " -----" << endl;
	//quad.x = matLabirinto[0][3], quad.y = matLabirinto[0][1];
	//cout << matLabirinto[0][3] << ";" << matLabirinto[0][1];
	desenhaQuadrado(quad.x = quad.x + 0, quad.y = quad.y + 0);
	quad.matrix = matLabirinto;
	//criarPerdicados(matLabirinto);
}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f (1.0, 1.0, 1.0);
	glLoadIdentity();
	/* clear the matrix */

	int **matLabirinto;
	matLabirinto = carregarMatriz("teste.txt");
	//quad.matPos = matLabirinto;
	pintarGPS();
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
		cout<< quad.matrix[0][3]<<endl;
		cout << quad.matrix[0][4] << endl;

		cout << quad.y << endl;
		cout << quad.x << endl;
		//quad.x = quad.x;
		if (quad.matrix[0][3] == quad.y +1 && quad.matrix[0][4] == quad.x){
			cout << " FIM 11111111111111111 " << endl;
		}

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
		mod.posGPS = fastestWayAvailable(quad.matrix, quad.x, quad.y);
		mod.gps = true;
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
	mod.gps = false;
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

