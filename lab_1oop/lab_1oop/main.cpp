#include "menu.h"

int main() {
    vector<Figure*> figures; // ������ ��� �������� �����
    Menu menu = Menu(figures);
    menu.handle();
    return 0;
}
