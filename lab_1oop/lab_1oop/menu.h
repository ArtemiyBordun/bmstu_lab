#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>

#include "figures.h"
#include "figuremanager.h"

using namespace std;

enum POSCHOICE {
	INCORRECT = -1,
	ADD = 1,
	PRINTPARAM = 2,
	PRINTAREA = 3,
	PRINTSUM = 4,
	SORT = 5,
	REMOVEBYNUM = 6,
	REMOVEBYMAXAREA = 7,
	SECRET = 42,
	EXIT = 0
};

class Menu
{
private:
	vector<Figure*> figures;
	FigureManager* manager;
public:
	Menu() = default;
	Menu(vector<Figure*>& figures);

	void handle();
	int getUserChoice();
	void printMenu();
	void clearCin();

	void exitPrint();
	void printInvalid();
	void printInfo(bool needArea);
	void printSumArea();

	void printCat();
};

#endif