/*all disc functions*/
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
/*Input: win->Pointer to Window , y,x -> starting co-ordinates, s-> width; data-> to write inside 
  Description: Draw a rectangle of height 2 units*/
void drawdisc(WINDOW* win, int y, int x, int s, char data[]) {
	int i = x, j = y;
	mvwaddch(win, j, i++, ACS_ULCORNER);
	for(;i<s+x;i++)
		mvwaddch(win, j, i, ACS_HLINE);
	mvwaddch(win, j++, i, ACS_URCORNER);
	mvwaddch(win, j++, i, ACS_VLINE);
	mvwaddch(win, j, i--, ACS_LRCORNER);
	for(;i>x;i--)
		mvwaddch(win, j, i, ACS_HLINE);
	mvwaddch(win, j--, i, ACS_LLCORNER);
	mvwaddch(win, j++, i, ACS_VLINE);
	i = x + (1 +s-strlen(data))/2; j = y + 1;
	mvwprintw(win, j, i, "%s", data);
}
/*Input: win->Pointer to Window , fromiline,x -> starting co-ordinates, toline,x -> end co-ordinates, s-> size of box; label-> label below the box 
  Description: animation of vertical disc movement. Stack push*/
void walkin(WINDOW *win, int fromline, int toline, int col, int width, char data[]) {
	int brk = 0;
	while(1) {
		drawdisc(win, fromline, col, width, data);
		napms(100);
		if(brk == 1)
			break;
		cleardisc(win, fromline, col, width, data);
		fromline >= toline? fromline--: fromline++;
		if(fromline == toline) 
			brk = 1;
	}
}
/*Input: win->Pointer to Window , fromiline,x -> starting co-ordinates, toline,x -> end co-ordinates, s-> size of box; label-> label below the box 
  Description: animation of vertical disc movement. Stack pop*/
void walkout(WINDOW *win, int fromline, int toline, int col, int width, char data[]) {
	int brk = 0, i = col, j = fromline +2;
	cleardisc(win, fromline, col, width, data);
	mvwaddch(win, j, i++, ACS_ULCORNER);
	for(;i<width+col;i++)
		mvwaddch(win, j, i, ACS_HLINE);
	mvwaddch(win, j, i, ACS_URCORNER);
	fromline >= toline? fromline--: fromline++;
	while(1) {
		drawdisc(win, fromline, col, width, data);
		napms(100);
		cleardisc(win, fromline, col, width, data);
		fromline >= toline? fromline--: fromline++;
		if(brk == 1)
			break;
		if(fromline == toline) 
			brk = 1;
	}
}
/*Input: win->Pointer to Window , y,x -> starting co-ordinates, s-> width of box; data-> dat in the box 
  Description: animation of vertical disc movement*/
void cleardisc(WINDOW* win, int y, int x, int s, char data[]) {
	int i = x, j = y;
	mvwaddch(win, j, i++, ' ');
	for(;i<s+x;i++)
		mvwaddch(win, j, i, ' '  );
	mvwaddch(win, j++, i, ' ' );
	mvwaddch(win, j++, i, ' ' );
	mvwaddch(win, j, i--, ' ' );
	for(;i>x;i--)
		mvwaddch(win, j, i, ' ' );
	mvwaddch(win, j--, i, ' ' );
	mvwaddch(win, j++, i, ' ' );
	i = x + (1 +s-strlen(data))/2; j = y + 1;
	mvwprintw(win, j, i, "%s", "   ");
}
