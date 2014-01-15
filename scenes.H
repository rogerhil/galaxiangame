#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <string>
#include <GL/glut.h>
#include <stdlib.h>
#include <fstream>
#include "enemies.H"
#include "functions.H"
#include "background.H"
#include "globalconsts.H"
#include "ship.H"
#include "game.H"
#include <list>

class Level{
	list<Enemies> enemies;
	Background bg;
	list<string> paths;
	int total_num_enemies;
	int killed_num_enemies;
	int points;
	int stars_density;
public:
	
	void loadEnemies();
	void loadBackground(int);
	void pushPath(string);
	int loadLevel(int);
	void moveEnemies(int);
	bool colides(int, int, bool);
	void individualAttack(int);
	void enemyShut(int);
	void drawEnemiesShoots(SpaceShip&, Game&);
	bool isClear();
	int getPoints();
	int getKilledNumEnemies();
	int getTotalNumEnemies();
	void drawAll(int, int);
	void reset();
	list<string> getEnemiesDetails();
	
	Level();
	virtual ~Level();
	
	
};


#endif // SCENE_H
