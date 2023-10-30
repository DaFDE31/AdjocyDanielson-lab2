#include <sys/time.h>

double elapsed_time(struct timeval* start_time, struct timeval* end_time){
    
    double start = start_time->tv_usec + (start_time->tv_sec * 1000000.0);

    double end = end_time->tv_usec + (end_time->tv_sec * 1000000.0);

    double value = (end- start)/1000000;
    
    return value;
}