#include <stdio.h>
#include <curses.h>
#include "aux_s.h"
#include "movement.h"

#define ETERNITY 1

int main()
{
	coord head;
	head.x = 20;
	head.y = 12;
	
	coord food;

	int bsize = 3, jnr = 0, bonus = 0, food_count = 0;
	int ok = 0, nfds = 1, speed = 100000, scor = 0;
	float multi = 1;
	int counter = 1, grow = 0, sel, nofood = 1, opt, col;
	char c, aux, old_c;

	objects *ob = malloc(5*sizeof(objects));

	fd_set read_descriptors;
	struct timeval tmp;

	FD_ZERO(&read_descriptors);
	FD_SET(0, &read_descriptors);

	tmp.tv_sec = 0;
	tmp.tv_usec = 500000 - speed;
	
	junction *v;
	v = malloc(sizeof(junction));

	initscr();
	start_color();
	
	use_default_colors();
	
	init_pair(1, -1, -1);
	init_pair(2, COLOR_GREEN, -1);
	init_pair(3, 2, -1);
	init_pair(4, COLOR_BLUE, -1);
	init_pair(5, 1, -1);

	noecho();
	cbreak();
	curs_set(0);
	refresh();

	attron(COLOR_PAIR(1));
//	draw_border(0, 0, 23, 79, '#', '#', '#');
	opt = menu();

	clear();

	switch(opt)
	{
		case 1:
			col = 0;
			break;

		case 2:
			col = 1;
			ob = create_obstacles(ob);
			break;

		case 4:
			endwin();
			return 0;
			break;
	}

	draw_border(1, 0, 23, 79, '#', '#', '#');
	
//	attroff(COLOR_PAIR(1));
	move(head.y, head.x);
	attron(COLOR_PAIR(3));
	addch('<');

	if(nofood)
		{
			food = add_food(head, v, jnr, col, ob);
			nofood = 0;
		}

	refresh();

	getch();

	c = 'a';
	old_c = c;

	while(ETERNITY)
	{		
		FD_SET(0, &read_descriptors);
		tmp.tv_sec = 0;
		tmp.tv_usec = 500000 - speed;

		mvprintw(0, 0, "scor:%d", scor);
		
		sel = select(nfds, &read_descriptors, NULL, NULL, &tmp);
		if(sel == 1)
			aux = getch();

		if(verif_dir(c, aux))
		{
			ok = 1;
			c = aux;
		}

		if(tolower(c) == 'q')
			break;
		
		if(tolower(c) != 'p')
		{
			mvprintw(0, 35, "     ");
			if(counter == bsize || ok)
			{
				v = add_j( v, jnr, head.x, head.y, counter, old_c);
				jnr++;
				counter = 0;
			}
		
			if(tolower(c) == 'r')
			{
				c = old_c;
				bsize++;
				grow = 1;
				counter++;
			}

			head = move_head( head, &c, jnr, v, col, ob);
			counter++;

			if(tolower(c) == 'q')
				break;

			if(head.x == food.x && head.y == food.y)
			{
				grow = 1;
				nofood = 1;
				food_count++;
				scor+=10;
			}

			if(jnr != 0 && !grow)
			{
				attron(COLOR_PAIR(1));
				v = move_body( v, jnr);
				if(v[0].size == 0)
				{
					v = rm_j(v, jnr);
					jnr--;
				}
			}
		
			if(food_count != 0 && food_count % 2 == 0 && speed <= 400000)
			{
				speed = speed + 50000;
				food_count = 0;
			}

			grow = 0;
			old_c = c;
			ok = 0;
		}
		else
			mvprintw(0, 35, "Pauza");

		if(nofood)
		{
			food = add_food(head, v, jnr, col, ob);
			nofood = 0;
		}

		refresh();
	}

	if(tolower(aux) == 'q')
		mvprintw(0, 32, "Ai cedat nervos!");
	else
		mvprintw(0, 35, "Felicitari! Ai restanta!");
	
	cbreak();
	getch();

	endwin();

	return 0;
}
