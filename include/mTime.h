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

int msleep(long msec){
  if (msec < 0) {
    errno = EINVAL;
    return -1;
  }

  struct timespec ts;
  ts.tv_sec = msec/1000;
  ts.tv_nsec = (msec%1000) * 1000000;

  int res = nanosleep(&ts, NULL);

  return res;
}

#endif // endif for _MTIME_H
