#include "ship.H"

SpaceShip::SpaceShip(){
	base = 20;
	height = 30;
	speed = 0.0;
	max_speed = 0.001;
	oldposx = 0.0;
	posx = 0.0;
	posy = 0.0;
	lifes = 3;
	color[0] = 1.0;
	color[1] = 0.5;
	color[2] = 1.0;
	
}
SpaceShip::~SpaceShip()
{}

float SpaceShip::getPosx() {
	return posx;
}

float SpaceShip::getPosy() {
	return posy;
}

int SpaceShip::getBase() {
	return base;
}

int SpaceShip::getHeight() {
	return height;
}

int SpaceShip::getLifesNum() {
	return lifes;
}

void SpaceShip::setOldposx(float x) {
	oldposx = x;
}

void SpaceShip::setPosx(float x) {
	posx = x;
}

void SpaceShip::setPosy(float y) {
	posy = y;
}

void SpaceShip::setHeight(int h) {
	height = h;
}

void SpaceShip::decreaseLifes() {
	lifes--;	
}

void SpaceShip::setColor(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void SpaceShip::turn(int x) {
	if (x > posx) {
		speed = max_speed;
	}
	if (x < posx) {
		speed = max_speed*(-1);
	}

	if (x + 1 > posx && x - 1 < posx) {
		speed = 0;
	}

	posx += speed;
}

void SpaceShip::draw() {
	glColor3f(color[0], color[1], color[2]);
	int b1 = 0;
	int b2 = 0;
	if (speed == 0.0) {
		b1 = 0;
		b2 = 0;
	} else {
		if (speed > 0.0) {
			b1 = 4;
			b2 = 4;
		} else {
			b1 = 4;
			b2 = -4;
		}	
	}
	glBegin(GL_POLYGON);		
	glVertex2i(posx - base/2 + b1, posy);
	glVertex2i(posx + base/2 - b1, posy);
	glVertex2i(posx + base - b2, posy + height/4);
	glVertex2i(posx, posy + height);
	glVertex2i(posx - base - b2, posy + height/4);
	glEnd();					
}

bool SpaceShip::isInside(int x, int y) {
	if ((x + 20 > posx) &&
	    (x - 20 < (posx + base)) &&
	     (y + 20> (posy - height)) &&
	     (y - 20< posy)) {
		
		return true;     	
	} else {
		return false;	
	}
}


bool SpaceShip::colides(int x, int y) {
	return isInside(x,y);
}
