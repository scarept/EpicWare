#ifndef WCF_H
#define WCF_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <WebServices.h>
#include <EpicService\schemas.microsoft.com.2003.10.Serialization.xsd.h>
#include <EpicService\schemas.microsoft.com.2003.10.Serialization.Arrays.xsd.h>
#include <EpicService\tempuri.org.xsd.h>
#include <EpicService\tempuri.org.wsdl.h>
#include <EpicService\EpicWareWeb.xsd.h>
#include <EpicService\EpicWareWeb.Models.xsd.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class WCF
{
private:

	wchar_t * stringToWchar(string texto);

public:
	
	WCF();
	~WCF();
	vector<Word> getEveryWord();
	vector<int> getAllUsers(void);
	//int getConnectionStrenght(int, int);
	User* getUserAutentication(string username, string password);
	vector<int> getUserFiends(string username, string password, int idUser);
};

#endif