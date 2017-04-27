#include "control.h"
#include <stdlib.h>

char g_chBackGround[ROW][COL] = {0};
char g_chCurBrick[4][4] = {0};
int g_nX = 0;
int g_nY = 0;
int g_nRotate = 0;
int g_nType = 0;

//所有可能出现的方块
char g_chAllBrick[][4] =
{
    //L型type0
    0,0,0,0,
    1,0,0,0,
    1,0,0,0,
    1,1,0,0,

    0,0,0,0,
    0,0,0,0,
    0,0,1,0,
    1,1,1,0,

    0,0,0,0,
    1,1,0,0,
    0,1,0,0,
    0,1,0,0,

    0,0,0,0,
    0,0,0,0,
    1,1,1,0,
    1,0,0,0,

    //J型type1
    0,0,0,0,
    0,1,0,0,
    0,1,0,0,
    1,1,0,0,

    0,0,0,0,
    0,0,0,0,
    1,1,1,0,
    0,0,1,0,

    0,0,0,0,
    1,1,0,0,
    1,0,0,0,
    1,0,0,0,

    0,0,0,0,
    0,0,0,0,
    1,0,0,0,
    1,1,1,0,

    //I型type2
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    1,1,1,1,

    1,0,0,0,
    1,0,0,0,
    1,0,0,0,
    1,0,0,0,

    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    1,1,1,1,

    1,0,0,0,
    1,0,0,0,
    1,0,0,0,
    1,0,0,0,

    //O型type3
    0,0,0,0,
    0,0,0,0,
    1,1,0,0,
    1,1,0,0,

    0,0,0,0,
    0,0,0,0,
    1,1,0,0,
    1,1,0,0,

    0,0,0,0,
    0,0,0,0,
    1,1,0,0,
    1,1,0,0,

    0,0,0,0,
    0,0,0,0,
    1,1,0,0,
    1,1,0,0,

    //T型type4
    0,0,0,0,
    0,0,0,0,
    0,1,0,0,
    1,1,1,0,

    0,0,0,0,
    0,1,0,0,
    1,1,0,0,
    0,1,0,0,

    0,0,0,0,
    0,0,0,0,
    1,1,1,0,
    0,1,0,0,

    0,0,0,0,
    1,0,0,0,
    1,1,0,0,
    1,0,0,0,

    //S型type5
    0,0,0,0,
    0,0,0,0,
    0,1,1,0,
    1,1,0,0,

    0,0,0,0,
    1,0,0,0,
    1,1,0,0,
    0,1,0,0,

    0,0,0,0,
    0,0,0,0,
    0,1,1,0,
    1,1,0,0,

    0,0,0,0,
    1,0,0,0,
    1,1,0,0,
    0,1,0,0,

    //Z型type6
    0,0,0,0,
    0,0,0,0,
    1,1,0,0,
    0,1,1,0,

    0,0,0,0,
    0,1,0,0,
    1,1,0,0,
    1,0,0,0,

    0,0,0,0,
    0,0,0,0,
    1,1,0,0,
    0,1,1,0,

    0,0,0,0,
    0,1,0,0,
    1,1,0,0,
    1,0,0,0
};

int GetNewBrick() {
    int nIndexRow = 0;
    int nIndexCol = 0;
    int nIndexBrick = 0;
    int nTotalShape= 0;
    //初始化
    g_nY = 0;
    g_nX = COL / 2;

    nTotalShape = (sizeof(g_chAllBrick) / sizeof(g_chAllBrick[0])) / 16;
    g_nType = rand() % nTotalShape;
    g_nRotate = rand() % ROTATE_NUM;
    nIndexBrick = 16*g_nType + 4*g_nRotate;
    //填充方块
    for (nIndexRow = 0; nIndexRow < 4; nIndexRow++) {
        for (nIndexCol = 0; nIndexCol < 4; nIndexCol++) {
            g_chCurBrick[nIndexRow][nIndexCol] =
                g_chAllBrick[nIndexBrick+nIndexRow][nIndexCol];
        }
    }

    return 1;
}

int InitBackGround() {
    //遍历数组,把"边缘"变成 1,其他部分为0
    int nIndexRow = 0;
    int nIndexCol = 0;

    for (nIndexRow = 0; nIndexRow < ROW; nIndexRow++)
    {
        for (nIndexCol = 0; nIndexCol < COL; nIndexCol++)
        {
            if (nIndexCol == 0 
                || nIndexCol ==COL - 1 
                || nIndexRow == ROW - 1)
            {
                g_chBackGround[nIndexRow][nIndexCol] = FLAG_FIL;
            }
            else
            {
                g_chBackGround[nIndexRow][nIndexCol] = FLAG_EMP;
            }
        }
    }
    return 1;
}

