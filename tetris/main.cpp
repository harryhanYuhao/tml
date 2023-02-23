// Refactor tml code:
// 1. Make it more readable and maintainable
// 2. resolving bugs for rotation by introducing algorithm with vector and matrices.
// 3. Multithreading keyboard listenners.
// 4. Add new features in game: scores, difficulty, etc.
#include<iostream>
#include<thread>
#include<ctime>
#include<chrono>
#include<vector>
#include"conio.h"

#define wdt 6
#define het 30

#define keya 97
#define keyd 100 
#define keys 115
#define keye 101
#define keyx 120

long start, end;

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

void fun(){
	static int counter {0};
	std::cout<<counter++<<std::endl;
}

void init(){
	ctime(&(::start));	
	return;
}

int main(){
	init();
	while(1){
		ctime(&(::end));
		if ((::end-::start)>100){
			fun();
			::start=::end;
		}
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
}
