#ifndef _TENGIN_H
#define _TENGIN_H	1
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "mTime.h"


static float te_fpm;
static int te_boarder_status;
static char te_boarder_symbol;
static int te_clear_screen_status;
static void te_print_boarder(int);
static const char * toSymbol(int, int);

static float te_fpm = 10;
static int te_boarder_status = 1;
static char te_boarder_symbol = '#';
static int te_clear_screen_status = 0;


void teSetFpm(int);
void teSetBoarder(int);
void teClearScreen(int);
void teRender(int * ptr, int *, int width, int heigth, int fun());

/* The Function that Passed in */
// Input array accept ascii keys
void teRender(int * ptr, int * cptr, int width, int heigth, int fun()){
	long now, pre;
	mTime(&now); mTime(&pre);
	while (fun()){ // main loop
		mTime(&now); 
		while ((now-pre)>=(1000000000.0f/te_fpm)){
			if (te_clear_screen_status) puts("\033c"); // Clear Screen
			printf("FPS: %4.2lf\n", 1000000000.0f/((float)(now-pre))); // FPS

			te_print_boarder(width+2); printf("\n"); // Boarder

			for (int i = 0; i < heigth; i++){
				te_print_boarder(1);
				for (int j = 0; j < width; j++){
					printf("%s", toSymbol(ptr[j+width*i], cptr[j+width*i]));
				}
				te_print_boarder(1);
				printf("\n");
			}

			te_print_boarder(width+2); printf("\n"); // Boarder

			pre=now; // Time tracking
		}
		usleep(1); // Deprecated: needs to be substituded Sleeps for microseconds
	}
	return;
}

//strcat(s1, s2); Concatenate first string with the secound.

static const char * toSymbol(int sym, int color){ // Use Hashtable
	char res [40];
	char * resChar = "!";
	char * color_string = "\x1b[31m";
	char * reset = "\x1b[0m";
	
	// switch (color){
	// 	case 0: color_string = "\x1b[31m"; break;
	// }
	strcat(res, color_string); strcat(res, resChar); strcat(res, reset);
	printf("%s\n", res);
	return res;
}

static void te_print_boarder(int num){
	if (!te_boarder_status) return;
	for (int i = 0; i < num; i++) printf("%c", te_boarder_symbol);
	return;
}

void teSetFPM(int fpm){
	te_fpm = (float)fpm;
	return;
}

void teSetBoarder(int set){
	te_boarder_status = set;
	return;
}

void teClearScreen(int status){
	te_clear_screen_status = status;
	return;
}


#endif
