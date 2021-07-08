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