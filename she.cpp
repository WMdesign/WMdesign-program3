#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#define WIN_WIDTH  640
#define WIN_HEIGHT 480
#define MAX_SNAKE 500
struct Pos
{
	int x;
	int y;
	DWORD color;
};
struct Snake
{
	int num;
	int dir;
	int score;
	int size;
	int speed;
	struct Pos coor[MAX_SNAKE];
}snake;
struct Food
{
	int x;
	int y;
	DWORD color;
	bool flag;
}food;
enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

void GameInit()
{
	srand(GetTickCount());
	snake.num = 3;
	snake.dir = RIGHT;
	snake.score = 0;
	snake.size = 10;
	snake.speed = 10;
	snake.coor[0].x = 20;
	snake.coor[0].y = 0;
	snake.coor[0].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	snake.coor[1].x = 10;
	snake.coor[1].y = 0;
	snake.coor[1].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	snake.coor[2].x = 0;
	snake.coor[2].y = 0;
	snake.coor[2].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.x = rand() % (WIN_WIDTH / 10) * 10;
	food.y = rand() % (WIN_HEIGHT / 10) * 10;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.flag = true;

}
void GameDraw()
{
	cleardevice();
	setfillcolor(snake.coor[0].color);
	for (int i = 0; i < snake.num; i++)
	{
		setfillcolor(snake.coor[i].color);
		fillrectangle(snake.coor[i].x, snake.coor[i].y, snake.coor[i].x + 10, snake.coor[i].y + 10);
	}
	if (food.flag)
	{
		setfillcolor(food.color);
		solidellipse(food.x, food.y,food.x+10,food.y+10);
	}
	char temp[20] = "";
	sprintf(temp,"·ÖÊý:%d",snake.score);
	outtextxy(10,10,temp); 
}
void GameMove()
{
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.coor[i].x=snake.coor[i - 1].x;
		snake.coor[i].y=snake.coor[i - 1].y;
	}
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y -= snake.speed;
		break;
	case DOWN:
		snake.coor[0].y += snake.speed;
		break;
	case LEFT:
		snake.coor[0].x -= snake.speed;
		break;
	case RIGHT:
		snake.coor[0].x += snake.speed;
		break;
	}
	
}
void GameController()
{
	char key = _getch();
	switch (key)
	{
	case 72:
		if (snake.dir != DOWN)
		{
			snake.dir = UP;
		}
		break;
	case 80:
		if (snake.dir != UP)
		{
			snake.dir = DOWN;
		}
		break;
	case 75:
		if (snake.dir != RIGHT)
		{
			snake.dir = LEFT;
		}
		break;
	case 77:
		if (snake.dir != LEFT)
		{
			snake.dir = RIGHT;
		}
		break;
	}
	printf("%d\n", key);
}
void createFood()
{
	if (!food.flag)
	{
		food.x = rand() % (WIN_WIDTH / 10) * 10;
		food.y = rand() % (WIN_HEIGHT / 10) * 10;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.flag = true;
	}
}
void EatFood()
{
	if (food.flag && snake.coor[0].x == food.x && snake.coor[0].y == food.y)
	{
		food.flag = false;
		snake.num++;
		snake.score += 10;
		snake.coor[snake.num - 1].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		createFood();
	}
}


int main()
{
	initgraph(640, 480,1);
	setbkcolor(RGB(207, 214, 229));
	cleardevice();
	GameInit();
	while (1)
	{
		GameDraw();
		GameMove();
		BeginBatchDraw();
		if (_kbhit())
		{
			GameController();
		}
		FlushBatchDraw();
		EatFood();
		Sleep(100);
	}
	return 0;
}