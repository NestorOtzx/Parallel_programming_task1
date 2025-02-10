#include <iostream>
#include <pthread.h>
#include <unistd.h>

#define ARRAY_SIZE 10
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3
#define MAX_PRODUCE 100


int shared_array[ARRAY_SIZE] = {0};
bool isFull = false;
bool isEmpty = true;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;  // Mutex for synchronization


void* producer(void* arg) {
    int id = *(int*)arg;
    delete (int*)arg; //free memo

    int produce_num = 0;
    

    while (true) {
        pthread_mutex_lock(&mtx); 
        int wait_for = 1 + rand() % 3;
        for (int i = 0; i < ARRAY_SIZE; i++) {
            if (shared_array[i] == 0) {
                produce_num = (produce_num % MAX_PRODUCE) + 1;
                shared_array[i] = produce_num;
                std::cout<<"Producer "<<id<<": Added "<<shared_array[i]<<" at index "<<i<<std::endl;
                //std::cout<<"Producer "<< id <<": Waiting for "<< wait_for<<" seconds..."<<std::endl;
                break;
            }
        }

        pthread_mutex_unlock(&mtx);  // Unlock the mutex while waiting
        sleep(wait_for);  // Wait for the specified amount of time
    }
    return nullptr;
}


// Function to simulate the consumer behavior
void* consumer(void* arg) {
    int id = *(int*)arg;
    delete (int*)arg; //free memo


    while (true) {
        pthread_mutex_lock(&mtx);
        int wait_for = 1 + rand() % 6;
        for (int i = 0; i < ARRAY_SIZE; i++) {
            if (shared_array[i] != 0) {
                int value = shared_array[i];
                shared_array[i] = 0;
                std::cout<< "Consumer "<<id<<": Removed "<<value<<" from index "<<i<<std::endl;
                //std::cout<<"Consumer "<<id<<": Waiting for "<<wait_for<<" seconds..."<< std::endl;
                break;
            }
        }
        
        pthread_mutex_unlock(&mtx);
        sleep(wait_for);
    }

    return nullptr;
}


int main() {
    pthread_t producers[NUM_PRODUCERS];  
    pthread_t consumers[NUM_CONSUMERS];

    
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        int * id = new int();
        *id=i;
        pthread_create(&producers[i], nullptr, producer, id);
    }
    

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        int * id = new int();
        *id=i;
        pthread_create(&consumers[i], nullptr, consumer, id);  // Start each consumer thread
    }

    // Wait for all producer threads to finish
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], nullptr);  // Ensure all producer threads complete before moving on
    }


    // Wait for all consumer threads to finish
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], nullptr);  // Ensure all consumer threads complete before finishing
    }

    // Print the final state of the shared array
    std::cout<<"Final shared array state:"<<std::endl;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        std::cout<<shared_array[i]<<" ";  // Print the values in the array
    }
    std::cout<<std::endl;

    pthread_mutex_destroy(&mtx);
    return 0;
}
