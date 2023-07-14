#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "mTime.h"


static float te_fps;
static int te_boarder_status;
static char te_boarder_symbol;
static int te_clear_screen_status;
static void te_print_boarder(int);
static const char * toSymbol(int, int);

static float te_fps = 10;
static int te_boarder_status = 1;
static char te_boarder_symbol = '#';
static int te_clear_screen_status = 1;
static const char * te_color_escpae [10] = 
	{
		"\0",
		"\x1b[31m",
		"\x1b[32m", 
		"\x1b[33m", 
		"\x1b[34m", 
		"\x1b[35m", 
		"\x1b[36m",
		"\0","\0",
		"\x1b[100m",
};


void teSetFPS(int);
void teSetBoarder(int);
void teSetClearScreen(int);
void teRender(int *, int *, int, int, int (void));

/* The Function that Passed in */
// The first input to array ascii keys
// The second input is array to consigning color to each inputs.
// The arrays are two dimensional array in the form of one dimension 
// The origin is at top left, positive x direction is right, y is down. 
// The (a, b) coordinate will be rendered as the character
// of ptr[a+b*width], the color of cptr[a+b*width]
// width and height needs to be supplied
// fun listed termination condition
void teRender(int * ptr, int * cptr, int width, int heigth, int fun(void)){
	long now, pre;
	mTime(&now);
  mTime(&pre);
	now += 1000000000;
	while (1){ // main loop
		mTime(&now); 
		while ((now-pre)>=(1000000.0f/te_fps)){ 
			if (!fun()) goto exit;
			printf("\n");
			// \033c clear Screen
			// \033[H move cursor to home position
			if (te_clear_screen_status) printf("\x1b[c"); // Clear Screen
			printf("FPS: %4.2lf\n", 1000000.0f/((float)(now-pre))); // FPS

			te_print_boarder(width+2); printf("\n"); // Boarder

			for (int i = 0; i < heigth; i++){
				te_print_boarder(1);
				for (int j = 0; j < width; j++){
					const char * bur = toSymbol(ptr[j+width*i], cptr[j+width*i]);
					printf("%s", bur);
					free((void *)bur);
				}
				te_print_boarder(1);
				printf("\n");
			}

			te_print_boarder(width+2); printf("\n"); // Boarder

			pre=now; // Time tracking
		}
    msleep(1);
	}
exit:
	return;
}

static const char * toSymbol(int sym, int color){ 
	char *res = (char*) calloc(50, sizeof(char));
	char resChar [2] = {(char)sym, '\0'};
	const char * color_string = te_color_escpae[color];
	char * reset = "\x1b[0m";
	
	sprintf(res,"%s%s%s", color_string, resChar, reset);
	//strcat(res, color_string); strcat(res, resChar); strcat(res, reset);
	return res;
}

static void te_print_boarder(int num){
	if (!te_boarder_status) return;
	for (int i = 0; i < num; i++) printf("%c", te_boarder_symbol);
	return;
}

void teSetFPS(int fps){
	te_fps = (float)fps;
	return;
}

void teSetBoarder(int set){
	te_boarder_status = set;
	return;
}

void teSetClearScreen(int status){
	te_clear_screen_status = status;
	return;
}
