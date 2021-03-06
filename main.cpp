#include<iostream>
#include<string>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
//上面这个是为了能够使用sprintf（代码显示分数中）
#include<stdio.h>
#include<math.h>//平方 pow()
#include<graphics.h>//图形库插件
#include<conio.h>//_kbhit()，_getch()
#include<time.h>//srand（）和rand（）
#include<stdlib.h>//sleep（）
#include<mmsystem.h>//mci
#pragma comment(lib,"winmm.lib")//告诉编译器加载winmm.lib库文件

const int windowsLenth = 600;
const int windowsWidth = 400;
const int vx = -8;//column speed
const int gravity = 3;
const int radius = 10;
class Column
{
public:
	Column();
	//~Column();

	const int widthOfColumn = 20;//the width of column
	int heightOfBottomColumn;//the height of the column on the bottom
	int gapOfTwoColumn;//the lenth between topColumn and bottomColumn 
	int xCol, yCol;//the position of top left corner of the column

};
Column::Column( )
{
	
	this->heightOfBottomColumn = rand() % 100 + 50;//随机50-149
	this->gapOfTwoColumn = rand() % 50 + 100;//
	this->xCol = windowsLenth - widthOfColumn;
	this->yCol = windowsWidth-this->heightOfBottomColumn;
}
void moveColumn(Column column[],int Num)//move position of Column over time
{
	for (int i = 0;i < Num;i++)
	{
		column[i].xCol += vx;
	}
}
void drawColumn(Column column[],int Num)
{
	for (int i = 0;i < Num;i++)
	{
		fillrectangle(column[i].xCol, column[i].yCol, column[i].xCol + column[i].widthOfColumn, windowsWidth);//draw bottom rec
		fillrectangle(column[i].xCol, 0, column[i].xCol + column[i].widthOfColumn, column[i].yCol - column[i].gapOfTwoColumn);//draw top rec
	}
}
void changeColumn(Column column[],int Num)
{ 
	srand((unsigned int)time(NULL)); 
	for (int i = 0;i < Num;i++)
	{
		if (column[i].xCol <= -20)
		{
			column[i].xCol = windowsLenth - column[i].widthOfColumn;
			column[i].heightOfBottomColumn = rand() % 100 + 50;//随机50-149
			column[i].gapOfTwoColumn = rand() % 50 + 100;//
			column[i].yCol = windowsWidth - column[i].heightOfBottomColumn;
		}
	}
}


class Bird
{
public:
	Bird();
	//~Bird();
	const int xBird = 40;//x coordinates of bird
	int yBird;//y corrdinates of bird
	int vY;//the vertical velocity of the bird;
	const int vAfterJump = -15;//speed when press space

	void jump();//when player press the space,turn vY to vAfterJump
	void moveBird();//move position of Bird according to speed(vY) over time
	void drawBird();

};
Bird::Bird()
{
	this->vY = vAfterJump;
	this->yBird = windowsWidth / 2;
}
void Bird::jump()
{
	this->vY = vAfterJump;
}
void Bird::moveBird()
{
	this->vY = vY + gravity;
	this->yBird = yBird + vY;
}
void Bird::drawBird()
{
	fillcircle(this->xBird, this->yBird, radius);
}
//碰撞检测有问题
//bool isDie(Bird bird, Column column[], int Num)
//{
//	bool flag = false;
//	for (int i = 0;i < Num;i++)
//	{
//		if((bird.yBird + radius > column[i].yCol) && (bird.xBird + radius > column[i].xCol))//下柱子左边撞
//		{
//			flag = true;
//		}
//		else if (bird.xBird > column[i].xCol && bird.yBird + radius > column[i].yCol)//下柱子上边撞
//		{
//			flag = true;
//		}
//		else if ((bird.yBird + radius < column[i].yCol - column[i].gapOfTwoColumn) && (bird.xBird + radius > column[i].xCol))//上左
//		{
//			flag = true;
//		}
//		else if (bird.xBird > column[i].xCol && bird.yBird - radius < column[i].yCol -column[i].gapOfTwoColumn)//上柱子下边撞
//		{
//			flag = true;
//		}
//		else{}
//	}
//	if (bird.yBird == windowsWidth)
//	{
//		flag = true;
//	}
//     return flag;
//}

