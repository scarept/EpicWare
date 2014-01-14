#include "PathFinder.h"

PathFinder::PathFinder(){
	webService = new WCF();
}


PathFinder::~PathFinder(){}

void PathFinder::assertData(void){
	vector<int> users = webService->getAllUsers();
	
	for each (int user in users){
		vector<int> friends = webService->getUserFiends(username,password,user);
		for each(int userFriend in friends)
			joinConnection(user, userFriend);
	}

	webService->~WCF();
}

void PathFinder::joinConnection(int user, int userFriend){
	string userStr, friendStr;
	_itoa(user, &userStr[0], 10);
	_itoa(userFriend, &friendStr[0], 10);
	strcat(&userStr[0],",");
	strcat(&friendStr[0],",");
	try{
		PlTermv term(2);
		PlTermv stats(userStr.c_str(), friendStr.c_str());
		term[0] = PlCompound("liga", stats);
		PlQuery query("asserta", term);
		query.next_solution();
	}
	catch (PlException &ex){
		cout << (char *)ex << endl;
	}
}

void PathFinder::assertDataStrenght(void){
	int strenght;
	vector<int> users = webService->getAllUsers();

	for each (int user in users){
		vector<int> friends = webService->getUserFiends(username, password, user);
		for each(int userFriend in friends){
			strenght = webService->getConnectionStrenght(user, userFriend);
			joinConnection(user, userFriend, strenght);
		}
	}
	webService->~WCF();
}

void PathFinder::joinConnection(int user, int userFriend, int strenght){
	string userStr, friendStr, strenghtStr;
	
	_itoa(user, &userStr[0], 10);
	_itoa(userFriend, &friendStr[0], 10);
	_itoa(strenght, &strenghtStr[0], 10);
	strcat(&userStr[0], ",");
	strcat(&friendStr[0], ",");
	//strcat(&strenghtStr[0], ",");
	try{
		PlTermv term(2);
		PlTermv stats(userStr.c_str(), friendStr.c_str(), strenghtStr.c_str());
		term[0] = PlCompound("liga", stats);
		PlQuery query("assertz", term);
		query.next_solution();
	}
	catch (PlException &ex){
		cout << (char *)ex << endl;
	}

}

vector<int> PathFinder::getShortestPath(int user1, int user2){
	string user1Str, user2Str;
	vector<int> path;
	_itoa(user1, &user1Str[0], 10);
	_itoa(user2, &user2Str[0], 10);

	strcat(&user1Str[0], ",");
	strcat(&user2Str[0], ",");

	PlTermv av(3);
	av[0] = user1Str.c_str();
	av[1] = user2Str.c_str();
	
	PlQuery q("go", av);
	try{
		int i = 0;
		while (q.next_solution()){
			if (i < 1){
				char *indexes = strtok((char *)av[2], " ,'[]");
				if (indexes == NULL)
					return path;

				while (indexes != NULL){
					path.push_back(atoi(indexes));
					indexes = strtok(NULL, " ,'[]");
				}
			}
			i++;
		}
	}
	catch (PlException &ex){
		cout << (char *)ex << endl;
	}
	return path;
}

vector<int> PathFinder::getHeaviestPath(int user1, int user2){
	char user1Str[10], user2Str[10];
	char tempNode[256], tempCost[10];
	string tmp;
	vector<int> path;
	char *indexes;
	_itoa(user1, user1Str, 10);
	_itoa(user2, user2Str, 10);
	strcat(user1Str, ",");
	strcat(user2Str, ",");
	
	PlTermv av(4);
	av[0] = user1Str;
	av[1] = user2Str;
	PlQuery q("go", av);
	try{
		while (q.next_solution()){
			strcpy(tempNode, (char *)av[2]);
			strcpy(tempCost, (char *)av[3]);
		}

		if (&tempNode[0] == NULL)
			return path;
		
		indexes = strtok(&tempNode[0], " ,'[]");
		while (indexes != NULL){
			path.push_back(atoi(indexes));
			indexes = strtok(NULL, " ,'[]");
		}
	}
	catch (PlException &ex){
		cout << (char *)ex << endl;
	}
	return path;
}

vector<int> PathFinder::startPath(bool isHeaviest, int argc, char **argv, int id1, int id2){
	char file[80];
	if (isHeaviest)
		strcpy(file, "heaviest.pl");
	else
		strcpy(file, "caminho_mais_curto.pl");

	_putenv("SWI_HOME_DIR=C:\\Program Files\\swipl");
	char* dummy_args[] = { argv[0], "-s", file, NULL };

	argv = dummy_args;
	argc = sizeof(dummy_args) / sizeof(dummy_args[0]) - 1;

	PlEngine e(3, argv);

	if (isHeaviest){
		assertDataStrenght();
		return getHeaviestPath(id1, id2);
	}
	assertData();
	return getShortestPath(id1, id2);
}