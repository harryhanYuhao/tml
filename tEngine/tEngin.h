#ifndef _TENGIN_H
#define _TENGIN_H	1
#include <stdio.h>
#include <unistd.h>
#include "mTime.h"

static int State_teRender = 1;

void teRender(int * ptr, int width, int heigth, int fun());

void teRenderState(int);

static char * toSymbol(int);



/* The Function that Passed in */
void teRender(int * ptr, int width, int heigth, int fun()){
	long now, pre;
	mTime(&now); mTime(&pre);
	while (fun()){
		mTime(&now);
		while ((now-pre)>=100000000){
			// puts("\033c");
			for (int i = 0; i < heigth; i++){
				for (int j = 0; j < width; j++){
					printf("%s", toSymbol(ptr[j+width*i]));
				}
				printf("\n");
			}
			printf("%ld\n", 1000000000L/(now-pre));
			pre=now;
		}
		usleep(1); // Deprecated: needs to be substituded Sleeps for microseconds
	}
	return;
}

void teRenderState(int state){
	State_teRender=state;
	return;
}

static char * toSymbol(int input){
	switch (input){
		case 0: return " ";
		case 1: return "*";
	}
	return "?";
}

#endif
