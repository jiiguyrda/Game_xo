#include <stdio.h>
#include <conio.h>
#include <windows.h>

// Функции меню (остаются без изменений)
void setCursorPosition(int x, int y) {
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printMenu(int selected) {
    const char *menu[] = {"Начать", "Лидеры", "Об игре", "Выход"};
    system("cls");
    printf("Меню (используйте стрелки ↑↓ и цифры 1-4, Enter для выбора)\n\n");
    for (int i = 0; i < 4; i++) {
        if (i == selected) {
            printf(" > %d. %s\n", i + 1, menu[i]);
        } else {
            printf("   %d. %s\n", i + 1, menu[i]);
        }
    }
}

// Функции для игры в крестики-нолики
void drawBoard(char board[3][3]) {
    system("cls");
    printf("Крестики-нолики\n\n");
    printf("Используйте стрелки для перемещения, Enter для хода\n");
    printf("ESC - выход в меню\n\n");
    
    for (int i = 0; i < 3; i++) {
        printf("   ");
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("│");
        }
        printf("\n");
        if (i < 2) {
            printf("   ───┼───┼───\n");
        }
    }
    printf("\nХод: %s\n", (board[0][0] == ' ' ? "Игрок 1 (X)" : "Игрок 2 (O)"));
}

int checkWin(char board[3][3], char player) {
    // Проверка строк и столбцов
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1;
        }
    }
    
    // Проверка диагоналей
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return 1;
    }
    
    return 0;
}

int isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void playTicTacToe() {
    char board[3][3];
    int cursorX = 0, cursorY = 0;
    char currentPlayer = 'X';
    int gameOver = 0;
    
    // Инициализация доски
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
    
    while (!gameOver) {
        // Отрисовка доски с курсором
        system("cls");
        printf("Крестики-нолики\n\n");
        printf("Используйте стрелки для перемещения, Enter для хода\n");
        printf("ESC - выход в меню\n\n");
        
        for (int i = 0; i < 3; i++) {
            printf("   ");
            for (int j = 0; j < 3; j++) {
                if (i == cursorY && j == cursorX) {
                    printf("[%c]", board[i][j]);
                } else {
                    printf(" %c ", board[i][j]);
                }
                if (j < 2) printf("│");
            }
            printf("\n");
            if (i < 2) {
                printf("   ───┼───┼───\n");
            }
        }
        printf("\nХод: %s\n", (currentPlayer == 'X' ? "Игрок 1 (X)" : "Игрок 2 (O)"));
        
        // Обработка ввода
        int key = _getch();
        if (key == 0 || key == 224) {
            key = _getch();
            switch (key) {
                case 72: // Стрелка вверх
                    cursorY = (cursorY == 0) ? 2 : cursorY - 1;
                    break;
                case 80: // Стрелка вниз
                    cursorY = (cursorY == 2) ? 0 : cursorY + 1;
                    break;
                case 75: // Стрелка влево
                    cursorX = (cursorX == 0) ? 2 : cursorX - 1;
                    break;
                case 77: // Стрелка вправо
                    cursorX = (cursorX == 2) ? 0 : cursorX + 1;
break;
            }
        } else if (key == 13) { // Enter
            if (board[cursorY][cursorX] == ' ') {
                board[cursorY][cursorX] = currentPlayer;
                
                // Проверка на победу
                if (checkWin(board, currentPlayer)) {
                    drawBoard(board);
                    printf("\nПоздравляем! %s выиграл!\n", 
                           (currentPlayer == 'X' ? "Игрок 1 (X)" : "Игрок 2 (O)"));
                    printf("Нажмите любую клавишу для возврата в меню...");
                    _getch();
                    gameOver = 1;
                } else if (isBoardFull(board)) {
                    drawBoard(board);
                    printf("\nНичья! Поле полностью заполнено.\n");
                    printf("Нажмите любую клавишу для возврата в меню...");
                    _getch();
                    gameOver = 1;
                } else {
                    // Смена игрока
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                }
            }
        } else if (key == 27) { // ESC
            return; // Выход в меню
        } else if (key >= '1' && key <= '9') {
            // Быстрый выбор ячейки с клавиатуры
            int cell = key - '1';
            cursorY = cell / 3;
            cursorX = cell % 3;
        }
    }
}

int main() {
    int selected = 0;
    int key;

    while (1) {
        printMenu(selected);
        key = _getch();

        if (key == 0 || key == 224) {
            key = _getch();
            if (key == 72) {
                selected = (selected == 0) ? 3 : selected - 1;
            } else if (key == 80) {
                selected = (selected == 3) ? 0 : selected + 1;
            }
        } else if (key >= '1' && key <= '4') {
            selected = key - '1';
        } else if (key == 13) {
            system("cls");
            const char *menu[] = {"Начать", "Лидеры", "Об игре", "Выход"};
            
            switch (selected) {
                case 0: // Начать игру
                    playTicTacToe();
                    break;
                case 1: // Лидеры
                    printf("Таблица лидеров (в разработке)\n");
                    printf("Нажмите любую клавишу чтобы вернуться в меню...");
                    _getch();
                    break;
                case 2: // Об игре
                    printf("Крестики-нолики\n");
                    printf("Классическая игра для двух игроков.\n");
                    printf("Первый игрок играет крестиками (X),\n");
                    printf("второй - ноликами (O).\n\n");
                    printf("Цель игры - первым выстроить 3 своих\n");
                    printf("фигуры в ряд по горизонтали, вертикали\n");
                    printf("или диагонали.\n\n");
                    printf("Нажмите любую клавишу чтобы вернуться в меню...");
                    _getch();
                    break;
                case 3: // Выход
                    return 0;
            }
        }
    }
    return 0;
}