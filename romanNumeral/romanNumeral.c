#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>


void toRoman(int arabic){
	char res [50] = "";
	int tens = 10, digit=1;
	while (arabic/tens!=0){
		digit++; tens*=10;
	}
	for (int i = digit; i > 0; i--){
		arabic=arabic%((int)pow(10, i-1));
		printf("%d\n", arabic);
		printf("%s\n", res);
		if (i==4){	
			int temp = arabic/1000;
			for (int i = 0; i < temp; i++){
				strcat(res, "M");
			}
		}
		else{
			char d1[1], d2[1], d3[1];
			if (i==3){
				d1 [0] = 'C', d2 [0]= 'D', d3 [0] = 'M';
			}
			if (i==2){
				d1 [0]= 'X', d2[0] = 'L', d3[0] = 'C';
			}
			if (i==1){
				d1[0] = 'I', d2[0] = 'V', d3[0] = 'X';
			}
			int temp = arabic/pow(10, i-1);
			if (temp==0) continue;
			if (temp <=3) {
				for (int i = 0; i < temp; i++){ strcat(res, d1);}
				continue;
			}
			if (temp == 4) {
				strcat(res, d1); strcat(res, d2); continue;
			}
			if (temp <=8){
				strcat(res, d2);
				for (int i = 0; i < temp-5; i++) strcat(res, d1);
				continue;
			}
			if (temp==9) {
				strcat(res, d1); strcat(res, d3);
				continue;
			}
		}
	}	
	printf("%s\n", res);
}

int main() {//int argc, char *argv[]
	toRoman(1);
	printf("%lf\n", pow(10,2));
	// char buf[20];
	// 
	// printf("%s", "Enter Roman Numerals or Arabic Numbers!\n"); // Prints to the console
	// if (fgets(buf, 20, stdin)==NULL) fprintf(stderr, "Invalid Input!\n");
	// if (isdigit(*buf)){
	// 	printf("%s\n", "It is a digit!");
	// 	int in = 0;
	// 	for (int i = 0; buf[i]!='\n'&&buf[i]!=' '; i++){
	// 		in = 10*in + buf[i]-'0';
	// 	}
	// 	printf("%d\n", in);
	// }
	// for (int i=0; buf[i]!='\0'; ++i){
	// 	switch (buf[i]){
	// 		case 'X': printf("%s\n", "aaa"); break;
	// 	}
	// }
	

	return 0;
}
