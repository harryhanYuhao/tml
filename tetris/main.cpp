// Refactor tml code:
// 1. Make it more readable and maintainable
// 2. resolving bugs for rotation: DONE
// 3. Multithreading keyboard listenners: DONE
// 4. Add new features in game: scores, difficulty, down keys to make it move faster, space to make it drop immediately.
// 5. Add Color
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

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GREYBOX "\x1b[100m"
#define ANSI_COLOR_RESET   "\x1b[0m"

long start, end; // Time tracker for screen buffer
long gstart, gend; // Time tracker for game loop
int screenbuffer [WDT*HET] {0}; // width times height.
int gamebuffer[WDT*HET] {0}; // The Game buffer that maps to screenbuffer
int score;
int keypressed {0}; // For thread communication

int speedNormal {300};
int speekFast = speedNormal/200;
int sCounter {0};
int speed = speedNormal; // Game speed

int cor [5] {WDT/2, 1}; // The x, y coordinates of the tetris. from upper left corner clockwise (0, 0) (3, 0) (3, 3) (0, 3)

// We need 6 basic shapes for the tetris.
int LTetris [16] {0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0};
int LineTetris [16] {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0};
int SquareTetris [16] {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0};
int ForkTetris [16] {0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0};
int ChiralTetris1 [16] {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0};
int ChiralTetris2 [16] {0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0};

int activePiece [16]; // 4*4 array holding the structures of the tetris.

int gamepieceCor [4] {0}; // The coordinate of the tetris In game coordinate 
int expectedPieceCor [4] {0};

bool gameState {1};
bool newPiece {0};


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

std::string bufferToChar(int a){
	switch (a){
		case 0 : return " ";
		case 1 : return "*";
		case 2 : return "*"ANSI_COLOR_RESET;
		case 3 : return ANSI_COLOR_GREYBOX"*"ANSI_COLOR_RESET;
		default: return "?";
	}
	return "?";
}

void updateGamePieceCor(){
	int * ptr = gamepieceCor;
	for (int i=0; i<16; ++i){
		if (activePiece[i]==1){
			*(ptr++)=cor[0]+WDT*(cor[1])+i%4+WDT*(i/4);
		}
	}
	return;
}

void randomActiveGamePiece(){ //Modify activePiece to be one of the random consititute.
	std::vector<int> allList;
	allList.insert(allList.end(), std::begin(LTetris), std::end(LTetris));
	allList.insert(allList.end(), std::begin(SquareTetris), std::end(SquareTetris));
	allList.insert(allList.end(), std::begin(LineTetris), std::end(LineTetris));
	allList.insert(allList.end(), std::begin(LineTetris), std::end(LineTetris));
	allList.insert(allList.end(), std::begin(ChiralTetris1), std::end(ChiralTetris1));
	allList.insert(allList.end(), std::begin(ChiralTetris2), std::end(ChiralTetris2));
	allList.insert(allList.end(), std::begin(ForkTetris), std::end(ForkTetris));
	int random = rand()%10;
	for (int i=0; i<16; ++i){
		activePiece[i]=allList[(random%7)*16+i];
	}
	// for (int i=0; i<16; ++i){
	// 	activePiece[i]=LineTetris[i];
	// }
	updateGamePieceCor();	
	return;
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
		if (!gameState) return;
	}
	return;
}

