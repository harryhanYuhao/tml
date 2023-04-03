#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "tEngine.h" 

#define WDT 80
#define HET 30

void init();
int fun();

const float PI = 3.1415926;
const int NUM = 200; 
int * screenBuffer, * colorBuffer;

typedef struct {
	float x, y, z;
} pt;

pt ** ptArray;

pt* new_pt(float x, float y, float z){ // needs to be freed
	pt* res = malloc(sizeof(pt));
	res->x = x;
	res->y = y;
	res->z = z;
	return res;
}

void printpt(pt * ptin){
	printf("x: %f; y: %f; z: %f\n", ptin->x, ptin->y, ptin->z);
	return;
}

void map(pt * point, int * x, int * y){
	*x=((int)((point->x)*(WDT/2))+WDT/2)%WDT;
	*y=((int)((point->y)*(HET/2))+HET/2)%HET;
	return;
}

int main() {//int argc, char *argv[]
	init();
	for (int i = 0; i < NUM; i++){
		ptArray[i] = new_pt(0.85*cos(i*2*PI/NUM), 0.85*sin(i*2*PI/NUM), 0);
		// printpt(ptArray[i]);
	}
	teRender(screenBuffer, colorBuffer, WDT, HET, fun);
	return 0;
}

int fun() {
	static int counter = 0;
	counter++;

	for (int i = 0; i < WDT*HET; i++){
		screenBuffer[i]=32;
	}

	for (int i = 0; i < NUM; i++){
		(ptArray[i]->x)+=0.01;
		(ptArray[i]->y)+=0.01;
	}

	for (int i = 0; i < NUM; i++){
		int x, y;
		map(ptArray[i], &x,&y);
		// printf("%d, %d\n", x, y);
		screenBuffer[x+WDT*y]=50;
	}
	// if (counter > 1) return 0;

	return 1;
}

void init(){
	teSetFPM(5);
	teSetBoarder(1);
	teSetClearScreen(0);

	screenBuffer = (int*)calloc(WDT*HET, sizeof(int));
	colorBuffer = (int*)calloc(WDT*HET, sizeof(int));
	ptArray = (pt **)calloc(NUM, sizeof(pt*)); 

	return;
}
