#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <list>
#include <GL/glut.h>

using namespace std; 

string read_file(char*, bool);
bool write_file(string, string, bool);
string intToString(int);
string floatToString(float);
int getdir (string, list<string>&);
void renderBitmapString(float, float, char*, bool);