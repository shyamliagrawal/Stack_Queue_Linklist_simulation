/* handle stack case*/
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
/*Input: win-> window pointer, menu->submenu options, nchoice->number of choices*/
void stack(WINDOW* win, char *menu[], int nchoice) {
	WINDOW* win1, *win2;
	win1 = init(win, &win2);
	int topn, flag = 0;
	char topc[4];
	char data[4];
	mybox *top = newbox(win2, U, C - 4, 2*U, "top");
	mybox **array = nboxes(win2, HL+U, (2*C - U*16)/2, U, 16);
	int brk = 0, choice = 1;
	while(brk == 0) {
		print_menu(win, menu, choice, nchoice);
		choice = getchoice(win, menu, nchoice, choice);
		if(flag == 0 && (choice == PUSH || choice == POP )) {
			fancyprint(win, L - 3, C - 10 ,"Initialize First!");
			choice = 1;
			getch(); 
			wmove(win, L-3, 2);
			wclrtoeol(win);
			continue;
		}
		switch(choice) {
			case INIT:
				topn = 0;
				flag = 1;
				flashwin(win1, 1);
				wmove(win1, 2*L-2, 1);
				whline(win1, 0, C-2);
				flashwin(win2, 2);
				inbox(win2, top, "0"); 		
				break;				
			case PUSH:	
				if(flag == 0) {
					fancyprint(win, L - 3, C - 10, "Initialize First!");
					choice = 0;
					getch();
					break;
				}
				if(topn == MAXX ){
					fancyprint(win, L - 3, C - 10, "Stack FULL!");
					getch();
					break;
				}			
				fancyprint(win, L - 3, C - 10, "Enter data: ");
				flushinp();
				echo();
				wgetnstr(win, data, 3);
				noecho();
				flashwin(win1, 1);
				walkin(win1, 2, 2*L-U-topn*2, (C-U*2)/2 ,U*2, data);
				flashwin(win2, 2);
				inbox(win2, array[topn++], data); 
				sprintf(topc, "%d", topn);
				inbox(win2, top, topc); 			
				break;
			case POP:
				if(topn == 0) {
					fancyprint(win, L - 3, C - 10, "Stack EMPTY!!");
					getch();
					break;
				}	
				strcpy(data, array[--topn]->data);
				flashwin(win1, 1);
				walkout(win1, 2*L-U-(topn)*2, 2, (C-U*2)/2 ,U*2, data );				
				fancyprint(win, L - 3, C - 10, "Popped Value:");
				wprintw(win,"%s", data);	
				flashwin(win2, 2);
				inbox(win2, array[topn], "   "); 
				sprintf(topc, "%d", topn);
				inbox(win2, top, topc);
				break;
				break;
			case BACK:
				brk = 1;
		}
		wmove(win, L-3, 2);
		wclrtoeol(win);
		box(win, 0, 0);
	}
	free(top);
	free(array);
	delwin(win1);
	delwin(win2);
	touchwin(stdscr);
}
