#define COL 16
#define COL_BEGIN 1
#define COL_END 15
#define ROW 25
#define ROW_BEGIN 4
#define ROW_END 24
#define FLAG_FIL 1
#define FLAG_EMP 0
#define ROTATE_NUM 4

char g_chBackGround[ROW][COL];
char g_chCurBrick[4][4];
int g_nX;
int g_nY;

int InitBackGround();
int GetNewBrick();

int Left();
int Right();
int Up();
int Down();

int IsOverlap(int x, int y);
int IsCanRotate();
int Rotate();
int FixBrick();

int RemoveLine();
int isVanish();

//判断未显示的出方块的4行是否有内容
int isEmpty();