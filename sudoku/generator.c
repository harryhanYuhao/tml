#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SIZE 4

int main() {//int argc, char *argv[]
	srand(time(NULL));
	int list[SIZE*1000]={1};
	int *p = list;
	for (int i=0; i<SIZE*1000; ++i){
		*p = rand();
		printf("%d\n", *p);
		++p;
	}
	FILE *fp = fopen("rand.txt", "w+");
	for (int i=0; i<SIZE*1000; ++i){
		fprintf(fp,"%d\n", list[i]);
	}
	fclose(fp);
	FILE * md = fopen("md.txt", "w+");
	for (int i=0; i<SIZE*1000; ++i){
		fprintf(fp,"%d\n", list[i]%4);
	}
	fclose(md);

	// Some numpy data analysis show the the above method can behave like a uniformly ditr


	return 0;
}

