/*main logic
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
int main() {
	WINDOW* menu_win, *submenu_win;
	int menu_choice = 1, submenu_choice = 1;
	char* menu[] = {"DATA STRUCTURES","STACK", "QUEUE", "LINKED LIST", "HELP", "EXIT"};
	char* submenu_stack[] = {"STACK", "INIALIZE", "PUSH", "POP", "BACK"};
	char* submenu_queue[] = {"QUEUE", "INITIALIZE", "ENQUEUE", "DEQUEUE","BACK"};
	char* submenu_list[] = {"LINKED LIST", "INITIALIZE", "APPEND", "INSERT" ,"REMOVE", "FIND", "BACK"};
	char* submenu_exit[] = {"EXIT NOW?", "YES!", "NO!"};
	initscr();
	cbreak();
	noecho();
	curs_set(FALSE);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
	init_pair(4, COLOR_WHITE, COLOR_BLUE);
	immedok(stdscr, TRUE);
	bkgd(COLOR_PAIR(4) );
	fancyprint(stdscr, HL - U, C-U, "Use Arrow keys to navigate through options.Press 'ENTER' to select!");
	menu_win = newwin(L, 2*C, HL, C/2);
	immedok(menu_win, TRUE);
	while(1) {
		box(menu_win, 0, 0);
		print_menu(menu_win, menu, menu_choice, 5);
		menu_choice = getchoice(menu_win, menu, 5, menu_choice);
		wclear(submenu_win = menu_win);
		box(submenu_win, 0, 0);
		wattron(submenu_win, COLOR_PAIR(4));
		switch (menu_choice) {
		case STACK:
			stack(submenu_win, submenu_stack, 4);
			break;
		case QUEUE:
			queue(submenu_win, submenu_queue, 4);
			break;
		case LIST:
			list(submenu_win, submenu_list, 6);					
			break;
		case HELP: 
			wbkgd(submenu_win, COLOR_PAIR(3) );
			mvwprintw(submenu_win, 2, 2, "In case of any problems or even for better results: Exit Now and run again maximizing the terminal window\n");
			getch();
			break;
		case EXIT:
			print_menu(submenu_win, submenu_exit, submenu_choice, 2);
			submenu_choice = getchoice(submenu_win, submenu_exit, 2, submenu_choice);
			switch (submenu_choice) {
			case YES:
				delwin(submenu_win);
				endwin();
				exit(0);
			case NO:
				break;		
			}
			break;
		default:
			break;
		}
		wclear(submenu_win);
		mvwin(menu_win, HL, C/2);
		bkgd(COLOR_PAIR(4));
	}
	return 0;
}
