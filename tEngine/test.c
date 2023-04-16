#include <stdio.h>
#include "tEngine.h"
#include <stdlib.h>

void init();

int disjoin(){
	// static int counter = 0;
	// if (counter++>0) return 0;
	return 1;
}

void init(){
	teSetFPS(40);
	teSetClearScreen(1);
	return;
}
int main() {//int argc, char *argv[]

	init();
	int width = 4, height = 4;
	
	int * array = (int*)malloc(width*height*sizeof(int));
	int * color = (int*)malloc(width*height*sizeof(int));
	
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			array[j+width*i]=33;
			color[j+width*i]=1;
		}
	}

	// for (int i = 0; i < height; i++){
	// 	for (int j = 0; j < width; j++){
	// 		printf("%d", array[j+width*i]);
	// 	}
	// 	puts("\n");
	// }
	
	teRender(array, color, width, height, &disjoin);
	// while (1){
	// 	toSymbol(40,1);
	// }
	return 0;
}

