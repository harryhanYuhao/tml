// Refactor tml code:
// 1. Make it more readable and maintainable
// 2. resolving bugs for rotation by introducing algorithm with vector and matrices.
// 3. Multithreading keyboard listenners.
// 4. Add new features in game: scores, difficulty, down keys to make it move faster, space to make it drop immediately.
#include<iostream>
#include<thread>
#include<ctime>
#include<chrono>
#include<vector>
#include"conio.h"
#include<stdlib.h>

#define WDT 10
#define HET 25

#define KEYA 97
#define KEYD 100 
#define KEYS 115
#define KEYE 101
#define KEYX 120

long start, end;
int screenbuffer [WDT*HET] {0}; // width times height.
int score;

void rotation(){
	double x, y, tx, ty;
	for (int i=0; i<16; ++i){
		tx=(i%4)-1.5;
		ty=(int)((i-tx)/4)-1.5;
		// std::cout<<ty<<std::endl;
		// std::cout<<tx<<" "<<ty<<std::endl;
		x = -ty+1.5; y=tx+1.5;
		printf("%d:%f, %f, %d\n",i, x,y,int(4*y+x));
		// printf("%ld, %ld\n", x,y);
	}
}

void pa9(int* a){
	for (int i=0; i<9; ++i) std::cout<<a[i]<<' ';
}

void ctime(long *res){ // Get Current Time
	auto now = std::chrono::system_clock::now();
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
	auto epoch = now_ms.time_since_epoch();
	auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
	long duration = value.count();
	*res = duration;
}

char bufferToChar(int a){
	switch (a){
		case 0 : return ' ';
		case 1 : return '*';
		case 2 : return '*';
	}
	return '?';
}

void screen(){ //Update Screen according to the buffer.
	// static int counter {0};
	
	// std::cout<<counter++<<" "<<rand()%100+1<<std::endl;
	while(1){
		ctime(&(::end)); // In milliseconds
		if ((::end-::start)>=10){ //100 fps
			for (int i=0; i<100; i++) std::cout<<std::endl; // Updating the screen. 

			std::cout<<"fps: "<<1000/(::end-::start)<<std::endl; // FPS
			std::cout<<"SCORE: "<<::score<<std::endl; // FPS

			for(int i=0; i<WDT+2; ++i){ // Printing the margin
				std::cout<<"#";
			}
			std::cout<<std::endl;

			for (int i=0; i<HET; ++i){
				std::cout<<"#"; //Printing the left margin
				for(int j=0; j<WDT; ++j){
					std::cout<<bufferToChar(::screenbuffer[j+i*WDT]);
				}
				std::cout<<"#"<<std::endl; //printing the right margin
			}

			for(int i=0; i<WDT+2; ++i){ //printing the bottom margin
				std::cout<<"#";
			}
			std::cout<<std::endl;

			::start=::end; // For time
		}
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
}

void init(){
	srand(time(NULL));
	ctime(&(::start));	
	return;
}

int main(){
	init();
	std::thread t1(screen);
	
	t1.join();
	return 0;
}
