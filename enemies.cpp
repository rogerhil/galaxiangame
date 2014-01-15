#include "enemies.H" 
#include <string>
#include <boost/regex.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>

using namespace std;
using namespace boost;

Enemy::Enemy() {
	ENEMYIDS++;
	id = ENEMYIDS;
	//cout << id << "|";
	base = 20;
	height = 10;
	bheight = 10;
	posinix = 0;
	posiniy = 0;
	posx = 0;
	posy = 0;
	diedtime = 5;
	is_individual = false;
	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;
	wp.setSpeed(-2);
	wp.setColor(1.0, 1.0, 0.3);
}

Enemy::~Enemy()
{}

bool Enemy::operator== (Enemy en) {
	if (id == en.id) {
		return true;
	} else {
		return false;	
	}
}

int Enemy::getId() {
	return id;
}


int Enemy::getBase() {
	return base;
}

int Enemy::getHeight() {
	return height;
}

int Enemy::getBheight() {
	return bheight;
}

float* Enemy::getColor() {
	return color;
}

int Enemy::getPosinix() {
	return posinix;
}

int Enemy::getPosiniy() {
	return posiniy;
}

int Enemy::getPosx() {
	return posx;
}

int Enemy::getPosy() {
	return posy;
}

int Enemy::getPosScreeny() {
	return posy + posiniy;
}


int Enemy::getDiedtime() {
	return diedtime;	
}

bool Enemy::isIndividual() {
	return is_individual;	
}

void Enemy::setBase(int b) {
	base = b;
}

void Enemy::setHeight(int h) {
	height = h;
	bheight = h;
}

void Enemy::setPosinix(int p) {
	posinix = p;
}

void Enemy::setPosiniy(int p) {
	posiniy = p;
}

void Enemy::setPosx(int p) {
	posx = p;
}

void Enemy::setPosy(int p) {
	posy = p;
}

void Enemy::setIsIndividual() {
	is_individual = true;
}

void Enemy::incrementPosx(int p) {
	posx += p;
}

void Enemy::incrementPosy(int p) {
	posy += p;
}

void Enemy::incrementDiedtime(int t) {
	diedtime += t;	
}

void Enemy::setColor(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Enemy::setInitialPosition(int x, int y) {
	posinix = x;
	posiniy = y;
}

void Enemy::setPosition(int x, int y) {
	posx = x;
	posy = y;
}

void Enemy::clone(Enemy en) {

	base = en.getBase();
	height = en.getHeight();
	bheight = en.getBheight();
	posinix = en.getPosinix();
	posiniy = en.getPosiniy();
	posx = en.getPosx();
	posy = en.getPosy();
	//color[0] = en.colo;
	//color[1] = 1.0;
	//color[2] = 1.0;

}

bool Enemy::isInside(int x, int y) {
	if ((x + 20 > posx + posinix) &&
	    (x - 20 < (posx + posinix + base)) &&
	     (y + 20> (posy + posiniy - bheight)) &&
	     (y - 20< posy + posiniy)) {
		
		return true;     	
	} else {
		return false;	
	}
}

void Enemy::setGridedPosition(int x, int y, int g, int winheight) {
	int *grid = getGrid(g);
	posx = (x/grid[0])*grid[0];
	posy = ((winheight - y)/grid[1] + 1)*grid[1];
}

int* Enemy::getGrid(int margin) {
    int *grid = new int[2];
    grid[0] = base + margin;
    grid[1] = height + margin;
    return grid;
}

void Enemy::shake(int v) {
	if (height <= bheight && bheight - height < v) {
	    height--;	
	} else {
		height = bheight;
	}
}

void Enemy::draw() {
	if ((posiniy + posy) <= 500 && (posiniy + posy) > 0) { 
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_POLYGON);			/* draw filled triangle */
		glVertex2i(0 + posinix + posx, posiniy + posy);			/* specify each vertex of triangle */
		glVertex2i(base + posinix + posx, posiniy + posy);
		glVertex2i(base/2 + posinix + posx, posiniy - height + posy);
		glEnd();				/* OpenGL draws the filled triangle */
	}
}

void Enemy::shut(int x, int y) {
	wp.shut(x, y);
}

string Enemy::getDetailsStr() {
	string details = "";
	details += "Id #" + intToString(getId()) + ": ";
	details += intToString(getPosx() + getPosinix()) + ", " + intToString(getPosy() + getPosiniy()) + "; ";
	return details;
}




