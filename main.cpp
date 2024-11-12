#include <iostream>
#include "BigInt.h"

int main(){
    BigInt<64> a = 3;
    BigInt<64> b = 4;
    BigInt<64> c = a + b;

    for(int i = -100; i < 100; i++)
    {
        for(int j = -100; j < 100; j++)
        {
            if(j != 0)
                if(BigInt<64>(i/j) != BigInt<64>(i) / BigInt<64>(j))
                    std::cout << (i/j) << " " << i << " " << j << std::endl;
        }
    }
}
