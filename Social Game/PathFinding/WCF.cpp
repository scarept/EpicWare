#include "WCF.h"
#include <string>
#include <vector>
#include <iostream>

const WS_STRING url = WS_STRING_VALUE(L"http://localhost:8733/Design_Time_Addresses/SocialGameService/Service1");

HRESULT hr = ERROR_SUCCESS;
WS_ERROR* error = NULL;
WS_HEAP* heap = NULL;
WS_SERVICE_PROXY* proxy = NULL;
WS_ENDPOINT_ADDRESS address = {};

WCF::WCF()
{
	//endereço do serviço
	address.url = url;

	hr = WsCreateHeap(4096, 512, NULL, 0, &heap, error);
	WS_HTTP_BINDING_TEMPLATE templ = {};
	//criação do proxy para o serviço
	hr = BasicHttpBinding_IService1_CreateServiceProxy(&templ, NULL, 0, &proxy, error);
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

vector<int> WCF::getFriendsByUser(int userID){
	 
	//Numero de palavras retornadas
	unsigned int n = 0;
	int *ids;
	vector<int> friendsVector;
	
	//chamada de uma operação do service – getEveryWord. O resultado vem no parâmetro words
	hr = BasicHttpBinding_IService1_getUserConnected(proxy, userID, &n, &ids, heap, NULL, 0, NULL, error);

	for (int i = 0; i < n; i++){
		friendsVector.push_back(*ids);
		ids = ids + 1;
	}

	return friendsVector;
}

vector<int> WCF::getAllUsers(void){
	unsigned int n = 0;
	int *ids;
	vector<int> users;

	hr = BasicHttpBinding_IService1_getAllUsers(proxy, &n, &ids, heap, NULL, 0, NULL, error);

	for (int i = 0; i < n; i++){
		users.push_back(*ids);
		ids = ids + 1;
	}

	return users;
}

int WCF::getConnectionStrenght(int id1, int id2){
	unsigned int n = 0;
	int strenght;

	hr = BasicHttpBinding_IService1_getConnectionStrenght(proxy, id1, id2, &strenght, heap, NULL, 0, NULL, error);

	return strenght;
}