Enemies::Enemies() {
	baseposx = 0;
	baseposy = 0;
	bla = -1;
	sx = -1;
	sy = 0;
}

Enemies::~Enemies()
{}

void Enemies::push(Enemy en) {
	items.push_back(en);
}

void Enemies::individualPush(Enemy en) {
	en.setIsIndividual();
	individual_items.push_back(en);
}

void Enemies::diedPush(Enemy en) {
	died_items.push_back(en);
}

void Enemies::remove(Enemy en) {
	items.remove(en);
}

void Enemies::draw(int sh) {
	list<Enemy>::iterator i;
	list<Enemy>::iterator j;
	for(i = items.begin(); i != items.end(); ++i) {
		if (sh != 0) { 
			(*i).shake(sh);
		}
		(*i).draw();
	}
	
	for(j = individual_items.begin(); j != individual_items.end(); ++j) {
		if (sh != 0) { 
			(*j).shake(sh);
		}
		(*j).setColor(0.7, 0.3, 0.3);
		
		(*j).draw();
	}
	
	for(j = died_items.begin(); j != died_items.end(); ++j) {
		if (sh != 0) { 
			(*j).shake(sh);
		}
		(*j).draw();
	}
	
}

void Enemies::drawShoots(SpaceShip &myship, Game &game) {
	list<Enemy>::iterator i;
	int col;
	for(i = items.begin(); i != items.end(); ++i) {
		if ((*i).wp.isShutting()) {
			(*i).wp.draw();
			glFlush();
			col = myship.colides((*i).wp.getPosx(), (*i).wp.getPosy());
			if (col) {
				(*i).wp.endShut();
				game.setDead(true);
			}				
		}
	}
	
	for(i = individual_items.begin(); i != individual_items.end(); ++i) {
		if ((*i).wp.isShutting()) {
			(*i).wp.draw();
			glFlush();
			col = myship.colides((*i).wp.getPosx(), (*i).wp.getPosy());
			if (col) {
				(*i).wp.endShut();
				game.setDead(true);
			}				
		}
	}
	
}

void Enemies::addInfo(string& info, string key, string value) {
	info += key + ": " + value + "; ";
}

int Enemies::getItemsSize() {
	return items.size();	
}

string Enemies::parseColorToString(float* color) { 
	 string colorstr;
	 colorstr += floatToString(color[0]) + ", ";
	 colorstr += floatToString(color[1]) + ", ";
	 colorstr += floatToString(color[2]);
	 return colorstr;
}


string Enemies::getStringEnemiesInfo() {
	string info = "";
	list<Enemy>::iterator i;
	for(i = items.begin(); i != items.end(); ++i) {
		addInfo(info, "base", intToString((*i).getBase()));
		addInfo(info, "height", intToString((*i).getHeight()));
		addInfo(info, "posinix", intToString((*i).getPosinix()));
		addInfo(info, "posiniy", intToString((*i).getPosiniy()));
		addInfo(info, "posx", intToString((*i).getPosx()));
		addInfo(info, "posy", intToString((*i).getPosy()));
		addInfo(info, "color", parseColorToString((*i).getColor()));
		info += "\n";
	}
	return info;
}

void Enemies::loadStringEnemiesInfo(string path, int p) {
	
	ifstream file;
	file.open(path.c_str());
	string line = "";
	cmatch what;
	string re = newReProperty((char*)"base");
	re += newReProperty((char*)"height");
	re += newReProperty((char*)"posinix");
	re += newReProperty((char*)"posiniy");
	re += newReProperty((char*)"posx");
	re += newReProperty((char*)"posy");
	re += "\\s*color\\s*:\\s*([\\d\\.]+)\\s*,\\s*([\\d\\.]+)\\s*,\\s*([\\d\\.]+)\\s*;\\s*";
	regex redata(re);
    bool ok;
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, line);
			ok = regex_match(line.c_str(), what, redata);
			if (ok) {
				Enemy en;
				en.setBase(atoi(((string)what[1]).c_str()));
				en.setHeight(atoi(((string)what[2]).c_str()));
				en.setPosinix(atoi(((string)what[3]).c_str()));
				en.setPosiniy(atoi(((string)what[4]).c_str()) + p * WINHEIGHT);
				en.setPosx(atoi(((string)what[5]).c_str()));
				en.setPosy(atoi(((string)what[6]).c_str()));
				en.setColor(atof(((string)what[7]).c_str()), atof(((string)what[8]).c_str()), atof(((string)what[9]).c_str()));
				push(en);
				
			}
		}
		file.close();
	}
}

