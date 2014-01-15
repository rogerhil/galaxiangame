#include "events.H"

void passiveMouseCB(int x, int y)	{
	if (!game.isRunning() && !game.isDead()) return;
    if (!game.isEditMode()) {
        game.setCurrentMousePosition(x, y);
        glFlush();
    }
}

void idleCB() {
	//if (!game.isRunning()) return;
	if (game.isEndOfGame()) {
		game.setRunning(false);
		endGame();
		return;
	}

	if (game.isLevelCleared()) {
		levelCleared();
		return;
	}

	if (myship.getLifesNum() <= 0) {
		gameOver();
		game.setRunning(false);
		return;
	}

	if (!game.isEditMode()) {
		myship.turn(game.getLastMouseX());
	}
	
}

void dieShip(int i) {
	if (!game.isRunning()) return;
	
	string footer = getGameStrData();
	int load_error = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	l.drawAll(0, game.getIt());
	myship.setHeight(myship.getHeight()-1);
	myship.draw();
	renderBitmapString(10, 10, (char*) footer.c_str(), false);
	glFlush();
	i++;
	if (i < 100) {
		glutTimerFunc(25, dieShip, i);
	} else {
		load_error = l.loadLevel(game.getLevelNumber());
		myship.setHeight(30);
		myship.decreaseLifes();
		game.setDead(false);
		glutTimerFunc(500, displayAll, 1);
	}

}

void shutDisplay(int i) {
	if (!game.isRunning() && !game.isDead()) return;
	bool col;
	if (myship.wp.isShutting()) {
		drawAll(game.getIt());
		myship.wp.draw();
		glFlush();
		col = l.colides(myship.wp.getPosx(), myship.wp.getPosy(), true);
		if (col) {
			myship.wp.endShut();
		}
	}
	
	l.drawEnemiesShoots(myship, game);
	
	glutTimerFunc(10, shutDisplay, i);
}

void displayAll(int i) {
	if (!game.isRunning() && !game.isDead()) return;
	drawAll(i);
	if (game.isDead()) {
		glutTimerFunc(25, dieShip, i);
	} else {
		i++;
		game.setIt(i);
		glutTimerFunc(50, displayAll, i);
	} 
}

void drawAll(int i) {
	string footer = getGameStrData();
	int sh = i % 8;
	glClear(GL_COLOR_BUFFER_BIT);
	l.drawAll(sh, i);
	myship.draw();
	renderBitmapString(10, 10, (char*) footer.c_str(), false);
	glFlush();	
}

void moveAll(int i) {
	if (!game.isRunning()) return;
	bool col;
	l.moveEnemies(game.getLastMouseX());
	col = l.colides(myship.getPosx() + myship.getBase() / 2, myship.getPosy() + (myship.getHeight() / 2), true);
	if (col) {
		game.setDead(true);
	}

	if (l.isClear() && game.isRunning()) {
		game.setLevelCleared(true);
		game.setRunning(false);
		game.incrementLevelNumber();
	}
	glutTimerFunc(50, moveAll, 1);
}

void individualAttack(int i) {
	if (!game.isRunning() && !game.isDead()) return;
	l.individualAttack(i);
	i++;
	glutTimerFunc(2000, individualAttack, i);
}

void enemyShut(int i) {
	if (!game.isRunning() && !game.isDead()) return;
	l.enemyShut(0);
	i++;
	glutTimerFunc(3000, enemyShut, i);
}

void mainScreenDisplay(int i) {
	mainScreen();
}

void mouseCB(int button, int state, int x, int y) {
    
    if (game.isEditMode()) {
    	if (state) {
	    	Enemy en;
		    en.setGridedPosition(x, y, 5, WINHEIGHT);
		    en.setColor(1.0, 1.0, 0.8);
		    en.draw();
		    edit_enemies.push(en);
		    glFlush();
    	}
    } else {
    	
    	if (button == 0) {
    		if (!game.isRunning() && !game.isDead()) return;
	    	if (!state) {
	    		if (!myship.wp.isShutting()) {
		    		myship.wp.shut(myship.getPosx(), myship.getPosy());
	    		}
	    	}
    	
    	} else {
    		if (state == 0) {
				if (game.isRunning()) {
					stopEvents();
				} else {
					startEvents();
				}
    		}
		}
    }
}


void keyCB(unsigned char key, int x, int y)	{
	
	switch (key) {
		case 27:
		   exit(0);
		   break;
		case 'q':
		   exit(0);
		   break;
		case 'E':
			if (game.isEditMode()) {
					game.setEditMode(false);
					game.setRunning(true);
				} else {
					game.setEditMode(true);
					game.setRunning(false);
				}
			break;
		case ')':
			saveGroupEnemies();
			break;	    
		case 'r':
			game.setLevelCleared(false);
			reloadGame();
			break;
		case 's':
			if (!game.isRunning()) {
				game.setLevelCleared(false);
				reloadGame();
				startEvents();
			}
			break;
		case 'p':
			if (game.isRunning()) {
				stopEvents();
			} else {
				startEvents();
			}			
			break;
		case 'm':
			stopEvents();
			glutTimerFunc(1, mainScreenDisplay, 1);
			break;
		case 'd':
			if (game.isRunning()) {
				stopEvents();
				details();
			} else {
				startEvents();
			}			
			
	} 
}


void startEvents() {
	game.setRunning(true);
	glutIdleFunc(idleCB);
	glutPassiveMotionFunc(passiveMouseCB);
	glutTimerFunc(1, displayAll, 1);
	glutTimerFunc(1, moveAll, 1);
	glutTimerFunc(1, shutDisplay, 1);
	glutTimerFunc(5000, individualAttack, 1);
	glutTimerFunc(1000, enemyShut, 1);
		
}

void stopEvents() {
	game.setRunning(false);
	glutIdleFunc(NULL);
	glutPassiveMotionFunc(NULL);
}
