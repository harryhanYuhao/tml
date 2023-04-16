#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "tEngine.h" 

#define WDT 68
#define HET 29

void init();
int fun();

const float PI = 3.1415926;
const int NUM = 230; 
const int ITER = 17;
int * screenBuffer, * colorBuffer;
float * depthArray;

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

pt* copy_pt(pt * in){ // needs to be freed
	pt* res = malloc(sizeof(pt));
	res->x =in-> x;
	res->y =in-> y;
	res->z =in-> z;
	return res;
}

void printpt(pt * ptin){
	printf("x: %f; y: %f; z: %f\n", ptin->x, ptin->y, ptin->z);
	return;
}

void project(pt * point, int * x, int * y){
	pt * copy = copy_pt(point);
	float temp = tan(PI/4);
	copy->z=-copy->z;
	copy->z +=1.45;

	cFMatrix3* proj = new_cFMatrix3(
			1.0f/(temp*copy->z), 0.0f, 0.0f,
			0.0f,1.0f/(temp*copy->z), 0.0f,
			0.0f, 0.0f, 1.0f
	);

	v3TimesM3(copy, proj);

	*x=((int)((copy->x)*(WDT/2))+WDT/2)%WDT;
	*y=((int)((copy->y)*(HET/2))+HET/2)%HET;
	// printf("x: %d, y: %d\n", *x, *y);
	return;
}

int main() {//int argc, char *argv[]
	init();
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
			0.0f, cos(1.09*delta), -sin(1.09*delta), 
			0.0f, sin(1.09*delta), cos(1.09*delta)
	);

	cFMatrix3* roty = new_cFMatrix3(
			cos(1.17*delta),0.0f, sin(1.17*delta), 
			0.0f, 1.0f, 0.0f,
			-sin(1.17*delta),0.0f, cos(1.17*delta)
	);

	cFMatrix3* rotz = new_cFMatrix3(
			 cos(1.38*delta), -sin(1.38*delta), 0.0f,
			 sin(1.38*delta), cos(1.38*delta),   0.0f,
			0.0f, 0.0f, 1.0f
	);

	for (int i = 0; i < ITER*NUM; i++){
		if (ptArray[i]==NULL) continue;
		v3TimesM3(ptArray[i], rotx);
		v3TimesM3(ptArray[i], roty);
		v3TimesM3(ptArray[i], rotz);
	}

	// for (int i = 0; i < NUM; i++){
	// 	(ptArray[i]->x)+=0.01;
	// 	(ptArray[i]->y)+=0.01;
	// }
	
	for (int i = 0; i < WDT*HET; i++){
		depthArray[i]=-10.0f;
	}

	for (int i = 0; i < ITER*NUM; i++){
		// printpt(ptArray[i]);
		if (ptArray[i]==NULL) continue;
		int x, y;
		project(ptArray[i], &x,&y); 
		// printf("%d, %d, %f\n", x, y, ptArray[i]->z);
		if ((depthArray[x+WDT*y])<=(ptArray[i]->z)){
			depthArray[x+WDT*y] = ptArray[i]->z;
			if (ptArray[i]->z>0.7)	screenBuffer[x+WDT*y]=(int)'@';
				else if (ptArray[i]->z>0.5) screenBuffer[x+WDT*y]=(int)'#';
				else if (ptArray[i]->z>0.3) screenBuffer[x+WDT*y]=(int)'$';
				else if (ptArray[i]->z>0.1) screenBuffer[x+WDT*y]=(int)'!';
				else if (ptArray[i]->z>-0.3) screenBuffer[x+WDT*y]=(int)'~';
				else if (ptArray[i]->z>-0.5) screenBuffer[x+WDT*y]=(int)':';
				else screenBuffer[x+WDT*y]=(int)'.';
		}
	}
	// if (counter > 1) return 0;

	return 1;
}

void init(){
	teSetFPS(24);
	teSetBoarder(0);
	teSetClearScreen(0);

	screenBuffer = (int*)calloc(WDT*HET, sizeof(int));
	colorBuffer = (int*)calloc(WDT*HET, sizeof(int));
	ptArray = (pt **)calloc(ITER*NUM, sizeof(pt*)); 
	depthArray = (float*)calloc(WDT*HET, sizeof(float));

	float del = 0.02;
	int bd = 6;
	for (int i = 0; i < NUM; i++){
		for(int j=0;j<bd; ++j){
			ptArray[NUM*j+i]   = new_pt((0.9-del*j)*cos(i*2*PI/NUM), (0.9-del*j)*sin(i*2*PI/NUM), 0);
		}
		ptArray[bd*NUM+i] = new_pt((0.9-del) *cos(i*2*PI/NUM), (0.9-del) *sin(i*2*PI/NUM), -0.03);
		ptArray[(bd+1)*NUM+i] = new_pt((0.9-del) *cos(i*2*PI/NUM), (0.9-del) *sin(i*2*PI/NUM), 0.03);

		ptArray[(bd+2)*NUM+i] = new_pt((0.9-2*del) *cos(i*2*PI/NUM), (0.9-2*del) *sin(i*2*PI/NUM), -0.03);
		ptArray[(bd+3)*NUM+i] = new_pt((0.9-2*del) *cos(i*2*PI/NUM), (0.9-2*del) *sin(i*2*PI/NUM), 0.03);
		ptArray[(bd+4)*NUM+i] = new_pt((0.9-2*del) *cos(i*2*PI/NUM), (0.9-2*del) *sin(i*2*PI/NUM), -0.06);
		ptArray[(bd+5)*NUM+i] = new_pt((0.9-2*del) *cos(i*2*PI/NUM), (0.9-2*del) *sin(i*2*PI/NUM), 0.06);

		ptArray[(bd+6)*NUM+i] = new_pt((0.9-3*del) *cos(i*2*PI/NUM), (0.9-3*del) *sin(i*2*PI/NUM), -0.03);
		ptArray[(bd+7)*NUM+i] = new_pt((0.9-3*del) *cos(i*2*PI/NUM), (0.9-3*del) *sin(i*2*PI/NUM), 0.03);
		ptArray[(bd+8)*NUM+i] = new_pt((0.9-3*del) *cos(i*2*PI/NUM), (0.9-3*del) *sin(i*2*PI/NUM), -0.06);
		ptArray[(bd+9)*NUM+i] = new_pt((0.9-3*del) *cos(i*2*PI/NUM), (0.9-3*del) *sin(i*2*PI/NUM), 0.06);

		ptArray[(bd+10)*NUM+i] = new_pt((0.9-4*del) *cos(i*2*PI/NUM), (0.9-4*del) *sin(i*2*PI/NUM), -0.03);
		ptArray[(bd+11)*NUM+i] = new_pt((0.9-4*del) *cos(i*2*PI/NUM), (0.9-4*del) *sin(i*2*PI/NUM), 0.03);
	}

	return;
}
