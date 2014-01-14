#include "Grafo.h"
#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>     



//conversoes
#define radToDeg(x)   (180*(x)/M_PI)
#define degToRad(x)   (M_PI*(x)/180)

#define __GRAFO__FILE__ "exemplo.grafo"

No nos[_MAX_NOS_GRAFO];
Arco arcos[_MAX_ARCOS_GRAFO];
int numNos=0, numArcos=0;

using namespace std;

void addNo(No no){
	if(numNos<_MAX_NOS_GRAFO){
		nos[numNos]=no;
		numNos++;
	}else{
		cout << "Número de nós chegou ao limite" << endl;
	}
}

void deleteNo(int indNo){
	if(indNo>=0 && indNo<numNos){
		for(int i=indNo; i<numNos; nos[i++]=nos[i+i]);
		numNos--;
	}else{
		cout << "Indíce de nó inválido" << endl;
	}
}

void imprimeNo(No no){
	cout << "X:" << no.x << "Y:" << no.y << "Z:" << no.z <<endl;
}

void listNos(){
	for(int i=0; i<numNos; imprimeNo(nos[i++]));
}

No criaNo(float x, float y, float z){
	No no;
	no.x=x;
	no.y=y;
	no.z=z;
	return no;
}

void addArco(Arco arco){
	if(numArcos<_MAX_ARCOS_GRAFO){
		arcos[numArcos]=arco;
		numArcos++;
	}else{
		cout << "Número de arcos chegou ao limite" << endl;
	}
}

void deleteArco(int indArco){
	if(indArco>=0 && indArco<numArcos){
		for(int i=indArco; i<numArcos; arcos[i++]=arcos[i+i]);
		numArcos--;
	}else{
		cout << "Indíce de arco inválido" << endl;
	}
}

void imprimeArco(Arco arco){
	cout << "No início:" << arco.noi << "Nó final:" << arco.nof << "Peso:" << arco.peso << "Largura:" << arco.largura << endl;
}

void listArcos(){
	for(int i=0; i<numArcos; imprimeArco(arcos[i++]));
}

Arco criaArco(int noi, int nof, float peso, float forcaLig){
	Arco arco;
	arco.noi=noi;
	arco.nof=nof;
	arco.peso=peso;
	arco.forcaLig = forcaLig;

	return arco;
}

void gravaGrafo(){
	ofstream myfile;

	myfile.open (__GRAFO__FILE__, ios::out);
	if (!myfile.is_open()) {
		cout << "Erro ao abrir " << __GRAFO__FILE__ << "para escrever" <<endl;
		exit(1);
	}
	myfile << numNos << endl;
	for(int i=0; i<numNos;i++)
		myfile << nos[i].x << " " << nos[i].y << " " << nos[i].z <<endl;
	myfile << numArcos << endl;
	for(int i=0; i<numArcos;i++)
		myfile << arcos[i].noi << " " << arcos[i].nof << " " << arcos[i].peso << " " << arcos[i].forcaLig << endl;
	myfile.close();
}

void ligacaoNos(int noi, int nof){
	arcos[numArcos].noi = noi;
	arcos[numArcos].nof = nof;
	arcos[numArcos].peso = 10;
	arcos[numArcos].forcaLig = 2;
	arcos[numArcos].largura = 1;


	numArcos = numArcos + 1;

}

bool testaExistencia(int idUser){

	bool resultado = false;
	for (int i = 0; i < numNos; i++){
		if (nos[i].userId != idUser){
			resultado = false;
		
		}
		else{

			return resultado = true;
		}

	}
	return resultado;
}

int contaDiferentes(vector<int> amigosDiretos){

	int resultado=0;
	int tamanho = amigosDiretos.size();
	for (int i = 0; i < numNos; i++){
		for (int j = 0; j < tamanho;j++){
			if (amigosDiretos[j] == nos[i].userId){
				resultado++;
			}
		}
	}
	resultado = tamanho - resultado;
	return resultado;
}

