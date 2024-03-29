// ConsoleApplication3.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
void Background();
void press();   //判断按下按键的函数
void change(int a, int b); //交换两个方块的函数
void startandjudge(); //初始化和判断胜利的函数
int Square[9];		// 生成九宫格的数组
int i = 0, j, k;   //i用于初始界面；j用于记录空格；k用于计算步数
int vacant;		// 初始化空缺位置

void Background()	// 该函数用于生成背景
{
	setbkcolor(LIGHTGRAY);    // 设置背景色（这里设置成了灰色）
	cleardevice();		// 用背景色填充屏幕
	setfillstyle(2, 6);	// 设置1-8号矩形块的样式

	if (Square[0] != 0)     //九个if语句分别指示了画出矩形的位置
		bar(160, 60, 240, 140);
	if (Square[1] != 0)
		bar(260, 60, 340, 140);
	if (Square[2] != 0)
		bar(360, 60, 440, 140);
	if (Square[3] != 0)
		bar(160, 160, 240, 240);
	if (Square[4] != 0)
		bar(260, 160, 340, 240);
	if (Square[5] != 0)
		bar(360, 160, 440, 240);
	if (Square[6] != 0)
		bar(160, 260, 240, 340);
	if (Square[7] != 0)
		bar(260, 260, 340, 340);
	if (Square[8] != 0)
		bar(360, 260, 440, 340);


	if (Square[0] != 0)
		outtextxy(200, 90, '0' + Square[0]);

	if (Square[1] != 0)
		outtextxy(300, 90, '0' + Square[1]);

	if (Square[2] != 0)
		outtextxy(400, 90, '0' + Square[2]);

	if (Square[3] != 0)
		outtextxy(200, 190, '0' + Square[3]);

	if (Square[4] != 0)
		outtextxy(300, 190, '0' + Square[4]);

	if (Square[5] != 0)
		outtextxy(400, 190, '0' + Square[5]);

	if (Square[6] != 0)
		outtextxy(200, 290, '0' + Square[6]);

	if (Square[7] != 0)
		outtextxy(300, 290, '0' + Square[7]);

	if (Square[8] != 0)
		outtextxy(400, 290, '0' + Square[8]);

	if (i == 0)
	{
		printf("\n\n\n\n\n\t\t按任意键退出游戏");
		_getch();
	}
	char s[200];              //这里假设移动步数不会超过200位的整数
	_itoa_s(k, s, 10);  //交换字符串，把k的值给s在下面输出
	outtextxy(450, 40, "你已经移动了");
	outtextxy(550, 40, s);
	outtextxy(580, 40, "次");
	i += 1;
	return;
}





void press()		// 判断所按下键的函数
{
	void startandjudge();

	char key = 0;
	key = _getch();

	switch (key)
	{
	case 80:		// 上
		if (vacant >= 3)  //只有空缺处位于大于等于第三个的位置时向上按键才起作用，以下同理
		{
			change(vacant, vacant - 3);
			k++;
		}
		break;
	case 72:		// 下
		if (vacant <= 5)
		{
			change(vacant, vacant + 3);
			k++;
		}
		break;
	case 77:		// 左
		if (vacant % 3 != 0)
		{
			change(vacant, vacant - 1);
			k++;
		}
		break;
	case 75:		// 右
		if (vacant % 3 != 2)
		{
			change(vacant, vacant + 1);
			k++;
		}
		break;
	case 32:		// 空格键重新开始
		i = 0;
		startandjudge();

	case 27:
		cleardevice();

		printf("\n\n\n\t\t\t———————————————————\n");
		printf("\n\t\t\t\t下次再见\n");
		printf("\n\t\t\t—————————————————————\n");
		_getch();
		closegraph();
		exit(1);
	}

	return;
}

void change(int a, int b)		// 交换两个矩形方块的函数
{
	int t;
	t = Square[a];
	Square[a] = Square[b];
	Square[b] = t;

	return;
}




void startandjudge()		// 初始化界面和判断胜利与否
{
	int a, b, c;


	k = 0;
	i = 0;
	for (a = 0; a<8; a++)
		Square[a] = a + 1;
	Square[8] = 0;

	Background();
	for (c = 0; c<100; c++)		 // 随机打乱顺序
	{
		a = rand() % 9;
		b = (a + 2) % 8;		 // 关于有无解问题算法不清楚，参考了网络内容

		change(a, b);
	}
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
	while (1)
	{
		Background();

		for (a = 0; a<8; a++)
			if (Square[a] != a + 1)
				break;
		if (a == 8)
		{
			outtextxy(250, 180, "成功,移动步数见右上角");
			outtextxy(250, 200, "此时播放的音乐为《拉德斯基进行曲》");
			outtextxy(250, 220, "按任意键重新开始");
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
			_getch();
			startandjudge();
		}
		for (j = 0; j <= 8; j++)
			if (Square[j] == 0)
				break;
		vacant = j;

		press();
	}
}

int main()
{

	int gdriver = VGA, gmode = VGAHI;
	initgraph(640, 480);
	srand((unsigned)time(NULL));
	cleardevice();                 //参考自网络
	outtextxy(180, 180, "—————————————————");
	outtextxy(250, 200, "欢迎来到九宫格游戏");
	outtextxy(180, 220, "—————————————————");
	outtextxy(200, 280, "请按任意键（除Esc外）开始游戏");
	outtextxy(200, 300, "按Esc键退出游戏");
	outtextxy(200, 320, "用方向键控制空格的移动");
	outtextxy(200, 340, "直至1-8的顺序正确，且空缺落在右下角为获胜");
	outtextxy(200, 360, "游戏过程中按空格键重新开始游戏");
	outtextxy(200, 380, "屏幕右上角会显示你所用的步数");
	outtextxy(20, 460, "注：游戏过程中的背景音乐为《蓝色多瑙河》");//生成界面的基础内容
	if (_getch() == 27)
	{

		cleardevice();
		closegraph();
		printf("\n\n\n\t\t\t—————————————————————\n");
		printf("\n\t\t\t\t\t下次再见！\n");
		printf("\n\t\t\t————————————————————————\n");
		printf("\n\n\n\n\n\t\t\t\t请按任意键退出 ");
		_getch();
		return 0;
	}

	startandjudge();
	return 0;
}
