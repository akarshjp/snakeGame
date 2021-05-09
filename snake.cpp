#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;
bool gameOver;
const int width = 50;
const int height = 20;
int x, y;
int fruitx, fruity, score;
int tailx[100], taily[100];
int ntail;
enum cDirection {STOP=0, UP, DOWN, LEFT, RIGHT};
cDirection dir;
void setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;					//Placing head of the snake( x and y co-ordinate)
	y = height / 2;
	fruitx = rand() % width;		//Placing the fruit at a random place( x and y co-ordinate)
	fruity = rand() % height;
	score = 0;						//Maintaining a score
}
void draw()
{
	system("cls");
	cout << "***********Welcome to Akarsh's Snake Game***********\n**********************Enjoy**********************\n";
	for (int i = 0; i < width+2; i++)	//Upper boundary
	{
		cout << "_";
	}
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)	//Side boundary
		{
			if (j == 0)
				cout << "|";
			if (i == y && j == x)		//Symbol of head
				cout << "O";
			else if (i == fruity && j == fruitx)
				cout << "*";			//Symbol of fruit
			else
			{
				bool print = false;
				for (int k = 0; k < ntail; k++)
				{
					if (tailx[k] == j && taily[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
			if (j == width-1)
				cout << "|";
		}
		cout << endl;
	}
	for (int i = 0; i < width+2; i++)	//Lower boundary
	{
		cout << "_";
	}
	cout << endl;
	cout << "Score:" << score << endl;
}
void input()
{
	if (_kbhit())						//Records input from keyboard
	{
		switch (_getch())
		{
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void logic()
{
	int prevx = tailx[0];
	int prevy = taily[0];
	int prev2x, prev2y;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i <ntail; i++)
	{
		prev2x = tailx[i];
		prev2y = taily[i];
		tailx[i] = prevx;
		taily[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	/*if (x > width || x < 0 || y>height || y<0)
	{
		gameOver = true;
	}
	*/
	if (x >= width)
		x = 0;
	if (x < 0)
		x = width - 1;
	if (y >= height)
		y = 0;
	if (y < 0)
		y = height - 1;
	for (int i = 0; i < ntail; i++)
	{
		if (tailx[i] == x && taily[i] == y)
			gameOver = true;
	}
	if (x == fruitx && y == fruity)
	{
		score = score + 10;
		fruitx = rand() % width;		//Placing the fruit at a random place after being eatern
		fruity = rand() % height;
		ntail++;
	}
}
int main()
{
	
	setup();
	while (!gameOver)
	{
		draw();
		input();
		logic();
		Sleep(10);
	}

}
