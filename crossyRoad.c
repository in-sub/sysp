#include        <stdio.h>
#include        <curses.h>
#include        <signal.h>
#include        <string.h>
#include        <termios.h>
#include        <stdlib.h>
#include 	<pthread.h>
#include	<unistd.h>
#include        "crossyRoad.h"

struct ppball the_ball;

void set_up(struct obstacle[]);         	//전체 초기화
void init_ball();				//공 초기화
void init_obs(struct obstacle[]);                //장애물 초기화
void add_boundary();				//경계선  그리기
void add_road();				//도로 그리기

void ball_move();				//공 움직임
void within_boundary(struct ppball*);		//공이 경계선을 넘지 않도록
void set_score(int, int);			//점수 계산

void *move_obs(void *);				//장애물 움직임

int is_ended();

pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;

int is_game_over = 0;
int input;
int score = 0;
int dif;

int main(){
	int i;
	struct obstacle the_obstacle[NUM_ROAD];
	pthread_t threads[NUM_ROAD];

	set_up(the_obstacle);

	for(i =0 ; i < NUM_ROAD; i++)
		if(pthread_create(&threads[i], NULL, move_obs, &the_obstacle[i])){		
			fprintf(stderr,"Error with creating thread");
			endwin();
			exit(0);
		}

	input = getchar();
        while(!is_ended()){
                if(input=='w')      {the_ball.y_dir = -2;   the_ball.x_dir = 0;}
                else if(input=='s') {the_ball.y_dir = 2;    the_ball.x_dir = 0;}
                else if(input=='a') {the_ball.x_dir = -2;   the_ball.y_dir = 0;}
                else if(input=='d') {the_ball.x_dir = 2;    the_ball.y_dir = 0;}
                ball_move();
		input = getchar();
        }

	pthread_mutex_lock(&mx);
	for(i =0; i < NUM_ROAD; i++)
		pthread_cancel(threads[i]);
	
        endwin();
	return 0;
}

void set_up(struct obstacle the_obstacle[]){        
	init_ball();                                                   
	init_obs(the_obstacle);
        initscr();
        noecho();
        crmode();
	clear();
        signal(SIGINT, SIG_IGN);
        mvaddstr(5, 9, "SCORE: ");
        mvaddstr(5, 16, "0");
	mvaddstr(TOP_ROW+1, X_INIT-2, "G O A L");
        add_boundary();                                                 //경계선 그리기
        add_road();                                                     //도로 그리기
        mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);	//공 그리기
	refresh();
}

void init_obs(struct obstacle the_obstacle[]){
	int i;

	srand(getpid());
	for(i = 0; i < NUM_ROAD; i++){
		the_obstacle[i].str = OBS_SYMBOL;
		the_obstacle[i].row = Y_INIT-2-(2*i);
		the_obstacle[i].delay = 1+(rand()%15);
		the_obstacle[i].dir = ((rand()%2)?1:-1);
		the_obstacle[i].idx = i;
//		the_obstacle[i].col = rand()%EFT_EDGE+2;
		the_obstacle[i].col = (rand()%(RIGHT_EDGE-LEFT_EDGE-2*LENGTH))+LEFT_EDGE+2;
	}
}

void init_ball(){
        the_ball.y_pos = Y_INIT;
        the_ball.x_pos = X_INIT;
        the_ball.y_dir = 0;
        the_ball.x_dir = 0;
        the_ball.symbol = BALL_SYMBOL;
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

        for(i=11; i<BOT_ROW-1; i+=2)   mvaddstr(i, 21, ROAD_SYMBOL);
}

void ball_move(){
        
	int y_cur, x_cur;

        y_cur = the_ball.y_pos;
        x_cur = the_ball.x_pos;

        within_boundary(&the_ball);

	set_score(y_cur, x_cur);   

        mvaddch(y_cur, x_cur, BLANK);
        mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
        move(LINES-1, COLS-1);
        refresh();
}

void within_boundary(struct ppball *bp){
        int y, x;
        y = bp->y_pos + bp->y_dir;
        x = bp->x_pos + bp->x_dir;

        if(y>TOP_ROW && y<BOT_ROW && x>LEFT_EDGE+1 && x<RIGHT_EDGE-1){
                bp->y_pos = y;
		bp->x_pos = x;
	}	
}

void set_score(int y_cur, int x_cur){
	static int back_cnt = 0;
        char str_score[3];
	
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
}

void *move_obs(void *arg){
        struct obstacle *info = arg;
        int len = strlen(info->str)+2;
        char num[3];

        while(1){
                if((info->idx  == (Y_INIT-the_ball.y_pos-2)/2 && info->col < the_ball.x_pos &&  the_ball.x_pos < (info->col+LENGTH))|| is_ended()){
			is_game_over = 1;
                        break;
		}

                usleep(info->delay*TIME);

                pthread_mutex_lock(&mx);
                move(info->row, info->col);
                addch(' ');
                addstr(info->str);
                addch(' ');
                move(LINES-1, COLS-1);
                refresh();
                pthread_mutex_unlock(&mx);
                info->col += info->dir;
                if(info->col == LEFT_EDGE+1  && info->dir == -1)
                        info->dir = 1;
                else if(info->col+len>=RIGHT_EDGE  && info->dir == 1 )
                        info->dir = -1;
        }
        move(0, 0);
	if(score == NUM_ROAD+1)
		addstr("you win");
	else	addstr("game over");
        refresh();
        sleep(10);
}

int is_ended(){
	if( input == 'Q' || score == NUM_ROAD+1 || is_game_over == 1)
		return 1;
	return 0;
}
