
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <iostream>
#include <string>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#include "weapons.H"

class SpaceShip {
	float speed;
	float max_speed;
	int base;
	int height;
	float oldposx;
	float posx;
	float posy;
	float color [3];
	int lifes;
	
public:
	Weapon wp;
	SpaceShip();
	virtual ~SpaceShip();
	float getPosx();
	float getPosy();
	int getBase();
	int getHeight();
	int getLifesNum();
	void setPosx(float);
	void setPosy(float);
	void setHeight(int);
	void setOldposx(float);
	void setColor(float, float, float);
	void decreaseLifes();
	void turn(int);
	void draw();
	bool isInside(int, int);
	bool colides(int, int);
	
};

#endif // SPACESHIP_H
