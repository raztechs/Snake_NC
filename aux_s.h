#ifndef _AUX_
#define _AUX_

#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <sys/select.h>


#define ETERNITY 1


typedef struct{
	int x, y;
	char dir;
	int size;
}junction;


typedef struct{
	int x;
	int y;
}coord;


typedef struct{
	coord start;
	int tip;
}objects;

const coord obst_0[] = {
	{4, 4}, {5, 4}, {6, 4}, {7, 4}, 
	{8, 4}, {9, 4}, {10, 4}, {11, 4},
	{12, 4}, {13, 4}, {14, 4}, {15, 4},
	{16, 4}, {17, 4}, {18, 4}, {19, 4},
	{20, 4}, {21, 4}, {22, 4}, {23, 4},
	{13, 2}, {14, 2}, {13, 3}, {14, 3},
	{13, 5}, {14, 5}, {13, 6}, {14, 6}
};

const coord obst_1[] = {
	{4, 4}, {5, 4}, {6, 4}, {7, 4}, 
	{8, 4}, {9, 4}, {10, 4}, {11, 4},
	{12, 4}, {13, 4}, {14, 4}, {15, 4},
	{16, 4}, {17, 4}, {18, 4}, {19, 4},
	{20, 4}, {21, 4}, {22, 4}, {23, 4}
};

const coord obst_2[] = {
	{4, 3}, {5, 3}, {6, 3}, {7, 3}, 
	{8, 3}, {9, 3}, {10, 3}, {11, 3},
	{12, 3}, {13, 3}, {14, 3}, {15, 3},
	{16, 3}, {17, 3}, {18, 3}, {19, 3},
	{20, 3}, {21, 3}, {22, 3}, {23, 3},
	{4, 4}, {4, 5}
};

const coord obst_3[] = {
	{4, 5}, {5, 5}, {6, 5}, {7, 5}, 
	{8, 5}, {9, 5}, {10, 5}, {11, 5},
	{12, 5}, {13, 5}, {14, 5}, {15, 5},
	{16, 5}, {17, 5}, {18, 5}, {19, 5},
	{20, 5}, {21, 5}, {22, 5}, {23, 5},
	{23, 4}, {23, 3}
};

const coord obst_4[] = {
	{4, 3}, {5, 3}, {6, 3}, {7, 3}, 
	{8, 3}, {9, 3}, {10, 3}, {11, 3},
	{12, 3}, {13, 3}, {14, 3}, {15, 3},
	{16, 3}, {17, 3}, {18, 3}, {19, 3},
	{20, 3}, {21, 3}, {22, 3}, {23, 3},
	{23, 4}, {23, 5}
};

const coord obst_5[] = {
	{4, 5}, {5, 5}, {6, 5}, {7, 5}, 
	{8, 5}, {9, 5}, {10, 5}, {11, 5},
	{12, 5}, {13, 5}, {14, 5}, {15, 5},
	{16, 5}, {17, 5}, {18, 5}, {19, 5},
	{20, 5}, {21, 5}, {22, 5}, {23, 5},
	{4, 4}, {4, 3}
};

objects *create_obstacles(objects *v)
{
	int i, j;

	v[0].start.x = 1;
	v[0].start.y = 2;
	v[1].start.x = 53;
	v[1].start.y = 2;
	v[2].start.x = 27;
	v[2].start.y = 9;
	v[3].start.x = 1;
	v[3].start.y = 16;
	v[4].start.x = 53;
	v[4].start.y = 16;

	srand(time(NULL));

	attron(COLOR_PAIR(1));

	for(i = 0; i < 5; i++)
	{
		v[i].tip = rand() % 5;
		switch(v[i].tip)
		{
			case 0:
				for(j = 0; j < 28; j++)
					mvprintw(v[i].start.y + obst_0[j].y - 1, v[i].start.x + obst_0[j].x - 1, "@");
				break;

			case 1:
				for(j = 0; j < 20; j++)
					mvprintw(v[i].start.y + obst_1[j].y - 1, v[i].start.x + obst_1[j].x - 1, "@");
				break;

			case 2:
				for(j = 0; j < 22; j++)
					mvprintw(v[i].start.y + obst_2[j].y - 1, v[i].start.x + obst_2[j].x - 1, "@");
				break;

			case 3:
				for(j = 0; j < 22; j++)
					mvprintw(v[i].start.y + obst_3[j].y - 1, v[i].start.x + obst_3[j].x - 1, "@");
				break;

			case 4:
				for(j = 0; j < 22; j++)
					mvprintw(v[i].start.y + obst_4[j].y - 1, v[i].start.x + obst_4[j].x - 1, "@");
				break;

			case 5:
				for(j = 0; j < 22; j++)
					mvprintw(v[i].start.y + obst_5[j].y - 1, v[i].start.x + obst_5[j].x - 1, "@");
				break;
		}
	}

	refresh();
	return v;
}

