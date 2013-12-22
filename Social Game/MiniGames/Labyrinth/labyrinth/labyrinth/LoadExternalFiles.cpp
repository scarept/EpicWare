#include "LoadExternalFiles.h"

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
	/*
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
	*/


	return matLabirinto;
}