/*menu functions*/
/*****************************************************************************
 * Copyright (C) Shyamli Agrawal shyamliagrawal@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
#include"header.h"
/*Print menu in window win with n_choices options option[] highlighting the option highlight*/
void print_menu(WINDOW* win, char* option[], int highlight, int n_choices) {
	int i = 0, row = 1, wid;
	getmaxyx(win, i, wid);
	i = 0;
	wbkgd(win, COLOR_PAIR(3));
	print_mid(win, row, option[i++]);
	wmove(win, ++row, 1);
	whline(win, 0, wid-2);
	for(;i < n_choices + 1; i++) {
		row+=2;
		if( highlight == i) {
			wattron(win, A_REVERSE); 
			print_mid(win, row, option[i]);
			wattroff(win, A_REVERSE);
		}
		else
			print_mid(win, row, option[i]);	
	}
	if(strcmp(option[0],"DATA STRUCTURES") == 0)
		message(option[0], highlight);
}
/*returns the choice selected by user passing other arguements to printmenu*/
int getchoice(WINDOW* win, char* option[], int n_choices, int highlight) {
	keypad(win, TRUE);
	int choice = 0, c;
	while(1) {
		c = wgetch(win);
		switch(c) {
			case KEY_UP:	
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else 
					++highlight;
				break;
			case ENTER:
				choice = highlight;
				break;
			default:
				break;
		}
		print_menu(win, option, highlight, n_choices);
		if(strcmp(option[0],"DATA STRUCTURES") == 0)
			message(option[0], highlight);
		if(choice != 0)
			break;
	}	
	return choice;
}
/*Print message a in window win, in middle of row row*/
void print_mid(WINDOW* win, int row, char* a) {
	int y, x;
	getmaxyx(win, y, x);
	y = strlen(a);
	if(x > y)
		mvwprintw(win, row, (x-y)/2, "%s", a);
	else
		mvwprintw(win, row, 1, "%s", a);
}
/* Prints corresponding message at bottom w.r.t. the highliht in menu*/
void message(char type[], int highlight) {
	move(3*HL+2, 0);
	deleteln();
	attron(COLOR_PAIR(3)| A_REVERSE);
	char* DS[6] = {"LIFO: Last In First Out Linear data arrangement", "FIFO: First In First OUT Linear Data Arrangement", "Linear Data Arrangement.", "Quich Help!", "Exit the Program!"};
	if(highlight < 6 && highlight > 0)
			print_mid(stdscr, 3*HL+2, DS[--highlight]); 
	attroff(COLOR_PAIR(3)| A_REVERSE);
}
		
