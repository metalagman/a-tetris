//-------------------------------------
// стандартные заголовочные файлы
//-------------------------------------
#include <bios.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//-------------------------------------
// макросы
//-------------------------------------
#define KEY_UP 18432
#define KEY_DOWN 20480
#define KEY_LEFT 19200
#define KEY_RIGHT 19712
#define KEY_ESCAPE 283
#define KEY_SPACE 14624
#define KEY_ENTER 7181
#define DAT_FILE "tetris.dat"
//-------------------------------------
// типы пользователя
//-------------------------------------
typedef unsigned bool;
typedef unsigned uint;
//-------------------------------------
// прототипы функций
//-------------------------------------
bool control();
void menu(int ng = 1);
void coolbar(int left, int top, int right, int bottom, int thick = 10);
//-------------------------------------