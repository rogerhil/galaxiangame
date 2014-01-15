#include "game.H"

Game::Game() {
	edit_mode = false;
	last_mouse_x = 0;
	last_mouse_y = 0;
	level_number = 1;
	it = 0;
	is_running = false;
	is_dead = false;
	level_cleared = false;
	end_of_game = false;
}
Game::~Game()
{}


bool Game::isEditMode() {
	return edit_mode;
}

bool Game::isRunning() {
	return is_running;
}

bool Game::isDead() {
	return is_dead;
}

bool Game::isLevelCleared() {
	return level_cleared;
}

bool Game::isEndOfGame() {
	return end_of_game;
}


int Game::getLastMouseX() {
	return last_mouse_x;
}

int Game::getLastMousey() {
	return last_mouse_y;
}

int Game::getLevelNumber() {
	return level_number;
}

int Game::getIt() {
	return it;
}


void Game::setEditMode(bool e) {
	edit_mode = e;
}

void Game::setCurrentMousePosition(int x, int y) {
	last_mouse_x = x;
	last_mouse_y = y;
}

void Game::setRunning(bool r) {
	is_running = r;
}

void Game::setDead(bool d) {
	is_dead = d;
}

void Game::setLevelCleared(bool l) {
	level_cleared = l;
}

void Game::setLevelNumber(int n) {
	level_number = n;
}

void Game::incrementLevelNumber() {
	level_number++;
}

void Game::setEndOfGame(bool e) {
	end_of_game = e;
}

void Game::setIt(int i) {
	it = i;
}

void Game::incrementIt() {
	it++;
}

