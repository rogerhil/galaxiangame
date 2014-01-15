#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <string>
#include <GL/glut.h>
#include <stdlib.h>
#include <list>

#include "functions.H"
#include "weapons.H"
#include "globalconsts.H"
#include "ship.H"
#include "game.H"


using namespace std;

int ENEMYIDS = 0;

class Enemy{
	int id;
	int base;
	int height;
	int bheight;
	float color [3];
	int posinix;
	int posiniy;
	int posx;
	int posy;
	int diedtime;
	bool is_individual;
	
	
public:

	Enemy();
	virtual ~Enemy();
	bool operator == (Enemy);
	
	Weapon wp;
	
	int getId();
	
	int getBase();
	int getHeight();
	int getBheight();
	float* getColor();
	int getPosinix();
	int getPosiniy();
	int getPosx();
	int getPosy();
	int getPosScreeny();
	int getDiedtime();

	bool isIndividual();

	void setBase(int);
	void setHeight(int);
	void setPosinix(int);
	void setPosiniy(int);
	void setPosx(int);
	void setPosy(int);
	void setIsIndividual();
	void incrementPosx(int);
	void incrementPosy(int);
	void incrementDiedtime(int);
	
	bool isInside(int, int);
	
	void shake(int);
	
	void draw();
	void setColor(float, float, float);
	void setInitialPosition(int, int);
	void setPosition(int, int);
	void setGridedPosition(int, int, int, int);
	int* getGrid(int);
	void clone(Enemy);
	void shut(int, int);
	string getDetailsStr();
};


class Enemies{
	list<Enemy> items;
	list<Enemy> individual_items;
	list<Enemy> died_items;
	int baseposx;
	int baseposy;
	int bla;
	int sx;
	int sy;
	
public:
	Enemies();
	virtual ~Enemies();
	void push(Enemy);
	void individualPush(Enemy);
	void diedPush(Enemy);
	void remove(Enemy);
	void draw(int);
	void drawShoots(SpaceShip&, Game&);
	void clear();
	void addInfo(string&, string, string);
	int getItemsSize();
	string parseColorToString(float*);
	string getStringEnemiesInfo();
	void loadStringEnemiesInfo(string, int);
	bool colides(int, int, bool&);
	void moveEnemies(int);
	Enemy *getEnemyById(int);
	Enemy *getEnemyByIt(int);
	void individualAttack(int);
	void shut(int);
	list<string> getEnemiesDetails();
};

string newReProperty(char*);

#endif // ENEMY_H
