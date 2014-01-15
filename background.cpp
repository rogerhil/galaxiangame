#include "background.H"

Star::Star() {
	width = 1;
	height = 1;
	posinix = 0;
	posiniy = 0;
	posx = 0;
	posy = 0;
	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;
}

int Star::getPosx() {
	return posx;
}

int Star::getPosy() {
	return posy;
}


void Star::setPosx(int x) {
	posx = x;
}

void Star::setPosy(int y) {
	posy = y;
}

void Star::setWidth(int w) {
	width = w;
}

void Star::setHeight(int h) {
	height = h;
}

void Star::setColor(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Star::draw(float py) {
	if ((posiniy + posy + py) < 500 && (posiniy + posy + py) > 0) {
	    glColor3f(color[0], color[1], color[2]);
	    glBegin(GL_POLYGON);
	      glVertex2i(posinix + posx, posiniy + posy + py);
	      glVertex2i(posinix + posx, posiniy + posy  + py - height);
	      glVertex2i(posinix + posx + width, posiniy + posy  + py - height);
	      glVertex2i(posinix + posx + width, posiniy + posy  + py);
	    glEnd();
	}

}


Star::~Star()
{}


void Background::generateRandomStaticStars(int numstars) {
	int w = 400;
	int h = 500;
	int k, px, py;
	for (k = 0; k < numstars; k++) {
		px = rand() % w;
		py = rand() % h;
		Star s;
		s.setPosx(px);
		s.setPosy(py);
		static_stars.push_back(s);
	}	
}


list<Star> *Background::getStarsLevel(int level) {
	switch(level) {
		case 1:
			return &stars_level1;
			break;
		case 2:
			return &stars_level2;
			break;
		case 3:
			return &stars_level3;
			break;
		case 4:
			return &stars_level4;
			break;
		case 5:
			return &stars_level5;
			break;
		case 6:
			return &stars_level6;
			break;
	}
	return &stars_level1;
}

void Background::generateRandomStars(int n, int h, int level) {
	float r, g, b;
	int w = WINWIDTH;
	int k, px, py;
	list<Star> *stars = getStarsLevel(level);
	n = n * pow(2, level);
	h = h * pow(2, level);
	for (k = 0; k < n; k++) {
		px = rand() % w;
		py = rand() % h;
		Star s;
		s.setPosx(px);
		s.setPosy(py);
		s.setWidth(1);
		s.setHeight(1);
		r = rand() % 50;
		g = rand() % 50;
		b = rand() % 50;
		//r = (float)1/level;
		//g = (float)1/level;
		//b = (float)1/level;
		s.setColor(r, g, b);
		stars->push_back(s);
	}	
}

void Background::draw(float py) {
	list<Star>::iterator i;
	for(i = static_stars.begin(); i != static_stars.end(); ++i) {
		(*i).draw(0);
	}
	for(i = stars_level1.begin(); i != stars_level1.end(); ++i) {
		(*i).draw(py);
	}
	for(i = stars_level2.begin(); i != stars_level2.end(); ++i) {
		(*i).draw(py*2);
	}
	for(i = stars_level3.begin(); i != stars_level3.end(); ++i) {
		(*i).draw(py*4);
	}
	for(i = stars_level4.begin(); i != stars_level4.end(); ++i) {
		(*i).draw(py*8);
	}
	for(i = stars_level5.begin(); i != stars_level5.end(); ++i) {
		(*i).draw(py*16);
	}
	for(i = stars_level6.begin(); i != stars_level6.end(); ++i) {
		(*i).draw(py*32);
	}
}


void Background::clear() {
	static_stars.clear();
	stars_level1.clear();
	stars_level2.clear();
	stars_level3.clear();
	stars_level4.clear();
	stars_level5.clear();
	stars_level6.clear();
}

Background::Background()
{}
Background::~Background()
{}
