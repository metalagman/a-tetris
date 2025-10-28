//-------------------------------------
// прорисовка кнопки в соответствии с 
// её свойствами
//-------------------------------------
void tmenu::draw_button(binfo * bi)
{
int h, w, x, y;
setfillstyle(SOLID_FILL, 8);
bar(bi->left, bi->top, bi->right, bi->bottom);
setcolor(7);
rectangle(bi->left+1, bi->top+1, bi->right-1, bi->bottom-1);
setcolor(15);
rectangle(bi->left, bi->top, bi->right, bi->bottom);
h = textheight(bi->str);
w = textwidth(bi->str);
setcolor ((bi == this->active) ? 15 : 7);
if (w < bi->right - bi->left && h < bi->bottom - bi->top)
	{
	x = bi->left + (bi->right - bi->left - w) / 2;
	y = bi->top + (bi->bottom - bi->top - h) / 2+1;
	outtextxy(x, y, bi->str);
	}
}
//-------------------------------------
// самый обычный деструктор, очистка 
// динамических структур
//-------------------------------------
tmenu::~tmenu()
{
binfo * bi;
if (first) while (first->next)
	{
	bi = first;
	first = first->next;
	delete bi;
	}
}
//-------------------------------------
// добавление структуры с адресом bi к 
// линейному списку кнопок меню
//-------------------------------------
void tmenu::append(binfo *bi)
{
bi = bi;
bi->next = NULL;
if (last)
	{
	bi->prev = last;
	last->next = bi;
	}
last = bi;
if (!first)
	{
	bi->prev = NULL;
	first = bi;
	}
this->active = bi;
}
//-------------------------------------
// прорисовка всех кнопок
//-------------------------------------
void tmenu::draw()
{
binfo * bi = first;
while (bi)
	{
	draw_button(bi);
	bi = bi->next;
	}
delay(50);
}
//-------------------------------------