/*all box functions*/
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
/*Input: win->Pointer to Window , y,x -> starting co-ordinates, s-> size of box; y-> number of boxes 
  Output: pointer to newly created array of objects of structure mybox
  Description: Draw continuos n boxes and creates them in memory*/
mybox** nboxes(WINDOW* q, int w, int e, int r, int y) {
	char buffer[16];
	int i = 0;
	mybox** temp = (mybox**)malloc(y*sizeof(mybox));
	while(y--) {
		sprintf(buffer, "%d", i);
		temp[i++] = newbox(q, w, e, r, buffer);
		e = e + r;
	}
	return temp;
}
/*Input: win->Pointer to Window , y,x -> starting co-ordinates, s-> size of box; label-> label below the box 
  Output: pointer to newly created object of structure mybox
  Description: Draw a box and creates a structure mybox with that properties*/
mybox* newbox(WINDOW* win, int y, int x, int s, char label[]) {
	int i = x, j = y;
	mvwaddch(win, j, i++, ACS_ULCORNER);
	for(;i<s+x;i++)
		mvwaddch(win, j, i, ACS_HLINE);
	mvwaddch(win, j++, i, ACS_URCORNER);
	for(;j<s/2+y;j++)
		mvwaddch(win, j, i, ACS_VLINE);
	mvwaddch(win, j, i--, ACS_LRCORNER);
	for(;i>x;i--)
		mvwaddch(win, j, i, ACS_HLINE);
	mvwaddch(win, j--, i, ACS_LLCORNER);
	for(;j>y;j--)	
		mvwaddch(win, j, i, ACS_VLINE);
	mvwprintw(win, y+s/2+1, x+(1+s-strlen(label))/2, "%s", label);
	mybox *temp = (mybox*)malloc(sizeof(mybox));
	temp->y = y;
	temp->x = x;
	temp->s = s;
	strcpy(temp->label,label);
	strcpy(temp->data,"\0");
	return temp;
}
/*Input: win->Pointer to Window , b-> pointer to box in which we need to write label[] 
  Description: Write the label in the box at centre and and add that label to the mybox properties*/
void inbox(WINDOW* win, mybox* b, char *label) {
	int i = b->x + (1 +b->s-strlen(label))/2, j = b->y + b->s/4, k = b->s;
	wmove(win, j, b->x+1);	
	while(--k) waddch(win, ' ');
	strcpy(b->data, label);
	wattron(win, COLOR_PAIR(3) );
	mvwprintw(win, j, i, "%s", label);
	napms(500);
	wattroff(win, COLOR_PAIR(3));
	mvwprintw(win, j, i, "%s", label);
}
