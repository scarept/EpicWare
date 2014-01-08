#ifndef WCF_H
#define WCF_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "WebServices.h" 
#include "schemas.microsoft.com.2003.10.Serialization.xsd.h" 
#include "tempuri.org.xsd.h" 
#include "tempuri.org.wsdl.h" 
#include "SocialGameService.xsd.h"
#include <string> 
#include <iostream> 
#include <stdlib.h>
#include <vector>

using namespace std;

class WCF
{
private:
public:
	
	WCF();
	~WCF();
	vector<int> getFriendsByUser(int);
	vector<int> getAllUsers(void);
	int getConnectionStrenght(int, int);
};

#endif