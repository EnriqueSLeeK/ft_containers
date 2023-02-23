
#include <sys/time.h>
#include <iostream>

static double get_elapse_time (struct timespec &start, struct timespec &end) {
    double time_delta;
    time_delta = (end.tv_sec - start.tv_sec) * 1e9;
    time_delta = (time_delta + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    return (time_delta);
}

template <typename vec_type, typename data_type>
double measure_vector_time (data_type data) {
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    vec_type vector_container;

    vector_container.insert(vector_container.begin(), 5000, data);
    vector_container.clear();

    vector_container.insert(vector_container.begin(), 5000, data);
    vector_container.erase(vector_container.begin(), vector_container.end() - 100);
    vector_container.erase(vector_container.begin(), vector_container.begin() + 50);
    vector_container.insert(vector_container.begin(), 5000, data);
    vector_container.insert(vector_container.begin(),
                                vector_container.begin(),
                                vector_container.begin() + 10);

    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate the time
    return (get_elapse_time(start, end));
}

template <typename stack_type, typename data_type>
double measure_stack_time (data_type data) {
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    stack_type  stack;
    
    for (int i = 0; i < 50000; i++)
        stack.push(data);
    for (int i = 0; i < 50000; i++)
        stack.pop();

    clock_gettime(CLOCK_MONOTONIC, &end);

    return (get_elapse_time(start, end));
}

template <typename map_type,
            typename pair_type,
            typename data_type>
double measure_map_time (data_type k) {
    struct timespec start, end;

    pair_type pair[15000];
    for (int i = 0; i < 15000; i++) {
        pair[i].first = i;
        pair[i].second = k;
    }
    clock_gettime(CLOCK_MONOTONIC, &start);
    map_type map;

    for (int i = 0; i < 15000; i++) {
        map.insert(pair[i]);
    }

    for (int i = 0; i < 15000; i++) {
        map.erase(i);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    return (get_elapse_time(start, end));
}

template <typename set_type,
            typename data_type>
double measure_set_test (data_type k) {
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    set_type set;
    
    for (int i = 0; i < 5000; i++) {
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    return (get_elapse_time(start, end));
}