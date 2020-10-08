#include <iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;
// FOR ARROY KEYS ON KEYBOARD
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];  // coordinates of the tail
int lTail;                   // length of the tail

// enumeration is a user-defined data type that consists of integral constants.
// such as choices on a menu 
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
void Setup() {

	gameOver = false;
	dir = STOP;
	// originally place fruit at centre
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;  // randomly places fruit in width's range
	fruitY = rand() % height;
	score = 0;
}
void Draw() {
	system("cls");
	for (int i = 0; i < width+2; i++) // top walll
		cout << "#";
	cout << endl;
	// printing the map 
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#";
			if (i == y && j == x)          // coordinates of snake's head
				cout << "S";
			else if (i == fruitY && j == fruitX)  // coordinates of fruit
				cout << "F";
			else {
				bool print = false;          // to keep a track as to when to print 
				for (int k = 0; k < lTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";                      // print tail when coordinates of tail are equal
						print = true;                                 // current coordinates
					}
				}
				if (!print) {
					cout << " ";
				}
			}
				 
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
		
	}
	for (int i = 0; i < width+2; i++)  // bottom wall
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input() {
	if (_kbhit()) { // check which key is pressed 
		switch (_getch()) {  // get the key pressed by the user
		case KEY_LEFT:
			dir = LEFT;
			break;
		case KEY_RIGHT:
			dir = RIGHT;
			break;
		case KEY_UP:
			dir = UP;
			break;
		case KEY_DOWN:
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}

}
void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	// to attach tail to the head as the coordinates of the head are x and y 
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < lTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

	}
	switch (dir)
	{
		// to move the snake using commands 
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
	//if (x > width || x < 0 || y>height || y<0)   // when it goes outside the boundaries
		//gameOver = true;
	if (x >= width) x = 0; else if (x < 0) x = width - 1;     // exit from one side and enter from another
	if (y >= height) y = 0; else if (y < 0) y = height - 1;
	// if the snake hits itself
	for (int i = 0; i < lTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}
	// eating the fruit
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;  // randomly places fruit again in width's range
		fruitY = rand() % height;
		lTail++;
	}
}


int main()
{
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(30);
	}
}


