#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <CONIO.H>
#include "control.h"
#include "view.h"



int main()
{
    char chCmd = '\0';
    clock_t clkStart = clock();
    clock_t clkCurtime = 0;

    srand((unsigned int) time(NULL));

    StartGame();

    while(1)
    {
        //每个一秒,自动下降
        clkCurtime = clock();
        if (clkCurtime - clkStart > 1000)
        {
            clkStart = clkCurtime;
            OnDown();
        }

        if (_kbhit() != 0)
        {
            chCmd = _getch();
            switch(chCmd)
            {
            case 'a':
                OnLeft();
                printf("a\r\n");
                break;
            case 'w':
                OnUp();
                printf("w\r\n");
                break;
            case 's':
                OnDown();
                printf("s\r\n");
                break;
            case 'd':
                OnRight();
                printf("d\r\n");
                break;
            }
        }

    }



    return 0;
}