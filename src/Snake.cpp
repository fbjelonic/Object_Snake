/*
 * ClassesFile.cpp
 *
 *  Created on: Mar 13, 2019
 *      Author: filip
 */

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stropts.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <time.h>
#include "Snake.h"

using namespace std;

int Game::_kbhit() {
	/* This function is similar to the kbhit() of conio.h library. This
	 * is the equivalent for Linux Systems.
	 * Reference: http://www.flipcode.com/archives/_kbhit_for_Linux.shtml*/
	static const int STDIN = 0;
	static bool initialized = false;

	if (!initialized) {
		// Use termios to turn off line buffering
		termios term;
		tcgetattr(STDIN, &term);
		term.c_lflag &= ~ICANON;
		tcsetattr(STDIN, TCSANOW, &term);
		setbuf(stdin, NULL);
		initialized = true;
	}

	//int bytesWaiting;
	ioctl(STDIN, FIONREAD, &bytesWaiting);
	return bytesWaiting;
}

Game::Game() {
	bytesWaiting = false;
	running = false;
}

void Game::start() {
	while (!running) {
		if (_kbhit()) {
			running = true;
		}
	}
}

void Game::printPress() {
	cout << "Press any key to start!" << endl;
}

void Game::printScore() {
	cout << "Your score: " << score << endl;
}
void Game::printSpeed() {
	cout << "Frame Speed: " << (double) (10000 / milliseconds) / 10 << " Hz"
			<< endl;
}
void Game::keepRolling() {
	cout << "Keep rolling!" << endl;
}

bool Game::run() {
	return running;
}

void Game::sleepcp() {
	/* Platform independent Sleep-Command. Defines the Frame-Rate */
	clock_t time_end;
	time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	while (clock() < time_end) {
	}
}
void Game::youLost() {
	cout << "You lost!" << endl;
	cout << "Better luck next time :)" << endl;
	cout << "Your final score: " << score << endl;
}

Map::Map() {
}

void Map::printMap() {
	string welcome = "Welcome to Snake";
	int k = (width - (int) welcome.length()) / 2;
	string _space = string(k, ' ');
	system("tput reset");
	cout << _space + welcome << endl;
	for (int i = 0; i < Map::height; i++) {
		for (int a = 0; a < Map::width; a++) {
			cout << A[i][a];
		}
		cout << endl;
	}
}
void Map::printControl() {
	string _space = string((int) width / 2 - 5, ' ');
	cout << _space + "     w      " << endl;
	cout << _space + "     |      " << endl;
	cout << _space + "a <-- --> d " << endl;
	cout << _space + "     |      " << endl;
	cout << _space + "     s      " << endl;
}

void Border::buildBorder() {
	for (int i = 0; i < height; i++) {
		for (int a = 0; a < width; a++) {
			if (i == 0 || a == 0 || i == Map::height - 1
					|| a == Map::width - 1) {
				Map::changeMap(i, a, '#');
			} else {
				Map::changeMap(i, a, ' ');
			}
		}
	}
}

Border::Border() {
	buildBorder();
}

void Snake::initSnake() {
	for (int i = 0; i <= length; i++) {
		body[i][0] = Map::width / 2;
		body[i][1] = Map::height / 2;
	}
	v[0] = -1;
	v[1] = 0;
	oldv[0] = -1;
	oldv[1] = 0;
}
void Snake::parseDir(char* direction) {
	switch (*direction) {
	case 'w':
		v[0] = 0;
		v[1] = -1;
		break;
	case 'd':
		v[0] = 1;
		v[1] = 0;
		break;
	case 's':
		v[0] = 0;
		v[1] = 1;
		break;
	case 'a':
		v[0] = -1;
		v[1] = 0;
		break;
	default:
		break;
	}
}
bool Snake::checkDirection(char* x) {
	parseDir(x);
	if (oldv[0] + v[0] == 0 && oldv[1] + v[1] == 0) {
		return true;
	} else {
		return false;
	}
}
Snake::Snake(int x) :
		length(x),eating(false) {
	initSnake();
	buildSnake();
}
void Snake::buildSnake() {
	if (eating) {
		Map::changeMap(body[length-1][1], body[length-1][0], 'O');
		eating=false;
	} else {
		Map::changeMap(body[length][1], body[length][0], ' '); /* To erase old tail of Snake */
	}
	for (int i = 0; i < length; i++) {
		Map::changeMap(body[i][1], body[i][0], 'O');
	}
}
void Snake::move() {
	/* Defines the movement of the Snake by key pressed. */
	char direction;
	if (_kbhit()) {
		cin >> direction;
		if (checkDirection(&direction)) {
			v[0] = oldv[0];
			v[1] = oldv[1];
		}
		oldv[0] = v[0];
		oldv[1] = v[1];
	}
	for (int i = length; i > 0; i--) {
		body[i][0] = body[i - 1][0];
		body[i][1] = body[i - 1][1];
	}
	body[0][0] += v[0];
	body[0][1] += v[1];
}

bool Snake::bump() {
	if (A[body[0][1]][body[0][0]] == 'O' || A[body[0][1]][body[0][0]] == '#') {
		return true;
	}
	return false;
}

void Snake::eat() {
	length++;
	eating=true;
}
int Snake::getX() {
	return body[0][0];
}
int Snake::getY() {
	return body[0][1];
}

void Food::newFood() {
	srand(time(NULL));
	do {
		x[0] = rand() % (width - 4) + 2;
		x[1] = rand() % (height - 4) + 2;
	} while (A[x[1]][x[0]] != ' ');
}
void Food::buildFood() {
	Map::changeMap(x[1], x[0], 'X');
}

Food::Food() {
	newFood();
	buildFood();
}
void Food::makeFood() {
	/* this function is called, if the Food is eaten by the Snake
	 * and a new peace should be generated at a random spot. */
	score++;
	newFood();
	buildFood();
}
int Food::getX() {
	return x[0];
}
int Food::getY() {
	return x[1];
}

