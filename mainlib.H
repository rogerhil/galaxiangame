#ifndef MAINLIB_H
#define MAINLIB_H


#include "ship.H"
#include "enemies.H"
#include "background.H"
#include "scenes.H"
#include "globalconsts.H"
#include "game.H"

#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <string>
#include <GL/glut.h>

using namespace std;



Game game;
Enemies edit_enemies;
SpaceShip myship;
Level l;



void mainScreen();
void endGame();
void propvalue(string, string, int, int);
void details();
void levelCleared();
void gameOver();
string getGameStrData();
void reloadGame();
void saveGroupEnemies();

#endif // MAINLIB_H