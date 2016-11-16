# Stack_Queue_Linklist_simulation
In C using Ncurses library

The program shows simulation of data structures. It covers 3 data structures :
Stack
Queue
List
Operations available on each data structure are:
Stack : Initialize, Push, Pop, Clear
Queue : Initialize, Enqueue, Dequeue, Clear
List  : Initialize, Append, Insert, Remove, Find
The can choose any choice from menu and its submenu and see what is happening to the structure. One windows shows simple animation and abnother shows how Array based implementation works in the background.Full graphical interface is used.

This directory is structured as follows:

Data Structure Simulation
   |----> header.h         -- containing all headers 
   |----> main.c           -- main code n logic
   |----> menu.c           -- menu functions
   |----> disc.c           -- disc functions
   |----> box.c            -- box structure functions
   |----> custom.c         -- customization functions
   |----> stack.c          -- handle stack case
   |----> queue.c          -- handle queue case
   |----> linklist.c       -- handle linklist case
   |----> compile.txt      -- command to compile


Inside this directory
Compile : cc *.c -lncurses -o exec
Run     : ./exec
