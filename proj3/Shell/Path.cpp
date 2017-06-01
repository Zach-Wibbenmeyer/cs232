/* Zach Wibbenmeyer
 * Professor Norman
 * CS232 - Project 3
 */

// include the necessary libraries
#include "Path.h"

/*
 * Path() - constructor for Path
 * Retrieves variables and puts them in a vector
 */
Path::Path() {
	// get Path environment variable
	path = getenv("PATH");
	char* pch;
	pch = strtok(path, ":");
	while (pch != NULL) {
		//push each directory into the vector
		filePath.push_back(pch);
		pch = strtok(NULL, ":");
	}
}

/* find() - finds which directory the program in program is in
 * @param: program (type -> const string&)
 * @return: the index for correct directory in the vector myPath
 */
int Path::find(const string& program) {
	int programIndex;
	DIR *dir;
	struct dirent *ent;
	for (unsigned i = 0; i < filePath.size(); i++) {
		if ((dir = opendir(filePath[i])) != NULL) {
			while ((ent = readdir(dir)) != NULL) {
				if (ent->d_name == program) {
					programIndex = i;
				}
			}
			closedir(dir);
		}
	}
	return programIndex;
}

/* getDirectory() gets the directory specified by i
 * @param: i (type -> int)
 * @return: the name of the directory of which i is an index of
 */
char* Path::getDirectory(int i) const {
	if (i > filePath.size()) {
		throw range_error("index is out of range");
	}
	char* filePathCopy = filePath[i];
	return filePathCopy;
}
