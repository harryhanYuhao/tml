#include <stdio.h>
#include "tEngin.h"
#include <stdlib.h>

int disjoin(){
	static int counter = 0;
	// if (counter++>0) return 0;
	return 1;
}

int main() {//int argc, char *argv[]
	int width = 4, height = 4;
	
	int * array = (int*)malloc(width*height*sizeof(int));
	
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			array[j+width*i]=i;
		}
	}

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			printf("%d", array[j+width*i]);
		}
		puts("\n");
	}
	
	teRender(array, width, height, &disjoin);
	return 0;
}