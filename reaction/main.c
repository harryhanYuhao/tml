#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>
#include <time.h>

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

int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

int main()
{
	double startTime;
	int sum = 0;
	int iter = 5;
	srand((int)CurTime());
	
	int waitTime [5];

	for (int i = 0; i < iter; ++i){
		waitTime[i] = rand() % 10000 + 500;
		sum+=waitTime[i];
	}
	
	startTime = CurTime();
	for (int i = 0; i < iter; ++i){
		msleep(waitTime[i]);
		double tmp = CurTime();
		printf("ssss\n");
		getchar();
		printf("%f\n", CurTime()-tmp);
	}
	double timeUsed = CurTime() - startTime - sum / (float) 1000;
	printf("%f s Per reaction\n", timeUsed / (float)iter);

	return 0;
}
