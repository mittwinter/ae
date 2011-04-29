#ifndef __TIMING_H
#define __TIMING_H

#include <sys/resource.h>
#include <iostream>

int timeval_subtract ( struct timeval *result, struct timeval *x, struct timeval *y)
{
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }
     
  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;
     
  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}

double timediff( struct rusage& before, struct rusage& after )
{
  struct rusage sub;
  if( timeval_subtract(&sub.ru_utime,&after.ru_utime,&before.ru_utime)>0 )  { std::cerr << "Fehler in timediff() - Argumente vertauscht?" <<std::endl; abort(); }
  if( timeval_subtract(&sub.ru_stime,&after.ru_stime,&before.ru_stime)>0 )  { std::cerr << "Fehler in timediff() - Argumente vertauscht?" <<std::endl; abort(); }

  double ut = (double(sub.ru_utime.tv_sec) + (((double)sub.ru_utime.tv_usec)/1000000.0));
  double st = (double(sub.ru_stime.tv_sec) + (((double)sub.ru_stime.tv_usec)/1000000.0));

  return ut+st;
}

#endif
