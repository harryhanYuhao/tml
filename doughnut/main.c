#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "tEngine.h" 

#define WDT 70
#define HET 30

void init();
int fun();

const float PI = 3.1415926;
const int NUM = 400; 
int * screenBuffer, * colorBuffer;

typedef struct {
	float x, y, z;
} pt;

typedef struct {
	float x11, x12, x13;
	float x21, x22, x23;
	float x31, x32, x33;
} cFMatrix3;

cFMatrix3 * new_cFMatrix3(float x11, float x12, float x13, float x21, float x22, float x23, float x31, float x32, float x33){
	cFMatrix3 *  res = malloc(sizeof(cFMatrix3));
	res->x11=x11;
	res->x12=x12;
	res->x13=x13;
	res->x21=x21;
	res->x22=x22;
	res->x23=x23;
	res->x31=x31;
	res->x32=x32;
	res->x33=x33;
	return res;
}

// float vec_dot(pt * a, pt * b){
// 	return a->x+b->x+a->y+b->y+a->z+b->z;
// }

void v3TimesM3(pt * vec3, cFMatrix3 * m3){
	float a = vec3->x;
	float b = vec3->y;
	float c = vec3->z;

	vec3->x = a*m3->x11+b*m3->x12+c*m3->x13;
	vec3->y = a*m3->x21+b*m3->x22+c*m3->x23;
	vec3->z = a*m3->x31+b*m3->x32+c*m3->x33;
	return;
}

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

void project(pt * point, int * x, int * y){
	*x=((int)((point->x)*(WDT/2))+WDT/2)%WDT;
	*y=((int)((point->y)*(HET/2))+HET/2)%HET;
	return;
}

int main() {//int argc, char *argv[]
	init();
	for (int i = 0; i < NUM/2; i++){
		ptArray[i] = new_pt(0.85*cos(i*4*PI/NUM), 0.85*sin(i*4*PI/NUM), 0);
		// printpt(ptArray[i]);
	}

	for (int i = NUM/2; i < NUM; i++){
		ptArray[i] = new_pt(0.8*cos(i*4*PI/NUM), 0.8*sin(i*4*PI/NUM), 0);
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
	float delta = 0.04;

	cFMatrix3* rotx = new_cFMatrix3(
			1.0f, 0.0f, 0.0f,
			0.0f, cos(delta), -sin(delta), 
			0.0f, sin(delta), cos(delta)
	);

	for (int i = 0; i < NUM; i++){
		v3TimesM3(ptArray[i], rotx);
	}

	// for (int i = 0; i < NUM; i++){
	// 	(ptArray[i]->x)+=0.01;
	// 	(ptArray[i]->y)+=0.01;
	// }

	for (int i = 0; i < NUM; i++){
		int x, y;
		project(ptArray[i], &x,&y); 
		// printf("%d, %d\n", x, y);
		if (ptArray[i]->z>0){
			screenBuffer[x+WDT*y]=(int)'@';
		} else{
			screenBuffer[x+WDT*y]=(int)'.';
		}
	}
	// if (counter > 1) return 0;

	return 1;
}

void init(){
	teSetFPM(15);
	teSetBoarder(1);
	teSetClearScreen(0);

	screenBuffer = (int*)calloc(WDT*HET, sizeof(int));
	colorBuffer = (int*)calloc(WDT*HET, sizeof(int));
	ptArray = (pt **)calloc(NUM, sizeof(pt*)); 

	return;
}