void distribuicaoRadial(No no_inicio, vector<int> amigosDiretos, int nivel){
	//definir no inicio do ficheiro
	nivel = nivel + 1;
	float pi = 3.14;
	float raio = 14/nivel;
	float altura = -2-nivel;
	
	double alpha;

	int tamanhoLista = amigosDiretos.size();
	int tamanho = contaDiferentes(amigosDiretos);

	if (tamanho != 0){
		alpha = 360 / tamanho;
		alpha = degToRad(alpha);
	}
	for (int i = 0; i < tamanhoLista; i++){

		if (testaExistencia(amigosDiretos[i]) == false){
			float x = raio * ((cos(i*alpha)));
			float y = raio * (sin(i*alpha));

			nos[numNos].nome = "ND";
			nos[numNos].userId = amigosDiretos[i];
			nos[numNos].x = x + no_inicio.x;
			nos[numNos].y = y + no_inicio.y;
			nos[numNos].z = no_inicio.z + altura;
			/* função que conta o numero de tags MUDAR*/
			nos[numNos].largura = 1;
			nos[numNos].nivel = nivel;

			numNos = numNos + 1;

			ligacaoNos(no_inicio.userId, amigosDiretos[i]);
		}
		else{
			/* caso o nó já exista, e apenas é necessario a ligação */
			ligacaoNos(no_inicio.userId, amigosDiretos[i]);
		}
	}

}


void leGrafo(No  user1, vector<int> listaNos, int nivel, int posActual){
	No user;
	float alturaMaxima=18;
	if (nivel == 1){ // se for o nivel raiz;
		user = nos[0];
		//No user;
		user.x = 0;
		user.y = 0;
		user.z = alturaMaxima;
		user.largura = 2;
		//user.userId = 1;
		user.nome = "Eu";
		user.nivel = nivel;

		nos[0] = user;
	}
	else{
		user = nos[posActual];

	
	}
	//numNos = 1;
	//numArcos = 0;

	//int amigos[] = { 11, 2, 3,4,5,6,7,8,9,10,11,12 };
	distribuicaoRadial(user, listaNos, nivel);



	/*
	nos[0].userId = 1;
	nos[0].x = 0;
	nos[0].y = 0;
	nos[0].z = 0;
	nos[0].largura = 2; // calculo por numero de tags

	nos[1].userId = 2;
	nos[1].x = 5;
	nos[1].y = 5;
	nos[1].z = 5;
	nos[1].largura = 2;
	*/
	/*
	arcos[0].noi = 1;
	arcos[0].nof = 2;
	arcos[0].peso = 10;
	arcos[0].forcaLig = 2;
	arcos[0].largura = 1;
	*/
	//numNos = 2;
	//numArcos = 1;



	/*
	ifstream myfile;

	myfile.open (__GRAFO__FILE__, ios::in);
	if (!myfile.is_open()) {
	cout << "Erro ao abrir " << __GRAFO__FILE__ << "para ler" <<endl;
	exit(1);
	}

	myfile >> numNos;
	for (int i = 0; i < numNos; i++)
	myfile >> nos[i].x >> nos[i].y >> nos[i].z;
	myfile >> numArcos ;
	for(int i=0; i<numArcos;i++)
	myfile >> arcos[i].noi >> arcos[i].nof >> arcos[i].peso >> arcos[i].forcaLig >> arcos[i].largura;
	myfile.close();
	
	// calcula a largura de cada no = maior largura dos arcos que divergem/convergem desse/nesse no
	for (int i = 0; i<2; i++){
	nos[i].largura = 0;
	for (int j = 0; j<1; j++)
	//caso a ligação seja maior que o tamanho do nó
	if ((arcos[j].noi == i || arcos[j].nof == i) && nos[i].largura < arcos[j].forcaLig)
	nos[i].largura = arcos[j].forcaLig;
	}
	*/


}

