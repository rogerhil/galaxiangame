#include "mainlib.H"

void mainScreen() {
	glClear(GL_COLOR_BUFFER_BIT);
	string galaxian = "G A L A X I A N";
	string tp1 = "TP1 de Computacao Grafica";
	string start = "Pressione s para comecar ou q para sair";
	string por = "por Rogerio Hilbert Lima";
	glColor3f(0.5, 0.1, 0.8);
	renderBitmapString(40, 200, (char*) galaxian.c_str(), true);
	glColor3f(0.5, 0.1, 0.3);
	renderBitmapString(80, 170, (char*) tp1.c_str(), true);
	glColor3f(0.3, 0.9, 0.8);
	renderBitmapString(80, 130, (char*) start.c_str(), false);
	glColor3f(0.7, 0.1, 0.2);
	renderBitmapString(250, 20, (char*) por.c_str(), false);
	glFlush();	
}

void endGame() {
	string quit = "Pressione q para sair";
	string congrat = "CONGRATULATIONS!";
	string allclear = "ALL CLEARED!";

	glColor3f(0.5, 0.1, 0.8);
	renderBitmapString(70, 200, (char*) congrat.c_str(), true);
	glColor3f(0.5, 0.1, 0.8);
	renderBitmapString(110, 170, (char*) allclear.c_str(), true);
	glColor3f(0.3, 0.9, 0.8);
	renderBitmapString(135, 150, (char*) quit.c_str(), false);	
	glFlush();
}

void propvalue(string prop, string value, int x, int y) {
	glColor3f(0.9, 0.9, 0.4);
	renderBitmapString(x, y, (char*) prop.c_str(), false);
	glColor3f(0.9, 0.9, 0.4);
	renderBitmapString(x + 120, y, (char*) value.c_str(), false);
}

void details() {
	int x = 20;
	int y = 480;
	int space = 15;
	list<string> details = l.getEnemiesDetails();
	list<string>::iterator i;
	glClear(GL_COLOR_BUFFER_BIT);
	propvalue("Fase: ", intToString(game.getLevelNumber()), x, y);
	propvalue("Vidas: ", intToString(myship.getLifesNum()), x, y - space);
	propvalue("Pontos: ", intToString(l.getPoints()), x, y - space*2);
	propvalue("Inimigos mortos: ", intToString(l.getKilledNumEnemies()), x, y - space*3);
	propvalue("Total inimigos: ", intToString(l.getTotalNumEnemies()), x, y - space*4);
	propvalue("Ship position: ", intToString(myship.getPosx()) + ", " + intToString(myship.getPosy()), x, y - space*5);
	propvalue("Enemies positions: ", "", x, y - space*6);
	int s = 7;
	int r = 7;
	string en1, en2;
	
	for(i = details.begin(); i != details.end(); ++i) {
		if (s % 3 == 0) {
			propvalue(en1, en2, x, y - space*r);
			propvalue("", "                            " + (*i), x, y - space*r);
			r++;
		} else {
			if (s % 3 == 1) {
				en1 = (*i);
			} else {
				en2 = (*i);
			}
		}
		s++;
	}
	
	glFlush();

}

void levelCleared() {
	string clearedstr = "C L E A R !";
	string next = "Pressione s para prosseguir";
	glColor3f(0.5, 0.1, 0.8);
	renderBitmapString(120, 200, (char*) clearedstr.c_str(), true);
	glColor3f(0.3, 0.9, 0.8);
	renderBitmapString(100, 180, (char*) next.c_str(), false);
	glFlush();
}

void gameOver() {
	string gameover = "GAME OVER";
	string quit = "Pressione q para sair";
	glColor3f(0.5, 0.1, 0.8);
	renderBitmapString(120, 200, (char*) gameover.c_str(), true);
	glColor3f(0.3, 0.9, 0.8);
	renderBitmapString(130, 180, (char*) quit.c_str(), false);
	glFlush();
}

string getGameStrData() {
	return "Fase: " + intToString(game.getLevelNumber()) + "    " +
			"Vidas: " + intToString(myship.getLifesNum()) + "    " +   
	       "Pontos: " + intToString(l.getPoints()) +
	       "             " + intToString(l.getKilledNumEnemies()) +
	       " inimigos mortos de " + intToString(l.getTotalNumEnemies());
	       
}

void reloadGame() {
	bool load_error = 0;
	glClear(GL_COLOR_BUFFER_BIT);
 	game.setLevelCleared(false);
	load_error = l.loadLevel(game.getLevelNumber());
	if (load_error != 0) {
		game.setEndOfGame(true);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

void saveGroupEnemies() {
	string info;
	string editpath;
	bool wrote;
 	info = edit_enemies.getStringEnemiesInfo();
 	editpath = "newgroup.ene";
 	wrote = write_file(editpath, info, false);	
}
