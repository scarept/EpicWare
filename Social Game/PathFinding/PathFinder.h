#ifndef PATHFINDER_H
#define PATHFINDER_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "WCF.h"
#include <iostream>
#include <SWI-Prolog.h>
#include <SWI-Stream.h>
#include <SWI-cpp.h>
#include <string>
#include <vector>

using namespace std;

class PathFinder
{
private:
	WCF *webService;
	/*
	Treats and asserts connections between users into the prolog engine
	*/
	void assertData(void);
	/*
	Assert a single connection between two users into prolog engine
	*/
	void joinConnection(int, int);
	/*
	Treats and asserts connections with strenght between users into the prolog engine
	*/
	void assertDataStrenght(void);
	/*
	Assert a single connection between two users with strenght attached
	*/
	void joinConnection(int, int, int);
	/*
	Returns the shortest path between two users
	*/
	vector<int> getShortestPath(int, int);
	/*
	Returns the heaviest path between two users
	*/
	vector<int> getHeaviestPath(int, int);
public:
	PathFinder();
	~PathFinder();
	/*starts the path search*/
	vector<int> startPath(bool, int, char **, int, int);
};

#endif
