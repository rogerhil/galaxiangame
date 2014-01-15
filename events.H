#ifndef EVENTS_H
#define EVENTS_H

#include "mainlib.H"

void passiveMouseCB(int, int);
void idleCB();
void dieShip(int);
void displayAll(int);
void drawAll(int);
void moveAll(int);
void shutDisplay(int);
void individualAttack(int);
void enemyShut(int);
void mouseCB(int, int, int, int);
void keyCB(unsigned char, int, int);
void startEvents();
void stopEvents();


#endif // EVENTS_H
