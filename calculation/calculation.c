#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define RED "\033[31m"
#define BOLD "\033[1m"
#define NC "\033[0m"
#define printR(...)                                                            \
    do {                                                                       \
        printf(RED BOLD __VA_ARGS__);                                          \
        printf(NC);                                                            \
    } while (0)

// return seconds since epoch. Precision to millisec
double CurTime()
{
    struct timeval tp; // timeval defined in sys/time.h
    gettimeofday(&tp, NULL);
    long sec = tp.tv_sec;
    long us = tp.tv_usec;
    return (double)sec + (double)(us) / (double)1000000;
}

int genPrompt()
{
	int r1, r2;
	r1 = rand() % 100;
	r2 = rand() % 100;
	printf("%d + %d = ", r1, r2);
	return r1 + r2;
}

int main()
{
    double startTime = CurTime();
    srand((int)startTime); // seed the rand
    int correct = 0;
    int wrong = 0;
    char *buf = NULL; // getline will allocate the memory
    size_t size = 0;
	size_t readLen = 0;
    double timeLim = 10;

    int expected;
    while ((CurTime() - startTime) < timeLim) {
		expected = genPrompt();
		do{
		   	readLen = getline(&buf, &size, stdin);
		} while(readLen<=1); // when only return is read
        if (atoi(buf) == expected) {
            ++correct;
            timeLim += 0.5;
        } else {
            printR("Wrong!\n"); // print red
            ++wrong;
            timeLim -= 2;
        }
    }

	double timeUsed = CurTime() - startTime;
    free(buf);

    printf("%d out of %d in %.3f seconds\n", correct, correct + wrong,
			timeUsed);
    printf("Percent Correct: %.2f\% \n",
           (float)(correct) / (float)(correct + wrong) * (float)100);
	printf("%.3f ", timeUsed / (float) correct);
	printf("sec per correct answer\n");
    return 0;
}
