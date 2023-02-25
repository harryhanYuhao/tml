#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "conio.h"

void pline(char a){
	while(1){
		std::cout<<a<<std::endl;
		// std::this_thread::sleep_for(std::chrono::microseconds(100000));
		sleep(1);
	}
}

void key(){
	while(1){
		int kval = getch();
		std::cout<<"Key Pressed!"<<kval<<std::endl;
	}
}


int main(){
	std::thread t1(pline, 'a'); //Create a thread, can call function, function pointer, or lambda. Input of the function is separated by the comma.
	std::thread t2(key);

	t1.join(); // main thread wait for the thread to finish.
	t2.join();
	return 0;
}
