#include <stdio.h>
#include <stdlib.h>
#include "control.h"

int DrawScene()
{
    int nIndexRow = 0;
    int nIndexCol = 0;
    //1. 把当前方块和背景合并起来
    for (nIndexRow = 0; nIndexRow < 4; nIndexRow++)
    {
        for (nIndexCol = 0; nIndexCol < 4; nIndexCol++)
        {
            if (g_chCurBrick[nIndexRow][nIndexCol] == 1)
            {
                g_chBackGround[g_nY+nIndexRow][g_nX+nIndexCol] = 1;
            }
        }
    }
    //2. 遍历数组
    for (nIndexRow = 0; nIndexRow < ROW; nIndexRow++)
    {
        for (nIndexCol = 0; nIndexCol < COL; nIndexCol++)
        {
            if (g_chBackGround[nIndexRow][nIndexCol] == 1)
            {
                printf("■");
            }
            else
            {
                printf("□");
            }
        }
        printf("\r\n");
    }

    // 3. 把当前方块和背景拆分出来
    for (nIndexRow = 0; nIndexRow < 4; nIndexRow++)
    {
        for (nIndexCol = 0; nIndexCol < 4; nIndexCol++)
        {
            if (g_chCurBrick[nIndexRow][nIndexCol] == 1)
            {
                g_chBackGround[g_nY+nIndexRow][g_nX+nIndexCol] = 0;
            }
        }
    }

    return 1;
}

int StartGame()
{
    InitBackGround();
    GetNewBrick();
    DrawScene();

    return 1;
}

int OnLeft()
{
    system("cls");
    Left();
    DrawScene();
    return 1;
}

int OnRight()
{
    system("cls");
    Right();
    DrawScene();
    return 1;
}

int OnDown()
{
    system("cls");
    Down();
    DrawScene();

    return 1;
}

int OnUp()
{
    system("cls");
    Up();
    DrawScene();
    return 1;
}