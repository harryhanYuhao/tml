#include <pthread.h> // Multithreading
#include <stdio.h>
#include <stdlib.h>  // for atexit()
#include <termios.h> // For changing terminal mode
#include <unistd.h>  // For changing terminal mode

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GREYBOX "\x1b[100m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct termios original; // A struct to save the original state of terminal
int ESCPressed = 0;      // For thread communication

int LTetris [16] = {0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0};
int LineTetris [16] = {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0};
int SquareTetris [16] = {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0};
int ForkTetris [16] = {0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0};
int ChiralTetris1 [16] = {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0};
int ChiralTetris2 [16] = {0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0};

void disableRAWMode();
void enableRAWMode();
void *asciRead();
void *print();

int main() {
  // Start Multithreading
  pthread_t id_print, id_read;

  pthread_create(&id_print, NULL, print, NULL);
  pthread_create(&id_read, NULL, asciRead, NULL);

  pthread_join(id_print, NULL);
  pthread_join(id_read, NULL);

  return 0;
}

/// Reads keyboard input
void *asciRead() {
  enableRAWMode(); // local function: Enable Raw Mode
  char ch;
  while ((ch = getchar()) != 27); // ASCI code for ESC is 27
  ESCPressed = 1;
  printf("ESC Pressed!\n");
	return NULL;
}

void *print() {
  while (!ESCPressed) { // When ESC is not pressed
    sleep(1);
    printf("I am Printing!\n");
  }
  printf("Printing Thread Finished!\n");
	return NULL;
}

void rotation(int * inArray){ //Rotation
	int * ptr = (int*)calloc(16, sizeof(int));
	// TODO: USE memcopy 
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

void enableRAWMode() {
  struct termios raw;
  tcgetattr(STDIN_FILENO, &raw); // Save the state of the terminal to struct raw
  tcgetattr(STDIN_FILENO, &original);

	// Revert to canonical mode when exiting the program
  atexit(&disableRAWMode); 

	// Turn off echo and canonical mode
  raw.c_lflag &= ~(ECHO | ICANON); 

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRAWMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}
