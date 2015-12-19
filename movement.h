#ifndef _MOVE_
#define _MOVE_

#include "aux_s.h"

coord add_food(coord h, junction *v, int nrj, int col, objects *ob)
{
	int ok = 0, check = 1;
	coord food;
	srand(time(NULL));

	food.x = rand() % 79;
	food.y = rand() % 21 + 2;

	while(!ok)
	{
		if(col)
			check = collision(food.x, food.y, ob);
		if(!overlap(food.x, food.y, nrj, v) || !check)
		{
			food.x = rand() % 78 + 1;
			food.y = rand() % 21 + 2;
		}
		else
			ok = 1;
	}

	attron(COLOR_PAIR(4));
	mvwprintw(stdscr, food.y, food.x, "$");
	attroff(COLOR_PAIR(4));

	refresh();
	return food;
}

int collision(int x, int y, objects *ob)
{
	int i, j;

	for(i = 0; i < 5; i++)
	{
		switch(ob[i].tip)
		{
			case 0:
				for(j = 0; j < 28; j++)
					if(y == ob[i].start.y + obst_0[j].y - 1 && x == ob[i].start.x + obst_0[j].x - 1)
						return 0;
				break;

			case 1:
				for(j = 0; j < 20; j++)
					if(y == ob[i].start.y + obst_1[j].y - 1 && x == ob[i].start.x + obst_1[j].x - 1)
						return 0;
				break;

			case 2:
				for(j = 0; j < 22; j++)
					if(y == ob[i].start.y + obst_2[j].y - 1 && x == ob[i].start.x + obst_2[j].x - 1)
						return 0;
				break;

			case 3:
				for(j = 0; j < 22; j++)
					if(y == ob[i].start.y + obst_3[j].y - 1 && x == ob[i].start.x + obst_3[j].x - 1)
						return 0;
				break;

			case 4:
				for(j = 0; j < 22; j++)
					if(y == ob[i].start.y + obst_4[j].y - 1 && x == ob[i].start.x + obst_4[j].x - 1)
						return 0;
				break;

			case 5:
				for(j = 0; j < 22; j++)
					if(y == ob[i].start.y + obst_5[j].y - 1 && x == ob[i].start.x + obst_5[j].x - 1)
						return 0;
				break;
		}
	}

	return 1;
}

int overlap(int x, int y, int nrj, junction *v)
{
	int i;
	for(i = 0; i < nrj; i++)
		switch(v[i].dir)
		{
			case 'a':
				if(v[i].y == y && v[i].x <= x && (v[i].x + v[i].size - 1) >= x)
					return 0;
				break;

			case 'd':
				if(v[i].y == y && v[i].x >= x && (v[i].x - v[i].size + 1) <= x)
					return 0;
				break;

			case 'w':
				if(v[i].x == x && v[i].y <= y && (v[i].y + v[i].size - 1) >= y)
					return 0;
				break;

			case 's':
				if(v[i].x == x && v[i].y >= y && (v[i].y - v[i].size + 1) <= y)
					return 0;
				break;
		}
	return 1;
}

coord move_head(coord h, char *c, int nrj, junction *v, int col, objects *ob)
{
	int x_nou, y_nou;
	char n;	
	int check = 1;

	switch (tolower(*c))
		{
			case 'a':
				y_nou = h.y;
				if (col)
					check = collision(h.x - 1, h.y, ob);
				if (h.x > 1 && overlap(h.x - 1, h.y, nrj, v) && check)
				{
					x_nou = h.x - 1;
					n = '<';
				}
				else
				{
					x_nou = h.x - 1;
					n = 'X';
					*c = 'q';
				}
				break;

			case 'd':
				y_nou = h.y;
				if (col)
					check = collision(h.x + 1, h.y, ob);
				if (h.x + 1 < 79 && overlap(h.x + 1, h.y, nrj, v) && check)
				{
					x_nou = h.x + 1;
					n = '>';
				}
				else
				{
					x_nou = h.x + 1;
					n = 'X';
					*c = 'q';				
				}
				break;

			case 'w':
				x_nou = h.x;
				if(col)
					check = collision(h.x, h.y - 1, ob);
				if (h.y > 2 && overlap(h.x, h.y - 1, nrj, v) && check)
				{					
					y_nou = h.y - 1;
					n = '^';
				}
				else
				{					
					y_nou = h.y - 1;
					n = 'X';
					*c = 'q';
				}
				break;

			case 's':
				x_nou = h.x;
				if(col)
					check = collision(h.x, h.y + 1, ob);
				if (h.y + 1 < 23 && overlap(h.x, h.y + 1, nrj, v) && check)
				{
					y_nou = h.y + 1;
					n = 'v';
				}
				else
				{
					y_nou = h.y + 1;
					n = 'X';
					*c = 'q';
				}
				break;
		}

		attron(COLOR_PAIR(2));
		mvwprintw(stdscr, h.y, h.x, "o");
		
		if(*c == 'q')
			attron(COLOR_PAIR(5));
		else
			attron(COLOR_PAIR(3));
		mvwprintw(stdscr, y_nou, x_nou, "%c", n);

		attroff(COLOR_PAIR(3));
		attroff(COLOR_PAIR(5));

		h.y = y_nou;
		h.x = x_nou;

		return h;
}

junction *add_j(junction *v, int nr, int x, int y, int count, char dir)
{
	if(nr != 0)	
		v = realloc(v, (nr + 1)*sizeof(junction));
	
	v[nr].x = x;
	v[nr].y = y;
	v[nr].size = count;
	v[nr].dir = dir;

	return v;
}

junction *rm_j(junction *v, int nr)
{
	int i;
	
	for(i = 1; i <= nr; i++)
		v[i - 1] = v[i];
	if(nr > 1)
		v = realloc(v, (nr - 1)*sizeof(junction));

	return v;	
}

junction *move_body(junction *v, int nr)
{
	switch(tolower(v[0].dir))
		{
			case 'a':
				mvwprintw(stdscr, v[0].y, (v[0].x + v[0].size), " ");
				v[0].size--;
				break;

			case 'd':
				mvwprintw(stdscr, v[0].y, (v[0].x - v[0].size), " ");
				v[0].size--;
				break;

			case 'w':
				mvwprintw(stdscr, (v[0].y + v[0].size), v[0].x, " ");
				v[0].size--;
				break;

			case 's':
				mvwprintw(stdscr, (v[0].y - v[0].size), v[0].x, " ");
				v[0].size--;
				break;
		}

	return v;
}

#endif