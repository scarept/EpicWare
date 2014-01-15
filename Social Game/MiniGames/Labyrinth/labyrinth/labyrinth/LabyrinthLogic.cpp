using namespace std;

#include <iostream>
#include <SWI-Prolog\include\SWI-Prolog.h>
#include <SWI-Prolog\include\SWI-Stream.h>
#include <SWI-Prolog\include\SWI-cpp.h>
#include "Labyrinth.h"

int* fastestWayAvailable(int **matriz, int y, int x){
	//x = 2;
	//y = 1;
	int xFinal = matriz[0][3];
	int yFinal = matriz[0][4];
	//xFinal = 4;
	//yFinal = 8;



	
	char* dummy_args[] = { "libswipl.dll", "-s", "./pl/labyrinthIA.pl", NULL };
	PlEngine e(3, dummy_args);
	
	/* Colocar informação da matriz na base de conhecimento*/
	assertData(matriz);

	//char solution[255];

	PlTermv av(3);
	/* colocar dinamico */
	//av[0] = PlCompound("'(2,1)'"); // start point (current point)
	//av[1] = PlCompound("'(2,3)'"); // end point

	/*                                      */
	char *pointerInicial;
	char tempArr1[10];
	sprintf(tempArr1, "'(%d,%d)'", x, y);
	pointerInicial = tempArr1;
	//PlTermv az(pointerVal1, pointerVal2);
	av[0] = PlCompound(tempArr1);

	char *pointerFinal;
	char tempArr2[10];
	sprintf(tempArr2, "'(%d,%d)'", xFinal, yFinal);
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
			else if (*resTemp == ',' && segundo==1){
				segundo = 0;
				resTemp++;
				int num = atoi(resTemp);
				//valor = valor * 10;
				//valor = valor + num;
				valor = num;

				finalSize++;
				solution[finalSize] = valor;
				cout << valor << endl;

			}else {

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

/*
Recebe a matriz usada para desenhar o labirinto, e sempre que existe uma ligação entre 2 blocos é chamada a "joinConection" para criar o perdicado dinamico.
*/
void assertData(int **matriz){

	
	//char* argv[]= { "libswipl.dll", "-s", ".\/pl\/labyrinthIA.pl", NULL };

	//PlEngine e(3, argv);

	//PlTerm tt("liga(_,_)");
	//PlQuery r("retractall", tt);
	//r.next_solution();

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
				int tempXi = i;
				int tempYi = j - 1;

				int tempXf = i;
				int tempYf = j;

				joinConection(tempXi, tempYi, tempXf, tempYf);
				joinConection(tempXf, tempYf, tempXi, tempYi);

			}
			if (matriz[i][j] == 0 && matriz[(i - 1)][j] == 0)
			{
				int tempXi = i - 1;
				int tempYi = j;

				int tempXf = i;
				int tempYf = j;

				joinConection(tempXi, tempYi, tempXf, tempYf);
				joinConection(tempXf, tempYf, tempXi, tempYi);
			}
		}
	}
}

/*
Responsavel por inserir os valores que lhe são passados na base de conhecimento dinamica PROLOG.
Formato liga('(0,0)','(0,0)').
*/
void joinConection(int tempXi, int tempYi, int tempXf, int tempYf){

	PlTermv bv(2);

	char *pointerVal1;
	char tempArr1[10];
	sprintf(tempArr1, "(%d,%d)", tempXi, tempYi);
	pointerVal1 = tempArr1;

	char *pointerVal2;
	char tempArr2[10];
	sprintf(tempArr2, "(%d,%d)", tempXf, tempYf);
	pointerVal2 = tempArr2;


	PlTermv az(pointerVal1, pointerVal2);
	bv[0] = PlCompound("liga", az);
	cout << (char*)bv[0] << endl;
	PlQuery p("asserta", bv);
	p.next_solution();


}
