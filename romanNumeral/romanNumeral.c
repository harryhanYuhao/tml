#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>


void toRoman(int arabic){
	if (arabic == 0){
		printf("%s\n", "No Zero for Roman Numerals!");
		return;
	}

	if (arabic>3999) {
		printf("%s\n", "The biggest Roman Numeral is 3999, with representation MMMCMXCIX");
		return;
	}
	char res [50] = "";
	int tens = 10, digit=1;
	while (arabic/tens!=0){
		digit++; tens*=10;
	}
	for (int i = digit; i > 0; i--){
		char d1[2], d2[2], d3[2];
		d1[1]='\0'; d2[1]='\0'; d3[1]='\0';
		if (i==4){
			d1 [0] = 'M';
		}
		if (i==3){
			d1 [0] = 'C'; d2 [0]= 'D'; d3 [0] = 'M';
		}
		if (i==2){
			d1 [0]= 'X'; d2[0] = 'L'; d3[0] = 'C';
		}
		if (i==1){
			d1[0] = 'I'; d2[0] = 'V'; d3[0] = 'X';
		}
		int temp = arabic/pow(10, i-1);
		if (temp==0);
		else if (temp <=3) {
			for (int j = 0; j < temp; j++){
				strcat(res, d1);
			}
		}
		else if (temp == 4) {
			strcat(res, d1); strcat(res, d2); 
		}
		else if (temp <=8){
			strcat(res, d2);
			for (int j = 0; j < temp-5; j++) strcat(res, d1);
		}
		else if (temp==9) {
			strcat(res, d1); strcat(res, d3);
		}
	arabic=arabic%((int)pow(10, i-1));
	}	
	printf("%s\n", res);
}

void toArabic(char * roman, int len){
	return;
}

void test(){
	for (int i = 0; i < 4000; i++){
		printf("%d: ", i);	
		toRoman(i);
	}
}

int main() {//int argc, char *argv[]
	test();
	char buf[20];

	printf("%s", "Enter Roman Numerals or Arabic Numbers!\n"); // Prints to the console
	if (fgets(buf, 20, stdin)==NULL) fprintf(stderr, "Invalid Input!\n");
	if (isdigit(*buf)){
		printf("%s\n", "It is an Arabic Number");
		int a = 0; 
		for (int i=0; buf[i]!='\n'; ++i){
			a=10*a+buf[i]-'0';
		}
		toRoman(a);
	}
	
	return 0;
}
