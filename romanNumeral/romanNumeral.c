#include <stdio.h>
#include <math.h> // require compilation with -lm flag. For pow()
#include <string.h> //for strcat()
#include <ctype.h> // for isdigit()
#include <stdlib.h> // for malloc() and free()
// #include <unistd.h>


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
	int fault = 0;
	char nrChar [10]; 
	int nrCounter=0;
	for (int i = 0; i < len; i++){ // make all lower case to upper case. Note a=97, A=65.
		if (roman[i]>90) roman[i]=roman[i]-32;
	}
	for (int i = 0; i < 10; i++){
		nrChar[i]='\0';
	}
	int * buf = (int*)malloc(len*sizeof(int));
	for (int i = 0; i < len; i++){
		int ibuf = 0;
		switch (roman[i]){
			case 'M': ibuf=1000; break;
			case 'D': ibuf=500; break;
			case 'C': ibuf=100; break;
			case 'L': ibuf=50; break;
			case 'X': ibuf=10; break;
			case 'V': ibuf=5; break;
			case 'I': ibuf=1; break;
			default:
				nrChar[nrCounter]=roman[i];
				nrCounter++;
				fault = 4;
		}
		buf[i]=ibuf;
	}

	int sum=0;

	for (int i = 0; i < len-1; i++){
		if (buf[i]<buf[i+1]){
			if (i<len-1){
				if (buf[i]<buf[i+2]) 
				fault=1;
			}
			if (buf[i]*10<buf[i+1]) {
				fault=1;
			}
			buf[i]=-buf[i];
		}
	}


	if (sum>3999) fault = 3;
	if (fault){
		printf("%s\n", "Possible flawed Roman Numeral.");
		switch (fault){
			case 2: break;
			case 3: printf("%s\n", "The greatest Roman Numeral is 3999, numbers greater than which are represented by multiplication by the Romans."); break;
			case 4:
				printf("%s \n", "Non-Recognised Character:");
				for (int i = 0; i <nrCounter ; i++){
					printf("%c ", nrChar[i]);
				}
				printf("\n");
			
		}
	}
	for (int i = 0; i < len; i++)
		sum+=buf[i];
	printf("%s %d\n", "The deduced Arabic representation is:", sum);
	free(buf);
	return;
}

void test(){
	for (int i = 0; i < 4000; i++){
		printf("%d: ", i);	
		toRoman(i);
	}
}

int main() {//int argc, char *argv[]
	// test();
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
		return 0;
	}
	
	int len=0;
	for (; buf[len]!='\n'; len++);
	toArabic(buf, len);

	return 0;
}
