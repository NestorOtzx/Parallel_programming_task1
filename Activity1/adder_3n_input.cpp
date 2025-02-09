#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <cmath>
#include <algorithm>   

int sumArr(int arr[], int l, int r) {
    int ans = 0;
    for (int i = l; i < r; i++) {
        ans += arr[i];
    }
    return ans;
}

int main() {
    int pid, i = 0, pipe_fd[2], nChilds = 3;
    
    //Read standard input
    int n;
    std::cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    nChilds = std::min(nChilds, n); //if there are less than nChild numbers, then there will be that same amount of childs

    if (pipe(pipe_fd) == -1) {
        std::cout << "Error al crear la tubería." << std::endl; exit(1);
    }

    for(i = 0; i<nChilds; i++) //Create nChilds
    {
        pid = fork();
        if (pid < 0) { return -1; }
        else if (pid == 0) { break; }
    }
    
    if (pid == 0) {  // Child
        std::cout<<"child fork result:" <<pid<<" pid:" << getpid() <<" ppid: "<<getppid()<<" cycle id: "<<i<<std::endl;
        
        //split task in the nChilds
        int lenSubArr = ceil((float)n/(float)nChilds);
        int ansSum = sumArr(arr, lenSubArr*i, std::min(lenSubArr*i+lenSubArr, n));

        close(pipe_fd[0]);  // Stop reading
        write(pipe_fd[1], &ansSum, sizeof(ansSum));  //write
        close(pipe_fd[1]); //Stop writing

        exit(0); 
    }
    else {  // Parent
        std::cout<<"parent fork result:" <<pid<<" pid:" << getpid() <<" ppid: "<<getppid()<<" cycle id: "<<i<<std::endl;

        int totalSum = 0;

        close(pipe_fd[1]);  // Stop write
        for (int j = 0; j < nChilds; j++) {
            int ansSum;
            read(pipe_fd[0], &ansSum, sizeof(ansSum));  // Read 
            totalSum += ansSum;
        }
        close(pipe_fd[0]);  // Stop read

        std::cout << "Ans: " << totalSum << std::endl;
    }
    return 0;
}