int IsOverlap(int x, int y)
{
    int nIndexRow = 0;
    int nIndexCol = 0;
    for (nIndexRow = 0; nIndexRow < 4; nIndexRow++)
    {
        for (nIndexCol = 0; nIndexCol < 4; nIndexCol++)
        {
            if(g_chCurBrick[nIndexRow][nIndexCol] == 1)
            {
                if (g_chBackGround[y+nIndexRow][x + nIndexCol] == 1)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int Left()
{
  //判断能否左移
  if(/*可以*/IsOverlap(g_nX - 1, g_nY) != 1)
  {
    g_nX = g_nX - 1;
    return 1;
  }
  else
  {
    return 0;
  }
}
int Right()
{
  //判断能否右移
  if(/*可以*/IsOverlap(g_nX + 1, g_nY) != 1)
  {
    g_nX = g_nX + 1;
    return 1;
  }
  else
  {
    return 0;
  }
  return 1;
}
int Up()
{
  if (IsCanRotate()/*能否旋转*/)
  {
    Rotate();
    return 1;
  }
  return 0;
}
int Down()
{
  //能否下移
  if (IsOverlap(g_nX, g_nY + 1) != 1)
  {
    g_nY = g_nY + 1;
    return 1;
  }
  else
  {
    
    if(g_nY < ROW_BEGIN) {
        exit(0);
    }

    FixBrick();
    //扫描,判断是否需要消行
    while(IsVanish())
    {
      RemoveLine();
    }
    GetNewBrick();
  }

  return 1;
}

int RemoveLine()
{
  int i, j;
  for (i = ROW_END; i > ROW_BEGIN; i--) {
      for (j = COL_BEGIN; j < COL_END; j++) {
          g_chBackGround[i][j] = g_chBackGround[i-1][j];
      }
  }

  return 1;
}
int IsVanish()
{
    int i, j;;
    for (i = ROW_END-1; i > ROW_BEGIN; i--) {
        for (j = COL_BEGIN; j < COL_END; j++) {
            if (g_chBackGround[i][j] == 0) {
                return 0;
            }
        }
        return 1;
    }
}

int FixBrick()
{
  int nIndexRow = 0;
  int nIndexCol = 0;
  for (nIndexRow = 0; nIndexRow < 4; nIndexRow++) {
    for (nIndexCol = 0; nIndexCol < 4; nIndexCol++) {
      if(g_chCurBrick[nIndexRow][nIndexCol] == 1) {
        g_chBackGround[g_nY +nIndexRow][g_nX + nIndexCol] = 1;
      }
    }
  }
  return 1;
}

int IsCanRotate()
{
  int nIndexRow = 0;
  int nIndexCol = 0;
  int nIndexBrick = 0;
  char chTempBrick[4][4] = {0};
  int nRotate = 0;
  nRotate = (g_nRotate+1) % 4;
  
  //取出下一个旋转类型的方块
  nIndexBrick = 16*g_nType + 4*nRotate;

  for (nIndexRow = 0; nIndexRow < 4; nIndexRow++) {
    for (nIndexCol = 0; nIndexCol < 4; nIndexCol++) {
      chTempBrick[nIndexRow][nIndexCol] = 
        g_chAllBrick[nIndexBrick+nIndexRow][nIndexCol];
    }
  }

  //判断是否可以旋转
  for (nIndexRow = 0; nIndexRow < 4; nIndexRow++) {
    for (nIndexCol = 0; nIndexCol < 4; nIndexCol++) {
      if(chTempBrick[nIndexRow][nIndexCol] == FLAG_FIL) {
        if(g_chBackGround[g_nY+nIndexBrick+nIndexRow][g_nX+nIndexCol]
          == FLAG_FIL) {
          return 0;
        }
      }
    }
  }

  return 1;
}

int Rotate() {
  int nIndexRow = 0;
  int nIndexCol = 0;
  int nIndexBrick = 0;

  g_nRotate = (g_nRotate+1) % 4;
  
  nIndexBrick = 16*g_nType + 4*g_nRotate;
  for (nIndexRow = 0; nIndexRow < 4; nIndexRow++) {
    for (nIndexCol = 0; nIndexCol < 4; nIndexCol++) {
      g_chCurBrick[nIndexRow][nIndexCol] = 
        g_chAllBrick[nIndexBrick+nIndexRow][nIndexCol];
    }
  }

  return 1;
} 

int isEmpty() {
    int i, j;
    for (i = 0; i < ROW_BEGIN; i++) {
        for (j = COL_BEGIN; j < COL_END; j++) {
            if (g_chAllBrick[i][j] == 1) {
                return 0;
            }
        }
    }
    return 1;
}