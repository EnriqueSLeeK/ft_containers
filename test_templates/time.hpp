
#include <sys/time.h>
#include <iostream>

template <typename vec_type, typename data_type>
double measure_vector_time (data_type data) {
    //struct timeval start, end;
    struct timespec start, end;
    double  time_delta;

    //clock_gettime(CLOCK_REALTIME, &start);
    clock_gettime(CLOCK_MONOTONIC, &start);

    vec_type vector_container;
    vector_container.insert(vector_container.begin(), 500000, data);
    vector_container.clear();

    //clock_gettime(CLOCK_REALTIME, &end);
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate the time
    time_delta = (end.tv_sec - start.tv_sec) * 1e9;
    time_delta = (time_delta + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    return (time_delta);
}