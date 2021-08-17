# plank_catch_ball_game_interminal
a game -- plank catch ball in terminal

<img src="https://gitee.com/xsm970228/images2020.9.5/raw/master/20210817170431.png" alt="image-20210817170421534" style="zoom: 67%;" />

# curses包的介绍

此小游戏基于curses库进行开发，curses库是专门来进行unix/linux终端环境下的屏幕界面处理以及IO处理的，具体内容的开发指南见 [https://github.com/moX-xsm/plank_catch_ball_game_interminal/blob/main/UNIXLinux%E4%B8%8Bcurses%E5%BA%93%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.2003.%E4%B8%AD%E6%96%87%E7%89%88.pdf](https://github.com/moX-xsm/plank_catch_ball_game_interminal/blob/main/UNIXLinux%E4%B8%8Bcurses%E5%BA%93%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.2003.%E4%B8%AD%E6%96%87%E7%89%88.pdf)

本例中用到的curses库函数的介绍：

```cpp
initscr();//初始化窗口
noecho();//终端设置为noecho
cbreak();//行缓冲-->单字符
keypad(stdscr, TRUE);//打开功能键 上下左右等
move(y, x);//将光标移动到（x，y）出 x为列 y为行
mvaddch(y, x, c);//移动光标并输出字符c
mvaddstr(y, x, s);//移动光标并输出字符串s
refresh();//刷新界面
//颜色
init_pair(1, COLOR_BLACK, COLOR_RED);//初始化颜色序号1 前景色black 背景色red
attron(COLOR_PAIR(1));//开关颜色
attroff(COLOR_PAIR(1));
```

# 代码逻辑

1. 初始化

   ```cpp
   //初始化游戏画面
   void initfield()//初始化框图
   void initgame()；//初始化整个框图 画木板和球
   ```

2. 注册信号alarm处理函数`void draw();`

   ```cpp
   //注册信号和间隔计时器 每隔1000ms重新绘制画面
   signal(14, drawgame);
   struct itimerval itimer;
   itimer.it_interval.tv_sec = 0;
   itimer.it_interval.tv_usec = 100000;
   itimer.it_value.tv_sec = 0;
   itimer.it_value.tv_usec = 1000;
   setitimer(ITIMER_REAL, &itimer, NULL);
       
   //重新绘制画面 消除原来的板和球 重新绘制板和球
   void drawgame();
   ```

3. 不断的接受键盘的输入，并修改板和球的方向数值

