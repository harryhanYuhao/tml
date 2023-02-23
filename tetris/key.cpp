#include <iostream>
#include "conio.h"

#define kup 65 // A equivalent to upkey
#define kd 66 // B equivalent to downkeu
#define kl 67 // C equivalent to l
#define kr 68 // D equivalent to right
#define kx 120 // x: minuscule: unicode encoding 

int main(){
	int key = getch();
	if (key!= 1){
	while(key!= kx){
		key = getch();
		switch(key){
			case kup: 
				std::cout<<"up!\n"; break;
			case kd: 
				std::cout<<"down!\n"; break;
			case kl: 
				std::cout<<"left!\n"; break;
			case kr: 
				std::cout<<"right!\n"; break;
		}
		std::cout<<"h"<<std::endl;
	}
	}
	return 0;
}

