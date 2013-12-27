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
#include <vector>

class WCF
{
private:
public:
	
	WCF();
	~WCF();
	std::vector<Word> getEveryWord();
};

#endif