/* Zach Wibbenmeyer
 * Professor Norman
 * CS232 - Project 3
 *
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// CommandLine class
class CommandLine {
public:
	CommandLine(istream& in);
	char* getCommand() const;
	int getArgCount() const;
	char** getArgVector() const;
	char* getArgVector(int i) const;
	bool noAmpersand() const;

private:
	vector<string> argumentV;
	bool ampersand;
};
