// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>

using namespace std;

bool gameover;
const int width = 20;
const int height = 20;
int snakeX, snakeY, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGTH, UP, DOWN };
eDirection dir;

void Setup()
{
    gameover = false;
	dir = STOP;
	snakeX = width / 2 - 1;
	snakeY = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls"); //clear
	for (int i = 0; i < width + 1; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			{
				cout << "#";
			}
			if (i == snakeY && j == snakeX)
			{
				cout << "0";
			}
			else if (i == fruitY && j == fruitX)
			{
				cout << "F";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						cout << "o";
					}
				}
				if (!print)
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++)
	{	
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGTH;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameover = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = snakeX;
	tailY[0] = snakeY;
	for (int i = 0; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		snakeX--;
		break;
	case RIGTH:
		snakeX++;
		break;
	case UP:
		snakeY--;
		break;
	case DOWN:
		snakeY++;
		break;
	}

	/*if (snakeX > width || snakeX < 0 || snakeY > height || snakeY < 0)
	{
		gameover = true;
	}*/
	if (snakeX >= width - 1)
	{
		snakeX = 0;
	}
	else if (snakeX < 0)
	{
		snakeX = width - 2;
	}

	if (snakeY >= height - 1)
	{
		snakeY = 0;
	}
	else if (snakeY < 0)
	{
		snakeY = height - 2;
	}

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == snakeX && tailY[i] == snakeY)
		{
			gameover = true;
		}
	}

	if (snakeX == fruitX && snakeY == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int main()
{
    Setup();
	while (!gameover)
	{
		Draw();
		Input();
		Logic();
	}
	return 0;
}
