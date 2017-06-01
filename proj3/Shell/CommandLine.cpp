/* Zach Wibbenmeyer
 * Professor Norman
 * CS232 - Project 3
 */

#include "CommandLine.h"
#include <algorithm>
#include <cstring>

/*
 * CommandLine() - reads input from the user and repeats the task
 * @param: in (type -> istream&)
 * @return: the CommandLine
 */
CommandLine::CommandLine(istream& in) {
	ampersand = true;
	string temp;

	// check to see if cin is empty
	if (in.peek() != '\n') {
		while (in >> temp) {
			// if there is an ampersand
			if (temp == "&" ) {
				ampersand = false;
			} else {
				argumentV.push_back(temp);
			}
			temp = "";
			// check to see if cin is empty
			if (in.peek() == '\n') { break; }
		}
	}
	argumentV.push_back("");
}

/*
 * getCommand() - returns the command
 * @param: None
 * @return: output (type -> char*)
 */
char* CommandLine::getCommand() const {
	char* output = new char[argumentV[0].length()];
	strcpy(output, argumentV[0].c_str());
	return output;
}

/*
 * getArgCount() - returns argc
 * @param: None
 * @return: argumentV.size() - 2
 */
int CommandLine::getArgCount() const {
	return argumentV.size() - 2;
}

/*
 * getArgVector() - returns argumentV
 * @param: None
 * @return: output (type -> char**)
 */
char** CommandLine::getArgVector() const {
	char** output = new char*[argumentV.size()];

	// fill the each char* in output with argumentV[i]
	for (int i = 0; i < argumentV.size(); i++) {
		output[i] = new char[argumentV[i].length()];
		strcpy(output[i], argumentV[i].c_str());
	}
	output[argumentV.size() - 1] = NULL;
	return output;
}

/*
 * getArgVector() - returns a char* containing argumentV[i]
 * @param: i (type -> int)
 * Return: output (type -> char*)
 */
char* CommandLine::getArgVector(int i) const {
	char* output = new char[argumentV[i].length()];
	strcpy(output, argumentV[i].c_str());
	return output;
}

/*
 * noAmpersand() - returns no ampersand
 * @param: None
 * @return: noAmpersand (type -> bool)
 */
bool CommandLine::noAmpersand() const {
	return ampersand;
}
