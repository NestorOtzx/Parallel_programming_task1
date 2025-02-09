#include <iostream>
#include <time.h>

double monteCarloPi(int n) {
    int insideCircle = 0;

    for (int i = 0; i < n; ++i) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) { //in circle
            ++insideCircle;
        }
    }
    return 4.0 * insideCircle / n;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return -1;
    }
    int n = atoi(argv[1]);

    if (n <= 0) {
        return 1;
    }

    srand(0); //seed 

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    double ans = monteCarloPi(n);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    std::cout<<"pi: "<<ans<<std::endl;
    std::cout<<"time: "<<elapsed_time<<" seconds"<<std::endl;
    return 0;
}