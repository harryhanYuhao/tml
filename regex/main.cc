#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

bool parseRegex(string& regex, string &match) {
	if ((regex.size() < 1) && match.size()<1) {
		return true;	
	} else if ( (regex.size() < 1) || match.size()<1) {
		return false;
	}

	char c = regex[0];

	string subregex;
	string submatch;
	switch (c) {
		case 'a': case 'b': case 'c': case 'd':
		case 'e': case 'f': case 'g': case 'h':
		case 'i': case 'j': case 'k': case 'l':
		case 'm': case 'n': case 'o': case 'p':
		case 'q': case 'r': case 's': case 't':
		case 'u': case 'v': case 'w': case 'x':
		case 'y': case 'z':
			if (match[0] == c) {
				subregex = regex.substr(1);
				submatch = match.substr(1);
				return parseRegex(subregex, submatch);
			} else {
				return false;
			}
			break;
		case '?': 
			subregex = regex.substr(1);
			submatch = match.substr(1);
			return parseRegex(subregex, submatch);
			break;	
		case '*': 
			if (regex.size() == 1) {
				return true;
			}
			subregex = regex.substr(1);
			for (int i = 0; i <= match.size() - 1; i++) {
				submatch = match.substr(i);
				if (parseRegex(subregex, submatch)) {
					return true;
				}
			}
			break;
	}
	return false;
}

int main() { // int argc, char *argv[]
	string match = "aa";
	string regex = "a*";
	if ( parseRegex(regex, match) ) {
		cout<<"matched!"<<endl;
	}
	return 0;
}
