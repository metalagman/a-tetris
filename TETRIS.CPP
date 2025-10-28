//-------------------------------------
// включение хедер файлов пользователя
//-------------------------------------
#include "tetris.h"
#include "classes.h"
#include "menu.h"
//-------------------------------------
enum command { cmdNew=1, cmdResume, cmdExit }; 	// байт-коды кнопок
//-------------------------------------
// обьявление public переменной типа tfield	
//-------------------------------------
tfield field;
//-------------------------------------
void main()
{
menu(1);                                        // вывод меню
while (control());				// основной цикл игры
}
//-------------------------------------
// процедура control отслеживает нажатие клавиш 
// в игре и запускает соответствующие процедуры
//-------------------------------------
bool control()
{
bool i;
if (bioskey(1))
	switch (bioskey(0))
		{
		case KEY_UP:
		// вращение фигуры
			if (field.figure.rotate(field))
				field.draw(FIELD);
		break;
		case KEY_DOWN:
		// сдвиг фигуры вниз
			field.timer.reset();	
			if (!field.figure.move(D_DOWN, field))
				if (!field.new_figure())
					{
					menu();
					break;
					}
			field.draw(FIELD);
		break;
		case KEY_LEFT:
		// сдвиг фигуры влево
			field.figure.move(D_LEFT, field);
			field.draw(FIELD);
		break;
		case KEY_RIGHT:
		// сдвиг фигуры вправо
			field.figure.move(D_RIGHT, field);
			field.draw(FIELD);
		break;
		// вывод меню
		case KEY_ESCAPE:
			menu(0);
			break;
		case KEY_ENTER:
		// сдвиг фигуры вниз до упора
			while (field.figure.move(D_DOWN, field));
			if (!field.new_figure())
				menu();
			field.draw(FIELD);
		break;
		case KEY_SPACE:
		// вращение фигуры
			if (field.figure.rotate(field))
				field.draw(FIELD);
		}
// если истекло время, сдвигаем фигурку вниз
if (field.timer.check_time())
	{
	if (!field.figure.move(D_DOWN, field))
		if (!field.new_figure())
			menu();
	field.draw(FIELD);
	}
return 1;
}
//-------------------------------------
// процедура работы с главным меню.
// если ng<>0, после выхода из меню
// запускается новая игра
//-------------------------------------
void menu(int ng)
{
static tmenu menu;			// статический обьект класса tmenu
binfo *bi;                            	// указатель на описание кнопки
int x, y;
int r = 0;
cleardevice();				// очистка экрана
// если меню не инициализировано, то заполняем его
if (!menu.first)			
	{
	// установка начальных координат меню
	x = (getmaxx()-156)/2;
	y = (getmaxy()-84)/2;
	// добавление кнопки new game
	bi = button();
	bi->left = x;
	bi->top = y;
	bi->right = x+156;
	bi->bottom = y+36;
	bi->command = cmdNew;
	strcpy(bi->str, "NEW GAME");
	menu.append(bi);
	// добавление кнопки resume
	y += 44;
	bi = button();
	bi->left = x;
	bi->top = y;
	bi->right = x+156;
	bi->bottom = y+36;
	bi->command = cmdResume;
	strcpy(bi->str, "RESUME");
	menu.append(bi);
	// добавление кнопки exit game
	y += 44;
	bi = button();
	bi->left = x;
	bi->top = y;
	bi->right = x+156;
	bi->bottom = y+36;
	bi->command = cmdExit;
	strcpy(bi->str, "EXIT GAME");
	menu.append(bi);
	// делаем первую кнопку активной
	menu.active = menu.first;
	}
// рисуем рамку вокруг меню и само меню
coolbar(menu.first->left-18, menu.first->top-18, menu.last->right+18, menu.last->bottom+18, 11);
menu.draw();
// обработка нажатий клавиш внутри меню
while (!r)
	if (bioskey(1))
		switch (bioskey(0))
		{
		case KEY_ESCAPE:
			r = cmdResume;
			break;
		case KEY_DOWN:
			if (menu.active->next)
				menu.active = menu.active->next;
			menu.draw();
			break;
		case KEY_UP:
			if (menu.active->prev)
				menu.active = menu.active->prev;
			menu.draw();
			break;
		case KEY_ENTER:
			r = menu.active->command;
		}
// запуск соответствующих процедур
switch (r)
	{
	case cmdNew:
		field.new_game();
		break;
	case cmdResume:
		if (ng) field.new_game();
		break;
	case cmdExit:
		exit(0);
	}
cleardevice();
// прорисовка игрового поля
field.draw(ALL);
}
//-------------------------------------
void coolbar(int left, int top, int right, int bottom, int thick)
{
setfillstyle(SOLID_FILL, 7);
bar(left, top, right, bottom);
setcolor(8);
line(right, top, right, bottom);
line(right, bottom, left, bottom);
setcolor(15);
line(left, bottom, left, top);
line(left, top, right, top);
left += thick;
top += thick;
right -= thick;
bottom -= thick;
setfillstyle(SOLID_FILL, 0);
bar(left, top, right, bottom);
setcolor(15);
line(right, top, right, bottom);
line(right, bottom, left, bottom);
setcolor(8);
line(left, bottom, left, top);
line(left, top, right, top);
}
//-------------------------------------