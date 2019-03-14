//============================================================================
// Name        : Snake_Object.cpp
// Author      : Filip
// Version     :
// Copyright   : Non
// Description : Snake in object oriented way
//============================================================================


#include "ClassesFile.cpp"

using namespace std;

char Map::A[100][100];
int Map::width;
int Map::height;
int Game::score=0;
int Game::milliseconds=200;

int main() {

	Game game;

	Map map;

	Border border;
	border.SetMap(30,20);
	border.buildBorder();

	Snake snake(3);
	snake.buildSnake();

	Food food;

	map.printMap();
	game.printPress();
	map.printControl();
	game.start();
	while (game.run()){
		if (food.getX()==snake.getX() && food.getY()==snake.getY()){
			snake.eat();
			food.makeFood();
			game.incSpeed();
		}
		snake.move();
		if (snake.bump()){
			break;
		}
		food.buildFood();
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