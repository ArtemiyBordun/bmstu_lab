#include "logic.h"

void sortFigure(vector<Figure*>& figures) {
    if (figures.empty())
        cout << "Nothing to sort, nt:)" << endl;
    else {
        sort(figures.begin(), figures.end(), [](const Figure* a, const Figure* b) {
            return a->getArea() < b->getArea();
            });
        cout << "Figures sorted by area" << endl;
    }
}

void removeByNumber(vector<Figure*>& figures) {
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

void removeByMaxArea(vector<Figure*>& figures) {
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