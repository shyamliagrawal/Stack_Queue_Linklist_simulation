

#include<ncurses.h>
#include<string.h>
#include<stdlib.h>
#define C COLS/3
#define L LINES/2
#define HL LINES/4
#define U 4
#define MAXX    16
#define STACK   1
#define QUEUE   2
#define LIST    3
#define HELP    4
#define EXIT    5
#define INIT    1
#define PUSH    2
#define POP     3
#define BACK    4
#define ENQUEUE 2
#define DEQUEUE 3
#define APPEND  2
#define INSERT  3
#define DELETE  4
#define FIND    5
#define NBACK   6
#define YES     1
#define NO      2
#define ENTER   10
void print_menu(WINDOW*, char**, int, int);
void print_mid(WINDOW*, int, char*);
int getchoice(WINDOW*, char**, int, int);
void message(char *, int);
void stack(WINDOW* submenu_win, char **menu, int) ;
void queue(WINDOW* submenu_win, char **menu, int) ;
void list(WINDOW* submenu_win, char **menu, int) ;
void arrow(WINDOW*, int, int, int, int);
WINDOW* init(WINDOW*, WINDOW **);
typedef struct mybox{
	int y, x, s;
	char label[8], data[4];
}mybox;
mybox* newbox(WINDOW*, int, int, int, char*);
mybox** nboxes(WINDOW* q, int, int, int, int);
void drawdisc(WINDOW*, int, int, int, char *);
void cleardisc(WINDOW*, int, int, int, char *);
void inbox(WINDOW*, mybox*, char *);
void walkin(WINDOW *, int , int , int , int, char*);
void walkout(WINDOW *, int , int , int , int, char*);
void flashwin(WINDOW *, int);
void fancyprint(WINDOW*, int, int , char*);
