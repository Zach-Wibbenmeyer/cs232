/* Zach Wibbenmeyer
 * Professor Norman
 * CS232 - Project 3
 */

#include "Prompt.h"

/*
 * Prompt() - constructor for Prompt class
 */
Prompt::Prompt() {
	path = getcwd(buffer, PATH_MAX + 1);
}

/*
 * get() - gets the Prompt
 * @param: None
 * @return: path (type -> char*)
 */
char* Prompt::get() const {
	return path; 
}
