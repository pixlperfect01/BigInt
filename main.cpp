#include <iostream>
#include "BigInt.h"
#include <chrono>

int main(){
    BigInt<64> a = 3;
    BigInt<64> b = 4;
    BigInt<64> c = a + b;

    auto start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            if(j != 0)
                if(BigInt<64>(i%j) != BigInt<64>(i) % BigInt<64>(j))
                    std::cout << (i%j) << " " << i << " " << j << std::endl;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
}
