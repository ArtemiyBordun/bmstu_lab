#include "menu.h"

Menu::Menu(vector<Figure*>& figures) {
    FigureManager* manager = new FigureManager(figures);
    this->manager = manager;
}

void Menu::handle() {
    int choice;
    while (true) {
        figures = manager->getFigures();

        printMenu();
        choice = getUserChoice(); //ввод пользователем выбора пункта меню

        if (choice == ADD) {
            manager->addFigures();
            clearCin();
            continue;   //после добавления фигуры или ошибки, обратно выводим меню
        }
        else if (choice == PRINTPARAM) {
            printInfo(false);
        }
        else if (choice == PRINTAREA) {
            printInfo(true);
        }
        else if (choice == PRINTSUM) {
            printSumArea();
        }
        else if (choice == SORT) {
            manager->sortFigure();
        }
        else if (choice == REMOVEBYNUM) {
            manager->removeByNumber();
        }
        else if (choice == REMOVEBYMAXAREA) {
            manager->removeByMaxArea();
        }
        else if (choice == EXIT) {
            exitPrint();    //для красоты, чтобы не было вывода в мейне 
            break;
        }
        else if (choice == SECRET) {
            printCat();
        }
        else {
            printInvalid(); //то же что и выше)
        }

        cout << endl;
    }

    manager->deleteFigures(); // Освобождение памяти
}


void Menu::printMenu() {
    cout << "Menu:" << endl;
    cout << "1.  Add a figure" << endl;
    cout << "2.  Print list of figures with parameters" << endl;
    cout << "3.  Print list of figures with areas" << endl;
    cout << "4.  Print sum of all areas" << endl;
    cout << "5.  Sort figures by area" << endl;
    cout << "6.  Remove a figure by number" << endl;
    cout << "7.  Remove figures with area greater than a value" << endl;
    cout << "0.  Exit" << endl;
    cout << "42. Answers to all secrets of the world" << endl;
}

int Menu::getUserChoice() {
    int choice;  //функция для ввода пользователем выбора в меню
    cout << "Enter your choice: ";
    cin >> choice;
    if (cin.fail()) {
        clearCin();
        choice = INCORRECT;
    }
    return choice;
}

void Menu::clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер ввода
}

void Menu::exitPrint() {
    cout << "Thanks for using my program :3" << endl;
}

void Menu::printInvalid() {
    cout << "Invalid choice" << endl;
}

void Menu::printInfo(bool needArea) {
    int count = 1;
    if (figures.empty())
        cout << "The list of figures is empty!" << endl;
    else {
        for (const auto& figure : figures) {
            cout << count++ << ". ";
            figure->printInfo();
            if (needArea)
                cout << "   Area: " << figure->getArea() << endl;
        }
    }
}

void Menu::printSumArea() {
    double sum = 0;
    for (const auto& figure : figures)
        sum += figure->getArea();
    cout << "Sum of all areas: " << sum << endl;
}