#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <iostream>
#include <string>
#include <GL/glut.h>
#include <stdlib.h>
#include <cstdlib>
#include <list>
#include <math.h>

#include "globalconsts.H"

using namespace std;

class Star { 
	int width;
	int height;
	int posx;
	int posy;
	int posinix;
	int posiniy;
	float color[3];
	
	
public:
    
	Star();
	virtual ~Star();
	
	int getPosx();
	int getPosy();
	void setPosx(int);
	void setPosy(int);
	void setWidth(int);
	void setHeight(int);
	void setColor(float, float, float);
	
	void draw(float);
	
};

class Background{
	list<Star> static_stars;
	list<Star> stars_level1;
	list<Star> stars_level2;
	list<Star> stars_level3;
	list<Star> stars_level4;
	list<Star> stars_level5;
	list<Star> stars_level6;
	
public:
	void generateRandomStaticStars(int);
	void generateRandomStars(int, int, int);
	void draw(float);
	void clear();
	list<Star> *getStarsLevel(int);
	
	Background();
	virtual ~Background();
};

#endif // BACKGROUND_H
