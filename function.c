#include "function.h"

//记录木板位置和球位置
extern struct point Bpoint;
extern struct point Opoint;
//记录方向
extern struct point Bdir;
extern struct point Odir;

//中间位置
extern int cx;
extern int cy;

extern int flag;//球在板上
extern int score;//分数

//curse库中的move（y，x）我们将其交换
void gotoxy(int x, int y){
    move(y, x);
}

void gotoxy_putc(int x, int y, char c){
    mvaddch(y, x, c);
    move(LINES - 1, 1);
    refresh();
}

void gotoxy_puts(int x, int y, char *c){
    mvaddstr(y, x, c);
    move(LINES - 1, 1);
    refresh();
}

//初始化框图
void initfield(){
    mvaddch(0, 0, '0');
    gotoxy_putc(X + 2, 0, 'X');
    gotoxy_putc(0, Y + 2, 'Y');
    attron(COLOR_PAIR(1));
    for(int i = 1; i <= X; i++){
        gotoxy_putc(i, 1, '-');
        gotoxy_putc(i, Y, '-');
    }
    for(int i = 1; i <= Y; i++){
        gotoxy_putc(1, i, '-');
        gotoxy_putc(X, i, '-');
    }
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    gotoxy_puts(2, Y + 3, "Message: ");
    gotoxy_puts(X + 3, 2, "Help: ");
    attroff(COLOR_PAIR(2));
}

//初始化游戏画面
void initgame(){
    if(!has_colors() || start_color() == ERR){
        endwin();
        fprintf(stderr, "terminal not surpport color\n");
        exit(1);
    }
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_CYAN);
    init_pair(4, COLOR_BLACK, COLOR_BLACK);

    initfield(X, Y);

    //绘制木板
    Bpoint.x = cx - 3;
    Bpoint.y = Y - 3;
    Bdir.x = Bdir.y = 0;
    attron(COLOR_PAIR(3));
    for(int i = 0; i < 8; i++){
        gotoxy_putc(Bpoint.x + i, Bpoint.y, ' ');
        gotoxy_putc(Bpoint.x + i, Bpoint.y + 1, ' ');
    }
    attroff(COLOR_PAIR(3));

    //绘制球
    Opoint.x = cx, Opoint.y = Y - 4;
    Odir.x = Odir.y = 0;
    attron(COLOR_PAIR(2));
    gotoxy_putc(Opoint.x, Opoint.y, 'o');
    attroff(COLOR_PAIR(2));

    refresh();
}

void drawgame(){

    //消除之前的木板 加入新的木板
    attron(COLOR_PAIR(4));
    for(int i = 0; i < 8; i++){
        gotoxy_putc(Bpoint.x + i, Bpoint.y, ' ');
        gotoxy_putc(Bpoint.x + i, Bpoint.y + 1, ' ');
    }
    attroff(COLOR_PAIR(4));

    
    Bpoint.x += Bdir.x;
    Bpoint.y += Bdir.y;
    memset(&Bdir, 0, sizeof(Bdir));
    if(Bpoint.x >= X - 8) Bpoint.x = X - 8;
    if(Bpoint.x <= 2) Bpoint.x = 2; 


    attron(COLOR_PAIR(3));
    for(int i = 0; i < 8; i++){
        gotoxy_putc(Bpoint.x + i, Bpoint.y, ' ');
        gotoxy_putc(Bpoint.x + i, Bpoint.y + 1, ' ');
    }
    attroff(COLOR_PAIR(3));

    //消除之前的球 绘制新球
    gotoxy_putc(Opoint.x, Opoint.y, ' ');

    Opoint.x += Odir.x;
    Opoint.y += Odir.y;

    if(Opoint.x >= X - 1){
        Opoint.x = X - 1;
        Odir.x = -1;
        //Odir.y *= -1;
    }
    if(Opoint.x <= 2){
        Opoint.x = 2;
        Odir.x = 1;
        //Odir.y *= -1;
    }

    if(Opoint.y <= 2){
        Opoint.y = 2;
        Odir.y = 1;
        //Odir.x *= -1;
    }

    if(Opoint.y >= Y - 1){
        char info[1024] = {0};
        sprintf(info, "GameOver! Score = %d!", score);
        gotoxy_puts(3, Y + 5, info);
        
        //game over 还原现场
        flag = 0;
        score = 0;
        for(int i = 0; i <= X; i++){
            for(int j = 0; j <= Y; j++){
                gotoxy_putc(i, j, ' ');
            }
        }
        refresh();
        initgame();
    }

    if(flag && Opoint.x <= Bpoint.x + 8 && Opoint.x >= Bpoint.x && Opoint.y >= Y - 4){
        score += 100;
        Odir.y = -1;
        char info[1024] = {0};
        sprintf(info, "You get the ball ! Score = %d!", score);
        gotoxy_puts(3, Y + 4, info);
    }
    if(flag == 0){
        Opoint.x = Bpoint.x + 3;
    }
    attron(COLOR_PAIR(2));
    gotoxy_putc(Opoint.x, Opoint.y, 'o');
    attroff(COLOR_PAIR(2));

}
