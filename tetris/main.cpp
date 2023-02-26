// Refactor tml code:
// 1. Make it more readable and maintainable
// 2. resolving bugs for rotation: DONE
// 3. Multithreading keyboard listenners: DONE
// 4. Add new features in game: scores, difficulty, down keys to make it move faster, space to make it drop immediately.
#include <iostream>
#include <thread>
#include <ctime>
#include <chrono>
#include <vector>
#include "conio.h"
#include <stdlib.h>
#include <mutex>

#define WDT 10
#define HET 25

#define KEYA 97
#define KEYD 100 
#define KEYS 115
#define KEYE 101
#define KEYX 120

long start, end; // Time tracker for screen buffer
long gstart, gend; // Time tracker for game loop
int screenbuffer [WDT*HET] {0}; // width times height.
int score;
int keypressed {0}; // For thread communication

int speed {200}; // Game speed

int cor [5] {WDT/2, 5}; // The x, y coordinates of the tetris. from upper left corner clockwise (0, 0) (3, 0) (3, 3) (0, 3)

// We need 6 basic shapes for the tetris.
int LTetris [16] {0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0};
int LineTetris [16] {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0};
int SquareTetris [16] {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0};
int ForkTetris [16] {0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0};
int ChiralTetris1 [16] {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0};
int ChiralTetris2 [16] {0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0};

int activePiece [16]; 

std::mutex mtx;

void rotation(int * inArray){ //Rotation
	int * ptr = (int*)calloc(16, sizeof(int));
	for(int i=0; i<16; ++i){	
		ptr[i] = inArray[i];
	}
	for(int i=0; i<4; ++i){
		for(int j=0; j<4; ++j){
			inArray[3-i+4*j]=ptr[j+i*4];
		}
	}
	free(ptr);
	return;
}

void ctime(long *res){ // Get Current Time
	auto now = std::chrono::system_clock::now();
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
	auto epoch = now_ms.time_since_epoch();
	auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
	*res = value.count();
}

char bufferToChar(int a){
	switch (a){
		case 0 : return ' ';
		case 1 : return '*';
		case 2 : return '*';
		default: return '?';
	}
	return '?';
}

void keylistener(){ // The keylistener: on its own thread.

	while (1){
		int key = getch();
		if ((key == KEYA)||(key==KEYE)||(key==KEYS)||(key==KEYD)){	
			mtx.lock();
			keypressed = key;
			mtx.unlock();
		}
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
	return;
}

void gameloop() { // The game loop that modifies the screen buffer Updating at different time, in a different thread.
	int * ap = screenbuffer;
	while (1){
	ctime(&(::gend));
		if((::gend-::gstart)>=speed){ // modify here for change of game speed.
			if (keypressed!=0){
				switch(keypressed){
					case KEYE: rotation(activePiece); break;
					case KEYA: cor[0]--;
					case KEYD: cor[0]++;
					// case KEYS: 
				}
				mtx.lock();
				keypressed=0;
				mtx.unlock();
			}

			for(int i=0; i<4; ++i){
				for(int j=0; j<4; ++j){
					screenbuffer[(cor[1]+i)*WDT+cor[0]+j]=activePiece[j+4*i];
				}
			}

			::gstart=::gend;
		}
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
	return;
}

void screen(){ //Update Screen according to the buffer.
	// static int counter {0};
	
	// std::cout<<counter++<<" "<<rand()%100+1<<std::endl;
	while(1){
		ctime(&(::end)); // In milliseconds
		if ((::end-::start)>=20){ //50 fps
			for (int i=0; i<100; i++) std::cout<<std::endl; // Updating the screen. 

			std::cout<<"fps: "<<1000/(::end-::start)<<std::endl; // print the fps 
			std::cout<<"SCORE: "<<::score<<std::endl; // print the score

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
	return;
}

void init(){
	srand(time(NULL));
	ctime(&(::start));	
	ctime(&(::gstart));
	for(int i=0; i<16; ++i){
		activePiece[i]=LineTetris[i];
	}
	return;
}

int main(){
	init();
	std::thread t1(screen);
	std::thread t2(gameloop);
	std::thread t3(keylistener);
	
	t1.join();
	t2.detach();
	t3.detach();
	return 0;
}
