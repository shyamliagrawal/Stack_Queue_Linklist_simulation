/*customization functions*/
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
/*Input: win->Pointer to Window to be moved. win2->address to store the window created by program. 
  Output: win->newly created window
  Description: It iniyialize the screen to a certain arrangement by manipulating win, creates 2 new windows and return their pointers to caller*/
WINDOW* init(WINDOW *win, WINDOW** win2) {
	WINDOW *temp1, *temp2;
	temp1 = (WINDOW*)malloc(sizeof(WINDOW));
	temp2 = (WINDOW*)malloc(sizeof(WINDOW));
	mvwin(win, 0 ,C);
	temp1 = newwin(0, C, 0, 0);
	temp2 = newwin(0, 0, L, C);
	immedok(temp1, TRUE);
	immedok(temp2, TRUE);
	print_mid(temp1, 1, "Conceptual Representation");
	print_mid(temp2, 1, "Array based Implementation");
	box(temp1, 0, 0);
	box(temp2, 0, 0);
	wbkgd(temp1, COLOR_PAIR(1));
	wbkgd(temp2, COLOR_PAIR(2));
	*win2 = temp2;
	return temp1;
}
/*Input: win->Pointer to Window , row-> row position ,txt-> message to write 
  Description: to catch attention of user to the text*/
void fancyprint(WINDOW* win, int row, int col, char* txt) {
	int len = strlen(txt);
	while(len) {
		wmove(win, row, col);
		winsch(win, txt[len-1]);	
		napms(30);
		len--;
    }
    wmove(win, row, col + strlen(txt) + 1);
}
/* flashes the window win whoes original colour pair is i to white*/ 
void flashwin(WINDOW * win, int i) {
	wbkgd(win, COLOR_PAIR(3));
	napms(40);
	wbkgd(win, COLOR_PAIR(i));
	napms(40);
}
