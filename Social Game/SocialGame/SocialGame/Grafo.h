#ifndef _GRAFO_INCLUDE
#define _GRAFO_INCLUDE

#define _MAX_NOS_GRAFO 100
#define _MAX_ARCOS_GRAFO 200

#define NORTE_SUL	0
#define ESTE_OESTE	1
#define PLANO		2

typedef struct No{
	float x, y, z, largura;
	char * tags;
	char * estadoHumor;
	int userId;
	char * nome;
}No;

typedef struct Arco{
	int noi, nof; //substituir depois pelo user id
	float peso, largura;
	float forcaLig;
	//char * userIdi;
	//char * userIdf;
	char * tag;
	float raio;
}Arco;
/*
typedef struct Ligacao{
	char * userIdi;
	char * userIdf;
	char * forcaRel;
	int noi;
	int nof;
	float raio;
} Ligacao;
*/
extern No nos[];
extern Arco arcos[];
//extern Ligacao ligacao[];

extern int numNos, numArcos;

void addNo(No);
void deleteNo(int);
void imprimeNo(No);
void listNos();
No criaNo(float, float, float);

void addArco(Arco);
void deleteArco(int);
void imprimeArco(Arco);
void listArcos();
Arco criaArco(int, int, float, float);

void gravaGrafo();
void leGrafo(No noAtual, int * listaNos);

#endif