#include <stdio.h>
#include <conio.h>  // для Windows, getch() и kbhit()
#include <windows.h> // для управления курсором и цветом консоли

void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printMenu(int selected) {
    const char *menu[] = {"Начать", "Лидеры", "Об игре", "Выход"};
    system("cls");
    printf("Меню (используйте стрелки ↑↓ и цифры 1-4, Enter для выбора)\n\n");
    for (int i = 0; i < 4; i++) {
        if (i == selected) {
            // Выделение выбранного пункта (цвет или стрелка)
            printf(" > %d. %s\n", i+1, menu[i]);
        } else {
            printf("   %d. %s\n", i+1, menu[i]);
        }
    }
}

int main() {
    int selected = 0;
    int key;

    printMenu(selected);

    while (1) {
        key = _getch();

        if (key == 0 || key == 224) {
            // Обработка стрелок (двухбайтовый код)
            key = _getch();
            if (key == 72) {        // стрелка вверх
                selected = (selected == 0) ? 3 : selected - 1;
            } else if (key == 80) { // стрелка вниз
                selected = (selected == 3) ? 0 : selected + 1;
            }
            printMenu(selected);
        } else if (key >= '1' && key <= '4') {
            selected = key - '1';
            printMenu(selected);
        } else if (key == 13) { // Enter
            system("cls");
            const char *menu[] = {"Начать", "Лидеры", "Об игре", "Выход"};
            printf("Вы выбрали: %d. %s\n", selected + 1, menu[selected]);
            if (selected == 3) {  // "Выход"
                break;
            }
            printf("Нажмите любую клавишу чтобы вернуться в меню...");
            _getch();
            printMenu(selected);
        }
    }
    return 0;
}