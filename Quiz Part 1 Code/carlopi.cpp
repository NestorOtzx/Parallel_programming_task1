#include <iostream>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <atomic>
#include <random>
#include <cmath>
#include <iomanip>

struct ThreadArgs {
    int n_h;
    unsigned int seed;
    int insideCircle;
};

void* monteCarloPiThread(void* arg) {
    ThreadArgs* data = (ThreadArgs*)arg;
    int localInsideCircle = 0;
    unsigned int localSeed = data->seed;

    for (int i = 0; i < data->n_h; ++i) {
        double x = rand_r(&localSeed) / (double)RAND_MAX;
        double y = rand_r(&localSeed) / (double)RAND_MAX;
        if (x * x + y * y <= 1.0) {
            ++localInsideCircle;
        }
    }

    data->insideCircle = localInsideCircle; 
    return NULL;
}



double monteCarloPi(int n, int numThreads) {
    pthread_t threads[numThreads];
    ThreadArgs threadArgs[numThreads];

    int tossesPerThread = ceil((float)n /(float)numThreads);
    int remainder = n % numThreads;


    for (int i = 0; i < numThreads; ++i) {
        threadArgs[i].n_h = tossesPerThread + (i== numThreads-1 ? remainder : 0);
        threadArgs[i].seed = 0;
        pthread_create(&threads[i], NULL, monteCarloPiThread, (void*)&threadArgs[i]);
    }

    int totalInsideCircle = 0;
    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], NULL);
        totalInsideCircle += threadArgs[i].insideCircle;
    }

    return 4.0 * totalInsideCircle / n;
}

float relativeError(float p, float ps) {
    return std::fabs((p - ps) / ps);
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout<<"wrong input"<<std::endl;
        return -1;
    }

    int numThreads = atoi(argv[1]);
    int n = atoi(argv[2]);

    if (numThreads <= 0 || n <= 0) {
        std::cout<<"wrong input"<<std::endl;
        return -1;
    }

    //Use clock_gettime() instead clock()
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    double pi_value = monteCarloPi(n, numThreads); //process
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    std::cout<<"pi: "<<pi_value<<std::endl;
    std::cout<<"time: "<< elapsed_time<<" s"<<std::endl;
    std::cout<<"relative error to math.pi: "<<std::fixed << std::setprecision(6) << relativeError(pi_value, M_PI) << std::endl;
    return 0;
}