void draw_border(int min_y, int min_x, int max_y, int max_x, char c_y, char c_x, char aux)
{
	int i;

	if(aux != 0)
	{
		mvprintw(min_y, 0, "%c", aux);
		mvprintw(min_y, 79, "%c", aux);
	}

	for(i = min_x + 1; i <= max_x - 1; i++)	
	{
		mvprintw(min_y, i, "%c", c_y);
		mvprintw(max_y, i, "%c", c_y);
	}

	for(i = min_y + 1; i <= max_y; i++)
	{
		mvprintw(i, min_x, "%c", c_x);
		mvprintw(i, max_x, "%c", c_x);
	}
}


int verif_dir(char a, char b)
{
	switch (tolower(b))
	{
		case 'a':
			if (a == 'd' || a == 'a')
				return 0;
			else 
				return 1;
			break;

		case 'd':
			if (a == 'd' || a == 'a')
				return 0;
			else 
				return 1;
			break;

		case 'w':
			if (a == 's' || a == 'w')
				return 0;
			else 
				return 1;
			break;

		case 's':
			if (a == 's' || a == 'w')
				return 0;
			else 
				return 1;
			break;
			
		case 'q':
			return 1;
			break;

		case 'p':
			return 1;
			break;

		default:
			return 0;
			break;
		}
}

int menu()
{
	char c;
	int sel, opt = 1, ok, i;
	fd_set read_descriptors;
	struct timeval tmp;
	FD_ZERO(&read_descriptors);
	FD_SET(0, &read_descriptors);

	while(ETERNITY)
	{
		ok = 0;
		FD_SET(0, &read_descriptors);
		tmp.tv_sec = 0;
		tmp.tv_usec = 200000;

		draw_border(9, 26, 15, 53, '_', '|', 0);

		sel = select(1, &read_descriptors, NULL, NULL, &tmp);
		if(sel == 1)
		{
			c = getch();

			switch(tolower(c))
			{
					case 'a':
						if(opt > 1)
							opt--;
						break;

					case 'd':
						if(opt < 4)
							opt++;
						break;

					case 'e':
						ok = 1;
						break;
			}
		}

		mvprintw(2, 35, "Student Snake");


		mvprintw(10, 35, "Main Menu");

		switch(opt)
		{
				case 1:
					mvprintw(12, 32, "Fara obstacole >");
					break;

				case 2:
					for(i = 27; i <= 52; i++)
						mvaddch(12, i, ' ');
					mvprintw(12, 32, "< Cu obstacole >");
					break;

				case 3:
					for(i = 27; i <= 52; i++)
						mvaddch(12, i, ' ');
					mvprintw(12, 32, "< Instructiuni >");
					break;

				case 4:
					for(i = 27; i <= 52; i++)
						mvaddch(12, i, ' ');
					mvprintw(12, 36, "< Quit");
					break;
		}

		if(ok && opt != 3)
			return opt;
		else
			if(ok && opt == 3)
			{
				clear();
				draw_border(9, 17, 17, 60, '_', '|', 0);

				while(ETERNITY)
				{
					mvprintw(2, 35, "Instructiuni");
					mvprintw(7, 7, "Trebuie sa-ti ajuti serpisorul sa promoveze cursul de programare!");
					mvprintw(8, 5, "Strange puncte pentru a trece de examenul final si a scapa de restanta!");
					mvprintw(10, 18, "Puteti sa mutati sarpele folosind tastele:");
					mvprintw(11, 33, "A - stanga");
					mvprintw(12, 33, "D - dreapta");
					mvprintw(13, 33, "W - sus");
					mvprintw(14, 33, "S - jos");
					mvprintw(15, 23, "Pentru pauza, apasati tasta P.");
					mvprintw(16, 23, "Pentru a iesi, apasati tasta Q.");
					
					refresh();

					getch();
					break;
				}
				clear();
			}

		refresh();
	}
}

#endif