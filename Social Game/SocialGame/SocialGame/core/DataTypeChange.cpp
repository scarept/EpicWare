#include "DataTypeChange.h"

char* wcharToChar(wchar_t *texto){
	int i = 0;
	char *retorno = "";
	const int tamanho = wcslen(texto);
	char lista[60];
	//retorno = "a";
	//	char lista[tamanho];
	string aa;
	aa = *texto;
	while (texto[i] != '\0'){
		char letra = texto[i];
		lista[i] = letra;
		i++;
	}

	retorno = lista;

	return lista;
}

string wcharToString(wchar_t *texto){

	char textoString[260];
	char DefChar = ' ';
	WideCharToMultiByte(CP_ACP, 0, texto, -1, textoString, 260, &DefChar, NULL);

	std::string ss(textoString);

	return textoString;
}