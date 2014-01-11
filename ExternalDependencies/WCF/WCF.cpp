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

	hr = WsCreateHeap(4096, 512, NULL, 0, &heap, error);
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

int WCF::getConnectionStrenght(int id1, int id2){
	unsigned int n = 0;
	int strenght;

	hr = BasicHttpBinding_IWebService_getConnectioStrenght(proxy, id1, id2, &strenght, heap, NULL, 0, NULL, error);

	return strenght;
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

vector<int> WCF::getUserFiends(string username, string password, int idUser){
	unsigned int n = 0;
	int *ids;
	vector<int> friends;
	//username = "martinsmas";
	//password = "1812310";

	/*String conversion*/
	wchar_t *userN = new wchar_t[1024];
	wchar_t *passW = new wchar_t[1024];
	size_t *size = new size_t;
	
	try{
		mbstowcs_s(size, userN, 256, username.c_str(), username.length());
		mbstowcs_s(size, passW, 256, password.c_str(), password.length());
	}
	catch (exception &ex){
		cout << ex.what() << endl;
	}
	hr = BasicHttpBinding_IWebService_getUserFriendsByUserId(proxy, idUser, userN, passW, &n, &ids, heap, NULL, 0, NULL, error);
	for (int i = 0; i < n; i++){
		friends.push_back(*ids);
		ids++;
	}
	return friends;
}
