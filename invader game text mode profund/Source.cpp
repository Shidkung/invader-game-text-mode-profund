#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
bool bullet[5];
bool bullet_enemies;
int bullet_x[5], bullet_y[5], score, bullet_x_enemies, bullet_y_enemies;
char cursor(int x, int y)
{
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(5, 0);
	printf(" (O) ");
}
void erase_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y);
		setcolor(5, 0);
	printf("A");
}
void erase_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}
void erase_bullet_enemies(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}
void draw_bullet_enemies(int x, int y)
{
	gotoxy(x, y);
	setcolor(3, 0);
	printf("o");
}


void spawn_enemies()
{
	srand(time(NULL));
	for (int j = 0; j <= 10; j++) {
		gotoxy((rand() % 61) + 10, (rand() % 4) + 2);
		setcolor(2, 0);
		printf("O");
	}
}
void shoot_Bullet_ship(int n)
{
	erase_bullet(bullet_x[n], bullet_y[n]);
	if (bullet_y[n] > 0)
	{
		if (cursor(bullet_x[n], --bullet_y[n]) == 'O')
		{
			score++;
				gotoxy(100, 10);
			setcolor(7, 0);
			printf("%d", score);
			Beep(700, 100);
			spawn_enemies();
		}
		draw_bullet(bullet_x[n], bullet_y[n]);
	}
	else
	{
		bullet[n] = false;
	}
	
}
void shoot_Bullet_enemies(int w)
{
	erase_bullet_enemies(bullet_x[w], bullet_y[w]);
	if (bullet_y[w] > 0)
	{
		if (cursor(bullet_x[w], ++bullet_y[w]) == '(O)')
		{
			
		}
		draw_bullet_enemies(bullet_x[w], bullet_y[w]);
	}
	else
	{
		bullet[w] = false;
	}

}
int main()
{
	int temp_x = 0;
	setcursor(0);
	char ch = ' ';
	int x = 38, y = 20;
	draw_ship(x, y);
		spawn_enemies();
	gotoxy(100, 10);
	printf("%d", score);
	do {
			setcursor(0);
		if (_kbhit())//กด keyboard
		{
			ch = _getch();
			if (ch == ' ')
				for (int i = 0; i < 5; i++)
					if (!bullet[i])
					{
						bullet[i] = true;
						bullet_x[i] = x + 5;
						bullet_y[i] = y - 1;
						break;
					}
			/*if (ch == 'a' && x > 0) {
				erase_ship(x,y);draw_ship(--x, y); erase_ship(x, y); 
			}
			if (ch == 'd' && x < 80) {
				erase_ship(x,y);draw_ship(++x, y); Beep(500, 100);
			}
			if (ch == 'w' && y > 0) {
				draw_ship(x, --y); erase_ship(x, ++y); draw_ship(x, --y);
			}
			if (ch == 's' && y < 30) {
				draw_ship(x, ++y); erase_ship(x, --y); draw_ship(x, ++y); 
			}*/
				 if (ch == 'a') temp_x =-1;
				if (ch == 'd')  temp_x = 1;
				if (ch == 's')  temp_x = 0;
				fflush(stdin);
		}
		//up data ship
		erase_ship(x, y);
		if (x + temp_x >= 0 && x + temp_x <= 65)
		x += temp_x;
		draw_ship(x, y);
			/*if (!bullet_enemies)
			{
				bullet_enemies = true;
				bullet_x_enemies = x + 1;
				bullet_y_enemies = y + 1;
				break;
				if (bullet_enemies)
				{
					shoot_Bullet_enemies;

				}*/
			//}
		//up data bullet
		for (int i = 0; i < 5; i++)
		{
			if (bullet[i])
			{
				shoot_Bullet_ship(i);

			}
		}
		Sleep(75);
	} while (ch != 'x');
	return 0;
}