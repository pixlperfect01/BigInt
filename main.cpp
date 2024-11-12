#include <iostream>
#include "BigInt.h"

int main(){
    BigInt<64> a = 0b1100;
    BigInt<64> b = 0b1011;
    BigInt<64> c;

    std::cout << a.bits << std::endl;
    std::cout << b.bits << std::endl;
    std::cout << c.bits << std::endl;
}