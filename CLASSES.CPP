//-------------------------------------
// МЕТОДЫ КЛАССА TPIPE
//-------------------------------------
// инициализация элемента конвейера с
// номером id случайными данными
//-------------------------------------
void tpipe::add(uint id)
{
uint color, type;
do color = rand()%8+1;
while (color_exists(color));
do type = rand()%7;
while (type_exists(type));
elem[id].color = color;
elem[id].type = type;
}
//-------------------------------------
// проверка на наличие цвета c в конвейере 
//-------------------------------------
bool tpipe::color_exists(uint c)
{
bool r = 0;
int i;
for (i=0;i<PIPE_S;i++)
	if (elem[i].color == c)
		{
		r = 1;
		break;
		}
return r;
}
//-------------------------------------
// проверка на наличие типа t в конвейере 
//-------------------------------------
bool tpipe::type_exists(uint t)
{
bool r = 0;
int i;
for (i=0;i<PIPE_S;i++)
	if (elem[i].type == t)
		{
		r = 1;
		break;
		}
return r;
}
//-------------------------------------
// конструктор: инициализация конвейера 
//-------------------------------------
tpipe::tpipe()
{
time_t t;
uint i;
srand((unsigned) time(&t));
for (i=0;i<PIPE_S;i++)
	add(i);
}
//-------------------------------------
// извлечение описания фигуры из
// конвейера
//-------------------------------------
finfo tpipe::pop()
{
uint i;
finfo fi = elem[PIPE_S-1];
for (i=PIPE_S-1;i>0;i--)
	elem[i] = elem[i-1];
add(0);
return fi;
}
//-------------------------------------
// МЕТОДЫ КЛАССА TMATRIX
//-------------------------------------
// заполнение матрицы числом C_E
//-------------------------------------
void tmatrix::reset()
{
int i, j;
for (i=0; i<F_H; i++)
	for (j=0; j< F_W; j++)
		elem[i][j] = C_E;
};
//-------------------------------------
// обьединение двух матриц при 
// отсутствии пересечения
//-------------------------------------
bool tmatrix::append(tmatrix &m)
{
int i, j;
if (cross(m)) return 0;
for (i=0;i<F_H;i++)
	for (j=0;j<F_W;j++)
		if (elem[i][j]==C_E)
			elem[i][j] = m.elem[i][j];
return 1;
}
//-------------------------------------
// проверка двух матриц на пересечение
//-------------------------------------
bool tmatrix::cross(tmatrix &m)
{
int i, j;
for (i=0;i<F_H;i++)
	for (j=0;j<F_W;j++)
		if (m.elem[i][j]!=C_E&&elem[i][j]!=C_E)
			return 1;
return 0;
}
//-------------------------------------
// МЕТОДЫ КЛАССА TFIGURE
//-------------------------------------
// сдвиг фигуры, если он возможен, в 
// указанном направлении
//-------------------------------------
bool tfigure::shift(direction d)
{
bool t = 1;
uint i, j;
tmatrix & f = * this;
switch (d)
	{
	case D_LEFT:
	for (i=0;i<F_H;i++)
		if (f.elem[i][0]!=C_E)
			{
			t=0;
			break;
			}
	if (t)
		for (i=0;i<F_H;i++)
			{
			for (j=0;j<F_W-1;j++)
				f.elem[i][j]=f.elem[i][j+1];
			f.elem[i][F_W-1] = C_E;
			}
	break;
	case D_RIGHT:
	for (i=0;i<F_H;i++)
		if (f.elem[i][F_W-1]!=C_E)
			{
			t=0;
			break;
			}
	if (t)
		for (i=0;i<F_H;i++)
			{
			for (j=F_W-1;j>=1;j--)
				f.elem[i][j]=f.elem[i][j-1];
			f.elem[i][0] = C_E;
			}
	break;
	case D_UP:
	for (j=0;j<F_W;j++)
		if (f.elem[0][j]!=C_E)
			{
			t=0;
			break;
			}
	if (t)
		for (j=0;j<F_W;j++)
			{
			for (i=0;i<F_H-1;i++)
				f.elem[i][j]=f.elem[i+1][j];
			f.elem[F_H-1][j] = C_E;
			}
	break;
	case D_DOWN:
	for (j=0;j<F_W;j++)
		if (f.elem[F_H-1][j]!=C_E)
			{
			t=0;
			break;
			}
	if (t)
		for (j=0;j<F_W;j++)
			{
			for (i=F_H-1;i>0;i--)
				f.elem[i][j]=f.elem[i-1][j];
			f.elem[0][j] = C_E;
			}
	}
return t;
}
//-------------------------------------
// сдвиг фигуры, а затем проверка на
// пересечение с указанной матрицей
//-------------------------------------
bool tfigure::move(direction d, tmatrix &m)
{
bool t = 1;
uint i, j;
tfigure f = * this;
t = f.shift(d);
if (t)
	if (!m.cross(f))
		* this = f;
	else
		t = 0;
return t;
}
//-------------------------------------
// вращение фигуры в произвольном 
// направлении
//-------------------------------------
bool tfigure::spin()
{
const n = 4;
uint a[n][n], b[n*n];
int i, j, ci, cj, t, r;
// searching for figure matrix
for (i=0,t=0;i<F_H&&!t;i++)
	for (j=0;j<F_W&&!t;j++)
		if (elem[i][j] != C_E)
			{
			ci = i;
			t = 1;
			}
for (j=0,t=0;j<F_W&&!t;j++)
	for (i=0;i<F_H&&!t;i++)
		if (elem[i][j] != C_E)
			{
			cj = j;
			t = 1;
			}
// copying additional matrix
for (i=0;i<n;i++)
	for (j=0;j<n;j++)
		if (ci + i < F_H && cj + j < F_W)
			a[i][j] = elem[ci+i][cj+j];
		else
			a[i][j] = C_E;
// spinning additional matrix
for (i=0,t=0;i<n;i++)
	for (j=0;j<n;j++,t++)
		b[t] = a[i][j];

for (j=n-1,t=0;j>=0;j--)
	for (i=0;i<n;i++,t++)
		a[i][j] = b[t];

//optimizing additional matrix
t = 1;
while (t)
	{
	for (j=0;j<n;j++)
		if (a[0][j] != C_E) { t = 0; break; }
	if (t)
		for(j=0;j<n;j++)
			{
			for (i=0;i<n-1;i++)
				a[i][j] = a[i+1][j];
			a[n-1][j] = C_E;
			}
	}
t = 1;
while (t)
	{
	for (i=0;i<n;i++)
		if (a[i][0] != C_E) { t = 0; break; }
	if (t)
		for (i=0;i<n;i++)
			{
			for (j=0;j<n-1;j++)
				a[i][j] = a[i][j+1];
			a[i][n-1] = C_E;
			}
	}

for (i=n-1,t=0;i>=0&&!t;i--)
	for (j=0;j<n&&!t;j++)
		if (a[i][j] != C_E)
			t = 1;
i++;
r = ci + i < F_H;

for (j=n-1,t=0;j>=0&&!t;j--)
	for(i=0;i<n&&!t;i++)
		if (a[i][j] != C_E)
			t = 1;
j++;
r = r && cj+j < F_W;
if (r)
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			if (ci+i < F_H && cj+j < F_W)
				elem[ci+i][cj+j] = a[i][j];
return r;
}
//-------------------------------------
// вращение с проверкой на пересечение
//-------------------------------------
bool tfigure::rotate(tmatrix &m)
{
bool t = 1;
uint i, j;
tfigure f = * this;
t = f.spin();
if (t)
	if (!m.cross(f))
		* this = f;
	else
		t = 0;
return t;
}
//-------------------------------------
// МЕТОДЫ КЛАССА TBOX
//-------------------------------------
// инициализация фигуры f с помощью 
// первой в конвейере фигуры
//-------------------------------------
void tbox::extract(tfigure &f)
{
uint i;
finfo fi;
f.reset();
fi = pipe.pop();
switch (fi.type)
	{
	case 0:
	f.elem[0][1] = f.elem[1][1] = f.elem[2][1] = f.elem[3][1] = colors[fi.color]; break;
	case 1:
	f.elem[1][1] = f.elem[1][2] = f.elem[2][1] = f.elem[2][2] = colors[fi.color]; break;
	case 2:
	f.elem[0][1] = f.elem[1][1] = f.elem[2][1] = f.elem[2][2] = colors[fi.color]; break;
	case 3:
	f.elem[0][2] = f.elem[1][2] = f.elem[2][2] = f.elem[2][1] = colors[fi.color]; break;
	case 4:
	f.elem[0][1] = f.elem[1][1] = f.elem[2][1] = f.elem[1][2] = colors[fi.color]; break;
	case 5:
	f.elem[0][1] = f.elem[1][1] = f.elem[1][2] = f.elem[2][2] = colors[fi.color]; break;
	case 6:
	f.elem[0][2] = f.elem[1][2] = f.elem[1][1] = f.elem[2][1] = colors[fi.color];
	}
for (i=1;i<rand()%4;i++)
	f.spin();
while (f.shift(D_LEFT));
while (f.shift(D_UP));
}
//-------------------------------------
// конструктор обьекта tbox
//-------------------------------------
tbox::tbox()
{
extract(next);
}
//-------------------------------------
// фигура f := текущая фигура, затем 
// инициализация текущей фигуры
//-------------------------------------
void tbox::get(tfigure &f)
{
f = next;
for (int i=0;i<3;i++)
	f.shift(D_RIGHT);
extract(next);
}
//-------------------------------------
// МЕТОДЫ КЛАССА TFIELD
//-------------------------------------
// конструктор: инициалиация графики и
// загрузка лучшего счета
//-------------------------------------
tfield::tfield()
{
FILE * fi;
clrscr();
int gdriver = DETECT, gmode, errorcode;
initgraph(&gdriver, &gmode, "");
errorcode = graphresult();
if (errorcode != grOk)
	{
	printf("Graphics error: %s\n", grapherrormsg(errorcode));
	printf("Press any key to halt:");
	getch();
	exit(1);
	}
fi = fopen(DAT_FILE, "r");
if (fi)
	{
	fseek(fi, 0, SEEK_SET);
	fread(&(stat.best_score), sizeof stat.best_score, 1, fi);
	fclose(fi);
	}
}
//-------------------------------------
// деструктор: закрытие графики и 
// сохранение лучшего результата
//-------------------------------------
tfield::~tfield()              
{
FILE * fo;
fo = fopen(DAT_FILE, "w+b");
if (fo)
	{
	fseek(fo, 0, SEEK_SET);
	fwrite(&(stat.best_score), sizeof stat.best_score, 1, fo);
	fclose(fo);
	}
closegraph();
clrscr();
printf("Active Tetris v1.0\n(C) 2002 Alexey Samoylov");
}
//-------------------------------------
// прорисовка игрового поля используя 
// режим прорисовки dm
//-------------------------------------
void tfield::draw(draw_mode dm)
{
char * str;
const DR_TOP = 20, DR_LEFT = 130, DR_SIZE = 20, DR_BETWEEN = 2;
int i, j, t;
int color;
tmatrix m = * this;
int left, top, right, bottom;
//-------
switch (dm)
	{
	case ALL:
	coolbar(118, 8, 360, 470);
	draw(FIELD);
	coolbar(374, 8, 522, 158);
	draw(BOX);
	coolbar(374, 174, 522, 470);
	draw(SCORE);
	break;
	case FIELD:
	m.append(figure);
	top = DR_TOP;
	bottom = top + DR_SIZE;
	t = DR_SIZE + DR_BETWEEN;
	for (i=0; i<F_H; i++)
		{
		left = DR_LEFT;
		right = left + DR_SIZE;
		for (j=0; j<F_W; j++)
			{
			color = m.elem[i][j];
			setfillstyle(SOLID_FILL, color);
			bar(left, top, right, bottom);
			(left, top, right, bottom);
			left+=t;
			right+=t;
			}
		top+=t;
		bottom+=t;
		}
	break;
	case BOX:
	top = 40;
	bottom = top + DR_SIZE;
	t = DR_SIZE + DR_BETWEEN;
	for (i=0; i<4; i++)
		{
		left = 404;
		right = left + DR_SIZE;
		for (j=0; j<4; j++)
			{
			color = (box.next.elem[i][j]!=C_E) ? box.next.elem[i][j] : 0;
			setfillstyle(SOLID_FILL, color);
			bar(left, top, right, bottom);
			left+=t;
			right+=t;
			}
		top+=t;
		bottom+=t;
		}
	case SCORE:
	setcolor(2);
	str = new char [6];
	left = 394;
	setfillstyle(SOLID_FILL, 0);
	sprintf(str, "%d", stat.score);
	top = 194;
	outtextxy(left, top, "Score:");
	top += 12;
	bar(left, top, left+54, top+8);
	outtextxy(left, top, str);
	top += 20;
	sprintf(str, "%d", stat.best_score);
	outtextxy(left, top, "Best Score:");
	top += 12;
	bar(left, top, left+54, top+8);
	outtextxy(left, top, str);
	top += 74;
	sprintf(str, "%d", stat.level);
	outtextxy(left, top, "Level:");
	top += 12;
	bar(left, top, left+54, top+8);
	outtextxy(left, top, str);
	top += 78;
	sprintf(str, "%d", stat.figs_count);
	outtextxy(left, top, "Figures Used:");
	top += 12;
	bar(left, top, left+54, top+8);
	outtextxy(left, top, str);
	top += 16;
	sprintf(str, "%d", stat.lines_count);
	outtextxy(left, top, "Lines Cleared:");
	top += 12;
	bar(left, top, left+54, top+8);
	outtextxy(left, top, str);
	delete [] str;
	}
}
//-------------------------------------
// поиск первой solid линии
//-------------------------------------
int tfield::find_line()
{
int i, j;
for (i=F_H-1; i>=0; i--)
	for (j=0; j<F_W; j++)
		{
		if (elem[i][j]==C_E) break;
		if (j==F_W-1) return i;
		}
return -1;
}
//-------------------------------------
// удаление линии с индексом i
//-------------------------------------
void tfield::cut_off(int i)
{
int j;
if (i>-1)
	{
	if (i>0)
		for (; i>0; i--)
			for (j=0; j<F_W; j++)
				elem[i][j] = elem[i-1][j];
	for (j=0; j<F_W; j++)
		elem[0][j]=C_E;
	}
}
//-------------------------------------
// поиск всех линий и их удаление
//-------------------------------------
int tfield::cut_off_all()
{
int i, r=0;
while (1)
	{
	i = find_line();
	if (i==-1) break;
	cut_off(i);
	r++;
	}
return r;
}
//-------------------------------------
// добавление новой фигуры к игровому 
// полю
//-------------------------------------
bool tfield::new_figure()
{
const LIM = 1000;
bool r, sr = 0;
uint i, add=0, old_val, new_val;
tfield & f = * this;
append(figure);
old_val = (stat.score - stat.score % LIM) / LIM;
i = cut_off_all();
sr = i;
stat.lines_count += i;
while (i)
	{
	stat.score += 100+add;
	add += 25;
	if (stat.score > stat.best_score) stat.best_score = stat.score;
	new_val = (stat.score - stat.score % LIM) / LIM;
	if (new_val > old_val)
		{
		timer.decr();
		stat.level++;
		old_val = new_val;
		}
	i--;
	}
box.get(figure);
r = (f.cross(figure)) ? 0 : 1;
if (r)
	{
	draw(BOX);
	stat.figs_count++;
	timer.reset();
	}
if (sr) draw(SCORE);
return r;
}
//-------------------------------------
// инициализация новой игры
//-------------------------------------
void tfield::new_game()
{
stat.score = stat.lines_count = stat.figs_count = 0;
stat.level = 1;
box.pipe.pop();
reset();
figure.reset();
new_figure();
}
//-------------------------------------
// МЕТОДЫ КЛАССА TTIMER
//-------------------------------------
bool ttimer::check_time()
{
clock_t curr;
if ( !begin ) begin = clock();
curr = clock();
if ( curr - begin >= idle )
	{
	begin = NULL;
	return 1;
	}
return 0;
}
//-------------------------------------
void ttimer::decr()
{
if (idle > 1) idle--;
}
//-------------------------------------