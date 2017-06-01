/* Zach Wibbenmeyer
 * Professor Norman
 * CS232 - Project 3
 */

#include "ZShell.h"
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <exception>

/*
 * ZShell class constructor
 */
ZShell::ZShell() {

}

/*
 * run() - runs the Shell
 * @param: None
 */
void ZShell::run() {
	Path myPath;
	Environment environment;

	// forever while loop that runs the Shell
	while(true) {
		Prompt myPrompt;
		cout << myPrompt.get() << "$ " << flush;
		if (cin.peek() == '\n') { cin.ignore(INT_MAX, '\n'); }
		CommandLine myCL(cin);

		// handle exit
		if (!strcmp(myCL.getCommand(), "exit")) { break; }

		// handle pwd
		if (!strcmp(myCL.getCommand(), "pwd")) { myPrompt.get(); }

		// handle cd
		if (!strcmp(myCL.getCommand(), "cd")) {
			int rc = chdir(myCL.getArgVector(1));
			if (rc < 0) {
				cerr << "Cannot find directory: " << myCL.getArgVector(1) << endl;
			}
			continue;
		}

		char* path = new char[255];

		// handle errors
		try {
			strcpy(path, myPath.getDirectory(myPath.find(myCL.getCommand())));
		} catch (exception& e) {
			cerr << "Cannot find command: " << myCL.getCommand() << endl;
			continue;
		}
		strcat(path, "/");
		strcat(path, myCL.getCommand());

		int status;
		// fork the process
		pid_t pid = fork();

		// fork failure
		if (pid == -1) {
			cerr << endl << "The forked Failed" << endl;
		}

		if (pid == 0) {
			execve(path, myCL.getArgVector(), environment.getEnvironment());
		} else {
			if (myCL.noAmpersand()) {
				waitpid(pid, &status, WUNTRACED | WCONTINUED);
			}
		}
	}
}
