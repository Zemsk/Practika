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