void gameloop() { // The game loop that modifies the screen buffer Updating at different time, in a different thread.
	int * ap = screenbuffer;
	while (1){
		ctime(&(::gend));
		if(!gameState) return;
		if ((score-30)>0){
			speedNormal=(1900/score)+1000/(score-30)+600/(score-20)+400/(score-10)+80;
		}
		if((::gend-::gstart)>=speed/5){ // modify here for change of game speed.
			if (sCounter==0){speed = speedNormal;} // Press s will set the counter to 5.
			else{speed = speekFast; sCounter--;}

			if (newPiece){
				for (int i:gamepieceCor){
					screenbuffer[i]=2;
				}
				cor[0]=WDT/2; cor[1] = 1;
				newPiece = 0;
				randomActiveGamePiece();
				score+=2;
			}

			updateGamePieceCor();

			if (keypressed!=0){ //Key Detecting
				switch(keypressed){
					case KEYE: rotation(activePiece); break;
					case KEYA: cor[0]--; break;
					case KEYD: cor[0]++; break;
					case KEYS: sCounter = 10; break;
				}
				mtx.lock();
				keypressed=0;
				mtx.unlock();
			}
			
			//Bottom Detection
			for (int i:gamepieceCor){
				if(((i+WDT)>=WDT*HET)||(screenbuffer[i+WDT]==2)){ // The same condition is used for expectedPieceCor.
					newPiece = 1;
					break;
				}
			}

			// Expected Piece Detection
			for (int i=0; i<(sizeof(gamepieceCor)/sizeof(int)); ++i){
				expectedPieceCor[i]=gamepieceCor[i];
			}
			for (int i=0; i<HET; ++i){
				for (int j:expectedPieceCor){
					if(((j+WDT)>=WDT*HET)||(screenbuffer[i+WDT]==2)){
						break;
					}
				}
				for(int &j:expectedPieceCor) j+=WDT;
			}
			
			
			//End Game Detection 
			for (int i=0; i<WDT*HET; ++i){
				if ((screenbuffer[i]==2)&&(i<2*HET)) gameState = 0;
			}

			// Clear Rows:
			for (int i=0; i <HET; i++){
				for (int j=0; j<WDT; j++){
					if (screenbuffer[j+WDT*i]!=2) break;
					if (j==WDT-1){
						score +=10;
						for (int k=0; k<WDT; k++){
							screenbuffer[k+WDT*i]=0; //Clear the row
						}
						std::vector <int> buffer;
						for (int k=0; k<WDT*(i); ++k){ // Move all other rows one level down.
							buffer.push_back(screenbuffer[k]);
						}
						for (int k=0; k<WDT*(i); ++k){ // Move all other rows one level down.
							screenbuffer[k+WDT] = buffer[k];
						}
					}
				}
			}

			//Clear and draw to the Screen buffer 
			for (int i=0; i<WDT*HET; ++i){
				if(screenbuffer[i]==1||screenbuffer[i]==3) screenbuffer[i]=0;
			}

			for (int i:gamepieceCor) screenbuffer[i]=1;
			for (int i:expectedPieceCor) screenbuffer[i]=3;
		}
		if((::gend-::gstart>=speed)){
			cor[1]++;
			::gstart=::gend;
		}
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
	return;
}

void screen(){ //Update Screen according to the buffer.
	// static int counter {0};
	
	// std::cout<<counter++<<" "<<rand()%100+1<<std::endl;
	int counter {0};
	while(1){
		if (!gameState){ 
			std::cout<<"Game Finished! \n Your Score is: "<<score<<std::endl;
			std::cout<<"Press Any Key to Return!\n";
			return;
		}
		ctime(&(::end)); // In milliseconds
		if ((::end-::start)>=25){ //50 fps
			if(counter>20) {
				system("clear");
				counter = 0;
			}
			// for (int i:gamepieceCor) std::cout<<i<<std::endl;
			for (int i=0; i<50; i++) std::cout<<std::endl; // Updating the screen. TODO: uncomment it

			std::cout<<"e for rotation, a for left, b for right, s for down\n";
			std::cout<<"speed: "<<400/speed<<std::endl;
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
				// std::cout<<ANSI_COLOR_GREYBOX<<" "<<ANSI_COLOR_RESET;
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
	::speed=speedNormal;
	ctime(&(::start));	
	ctime(&(::gstart));
	randomActiveGamePiece();
	return;
}

int main(){
	init();
	std::thread t1(screen);
	std::thread t2(gameloop);
	std::thread t3(keylistener);
	
	t1.join();
	t2.join();
	t3.join();
	return 0;
}
