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