//碰撞检测
/*
bool isDie(Bird bird, Column column[], int Num)
{
	bool flag = false;
	for (int i = 0; i < Num; i++)
	{
		if(bird.xBird > column[i].xCol + column[i].widthOfColumn)
		{
			continue;
		}
		int rFang1 = (column[i].xCol - bird.xBird) * (column[i].xCol - bird.xBird) + (column[i].yCol - bird.yBird) * (column[i].yCol - bird.yBird);
		int rFang2 = (column[i].xCol - bird.xBird) * (column[i].xCol - bird.xBird) + 
			(column[i].yCol-column[i].gapOfTwoColumn - bird.yBird) * (column[i].yCol - column[i].gapOfTwoColumn - bird.yBird);
		if(rFang1 < 100 || rFang2 < 100)//尖角撞上
		{
			flag = true;
		}
		else if (((bird.yBird > column[i].yCol - radius) || (bird.yBird < column[i].yCol - column[i].gapOfTwoColumn + radius)) && (bird.xBird + radius > column[i].xCol))//左边撞上
		{
			flag = true;
		}
		else if ((column[i].xCol <= bird.xBird && bird.xBird <= column[i].xCol + column[i].widthOfColumn) && ((bird.yBird <= column[i].yCol - column[i].gapOfTwoColumn + radius) || (bird.yBird >= column[i].yCol - radius)))
		{ 
			flag = true;
		}
		else{}
	}
	return flag;
}
*/

//碰撞检测

class MyRectangle
{
public:
	MyRectangle(int x = 0, int y = 0, int wid = 0, int len = 20)
	{
		this->x = x;
		this->y = y;
		this->width = wid;
		this->lenth = len;
	}
	int x, y, width, lenth;
};

//void setrec()
//make sure closest point position (x,y)
//calculate dbetweenbirdandcolumn
//compare d and radius
bool isDie(Bird bird, Column column[], int num)
{
	MyRectangle DRec, TRec;
	int closestPointX = 0;
	int closestPointY = 0;
    bool flag = false;
   for(int i = 0; i < num; i++)
   {
    TRec.x = column[i].xCol;
	TRec.y = 0;
	TRec.width = column[i].yCol - column[i].gapOfTwoColumn;
	TRec.lenth = column[i].widthOfColumn;
    
 
	if (bird.xBird < TRec.x)
	{
		closestPointX = TRec.x;
	}
	else if (bird.xBird < TRec.x + TRec.lenth)
	{
		closestPointX = bird.xBird;
	}
	else
	{
		closestPointX = TRec.x + TRec.lenth;
	}
	if (bird.yBird < TRec.width)
	{
		closestPointY = bird.yBird;
	}
	else
	{
		closestPointY = TRec.width;
	}
	//square of d,radius
	double dFang = pow(closestPointX - bird.xBird, 2) + pow(bird.yBird - closestPointY, 2);
	double rFang = pow(radius, 2);
	if(dFang <= rFang)
	{
		flag = true;
	}
   }
   for (int i = 0; i < num; i++)
   {
	   DRec.x = column[i].xCol;
       DRec.y = column[i].yCol;
       DRec.width = windowsWidth - column[i].yCol;
       DRec.lenth = column[i].widthOfColumn;


	   if (bird.xBird < DRec.x)
	   {
		   closestPointX = DRec.x;
	   }
	   else if (bird.xBird < DRec.x + DRec.lenth)
	   {
		   closestPointX = bird.xBird;
	   }
	   else
	   {
		   closestPointX = DRec.x + DRec.lenth;
	   }
	   if (bird.yBird < DRec.y)
	   {
		   closestPointY = DRec.y;
	   }
	   else
	   {
		   closestPointX = bird.yBird;
	   }
	   //square of d,radius
	   double dFang = pow(bird.xBird - closestPointX, 2) + pow(bird.yBird - closestPointY, 2);
	   double rFang = pow(radius, 2);
	   if (dFang <= rFang)
	   {
		   flag = true;
	   }
   }
   if (bird.yBird > windowsWidth || bird.yBird < 0)
   {
	   flag = true;
   }
   return flag;
 }
 
 

//窗口句柄
HWND hwnd = NULL;

int main()//请从 项目 属性中把字符集改成多字节字符集，以运行程序。
{
	Bird bird;
	const int Num = 4;
	Column column1, column2, column3, column4;
	column2.xCol -= windowsLenth / 4;
	column3.xCol -= windowsLenth / 2;
	column4.xCol -= 3 * windowsLenth / 4;
	Column cArr[4] = { column1,column2,column3,column4 };

	hwnd = initgraph(windowsLenth,windowsWidth);
	mciSendString(_T("play happyFly.mp3 repeat"), 0, 0, 0);
	BeginBatchDraw();//双缓冲，消除闪烁
	while (1)
	{
		bird.moveBird();
		moveColumn(cArr,Num);
		changeColumn(cArr, Num);


		bird.drawBird();
		drawColumn(cArr,Num);

		FlushBatchDraw();//双缓冲，取消闪烁
		if (isDie(bird,cArr,Num))
		{
			MessageBox(hwnd, "game over", "", 0);
			break;
		}
		if (_kbhit())
		{
			char key = _getch();
			if (key == 32)
				bird.jump();
		}
		//show grade
		Sleep(100);
		cleardevice();

	}
	_getch();
	EndBatchDraw();
	closegraph();
	return 0;
}