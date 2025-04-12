#include "menu.h"

int main() {
    vector<Figure*> figures; // Вектор для хранения фигур
    Menu menu = Menu(figures);
    menu.handle();
    return 0;
}
