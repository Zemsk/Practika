#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <locale.h>
#define N 1000
#define KEY_ESC 27
#define KEY_ENTER 13

using namespace std;
bool gameover;
int width;
int height;
int sx, sy, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { Stop = 0, Left, Right, Up, Down };
eDirection dir;
FILE* rec;
char name[N];

void Setup() {
    gameover = false;
    dir = Stop;
    sx = width / 2 - 1;
    sy = height / 2 - 1;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Pole() {
    printf("Введите размер поля\n");
    printf("Высота:");
    scanf_s("%d", &height);
    printf("Ширина:");
    scanf_s("%d", &width);
}

void Recordivivod1() {
    char arr[N];
    rec = fopen("Score.txt", "r");
    while (fgets(arr, N, rec) != NULL)
        printf("%s", arr);
    printf("\n");
    fclose(rec);
}

void Recordivvod() {
    rec = fopen("Score.txt", "a");
    printf("Введите имя игрока:\n");
    scanf("%s", &name);
    fprintf(rec, "Игрок %s", name);
    fclose(rec);
}

void Recordivivod2() {
    rec = fopen("Score.txt", "a");
    fprintf(rec, " Счет %d\n", score);
    fclose(rec);
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 1; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1)
                printf("#");
            if (i == sy && j == sx)
                printf("@");
            else if (i == fruitY && j == fruitX)
                printf("f");
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        print = true;
                        printf("o");
                    }
                }
                if (!print)
                    printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < width + 1; i++)
        printf("#");
    printf("\n");
    printf("Очки:%d\n", score);
}

void Input() {
    if (_kbhit()) {
        switch (_getch())
        {
        case 'a':
            dir = Left;
            break;
        case 'd':
            dir = Right;
            break;
        case 'w':
            dir = Up;
            break;
        case 's':
            dir = Down;
            break;
        case KEY_ESC:
            gameover = true;
            break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = sx;
    tailY[0] = sy;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case Left:
        sx--;
        break;
    case Right:
        sx++;
        break;
    case Up:
        sy--;
        break;
    case Down:
        sy++;
        break;
    }

    if (sx >= width - 1)
        sx = 0;
    else if (sx < 0)
        sx = width - 2;
    if (sy >= width)
        sy = 0;
    else if (sy < 0)
        sy = height - 1;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == sx && tailY[i] == sy)
            gameover = true;
    }

    if (sx == fruitX && sy == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

void gamemenu() //игровое меню
{
    int p = 1, c = 0;
    const char* GAME_MENU =
        "\t 1. Игра\n"
        "\t 2. Игроки\n"
        "\t 3. Выход";
    system("cls"); printf("%s", GAME_MENU);
    while (TRUE) //навигация по меню
    {
        c = _getch();
        switch (c)
        {
        case '1':
        case '2':
        case '3':
            p = c - '0';
        case KEY_ENTER:
            switch (p)
            {
            case 1:
                system("cls");
                Pole();
                Recordivvod();
                Setup();
                return;
            case 2:
                system("cls");
                Recordivivod1();
                _getch();
                break;
            case 3:
                system("cls");
                exit(0);
            }
            system("cls"); printf("%s", GAME_MENU);
            p = 1;
            break;
        }
    }
}

int main() {
    HWND hwnd = GetConsoleWindow();
    MoveWindow(hwnd, 0, 0, 800, 500, TRUE);
    HMENU hm;
    hm = GetSystemMenu(hwnd, FALSE);
    RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
    RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Rus");
    gamemenu();
    while (gameover == 0) {
        Draw();
        Input();
        Logic();
        Sleep(250);
    }
    if (gameover == 1) {
        Recordivivod2();
        gamemenu();
    }
    return 0;
}