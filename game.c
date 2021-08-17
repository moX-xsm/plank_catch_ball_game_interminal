#include "function.h"

//记录木板位置和球位置
struct point Bpoint;
struct point Opoint;
//记录方向
struct point Bdir, Odir;

//中间位置
int cx = (X - 2) / 2 + 1;
int cy = (Y - 2) / 2 + 1;

int flag = 0;//球在板上
int score = 0;//分数

int main(){
    initscr();//初始化窗口
    noecho();//终端设置为noecho
    cbreak();//行缓冲-->字符
    keypad(stdscr, TRUE);//打开功能键 上下左右等

    initgame();//重绘主屏幕

    signal(14, drawgame);


    struct itimerval itimer;
    itimer.it_interval.tv_sec = 0;
    itimer.it_interval.tv_usec = 100000;
    itimer.it_value.tv_sec = 0;
    itimer.it_value.tv_usec = 1000;

    setitimer(ITIMER_REAL, &itimer, NULL);


    refresh();
    srand(time(0));
    while(1){
        int c = getch();
        switch(c){
            case KEY_LEFT:{
                Bdir.x -= 2;
                if(flag == 0) Odir.x -= 2;
            }break;
            case KEY_RIGHT:{
                Bdir.x += 2;
                if(flag == 0) Odir.x += 2;
            }break;
            case KEY_UP:{
                if(flag) break;
                flag = 1;
                gotoxy_puts(3, Y + 4, "                                         ");
                gotoxy_puts(3, Y + 5, "                                         ");
                Odir.x = (rand() & 1 ? 1 : -1);
                Odir.y = -1;
                break;
            }
            default:break;
            
        }
    }
    
    getch();
    endwin();
    return 0;
}

