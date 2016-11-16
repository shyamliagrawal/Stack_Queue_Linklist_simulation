/*all linklist case*/
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
#define Getval(x) getval(val, next, x, startn)
/*Input: win->Pointer to Window 
  Clears label of provided mybox array*/
void clearlabel(WINDOW* win, mybox **arr, int i) {
	while(i--) {
		mvwprintw(win, arr[i]->y + arr[i]->s/2 + 1, arr[i]->x + (1 +arr[i]->s-strlen(arr[i]->label))/2, "%s", "  ");
		strcpy(arr[i]->label, "\0");
		}
}
/* Find next empty position till max m and returns the index*/
int findblank(mybox** val, mybox **next, int m) {
	int temp = 0;
	while(temp < m) {
		if(strcmp(val[temp]->data, "  ") == 0)	
			break;
		temp++;
	}return temp;
}
/*gets value in list at position j and returns its pointer*/
char* getval(mybox** val, mybox ** next, int pos, int start) {
	int posi = start;
	while(--pos)
		sscanf(next[posi]->data, "%d", &posi);
	return val[posi]->data;	
}
/*Input: win-> window pointer, menu->submenu options, nchoice->number of choices*/
void list(WINDOW* win, char *menu[], int nchoice) {
	WINDOW* win1, *win2;
	win1 = init(win, &win2);
	int startn, endn, i = -1, pos, posi, emp, temp, key = 0, j;
	char startc[4], endc[4], data[4], buff[4];
	mybox* start = newbox(win2, 4, C - 8 - 8, 8, "Start");
	mybox* end = newbox(win2, 4, C + 8, 8, "End");
	mvwprintw(win2, HL + 3, 2, "DATA");
	mybox** val = nboxes(win2, HL + 2, (2*C - U*16)/2, U, 16);
	mvwprintw(win2, HL + 5, 2, "Next's Index");
	mybox** next = nboxes(win2, HL + 4, (2*C - U*16)/2, U, 16);
	clearlabel(win2, val, 16);
	int brk = 0, choice = 1, n;
	while(brk == 0) {
		print_menu(win, menu, choice, nchoice);
		choice = getchoice(win, menu, nchoice, choice);
		if(choice != INIT && choice != NBACK && i == -1) {
			fancyprint(win, L - 3,C - 20,  "Initialize First!");
			choice = 1;
			getch();
			continue;
		}
		switch (choice) {
			case INIT:
				startn = -1;
				endn = -1;
				i = 0;
				flashwin(win1, 1);
				wmove(win1, 2, 1);
				whline(win1, 0, C-2);
				flashwin(win2, 2);
				inbox(win2, start, "-1"); 	
				inbox(win2, end, "-1"); 
				break;		
			case APPEND:
				if(i == MAXX){
					fancyprint(win, L - 3,C - 20,  "List FULL!!");
					getch();
					break;
				}			
				fancyprint(win, L - 3,C - 20,  "Append Data: ");
				echo();
				wgetnstr(win, data, 3);
				noecho();
				emp = findblank(val, next, i++);
				flashwin(win1, 1);
				mvwprintw(win1, 1+(i)*2, (C-U*2)/2 - 2, "%d", i);
				walkin(win1, 2*L-4, (i)*2, (C-U*2)/2 ,U*2, data);
				flashwin(win2, 2);
				inbox(win2, val[emp], data); 
				inbox(win2, next[emp], "-1");
				if(endn >= 0) {
					sprintf(buff, "%d", emp);
					inbox(win2, next[endn], buff);  
				}
				if(startn == -1) {	
					startn = 0;
					sprintf(startc, "%d", startn);
					inbox(win2, start, startc); 
					}
				endn = emp;
				sprintf(endc, "%d", endn);
				inbox(win2, end, endc); 
				break;
			case INSERT:
				if(i == MAXX){
					fancyprint(win, L - 3,C - 20, "List FULL!!");
					getch();
					break;
				}	
				if(startn == -1) {	
					startn = 0;
					sprintf(startc, "%d", startn);
					inbox(win2, start, startc); 
					}		
				fancyprint(win, L - 3, C - 20, "Insert Data: ");
				echo();
				wgetnstr(win, data, 3);			
				fancyprint(win, L - 2, C - 20, "At Position: ");
				wscanw(win, "%d",&pos);
				noecho();
				if(pos > i + 1 || pos < 1) {
					mvwprintw(win, L-3, C-20, "                ");
					fancyprint(win, L - 3, C - 20, "Invalid position!");
					getch();
					break;
				}
				flashwin(win1, 1);
				j = i;
				while(j >= pos) {
					walkin(win1, j*2 , j*2 + 2, (C-U*2)/2 ,U*2, Getval(j));
					mvwprintw(win1, 3+(j)*2, (C-U*2)/2 - 2, "%d", j+1);
					napms(100);j--;
				}
				for(j = 1; j < (C-U*2)/2; j++) {
					drawdisc(win1, pos*2, j ,U*2, data );
					napms(100);
					cleardisc(win1, pos*2, j ,U*2, "   ");
					if(pos == 1) {
						wmove(win1, 2, 1);
						whline(win1, 0, C-2);
					}
				}
				drawdisc(win1, pos*2, (C-U*2)/2 ,U*2, data );
				mvwprintw(win1, 1+(pos)*2, (C-U*2)/2 - 2, "%d", pos);
				emp = findblank(val, next, i++);
				flashwin(win2, 2);
				inbox(win2, val[emp], data); 
				if(pos == 1) {
					sprintf(startc, "%d", startn);
					inbox(win2, next[emp], startc);
					startn = emp;
					sprintf(startc, "%d", startn);
					inbox(win2, start, startc);
				}
				else if(pos == i) {
					sprintf(buff, "%d", emp);
					inbox(win2, next[endn], buff);
					endn = emp;
					sprintf(endc, "%d", endn);
					inbox(win2, end, endc); 
					inbox(win2, next[emp], "-1");
					break;
				} 
				if(pos > 1) {
					posi = startn;
					while((pos--)-2) 
						sscanf(next[posi]->data, "%d", &posi);	
					inbox(win2, next[emp], next[posi]->data);
					sprintf(buff, "%d", emp);
					inbox(win2, next[posi], buff); 
				}
				break;
			case DELETE:
				if(i == 0){ 
					fancyprint(win, L - 3,C - 20, "List Empty!!");
					getch();
					break;
				};				
				echo();
				fancyprint(win, L - 3,C - 20, "At Position: ");
				wscanw(win, "%d",&pos);
				noecho();
				if(pos > i || pos < 1) {
					mvwprintw(win, L-3, C-20, "                ");
					fancyprint(win, L - 3,C - 20, "Invalid position!");
					getch();
					break;
				}
				flashwin(win1, 1);
				j = pos ; 
				for(temp = (C-U*2)/2; temp > 0; temp--) {
					drawdisc(win1, pos*2, temp ,U*2, data);
					napms(100);
					cleardisc(win1, pos*2, temp ,U*2, "   ");
					if(pos == 1) {
						wmove(win1, 2, 1);
						whline(win1, 0, C-2);						
					}
				}	
				cleardisc(win1, j*2, (C-U*2)/2 ,U*2, "   " );		
				while(j < i) {
					cleardisc(win1, j*2, (C-U*2)/2 ,U*2, "   " );
					napms(100);j++;
					walkin(win1, j*2 , 2*j - 2, (C-U*2)/2 ,U*2, Getval(j));
				}
				mvwprintw(win1, 1+(pos)*2, (C-U*2)/2 - 2, "%d", pos);
				mvwprintw(win1, 1+(i)*2, (C-U*2)/2 - 2, "  ");
				if(pos == i) {
					temp = (C-U*2)/2;
					mvwaddch(win1, pos*2, temp++, ACS_LLCORNER);
					for(;temp < (C-U*2)/2 + 2*U; temp++)
						mvwaddch(win1, pos*2, temp, ACS_HLINE);
					mvwaddch(win1, pos*2, temp, ACS_LRCORNER);
				}
				flashwin(win2, 2);
				if(pos == 1) {
					temp = startn;
					sscanf(next[temp]->data, "%d", &startn);
					if(startn == -1) {	
						endn = -1;
						sprintf(endc, "%d", endn);
						inbox(win2, end, endc); 
					}
					sprintf(startc, "%d", startn);
					inbox(win2, start, startc);
				}
				else {
					posi = startn;
					j = pos;
					while((j--)-2) 
						sscanf(next[posi]->data, "%d", &posi);
					sscanf(next[posi]->data, "%d", &temp);
					if(pos == i) {
						endn = posi;
						sprintf(endc, "%d", endn);
						inbox(win2, end, endc); 
					}
					inbox(win2, next[posi], next[temp]->data);
				}
				inbox(win2, val[temp], "  ");
				inbox(win2, next[temp], "  ");	
				i--;
				break;
			case FIND:	
				key = 0;	
				fancyprint(win, L - 3,C - 20, "Search key: ");
				echo();
				wgetnstr(win, data, 3);	
				noecho();
				j = startn;
				temp = 0;
				while(j != -1) {
					temp++;
					if(strcmp(val[j]->data, data) == 0)	{
						key = 1;	
						break;
					}	
					sscanf(next[j]->data, "%d", &n);
					j = n;
				}
				if( key == 1) {
					fancyprint(win, L - 2, C - 20, "At Position: ");
					wprintw(win, "%d", temp);
				}
				else
					fancyprint(win, L - 2, C - 20, " Not Found!");
				getch();			
				break;
			case NBACK:
				brk = 1;
		}
		wmove(win, L-3, 2);
		wclrtoeol(win);		
		wmove(win, L-2, 2);
		wclrtoeol(win);		
		box(win, 0, 0);
	}
	free(start);
	free(end);
	free(val);
	free(next);
	delwin(win1);
	delwin(win2);
	touchwin(stdscr);
}
