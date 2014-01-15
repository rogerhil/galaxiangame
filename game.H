#ifndef GAME_H
#define GAME_H


class Game{
	bool edit_mode;
	int last_mouse_x;
	int last_mouse_y;
	int level_number;
	int it;
	bool is_running;
	bool is_dead;
	bool level_cleared;
	bool end_of_game;

public:

	bool isEditMode();
	bool isRunning();
	bool isDead();
	bool isLevelCleared();
	bool isEndOfGame();
	
	int getLastMouseX();
	int getLastMousey();
	int getLevelNumber();
	int getIt();
	
	void setEditMode(bool);
	void setCurrentMousePosition(int, int);
	void setRunning(bool);
	void setDead(bool);
	void setLevelNumber(int);
	void setLevelCleared(bool);
	void setEndOfGame(bool);
	void setIt(int);
	void incrementIt();
	void incrementLevelNumber();
	
	Game();
	virtual ~Game();
};

#endif // GAME_H
