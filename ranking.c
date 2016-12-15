/*ranking*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<curses.h>
#include	"crossyRoad.h"

#define LINELEN 50

struct record ranking[11];
int idx_p[11];

char file[] = "ranking.txt";

void init_ranking(){
	int i;
        FILE *in_fp;

        for(i = 0; i < 11; i++)
                idx_p[i] = i;
 
        if( (in_fp = fopen(file, "r")) != NULL )
                read_file(in_fp);
        fclose(in_fp);
}


void record_ranking(){
	FILE *out_fp;
	if( (out_fp = fopen(file, "w")) != NULL)
        	write_file(out_fp);
	fclose(out_fp);
}

void read_file(FILE *fp){
	char line[LINELEN];;
	char *token = NULL;
	char space[] = " ";
	int i = 0, j = 0;
	
	//move(10, 10);
	while(fgets( line, LINELEN, fp) ){
		int tmp;
		//printf("%s\n", line);
		token = strtok(line, space);
		while(token != NULL){
			switch(j){
			case 0:
				ranking[i].rank = atoi(token);		
				//printf("%d ", ranking[i].rank);
				break;
			case 1:
				strcpy(ranking[i].name, token);
				//printf("%s ", ranking[i].name);
				break;
			case 2:
				ranking[i].stage = atoi(token);
				//printf("%d ", ranking[i].stage);
				break;
			case 3:
				ranking[i].score = atoi(token);
				//printf("%d\n",ranking[i].score);
			}
//			printf("%s ", token);
			token = strtok(NULL, space);
			j++;
		}
	//	addstr(line);
		i++;
		j = 0;
	}
	//refresh();
}

void write_file(FILE *fp){
	char temp[20];
	int i = 0, j = 0;

	while(i<10){
//	while(ranking[i].rank != -1){
		for(j = 0; j < 4; j++){
			switch(j){
			case 0:
				sprintf(temp, "%d ", ranking[idx_p[i]].rank);
				break;
			case 1:
				strcpy(temp, ranking[idx_p[i]].name);
				strcat(temp, " ");
				break;
			case 2:
				sprintf(temp, "%d ", ranking[idx_p[i]].stage);
	//			printf("%s", temp);
				break;
			case 3:
				sprintf(temp, "%d\n", ranking[idx_p[i]].score);
			}
	//			fseek(fp, 0L, SEEK_CUR);
			 fputs(temp, fp);
			
		}
	//	fputs("\n", fp);
		i++;
	}
}

void show_ranking(int stage, int score){
	int i = 0;
	char name[20];
	char ch;

	initscr();
	echo();
	clear();

	mvaddstr(20, 35, "input your name >> ");
	while((ch=getchar())!='\r')
		name[i] = ch;
//	instr(name);
//        fgets(name, sizeof(name), stdin);

	ranking[idx_p[10]].rank = 1;
	strcpy(ranking[idx_p[10]].name, name);
	ranking[idx_p[10]].stage = stage;
	ranking[idx_p[10]].score = score;
		
	compare_ranking();


	mvaddstr(23, 35, "rank username stage score\n");
	for( i=0; i<10; i++){
		sprintf(temp, "%d ",ranking[idx_p[i]].rank);
		addstr(temp);
		strcpy(temp, ranking[idx_p[i]].name);
		strcat(temp, " ");
		addstr(temp);
		sprintf(temp, "%d ", ranking[idx_p[i]].stage);
		addstr(temp);
		sprintf(temp, "%d\n", ranking[idx_p[i]].score);
		addstr(temp);
	}refresh();
	getch();
//	endwin();
}

void compare_ranking(){
	int i, j, k;
	int new_score, old_score;
	int temp;

	new_score = ranking[idx_p[10]].stage * 100 + ranking[idx_p[10]].score;

	for(i = 0; i < 10&&ranking[idx_p[i]].rank!=-1; i++){
		old_score = ranking[idx_p[i]].stage*100+ranking[idx_p[i]].score;

		if(new_score > old_score){
			temp = idx_p[i];
			idx_p[i] = 10;
			idx_p[10] = temp;
			break;
		}else if(new_score == old_score){
				
		}else{
			ranking[idx_p[10]].rank++;
		}				
	}

	for(j = i+1; j < 10; j++){
		temp = idx_p[j];
		idx_p[j] = idx_p[10];
		idx_p[10] = temp;
		ranking[idx_p[j]].rank++;
	}
}
