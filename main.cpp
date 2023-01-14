#include<iostream>
#include<thread>
#include<ctime>
#include<chrono>
#include<vector>
#include"conio.h"

#define wdt 40
#define het 30

#define keya 97
#define keyd 100 
#define keys 115
#define keye 101
#define keyx 120

void pa9(int* a){
	for (int i=0; i<9; ++i) std::cout<<a[i]<<' ';
}

long ctime(){
	auto now = std::chrono::system_clock::now();
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
	auto epoch = now_ms.time_since_epoch();
	auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
	long duration = value.count();
	return duration;
}

int counter = 0;
bool gs = 1;
long start, end; // for time 
int dra[wdt*het]; // drawing buffer.
int acp [2] = {wdt/2, 0}; // Active object position, (wdt, het)
long keytimes, keytimee; //key timer start, key timer ends

struct Tet{
	int squ[9] {0, 1, 1, 1, 0, 0, 0, 0, 1}; // Square
	int L[9] {1, 1, 1, 1, 0, 0, 0, 0, 0}; // L shape
	int line [9] {1, 1, 1, 0, 0, 0, 0, 0, 0}; // line only 3
	int t [9] {1, 1, 1, 0, 0, 0, 0, 0, 1}; // T shape
};

Tet stet;

void rotate(int li[9], int times){
	int temp[9];
	for (int i=0; i<8; ++i) temp[i] = li[(i+(2*times))%8];
	for (int i=0; i<8; ++i) li[i] = temp[i]; 
}

int actgp[9]; // the current coordinate of the active game piece in the game window. 
int actgpu [9]; // the current coordination of the active game piece not in the game window coordinate.
int gpset {1}; // whether the game piece is setted at the bottom;
std::vector<int> draUv;


void randt(){
	int s1 = ((ctime()%100)*7)%4;
	int s2 = ((ctime()%1000)%8);
	rotate(stet.squ, s2);
	rotate(stet.L, s2);
	rotate(stet.line, s2);
	rotate(stet.t, s2);
	switch (s1%4){
		case 0: for (int i=0; i!=9; ++i) ::actgpu[i]=stet.squ[i]; break;
		case 1: for (int i=0; i!=9; ++i) ::actgpu[i]=stet.L[i]; break;
		case 2: for (int i=0; i!=9; ++i) ::actgpu[i]=stet.line[i]; break;
		case 3: for (int i=0; i!=9; ++i) ::actgpu[i]=stet.t[i]; break;
	}

	::actgp[4]=::actgpu[8];
	for (int i=0; i!=3; ++i){
		::actgp[i] = ::actgpu[i];
	}
	::actgp[3] = ::actgpu[7]; ::actgp[5]=::actgpu[3]; ::actgp[6]=::actgpu[6]; ::actgp[7]=::actgpu[5]; ::actgp[8]=::actgpu[4];

	for (int i=0; i<3; ++i){
		for (int j=0; j<3; ++j){
			if (::actgp[i*3+j]!=0){
				::actgp[i*3+j] = ::actgp[i*3+j]*(wdt*i+j)+wdt/2;
			}
		}
	}
}


char toC(int i){ // int --> char: 
	switch (i){
		case 0: return ' '; break; // empty
		case 1: return '*'; break; // temporarily occupied
		case 2: return '*'; break; // permanently occupied 
	} return '?';
}


void draU (){ //drawing buffer update
	for (int i=0; i<wdt*het; ++i){
		if (dra[i]==1) dra[i]=0;
	}
	if (::gpset){
		randt();
		draUv.clear();
		for (int i=0; i<3; ++i){
			for (int j=0; j<3; ++j){
				if (::actgp[i*3+j]!=0){
					draUv.push_back(::actgp[i*3+j]); 
				}
			}
		}
		::gpset = 0;
	} else{
		int rcounter = 0; //row counter
		for (int i=0; i<het; ++i){
			bool det = true;
			for (int j=0; j<wdt; ++j){
				if (dra[wdt*i+j]!=2){
					det = 0;
					break;
				}

			}
		}
		for (int &element:draUv){ //move down
			element+=wdt;
			acp[1] += 1;
		}
		for (int element:draUv){
			if (element/wdt==het-1){ //bottom detect
				acp [0] = wdt/2; acp [1] = 0;
				::gpset = 1;
				for (int  element:draUv){
					dra[element] = 2;
				}
			}
			if ((dra[element+wdt] == 2)||(dra[element+1]==2)||(dra[element-1]==2)){ // collision detect
				::gpset = 1;
				for (int  element:draUv){
					dra[element] = 2;
				}
				acp [0] = wdt/2; acp [1] = 0;
			}
			if ((dra[element+wdt] == 2)&&(element/wdt)<5){ //endgame detect
				gs = 0;
			}
		}
		keytimes = ctime();
		keytimee = ctime();
		while ((keytimee - keytimes)<2){
			if(kbhit()){
				int keyval = getch();
				if(keyval == keya){
					for(int& element:draUv){ // move left
						--element;
					}
					break;
				}
				if(keyval == keyd){ // move right
					for(int& element:draUv){
						++element;
					}
					break;
				}
				if(keyval == keys){ //TODO better s algorithm
					for(int& element:draUv){
						if ((dra[element+wdt]==2)||(dra[element+2*wdt]==2)){
							break;
						}
						element+=wdt;
						std::cout<<"s pressed!\n";
					}
					break;
				}
				if (keyval == keye){
					rotate(actgpu, 1);
					::actgp[4]=::actgpu[8];
					for (int i=0; i!=3; ++i){
						::actgp[i] = ::actgpu[i];
					}
					::actgp[3] = ::actgpu[7]; ::actgp[5]=::actgpu[3]; ::actgp[6]=::actgpu[6]; ::actgp[7]=::actgpu[5]; ::actgp[8]=::actgpu[4];
				
					for (int i=0; i<3; ++i){
						for (int j=0; j<3; ++j){
							if (::actgp[i*3+j]!=0){
								::actgp[i*3+j] = ::actgp[i*3+j]*(wdt*i+j)+acp[0]+acp[1]*wdt/2;
							}
						}
					}
					draUv.clear();
					for (int i=0; i<3; ++i){
						for (int j=0; j<3; ++j){
							if (::actgp[i*3+j]!=0){
								draUv.push_back(::actgp[i*3+j]); 
							}
						}
					}
				}
				break;
			}
	//		std::this_thread::sleep_for(std::chrono::milliseconds(1));
			keytimee = ctime();
		}
	}
	
	for (int  element:draUv){
		if (dra[element]==0){
			dra[element] = 1;
		}
	}
}

void fun(){
	for (int i=0; i!=10;++i){
		std::cout<<"\n";
	}
	draU();
	for (int i=0; i!=het+2; ++i){
		for (int j=0; j!=wdt+2; ++j){
			if (i==0||i==het+1||j==0||j==wdt+1){
				std::cout<<"#";
			}else {
				std::cout<<toC(dra[(i-1)*wdt+j-1]);
			}
		}
		std::cout<<std::endl;
	}
}



bool delay(){
	::end = ctime();
	if ((::end-::start)>100){ // 100 milliseconds
		::start = ::end;
		return true;
	}
	return false;
}

void init(){
	for(int i=0; i<sizeof(dra)/sizeof(int);++i){
		dra[i] = 0;
	}
}

int main (){
	::start = ctime();
	init();
	while(1){
		if (delay()){ //update every 100 milliseconds;
			fun();
		//	pa9(actgp);
		}
		if (!gs){
			std::cout<<"game over!\n";
			break;
		}
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
	return 0;
}

