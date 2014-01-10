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
	//endere�o do servi�o
	address.url = url;

	hr = WsCreateHeap(2048, 512, NULL, 0, &heap, error);
	WS_HTTP_BINDING_TEMPLATE templ = {};
	//cria��o do proxy para o servi�o
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

	//chamada de uma opera��o do service � getEveryWord. O resultado vem no par�metro words
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
//	//chamada de uma opera��o do service � getEveryWord. O resultado vem no par�metro words
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