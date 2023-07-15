// This file is hard-linked
// present in tml/include
// present in psu/lib/c
#ifndef _MTIME_H
#define _MTIME_H

#include <sys/time.h>
#include <time.h>
#include <errno.h>

/// Current time in microseconds since epoch

// Complaint to C99 

long int mTime(long *in){
  long current_calendar_time = 0;
  // timeval defined in sys/time.h
  struct timeval tp; 
  gettimeofday(&tp, NULL);
  
  current_calendar_time += tp.tv_sec*(long)(1000000) + tp.tv_usec;
  *in = current_calendar_time;
	return current_calendar_time;
}

// Input: long micro_sec
// the current thread sleeps for micro_sec microseconds
// if interrupted by system signals during the waiting time,
// the remaining waiting time is simply ignored
int microSleep(long micro_sec){
  if (micro_sec < 0) {
    errno = EINVAL;
    return -1;
  }

  struct timespec ts;
  ts.tv_sec = micro_sec/1000000;
  ts.tv_nsec = (micro_sec%1000) * 1000;

  int res = nanosleep(&ts, NULL);

  return res;
}

#endif // endif for _MTIME_H
