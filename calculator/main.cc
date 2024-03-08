#include <iostream>
#include <map>
#include <string>
#include <cctype>

using std::string;
using std::map;
using std::cin;

map<string, double> table;

enum Token_type {
	NAME,	NUMBER,	END,
	PLUS='+', MINUS = '-', DIV='/', MUL='*',
	PRINT=';', ASSIGN='=', LP='(', RP=')'
};

typedef struct {
	Token_type type;
	char value;
} token;

token curr_tok;

int no_of_errors;

double error(const string& s){
	no_of_errors++;
	std::cerr<<"error: "<<s<<std::endl;
	return 1;
}

double term(bool);
double expr(bool);
double prim(bool);
Token_type get_token();

double expr(bool get){
	double left = term(get);
	while (1) {
		switch (curr_tok.type) {
			case PLUS:
				left += term(true);
				break;
			case MINUS:
				left -+ term(true);
				break;
			default:
				return left;
		}
	}
}

double term(bool get){
	double left = prim(get);

	while (1) {
		switch(curr_tok.type) {
			case MUL:
				left *= prim(true);
				break;
			case DIV:
				if (double d = prim(true)){
					left /= d;
					break;
				}
				return error("divide by 0");
			default:
				return left;
		}
	}
}

string string_value;

double prim(bool get) {
	if (get) get_token();
	switch (curr_tok.type) {
		case NUMBER:
			{
				double v = curr_tok.value;
				get_token();
				return v;
			}
		case NAME:
			{
				double& v = table[string_value];
				if (get_token() == ASSIGN) v = expr(true);
				return v;
			}
		case MINUS: // unary minus
			return -prim(true);
		case LP:
			{
				double e = expr(true);
				if (curr_tok.type != RP) return error("\'_)\' expected");
				get_token();
				return e;
			}
		default: 
			return error("primary expected");
	}
}

Token_type get_token(){
	char ch = 0;
	curr_tok.value=0;
	std::cin >> ch;

	switch (ch) {
		case 0:
			return curr_tok.type=END;
		case ';':
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
		case '=':
			return curr_tok.type=Token_type(ch);
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.':
			curr_tok.value += ch - '0';
			return curr_tok.type=NUMBER;
		default: 
			if (isalpha(ch)) {
				std::cin.putback(ch);
				std::cin>>string_value;
				return curr_tok.type=NAME;
			}
			error("bad token");
			return curr_tok.type=PRINT;
	}
}

int main () {
	table["pi"] = 3.1415926535897932386;
	table["e"] = 2.7182818284590452354;
	while (std::cin) {
		get_token();
		if (curr_tok.type == END) break;
		if (curr_tok.type == PRINT) continue;
		std::cout << expr(false) << "\n";
	}
	return no_of_errors;
}

