#include "functions.H"

int getdir (string dir, list<string> &files) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}



string read_file(char *path, bool binary=false) {
	ifstream file(path);
	string line = "";
	string text = "";
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, line);
			text += line;
		}
		file.close();
	}
	return text;
}

bool write_file(string path, string cont, bool binary=false) {
	ofstream file;
	if (binary) {
		file.open(path.c_str(), ios::in | ios::binary);
	} else {
		file.open(path.c_str());
	}
    if (file.is_open()) {
        file << cont;
        file.close();
        return true;
    } else {
        return false;
    }
}


string intToString(int value) {
	string str;
	char* buff = new char[100];
	sprintf(buff, "%d", value);
	str = buff;
	delete[] buff;
	return str;
}


string floatToString(float value) {
	string str;
	char* buff = new char[100];
	sprintf(buff, "%.4g",value);
	str = buff;
	delete[] buff;
	return str;
}


void renderBitmapString(float x, float y, char *str, bool wide) {  
	char *c;
	glRasterPos2f(x, y);
	glColor3f(1.0, 1.0, 1.0);
	for (c=str; *c != '\0'; c++) {
		if (wide) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , *c); 
		} else {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12 , *c);
		}
	}
}

