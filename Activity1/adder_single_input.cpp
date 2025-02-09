#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

int sumArr(int arr[], int l, int r) {
    int ans = 0;
    for (int i = l; i < r; i++) {
        ans += arr[i];
    }
    return ans;
}

int main() {
    int pid;
    int i;
    //Read standard input
    int n;
    std::cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1) {
        std::cout<< "Error al crear la tubería." << std::endl;
        exit(1);
    }
    
    pid = fork();
    
    if (pid < 0) {
        std::cout<<"Sorry...cannot fork"<<std::endl;
        exit(1);
    }
    else if (pid == 0) {  // Child
        std::cout<<"child: "<<i<<", PID: "<<getpid()<<", Parent PID: "<<getppid()<<std::endl;
        
        int ansSum = sumArr(arr, 0, n);

        close(pipe_fd[0]);  // Stop reading
        write(pipe_fd[1], &ansSum, sizeof(ansSum));  //write
        close(pipe_fd[1]); //Stop writing

        exit(0); 
    }
    else {  // Parent
        wait(NULL); //Wait for childrens
        int ansSum;
        std::cout<<"parent "<<i<<", PID: "<< getpid()<<std::endl;

        close(pipe_fd[1]);  // Close write
        read(pipe_fd[0], &ansSum, sizeof(ansSum));  // Read
        close(pipe_fd[0]);  // Close read

        std::cout<<"Parent ans: "<<ansSum<<std::endl;
    }
    
    return 0;
}