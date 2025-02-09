#include <iostream>  

double approximatePi(int upper_bound) {
    double pi_approx = 0.0;
    for (int i = 0; i < upper_bound; ++i) {
        double term = 1.0 / ((2*i) + 1); //1 / odd numbers
        if (i % 2 == 0) { //+-
            pi_approx += term;
        } else {
            pi_approx -= term;
        }
    }
    return 4 * pi_approx;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return -1;
    }
    int upper_bound = atoi(argv[1]);

    if (upper_bound <= 0) {
        return 1;
    }

    double pi_value = approximatePi(upper_bound);
    std::cout<<"i: "<<upper_bound<<" pi: "<<pi_value<<std::endl;
    return 0;
}

