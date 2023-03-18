#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>


int main() {//int argc, char *argv[]
	char buf[20];
	
	printf("%s", "Enter Roman Numerals or Arabic Numbers!\n"); // Prints to the console
	if (fgets(buf, 20, stdin)==NULL) fprintf(stderr, "Invalid Input!\n");
	if (isdigit(*buf)){
		printf("%s\n", "It is a digit!");
		int in = 0;
		for (int i = 0; buf[i]!='\n'&&buf[i]!=' '; i++){
			in = 10*in + buf[i]-'0';
		}
		printf("%d\n", in);
	}
	// for (int i=0; buf[i]!='\0'; ++i){
	// 	switch (buf[i]){
	// 		case 'X': printf("%s\n", "aaa"); break;
	// 	}
	// }
	

	return 0;
}
