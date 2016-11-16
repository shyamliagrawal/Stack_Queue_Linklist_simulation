/*handle queue case*/
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
void queue(WINDOW* win, char *menu[], int nchoice) {
	WINDOW* win1, *win2;
	win1 = init(win, &win2);
	int headn, tailn, flag = 0, i;
	char tailc[4], data[4] ;
	mybox* head = newbox(win2, U, C - 4*U, 2*U, "Head");
	mybox* tail = newbox(win2, U, C + 2*U, 2*U, "Tail");
	mybox **array = nboxes(win2, 3*(HL)/2, (2*C - 4*16)/2, 4, 16);
	int brk = 0, choice = 1;
	while(brk == 0) {
		print_menu(win, menu, choice, nchoice);
		choice = getchoice(win, menu, nchoice, choice);
		if(flag == 0 && (choice == ENQUEUE || choice == DEQUEUE)) {
			fancyprint(win, L - 3, C - 10, "Initialize First!");
			choice = 1;
			getch();
			wmove(win, L-3, 2);
			wclrtoeol(win);
			continue;
		}
		switch(choice) {
			case INIT:
				headn = tailn = 0;
				flag = 1;
				flashwin(win1, 1);
				wmove(win1, 2, 1);
				whline(win1, 0, C-2);
				flashwin(win2, 2);
				inbox(win2, head, "0"); 	
				inbox(win2, tail, "0"); 		
				break;		
			case ENQUEUE:
				if(tailn == MAXX - 1){
					fancyprint(win, L - 3, C - 10, "Queue FULL!!");
					getch();
					break;
				}			
				fancyprint(win,L-3, C-10, "Enqueue Data: ");
				echo();
				wgetnstr(win, data, 3);
				noecho();
				flashwin(win1, 1);
				walkin(win1, 2*L-4, (1+tailn)*2, (C-U*2)/2 ,U*2, data);
				flashwin(win2, 2);
				inbox(win2, array[tailn++], data); 
				sprintf(tailc, "%d", tailn);
				inbox(win2, tail, tailc); 
				break;
			case DEQUEUE:
				if(tailn == 0) {
					fancyprint(win, L - 3, C - 10, "Queue EMPTY!!");
					getch();
					break;
				} 
				i = headn;
				flashwin(win1, 1);
				if(i == tailn) 
					cleardisc(win1, 2+ i*2, (C-U*2)/2 ,U*2, "   " );
				else {
					while(i < tailn-1) {
						cleardisc(win1, 2+ i*2, (C-U*2)/2 ,U*2, "   " );
						napms(100);i++;
						walkin(win1, 2+i*2, i*2, (C-U*2)/2 ,U*2, array[i]->data);
					}	
				}
				fancyprint(win, L - 3, C - 10, "Dequed Value: ");
				wprintw(win, "%s", array[headn]->data);
				flashwin(win2, 2);
				inbox(win2, array[headn], "   ");  
				i = headn;
				while(i < tailn) {
					inbox(win2, array[i], array[i+1]->data);
					i++;
				} 
				inbox(win2, array[--tailn], "   ");
				sprintf(tailc, "%d", tailn);
				inbox(win2, tail, tailc); 
				break;
			case BACK:
				brk = 1;
				break;
		}
		wmove(win, L-3, 1);
		wclrtoeol(win);
		box(win, 0, 0);
	}
	free(head);
	free(tail);
	free(array);
	delwin(win1);
	delwin(win2);
	touchwin(stdscr);
}
