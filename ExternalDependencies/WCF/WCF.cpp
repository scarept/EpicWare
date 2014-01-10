#include "WCF.h"
#include <string>
#include <vector>

const WS_STRING url = WS_STRING_VALUE(L"http://wvm074.dei.isep.ipp.pt/LAPR5/WebService.svc?wsdl");

HRESULT hr = ERROR_SUCCESS;
WS_ERROR* error = NULL;
WS_HEAP* heap = NULL;
WS_SERVICE_PROXY* proxy = NULL;
WS_ENDPOINT_ADDRESS address = {};

WCF::WCF()
{
	//endereço do serviço
	address.url = url;

	hr = WsCreateHeap(2048, 512, NULL, 0, &heap, error);
	WS_HTTP_BINDING_TEMPLATE templ = {};
	//criação do proxy para o serviço
	hr = BasicHttpBinding_IWebService_CreateServiceProxy(&templ, NULL, 0, &proxy, error);
	hr = WsOpenServiceProxy(proxy, &address, NULL, error);
}

WCF::~WCF()
{
	if (proxy){
		WsCloseServiceProxy(proxy, NULL, NULL);
		WsFreeServiceProxy(proxy);
	}
	if (heap){ WsFreeHeap(heap); }
	if (error){ WsFreeError(error); }
}

std::vector<Word> WCF::getEveryWord(){

	//Numero de palavras retornadas
	unsigned int n = 0;

	Word* words;
	std::vector<Word> wordVector;

	//chamada de uma operação do service – getEveryWord. O resultado vem no parâmetro words
	hr = BasicHttpBinding_IWebService_GetEveryWord(proxy, &n, &words, heap, NULL, 0, NULL, error);
	
	for (int i = 0; i < n; i++){

		wordVector.push_back(*words);

		words = words + 1;
	}

	return wordVector;
}

//vector<int> WCF::getFriendsByUser(int userID){
//
//	//Numero de palavras retornadas
//	unsigned int n = 0;
//	int *ids;
//	vector<int> friendsVector;
//
//	//chamada de uma operação do service – getEveryWord. O resultado vem no parâmetro words
//	hr = BasicHttpBinding_ISWebService_getUserConnected(proxy, userID, &n, &ids, heap, NULL, 0, NULL, error);
//
//	for (int i = 0; i < n; i++){
//		friendsVector.push_back(*ids);
//		ids = ids + 1;
//	}
//
//	return friendsVector;
//}

vector<int> WCF::getAllUsers(void){
	unsigned int n = 0;
	int *ids;
	vector<int> users;

	hr = BasicHttpBinding_IWebService_getAllUsersID(proxy, &n, &ids, heap, NULL, 0, NULL, error);

	for (int i = 0; i < n; i++){
		users.push_back(*ids);
		ids = ids + 1;
	}

	return users;
}

//int WCF::getConnectionStrenght(int id1, int id2){
//	unsigned int n = 0;
//	int strenght;
//
//	hr = BasicHttpBinding_IWebService_getConnectionStrenght(proxy, id1, id2, &strenght, heap, NULL, 0, NULL, error);
//
//	return strenght;
//}

wchar_t * stringToWchar(string texto){

	wchar_t* wCharTexto = new wchar_t[1023];
	size_t* size = new size_t;
	size_t sizeInWords = 256;

	const char* cStr;
	cStr = texto.c_str();
	mbstowcs_s(size, wCharTexto, sizeInWords, cStr, strlen(cStr) + 1);

	return wCharTexto;
}

User* WCF::getUserAutentication(string username, string password){
	unsigned int n = 0;
	int *ids;
	vector<int> users;
	User *teste = NULL;

	/* eliminar depois dos testes */
	if (username == ""){
		username = "Halsahaf";
	}

	if (password == ""){
		password = "123456";
	}

	if (username != "" && password != ""){
		
		wchar_t* wcharUsername = new wchar_t[1023];
		size_t* sizeOut = new size_t;
		size_t sizeInWords = 256;

		const char* cStr;
		cStr = username.c_str();
		mbstowcs_s(sizeOut, wcharUsername, sizeInWords, cStr, strlen(cStr) + 1);

		wchar_t* wcharPassword = new wchar_t[1023];
		size_t* sizeOut2 = new size_t;
		size_t sizeInWords2 = 256;

		const char* cStr2;
		cStr2 = password.c_str();
		mbstowcs_s(sizeOut2, wcharPassword, sizeInWords, cStr2, strlen(cStr2) + 1);
		

		//wchar_t * wcharUsername = stringToWchar(username);
		//wchar_t * wcharPassword = stringToWchar(password);

		hr = BasicHttpBinding_IWebService_getUserByAutetication(proxy, wcharUsername, wcharPassword, &teste, heap, NULL, 0, NULL, error);
	} 

	return teste;

}

/*
User* WCF::getUserFiends(string username, string password, int idUser){
	unsigned int n = 0;
	int *ids;
	vector<int> users;
	User *teste = NULL;

	if (username == ""){
		username = "Halsahaf";
	}

	if (password == ""){
		password = "123456";
	}

	//stringw(aa.c_str()).c_str();

	wchar_t* wCharOutput = new wchar_t[1023];
	size_t* sizeOut = new size_t;
	size_t sizeInWords = 256;

	const char* cStr;
	cStr = username.c_str();
	mbstowcs_s(sizeOut, wCharOutput, sizeInWords, cStr, strlen(cStr) + 1);

	wchar_t* wCharOutput2 = new wchar_t[1023];
	size_t* sizeOut2 = new size_t;
	size_t sizeInWords2 = 256;

	const char* cStr2;
	cStr2 = password.c_str();
	mbstowcs_s(sizeOut2, wCharOutput2, sizeInWords, cStr2, strlen(cStr2) + 1);

	unsigned int *numero;

	User dd[10];

	hr = BasicHttpBinding_IWebService_getUserFriendsByUserId(proxy,idUser, wCharOutput, wCharOutput2,numero, dd, heap, NULL, 0, NULL, error);

	return teste;

}
*/