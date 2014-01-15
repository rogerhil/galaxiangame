#include "weapons.H"

Weapon::Weapon(){
	speed = 10;
	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;
	width = 4;
	height = 10;
	posx = 0;
	posy = 0;
	num = 1;
	space = 5;
	shutting = false;
}
Weapon::~Weapon()
{}


int Weapon::getPosx() {
	return posx;
}

int Weapon::getPosy() {
	return posy;
}

void Weapon::setSpeed(int s) {
	speed = s;
}

void Weapon::setPosx(int x) {
	posx = x;
}

void Weapon::setPosy(int y) {
	posy = y;
}

void Weapon::setColor(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Weapon::shut(int x, int y) {
	shutting = true;
	posx = x;
	posy = y;
}

void Weapon::endShut() {
	shutting = false;
	posy = 0;
	posx = 0;
}

bool Weapon::isShutting() {
	return shutting;
}

void Weapon::draw() {
	if (isShutting()) {
			posy += speed;
	}
	if (posy > 500) {
		endShut();
	}
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_POLYGON);			/* draw filled triangle */
    glVertex2i(posx, posy);			/* specify each vertex of triangle */
    glVertex2i(width + posx, posy);
    glVertex2i(width + posx, height + posy);
    glVertex2i(posx, height + posy);
    glEnd();				/* OpenGL draws the filled triangle */	
}
