/* Zach Wibbenmeyer
 * Professor Norman
 * CS232 - Project 3
 */

// include the necessary libraries
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdexcept>

using namespace std;

// Path class
class Path {

public:
	Path();
	int find(const string& program);
	char* getDirectory(int i) const;
	vector<char*> filePath;
	char* path;
};
