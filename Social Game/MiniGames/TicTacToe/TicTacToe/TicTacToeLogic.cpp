#include <SWI-Prolog.h>
#include <SWI-Stream.h>
#include <SWI-cpp.h>
#include <iostream> 
#include <fstream> 
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "TicTacToeLogic.h"

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
	cout << (char*)bv1[0] << endl;
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

	_putenv("SWI_HOME_DIR=..\\..\\..\\..\\ExternalDependencies\\SWI-Prolog");
	char* argv[] = { "", "-s", "tictactoe.pl", NULL };

	PlEngine e(3, argv);
	assertData();

	PlTermv av(2);

	char *res = (char*)0;
	char *res2 = (char*)0;;

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
			return 1;

		}

		/* VERIFICACA SE JOGO TERMINOU SEM VENCEDOR*/
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
			return 2;
		}
		else{
			return 0;
		}
	}
}

int jogadaJogador(int l, int c)
{
	return validaJogada(1, l, c);
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