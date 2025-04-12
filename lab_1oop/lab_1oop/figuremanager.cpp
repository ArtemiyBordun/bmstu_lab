#include "figuremanager.h"

FigureManager::FigureManager(vector<Figure*>& figures) : figures(figures) {}

void FigureManager::addFigures() {
    int figureType = 0;
    cout << "Enter the type of figure (1 - Circle, 2 - Rectangle, 3 - Triangle): ";
    cin >> figureType;

    if (figureType < CIRCLE || figureType > TRIANGLE) {
        cout << "Invalid figure type\n" << endl;
        //menu.clearCin();
    }
    else {
        string name = "";
        cout << "Enter the name of the figure: ";
        cin >> name;

        if (figureType == CIRCLE) {
            addCircle(name);
        }
        else if (figureType == RECTANGLE) {
            addRectangle(name);
        }
        else if (figureType == TRIANGLE) {
            addTriangle(name);
        }
    }
}

void FigureManager::addCircle(string name) {
    double pointCenterX, pointCenterY, radius = 0;
    cout << "Enter the center coordinates (x y): ";
    cin >> pointCenterX >> pointCenterY;

    Point coord(pointCenterX, pointCenterY);

    bool isCorrect = true;

    if (cin.good()) {
        cout << "Enter the radius: ";
        cin >> radius;
    }

    try {
        figures.push_back(new Circle(name, coord, radius));
        cout << "Circle added successfully\n" << endl;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void FigureManager::addRectangle(string name) {
    double pointTopLeftX, pointTopLeftY, pointBottomRightX, pointBottomRightY;
    cout << "Enter the top left coordinates (x y): ";
    cin >> pointTopLeftX >> pointTopLeftY;
    cout << "Enter the bottom right coordinates (x y): ";
    cin >> pointBottomRightX >> pointBottomRightY;

    if (cin.fail()) {
        pointBottomRightX = pointTopLeftX;
        pointBottomRightY = pointTopLeftY;
    }

    Point pointTop(pointTopLeftX, pointTopLeftY);
    Point pointBottom(pointBottomRightX, pointBottomRightY);

    try {
        figures.push_back(new Rectangle(name, pointTop, pointBottom));
        cout << "Rectangle added successfully\n" << endl;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void FigureManager::addTriangle(string name) {
    double pointVertex1X, pointVertex1Y, pointVertex2X, pointVertex2Y, pointVertex3X, pointVertex3Y;
    cout << "Enter the coordinates of vertex 1 (x y): ";
    cin >> pointVertex1X >> pointVertex1Y;
    Point coord1(pointVertex1X, pointVertex1Y);
    cout << "Enter the coordinates of vertex 2 (x y): ";
    cin >> pointVertex2X >> pointVertex2Y;
    Point coord2(pointVertex2X, pointVertex2Y);
    cout << "Enter the coordinates of vertex 3 (x y): ";
    cin >> pointVertex3X >> pointVertex3Y;
    if (cin.fail()) {
        pointVertex3X = pointVertex1X;
        pointVertex3Y = pointVertex1Y;
    }
    Point coord3(pointVertex3X, pointVertex3Y);

    try {
        figures.push_back(new Triangle(name, coord1, coord2, coord3));
        cout << "Triangle added successfully\n" << endl;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void FigureManager::deleteFigures() {
    for (const auto& figure : figures)
        delete figure;
}

vector<Figure*> FigureManager::getFigures() {
    return figures;
}

void FigureManager::sortFigure() {
    if (figures.empty())
        cout << "Nothing to sort, nt:)" << endl;
    else {
        sort(figures.begin(), figures.end(), [](const Figure* a, const Figure* b) {
            return a->getArea() < b->getArea();
            });
        cout << "Figures sorted by area" << endl;
    }
}

void FigureManager::removeByNumber() {
    int number;
    cout << "Enter the number of the figure to remove: ";
    cin >> number;

    if (number >= 1 && number <= figures.size()) {
        delete figures[number - 1];
        figures.erase(figures.begin() + number - 1);
        cout << "Figure removed successfully" << endl;
    }
    else
        cout << "Invalid figure number" << endl;
}

void FigureManager::removeByMaxArea() {
    double maxArea;
    cout << "Enter the maximum area value: ";
    cin >> maxArea;
    if (maxArea <= 0)
        cout << "Incorrect area\n";
    else {
        figures.erase(remove_if(figures.begin(), figures.end(), [maxArea](const Figure* figure) {
            return figure->getArea() > maxArea;
            }), figures.end());
        cout << "Figures with area greater than " << maxArea << " removed successfully" << endl;
    }
}