void Enemies::moveEnemies(int mx) {
	int xattack;
	
	if (baseposx < -10) {
		sx = 1;
	}
	if (baseposx > 10) {
		sx = -1;
	}
	baseposx += sx;

	list<Enemy>::iterator i;
	for(i = items.begin(); i != items.end(); ++i) {
		(*i).incrementPosx(baseposx);
		(*i).incrementPosy(-2);
		if ((*i).getPosScreeny() < 0) {
			items.remove((*i));
			break;
		}
	}
	
	for(i = individual_items.begin(); i != individual_items.end(); ++i) {
		if (((*i).getPosx()) > mx) {
			xattack = -2;
		} else {
			xattack = 2;
		}
		(*i).incrementPosx(xattack);
		(*i).incrementPosy(-7);
		if ((*i).getPosScreeny() < 0) {
			individual_items.remove((*i));
			break;
		}
	}
	
	for(i = died_items.begin(); i != died_items.end(); ++i) {
		(*i).incrementPosx(baseposx);
		(*i).incrementPosy(-2);
		(*i).incrementDiedtime(-1);
		(*i).setColor(1,1,1-((*i).getDiedtime()*(0.2)));
		(*i).setBase((*i).getBase()-(*i).getDiedtime()*(0.5));
		if ((*i).getDiedtime() <= 0) {
			died_items.remove((*i));
			break;
		}
		if ((*i).getPosScreeny() < 0) {
			died_items.remove((*i));
			break;
		}
	}	
	
	
}

bool Enemies::colides(int x, int y, bool &is_individual) {
	bool col = false;
	list<Enemy>::iterator i;
	for(i = items.begin(); i != items.end(); ++i) {
		if ((*i).isInside(x,y)) {
			Enemy newen;
			newen.clone((*i));
			diedPush(newen);
			items.remove((*i));
			col = true;
			break;
		}
	}
	for(i = individual_items.begin(); i != individual_items.end(); ++i) {
		if ((*i).isInside(x,y)) {
			Enemy newen;
			newen.clone((*i));
			diedPush(newen);
			individual_items.remove((*i));
			col = true;
			is_individual = true;
			break;
		}
	}
	
	return col;	
}

Enemy *Enemies::getEnemyById(int id) {
	Enemy *en;
	list<Enemy>::iterator i;
	for(i = items.begin(); i != items.end(); ++i) {
		if ((*i).getId() == id) {
			return &(*i); 
		}
	}
	return en;
}

Enemy *Enemies::getEnemyByIt(int it) {
	Enemy *en;
	list<Enemy>::iterator i;
	int k = 0;
	for(i = items.begin(); i != items.end(); ++i) {
		k++;
		if (k == it) {
			return &(*i); 
		}
	}
	return en;
}


void Enemies::individualAttack(int id) {
	Enemy newen;
	Enemy *olden;
	int size = getItemsSize();
	
	if (id != 0) {
		olden = getEnemyById(id);
	} else {
		if (size) {
			olden = getEnemyByIt(rand() % getItemsSize() + 1);
		}
	}
	if (size) {
		newen.clone(*olden);
		remove(*olden);
		newen.shut(newen.getPosx() + newen.getPosinix(), newen.getPosy() + newen.getPosiniy());
		individualPush(newen);
		
	}
}

void Enemies::shut(int id) {
	Enemy newen;
	Enemy *olden;
	int size = getItemsSize();
	
	if (id != 0) {
		olden = getEnemyById(id);
	} else {
		if (size) {
			olden = getEnemyByIt(rand() % getItemsSize() + 1);
		}
	}
	if (size) {
		olden->shut(olden->getPosx() + olden->getPosinix(), olden->getPosy() + olden->getPosiniy());
	}
}

void Enemies::clear() {
	items.clear();
	individual_items.clear();
	died_items.clear();

}

list<string> Enemies::getEnemiesDetails() {
	list<Enemy>::iterator i;
	list<string> details;
	for(i = items.begin(); i != items.end(); ++i) {
		details.push_back((*i).getDetailsStr());
	}
	return details;
}

string newReProperty(char* value) {
	char* basereg = new char[100];
	char* buff = new char[100];
	strcpy(basereg, "\\s*%s\\s*:\\s*(\\d+)\\s*;\\s*");
	sprintf(buff, basereg, value, value);
	return (string) buff;
}
