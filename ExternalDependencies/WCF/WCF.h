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
	int getConnectionStrenght(int, int);
	User* getUserAutentication(string username, string password); /*Alterar no cpp*/
	vector<int> getUserFiends(string username, string password, int idUser); /*Alterar no cpp*/
	UserData* WCF::getUserById(string username, string password, int idUser);/* alterar cpp */
	int WCF::getConnectioStrenght(string username, string password, int idUser1, int idUser2);
	int WCF::getNumberTagsForUserId(string username, string password, int idUser);
	vector<int> WCF::getFRReceivedPending(string username, string password, int idUser);
	BOOL WCF::getCreateFriendRequest(string username, string password, int idUser1, int idUser2);
	BOOL WCF::selectGameToPlay(string username, string password, int idFriendRequest, int idGame);
	BOOL WCF::acceptFriendRequest(string username, string password, int idFriendRequest);
	BOOL WCF::rejectFriendRequest(string username, string password, int idFriendRequest);
	BOOL WCF::registerGameResult(string username, string password, int idFriendRequest, int idGame, bool win, int points);
	vector<int> WCF::waitingGamePlay(string username, string password, int idUser);
};

#endif