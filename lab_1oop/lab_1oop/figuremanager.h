#ifndef FIGUREMANAGER_H
#define FIGUREMANAGER_H

#include "figures.h"

#include <string> 
#include <iostream>
#include <algorithm>

#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

using namespace std;

class FigureManager
{
private:
	vector<Figure*> figures;
	//Menu menu;
public:
	FigureManager() = default;
	FigureManager(vector<Figure*>& figures);

	vector<Figure*> getFigures();

	void addFigures();
	void addCircle(string name);
	void addRectangle(string name);
	void addTriangle(string name);
	void deleteFigures();

	void sortFigure();
	void removeByNumber();
	void removeByMaxArea();
};

#endif