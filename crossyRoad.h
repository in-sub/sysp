#define BLANK           ' '
#define BALL_SYMBOL     'O'
#define ROAD_SYMBOL     "========================="
#define BNDR_SYMBOL     '+'                             //경계선 심볼
#define OBS_SYMBOL	"OOOOOOO"
#define OBS_BLANK	"       "
#define TOP_ROW         9
#define BOT_ROW         21
#define LEFT_EDGE       9
#define RIGHT_EDGE      35

#define X_INIT          22
#define Y_INIT          20
#define MAXMSG		10
#define TIME		20000

struct ppball{
                int y_pos, x_pos;
                int y_dir, x_dir;
                char symbol;
};

struct obstacle{
		char *str;
		int idx;
		int row, col;
		int delay;
		int dir;
};
