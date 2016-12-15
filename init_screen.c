/*init_screen.c*/

#include		<stdio.h>
#include	<curses.h>
#include	<signal.h>
#include	"crossyRoad.h"

void init_screen(){
 		
 	int i;
 	initscr();
 	noecho();
 	crmode();
 	clear();
 	signal(SIGINT, SIG_IGN);
 	//'차'
 	for(i = 21; i < 24; i++ )
 		mvaddch(9, i, '=');
 	for(i = 17; i <28 ; i++)
 		mvaddch(10,i, '=');
 	mvaddch(11, 22, '=');
 	
 	mvaddch(12, 21, '=');
 	mvaddch(12, 23, '=');
 
 	mvaddch(13, 20, '=');
 	mvaddch(13, 24, '=');
 
 	mvaddch(14, 19, '=');
 	mvaddch(14, 25, '=');
 
 	mvaddch(15, 18, '=');
 	mvaddch(15, 26, '=');
 	
 	for(i = 9; i<17; i++)
 		mvaddch(i,30,'=');
 	for(i =31; i <34; i++ )
 		mvaddch(12,i,'=');
 
 	//'도'	
  	for(i = 40; i<49; i++)
 		mvaddch(9, i, '=');
 	for(i = 10; i<13; i++)
 		mvaddch(i, 40, '=');
 	for(i = 40; i<49; i++)
 		mvaddch(13, i, '=');
 	for(i = 14; i<16; i++)
 		mvaddch(i, 44, '=');
 	for(i = 38; i<51; i++)
 		mvaddch(16, i, '=');
 	
 	//'를'
 	for(i = 56; i < 65; i ++)
 		mvaddch(9, i, '=');
 	for(i = 10; i < 11; i++)
 		mvaddch(i,64, '=');
 	for(i= 56; i < 65; i ++)
 		mvaddch(11,i,'=');
 	for(i = 12; i <13; i ++)
 		mvaddch(i,56,'=');	
 	for(i = 56; i <65; i++ )
 		mvaddch(13,i,'=');
 	
 	for(i = 54; i<67; i++)
 		mvaddch(14, i, '=');
 
 	for(i = 56; i < 65; i ++)
 		mvaddch(15, i, '=');
 	for(i = 16; i < 17; i++)
 		mvaddch(i,64, '=');
 	for(i= 56; i < 65; i ++)
 		mvaddch(17,i,'=');
 	for(i = 18; i <19; i ++)
 		mvaddch(i,56,'=');	
 	for(i = 56; i <65; i++ )
 		mvaddch(19,i,'=');
 
 	//'건'
 
 	for(i = 61; i < 70; i++)
 		mvaddch(24, i, '=');
 	for(i = 24; i <30 ; i++)
 		mvaddch(i, 70, '=');
 	for(i = 72; i <74; i++)
 		mvaddch(27, i, '=');
 	for(i = 24; i < 30; i++)
 		mvaddch(i, 75, '=');
 	for(i = 30; i <32; i++ )
 		mvaddch(i, 63, '=');	
 	for(i = 63; i<76; i++)
 		mvaddch(32, i, '=');
 	
 	//'너'
 	
 	for(i= 24; i<31; i++)
 		mvaddch(i, 82, '=');
 	for(i = 82; i<92; i++)
 		mvaddch(30, i, '=');
 	for(i = 90; i <94; i++)
 		mvaddch(27, i, '=');
 	for(i = 24; i<33; i++)
 		mvaddch(i, 94,'=');		
 	
 	//'라'
 	for(i = 102; i < 110; i ++)
 		mvaddch(24, i, '=');
 	for(i = 24; i < 28; i++)
 		mvaddch(i,110, '=');
 	for(i= 102; i < 110; i ++)
 		mvaddch(28,i,'=');
 	for(i = 29; i <32; i ++)
 		mvaddch(i,102,'=');	
 	for(i = 102; i <110; i++ )
 		mvaddch(32,i,'=');
 	
 	for(i = 24; i<33; i++)
 		mvaddch(i, 113,'=');
 
 	for(i = 113; i<116; i++)
 		mvaddch(28, i, '=');
 	
 	for(i = 24; i < 31; i++)
 		mvaddstr(i, 120,"oo");
 	//'!'	
 	mvaddstr(32, 120, "oo");
 	mvaddch(33, 119, 'o');
 	mvaddch(33, 122, 'o');
 	mvaddstr(34, 120,"oo");
 	
 	//'자동차'
 	for(i = 24; i < 33; i++ )
		mvaddch(31, i, '=');
	mvaddch(31,24,'=');
	mvaddch(32,23,'=');
	mvaddch(33,22,'=');
	mvaddch(34,21,'=');
	
	for(i=18; i<23; i++)
		mvaddch(34, i, '=');
	for(i=34; i<37; i++)
		mvaddch(i, 18,'=');
	//'바퀴'
	for(i = 18; i < 22; i++)
		mvaddch(37, i, '=');
	mvaddch(36,24,'=');
	mvaddch(37,23,'=');
	mvaddch(37,25,'=');
	mvaddch(38,24,'=');
	
	for(i = 27; i<32; i++)
		mvaddch(37, i, '=');
	mvaddch(36,34,'=');
	mvaddch(37,33,'=');
	mvaddch(37,35,'=');
	mvaddch(38,34,'=');
	
	for(i = 37; i <40; i++)
		mvaddch(37,i,'=');
	

	mvaddch(31,32,'=');
	mvaddch(32,33,'=');
	mvaddch(33,34,'=');
	mvaddch(34,35,'=');
	
	for(i = 35; i <39; i++)
		mvaddch(34, i, '=');
	for(i = 34; i<37; i++)
		mvaddch(i, 39, '=');
	
	move(LINES-1,0);
	refresh();
	getch();
//	clear();
//	endwin();
}
