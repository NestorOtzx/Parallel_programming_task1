#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(0)); 

    int n;
    std::cin >> n; 

    std::cout << n << std::endl;

    for (int i = 0; i < n; i++) {
        int num = std::rand() % 100 + 1;
        std::cout << num << std::endl;
    }

    return 0;
}