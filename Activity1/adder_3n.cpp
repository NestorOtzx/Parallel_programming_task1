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
    nChilds = std::min(nChilds, (int)(sizeof(arr)/sizeof(int))); //if there are less than nChild numbers, then there will be that same amount of childs
    
    int arr [] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

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
        float lenArr = sizeof(arr)/4;
        int lenSubArr = ceil(lenArr/nChilds);
        int ansSum = sumArr(arr, lenSubArr*i, std::min(lenSubArr*i+lenSubArr, (int)lenArr));

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
        close(pipe_fd[0]);  // Stop

        std::cout << "Ans: " << totalSum << std::endl;
    }
    return 0;
}