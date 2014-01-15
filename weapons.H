#ifndef WEAPONS_H
#define WEAPONS_H

#include <iostream>
#include <string>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>


class Weapon {
	int speed;
	float color [3];
	int width;
	int height;
	int posx;
	int posy;
	int num;
	int space;
	bool shutting;
	
public:
	Weapon();
	virtual ~Weapon();
	int getPosx();
	int getPosy();
	void setPosx(int);
	void setPosy(int);
	void setSpeed(int);
	void setColor(float, float, float);
	void shut(int, int);
	void endShut();
	bool isShutting();
	void draw();
};

#endif // WEAPONS_H