#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <string>

using namespace std;

class Prompt {
public:
	Prompt();
	char* get() const;

private:
	char buffer[PATH_MAX + 1];
	char* path;
};
