#include <iostream>
#include "PixlLibs.hpp"
#include "int128.hpp"
#include "utils/string-math.hpp"

int main(){
	PixlLibs::BigInt::Int128 a;
	a = PixlLibs::BigInt::Int128::fromString("1");
	PixlLibs::BigInt::Int128 b;
	b = PixlLibs::BigInt::Int128::fromString("2");
	PixlLibs::BigInt::Int128 c;
	c = a - b;
	printf("NUMBER: %s\n\n", c.toString().data());
	for(char i = 0; i < 16; i++){
		printf("%u\n", c.bytes[i]);
	}
	//18446744073709551616n
	//
	// printf("%s a\n", stringDiv("1579", 6).data());
}