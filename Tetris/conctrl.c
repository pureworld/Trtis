#include "control.h"
#include <stdlib.h>

char g_chBackGround[ROW][COL] = {0};
char g_chCurBrick[4][4] = {0};
int g_nX = 0;
int g_nY = 0;
int g_nRotate = 0;
int g_nType = 0;

//���п��ܳ��ֵķ���
char g_chAllBrick[][4] =
{
    //L��type0
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

    //J��type1
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

    //I��type2
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

    //O��type3
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

    //T��type4
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

    //S��type5
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

    //Z��type6
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
    //��ʼ��
    g_nY = 0;
    g_nX = COL / 2;

    nTotalShape = (sizeof(g_chAllBrick) / sizeof(g_chAllBrick[0])) / 16;
    g_nType = rand() % nTotalShape;
    g_nRotate = rand() % ROTATE_NUM;
    nIndexBrick = 16*g_nType + 4*g_nRotate;
    //��䷽��
    for (nIndexRow = 0; nIndexRow < 4; nIndexRow++) {
        for (nIndexCol = 0; nIndexCol < 4; nIndexCol++) {
            g_chCurBrick[nIndexRow][nIndexCol] =
                g_chAllBrick[nIndexBrick+nIndexRow][nIndexCol];
        }
    }

    return 1;
}

int InitBackGround() {
    //��������,��"��Ե"��� 1,��������Ϊ0
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
  //�ж��ܷ�����
  if(/*����*/IsOverlap(g_nX - 1, g_nY) != 1)
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
  //�ж��ܷ�����
  if(/*����*/IsOverlap(g_nX + 1, g_nY) != 1)
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
  if (IsCanRotate()/*�ܷ���ת*/)
  {
    Rotate();
    return 1;
  }
  return 0;
}
int Down()
{
  //�ܷ�����
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
    //ɨ��,�ж��Ƿ���Ҫ����
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
  
  //ȡ����һ����ת���͵ķ���
  nIndexBrick = 16*g_nType + 4*nRotate;

  for (nIndexRow = 0; nIndexRow < 4; nIndexRow++) {
    for (nIndexCol = 0; nIndexCol < 4; nIndexCol++) {
      chTempBrick[nIndexRow][nIndexCol] = 
        g_chAllBrick[nIndexBrick+nIndexRow][nIndexCol];
    }
  }

  //�ж��Ƿ������ת
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