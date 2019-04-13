/*
 * Snake.h
 *
 *  Created on: Apr 13, 2019
 *      Author: filip
 */

#ifndef SNAKE_H_
#define SNAKE_H_

class Game{
private:
	bool running;
	int bytesWaiting;
protected:
	static int milliseconds;
	static int score;

	int _kbhit();
public:
	Game();
	void start();
	void printPress();
	void printScore();
	void printSpeed();
	void keepRolling();
	bool run();
	void sleepcp();
	void youLost();
	static void incSpeed() {
		if (score <= 13) {
			milliseconds -= 10;
		} else if (score <= 23) {
			milliseconds -= 2;
		} else if (score <= 33) {
			milliseconds -= 1;
		}
	}
};

class Map: public Game{
protected:
	static char A[100][100];
	static int width;
	static int height;

	static void changeMap(int a, int b, char c) {
		A[a][b] = c;
	}
public:
	Map();
	void printMap();
	void printControl();
	static void SetMap(int a, int b) {
		Map::width = a;
		Map::height = b;
	}
};


class Border: public Map{
private:
	void buildBorder();
public:
	Border();
};

class Snake: public Map{
private:
	int length;
	int body[1000][2];
	int v[2];
	int oldv[2];
	bool eating;

	void initSnake();
	void parseDir(char* direction);
	bool checkDirection(char* x);
public:
	Snake(int x);
	void buildSnake();
	void move();
	bool bump();
	void eat();
	int getX();
	int getY();
};

class Food: public Map{
private:
	int x[2];

	void newFood();
	void buildFood();
public:
	Food();
	void makeFood();
	int getX();
	int getY();
};

#endif /* SNAKE_H_ */
