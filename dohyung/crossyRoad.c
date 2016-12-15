/*croosRoad.c*/

#include        <stdio.h>
#include        <curses.h>
#include        <signal.h>
#include        <string.h>
#include        <termios.h>
#include        <stdlib.h>
#include 	<pthread.h>
#include	<unistd.h>
#include        "crossRoad1.h"

struct ppball the_ball;
struct obstacle the_obstacle[MAXMSG];

void set_up();          //전체 초기화
void init_ball();	//공 초기화
void add_boundary();    //경계선  그리기
void add_road();        //도로 그리기
void ball_move();       //공 움직임
void within_boundary(struct ppball*);   //공이 경계선을 넘지 않도록

int set_up_obs(struct obstacle the_obstacle[]);
void *animate();
pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;
int num_msg = 6;

int main(){
        int c;
	//int num_msg;
	int i;
	int set_up_obs(struct obstacle the_obstacle[]);
	
	pthread_t threads[MAXMSG];
	struct obstacle the_obstacle[MAXMSG];
	
	set_up_obs(the_obstacle);

        set_up();
	
	for(i = 1 ; i < num_msg-1; i++)
		if(pthread_create(&threads[i], NULL, animate, &the_obstacle[i])){		
			fprintf(stderr,"Error with creating thread");
			endwin();
			exit(0);
		}

        while((c=getchar()) !='Q'){
                if(c=='w')      {the_ball.y_dir = -2;   the_ball.x_dir = 0;}
                else if(c=='s') {the_ball.y_dir = 2;    the_ball.x_dir = 0;}
                else if(c=='a') {the_ball.x_dir = -2;   the_ball.y_dir = 0;}
                else if(c=='d') {the_ball.x_dir = 2;    the_ball.y_dir = 0;}
                ball_move();
        }
	pthread_mutex_lock(&mx);
	for(i = 1; i <num_msg-1; i++)
		pthread_cancel(threads[i]);
	
	
        endwin();
	return 0;
}

void set_up(){
        
	init_ball();                                                    //공 초기화
        initscr();
        noecho();
        crmode();
	clear();
        signal(SIGINT, SIG_IGN);
        mvaddstr(5, 9, "SCORE: ");
        mvaddstr(5, 16, "0");
        add_boundary();                                                 //경계선 그리기
        add_road();                                                     //도로 그리기
        mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);	//공 그리기
	refresh();
}

int set_up_obs(struct obstacle the_obstacle[]){
	
	int num_msg = 6;
	int i;

	srand(getpid());
	for(i = 1; i < num_msg-1; i++){
		the_obstacle[i].str = OBS_SYMBOL;
		the_obstacle[i].row = X_INIT-(2*i+2);
		the_obstacle[i].delay = 1+(rand()%15);
		the_obstacle[i].dir = ((rand()%2)?1:-1);
	}
	return num_msg;
}

void init_ball(){
        the_ball.y_pos = Y_INIT;
        the_ball.x_pos = X_INIT;
        the_ball.y_dir = 0;
        the_ball.x_dir = 0;
        the_ball.symbol = BALL_SYMBOL;
}

void *animate(void *arg){
	
	struct obstacle *info = arg;
	int len = strlen(info->str)+2;
	int col = LEFT_EDGE+2;
	//int col = rand()%(COLS-len-3);
	while(1)
	{
		usleep(info->delay*TIME);

		pthread_mutex_lock(&mx);
		move(info->row, col);
		addch(' ');
		addstr(info->str);
		addch(' ');
		move(LINES-1, COLS-1);
		refresh();
		pthread_mutex_unlock(&mx);
		
		col += info->dir;
		if(col == LEFT_EDGE+1  && info->dir == -1)
			info->dir = 1;
	else if(col+len>=RIGHT_EDGE  && info->dir == 1 )
			info->dir = -1;
	
	
	}

}

void add_boundary(){
        int i;

        //상
        for(i=LEFT_EDGE+1; i<RIGHT_EDGE; i+=2)  mvaddch(TOP_ROW, i, BNDR_SYMBOL);
        //하
        for(i=LEFT_EDGE+1; i<RIGHT_EDGE; i+=2)  mvaddch(BOT_ROW, i, BNDR_SYMBOL);
        //좌
        for(i=TOP_ROW+1; i<BOT_ROW; i++)        mvaddch(i, LEFT_EDGE, BNDR_SYMBOL);
        //우
        for(i=TOP_ROW+1; i<BOT_ROW; i++)        mvaddch(i, RIGHT_EDGE, BNDR_SYMBOL);
}

void add_road(){
        int i;

        for(i=11; i<20; i+=2)   mvaddstr(i, 10, ROAD_SYMBOL);
}

void ball_move(){
        
	int y_cur, x_cur;
        static int back_cnt = 0;
        static int score = 0;
        char str_score[3];

        y_cur = the_ball.y_pos;
        x_cur = the_ball.x_pos;

        within_boundary(&the_ball);

        if(y_cur < the_ball.y_pos)
                back_cnt++;
        else if(y_cur > the_ball.y_pos){
                if(back_cnt > 0)
                        back_cnt--;
                else if(back_cnt == 0){
                        score++;
                        sprintf(str_score, "%d", score);
                        mvaddstr(5, 16, "   ");
                        mvaddstr(5, 16, str_score);
                }
        }

        mvaddch(y_cur, x_cur, BLANK);
        mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
        move(LINES-1, COLS-1);
        refresh();
}

void within_boundary(struct ppball *bp){
        int y, x;
        y = bp->y_pos + bp->y_dir;
        x = bp->x_pos + bp->x_dir;

        if(y>TOP_ROW && y<BOT_ROW && x>LEFT_EDGE && x<RIGHT_EDGE){
                bp->y_pos = y;
		bp->x_pos = x;
	}
	
}

