#ifndef _FUNCTION_H
#define _FUNCTION_H
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/time.h>
#include<curses.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//定义窗口大小
#define X 70
#define Y 30

struct point {
    int x;
    int y;
};

//curse库中的move（y，x）我们将其交换
void gotoxy(int x, int y);
void gotoxy_putc(int x, int y, char c);
void gotoxy_puts(int x, int y, char *c);


//初始化框图
void initfield();
//初始化游戏画面
void initgame();
//间隔重新绘制游戏画面
void drawgame();

#endif