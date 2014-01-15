#include "scenes.H"

Level::Level() {
	total_num_enemies = 0;
	killed_num_enemies = 0;
	stars_density = 30;
}
Level::~Level()
{}

void Level::loadEnemies() {
	list<string>::iterator i;
	int p = 0;
	for(i = paths.begin(); i != paths.end(); ++i) {
		Enemies ens;
		ens.loadStringEnemiesInfo((*i), p);
		enemies.push_back(ens);
		total_num_enemies += ens.getItemsSize();
		p++;
	}
}

void Level::loadBackground(int numstars) {
	//bg.generateRandomStaticStars(numstars);
	bg.generateRandomStars(numstars, WINHEIGHT, 1);
	bg.generateRandomStars(numstars, WINHEIGHT, 2);
	bg.generateRandomStars(numstars, WINHEIGHT, 3);
	bg.generateRandomStars(numstars, WINHEIGHT, 4);
	bg.generateRandomStars(numstars, WINHEIGHT, 5);
	bg.generateRandomStars(numstars, WINHEIGHT, 6);
}

void Level::pushPath(string path) {
	paths.push_back(path);
}

int Level::loadLevel(int s) {
	list<string> files  = list<string>();
	list<string>::iterator i;
	string basepath = "levels/level" + intToString(s) + "/";
	int got = getdir(basepath, files);
	size_t found;
	
	if (got == 0) {
		reset();
	    for(i = files.begin(); i != files.end(); ++i) {
	        found = (*i).rfind("ene");
	        if (found!=string::npos) {
	        	pushPath(basepath + (*i));
	        }
	    }
	    loadEnemies();
	    loadBackground(stars_density);
	}
	return got;
}

bool Level::isClear() {
	int k = 0;
	list<Enemies>::iterator i;
	for(i = enemies.begin(); i != enemies.end(); ++i) {
		k += (*i).getItemsSize();
	}
	return k == 0;
}

int Level::getPoints() {
	return points;
}

int Level::getTotalNumEnemies() {
	return total_num_enemies;	
}

int Level::getKilledNumEnemies() {
	return killed_num_enemies;	
}

void Level::moveEnemies(int mx) {
	list<Enemies>::iterator i;
	for(i = enemies.begin(); i != enemies.end(); ++i) {
		(*i).moveEnemies(mx);
	}	
}

bool Level::colides(int x, int y, bool is_shot=false) {
	bool col;
	bool is_individual = false;
	list<Enemies>::iterator i;
	for(i = enemies.begin(); i != enemies.end(); ++i) {
		col = (*i).colides(x, y, is_individual);
		if (col) {
			if (is_shot) {
				if (is_individual) {
					points += 100;
				} else {
					points += 20;
				}
				killed_num_enemies++;
			}
			break;
		}
	}
	return col;
}

void Level::individualAttack(int id) {
	list<Enemies>::iterator i;
	for(i = enemies.begin(); i != enemies.end(); ++i) {
		if ((*i).getItemsSize() == 0) {
			continue;	
		}
		(*i).individualAttack(0);
		break;
	}	
}

void Level::enemyShut(int id) {
	list<Enemies>::iterator i;
	for(i = enemies.begin(); i != enemies.end(); ++i) {
		if ((*i).getItemsSize() == 0) {
			continue;	
		}
		(*i).shut(id);
		break;
	}	
}

void Level::drawAll(int sh, int v) {
	list<Enemies>::iterator i;
	for(i = enemies.begin(); i != enemies.end(); ++i) {
		(*i).draw(sh);
	}
	bg.draw((float)-v/2);
}

void Level::drawEnemiesShoots(SpaceShip &myship, Game &game) {
	list<Enemies>::iterator i;
	for(i = enemies.begin(); i != enemies.end(); ++i) {
		(*i).drawShoots(myship, game);
	}
}

void Level::reset() {
	list<Enemies>::iterator i;
	for(i = enemies.begin(); i != enemies.end(); ++i) {
		(*i).clear();
	}
	bg.clear();
	paths.clear();
	total_num_enemies = 0;
	killed_num_enemies = 0;

}

list<string> Level::getEnemiesDetails() {
	list<Enemies>::iterator i;
	list<string>::iterator j;
	list<string> details;
	list<string> d;
	for(i = enemies.begin(); i != enemies.end(); ++i) {
		d = (*i).getEnemiesDetails();
		for(j = d.begin(); j != d.end(); ++j) {	
			details.push_back((*j));
		}
	}
	return details;
}