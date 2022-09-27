#include "int128.hpp"
#include "utils/string-math.hpp"
#include <stdarg.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

PixlLibs::BigInt::Int128::Int128(){}

PixlLibs::BigInt::Int128::Int128(PixlLibs::BigInt::Int128& o){
	std::copy(o.bytes, o.bytes+16, bytes);
}

PixlLibs::BigInt::Int128::Int128(std::initializer_list<uint8_t> data){
	uint8_t ind = 15;
	auto byte = data.end();
	byte--;
	for(; byte != data.begin(); byte--){
		if(ind < 0) break;
		bytes[ind] = *byte;
		// printf("%i a\n", *byte);
		ind--;
	}
	bytes[ind] = *byte;
}

std::string PixlLibs::BigInt::Int128::toString(){
	// std::string a = "813274";
	// std::string b = "8374";
	// std::string c = multString(a, b);
	// printf("%s\n", c.data());
	std::string out = "0";
	std::string currentProd;
	uint8_t data[16];
	std::copy(bytes, bytes+16, data);
	
	for(uint8_t currentByte = 0; currentByte < 16; currentByte++){
		std::string currentNum = std::to_string(data[currentByte]);
		for(uint8_t i = 0; i < 15-currentByte; i++)
			currentNum = multString(currentNum, "256");
		out = addString(out, currentNum);
	}
	if(!out.length())
		return "0";
	return out;
}

PixlLibs::BigInt::Int128 PixlLibs::BigInt::Int128::fromString(std::string data){
	PixlLibs::BigInt::Int128 out = *(new PixlLibs::BigInt::Int128());
	uint8_t currentByte = 15;
	std::string quo = data + ""; // quotient
	int rem; // remainder
	while(quo != "0" && currentByte != 0){
		quo = stringDiv(quo, 256, rem);
		// printf("%s, %i\n\n", quo.data(), rem);
		out.bytes[currentByte] = rem;
		currentByte--;
	}
	if(!currentByte)
		out.bytes[currentByte] = rem;
	
	return out;
}

PixlLibs::BigInt::Int128 PixlLibs::BigInt::Int128::operator^(const PixlLibs::BigInt::Int128& o){
	PixlLibs::BigInt::Int128 out = *this;
	for(uint8_t byte = 0; byte < sizeof(out.bytes); byte++){
		out.bytes[byte] = bytes[byte] ^ o.bytes[byte];
	}
	return out;
}

PixlLibs::BigInt::Int128 PixlLibs::BigInt::Int128::operator&(const PixlLibs::BigInt::Int128& o){
	PixlLibs::BigInt::Int128 out = *this;
	for(uint8_t byte = 0; byte < sizeof(out.bytes); byte++){
		out.bytes[byte] = bytes[byte] & o.bytes[byte];
	}
	return out;
}

PixlLibs::BigInt::Int128 PixlLibs::BigInt::Int128::operator<<(unsigned char n){
	PixlLibs::BigInt::Int128 out = *this;
	// unsigned char tmp = 0;
	unsigned char carry = 0;
	while(n > 7){
		unsigned char newBytes[16];
		std::copy(out.bytes+1, out.bytes+17, newBytes);
		newBytes[sizeof(newBytes)-1] = 0;
		std::copy(newBytes, newBytes+16, out.bytes);
		n -= 8;
	}
	if(!n)
		return out;
	
	for(char byte = sizeof(out.bytes)-1; byte >= 0; byte--){
		unsigned char tmp = out.bytes[byte];
		out.bytes[byte] = (out.bytes[byte] << n) | carry;
		carry = tmp >> (8 - n);
	}

	return out;
}

PixlLibs::BigInt::Int128 PixlLibs::BigInt::Int128::operator+(const PixlLibs::BigInt::Int128& o){
	PixlLibs::BigInt::Int128 a = *this;
	PixlLibs::BigInt::Int128 b;
	PixlLibs::BigInt::Int128 carry;
	b = o;
	while(b.toString() != "0"){
		carry = a & b;
		a = a ^ b;
		b = carry << 1;
	}
	return a;
}

PixlLibs::BigInt::Int128 PixlLibs::BigInt::Int128::operator~(){
	PixlLibs::BigInt::Int128 out = *this;
	for(unsigned char i = 0; i < 16; i++){
		out.bytes[i] = ~out.bytes[i];
	}
	return out;
}

void PixlLibs::BigInt::Int128::operator=(const PixlLibs::BigInt::Int128& o){
	std::copy(o.bytes, o.bytes+16, bytes);
	// return *this;
}

PixlLibs::BigInt::Int128 PixlLibs::BigInt::Int128::operator-(PixlLibs::BigInt::Int128& o){
	PixlLibs::BigInt::Int128 a = *this;
	PixlLibs::BigInt::Int128 b = o;
	PixlLibs::BigInt::Int128 c = PixlLibs::BigInt::Int128::fromString("1");
	PixlLibs::BigInt::Int128 d = a + (~b + c);
	return d;
}