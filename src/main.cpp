#include <iostream>
#include "utils/csv_reader.h"
#include "utils/graph.h"
#include "manager.h"
#include "menu/menu.h"

int main() {
    Menu menu = Menu();
    menu.menuLoop();

    return 0;
}
