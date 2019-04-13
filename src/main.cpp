//============================================================================
// Name        : Snake_Object.cpp
// Author      : Filip Bjelonic
// Version     : 1.0
// Copyright   : Non
// Description : Snake in object oriented way
//============================================================================


#include "Snake.h"

using namespace std;

int Game::score=0;
int Game::milliseconds=200;
char Map::A[100][100];
int Map::width;
int Map::height;

int main() {

	Game game;

	Map map;
	map.SetMap(30,10);

	Border border;

	Snake snake(3);

	Food food;

	map.printMap();
	game.printPress();
	map.printControl();
	game.start();
	while (game.run()){
		snake.move();
		if (snake.bump()){
			break;
		}
		if (food.getX()==snake.getX() && food.getY()==snake.getY()){
			snake.eat();
			food.makeFood();
			game.incSpeed();
		}
		snake.buildSnake();
		map.printMap();

		game.printScore();
		game.printSpeed();
		game.keepRolling();

		game.sleepcp();
	}
	map.printMap();
	game.youLost();

}
