#ifndef _TENGIN_H
#define _TENGIN_H	1
#include <stdio.h>
#include <unistd.h>
#include "mTime.h"

void teRender(int * ptr, int width, int heigth, int fun());

static char * toSymbol(int);

static float te_fpm = 10;

void teSetFpm(int);


/* The Function that Passed in */
void teRender(int * ptr, int width, int heigth, int fun()){
	long now, pre;
	mTime(&now); mTime(&pre);
	while (fun()){
		mTime(&now);
		while ((now-pre)>=(1000000000.0f/te_fpm)){
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

static char * toSymbol(int input){
	switch (input){
		case 0: return " ";
		case 1: return "*";
	}
	return "?";
}

void teSetFPM(int fpm){
	te_fpm = (float)fpm;
	return;
}

#endif
