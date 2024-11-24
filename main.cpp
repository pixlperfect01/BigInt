#include <iostream>
#include "tests.h"
#include "BigInt.h"

#define N_BITS 1024

int main(){
    BigInt<N_BITS> x("10");
    BigInt<N_BITS> y = 3;
    std::cout << x << " ** " << y << " = ";
    std::cout << (std::pow(x, y)) << std::endl;
}
