#pragma once

#include <cstdint>
#include <string>
#include <initializer_list>

namespace PixlLibs {
	namespace BigInt {
		class Int128 {
		public:
			uint8_t bytes[16] = {0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0};
			Int128();
			Int128(Int128& o);
			// Int128(unsigned char data[]);
			Int128(std::initializer_list<uint8_t> data);
			std::string toString();
			Int128 operator+(const Int128& o);
			Int128 operator-(Int128& o);
			Int128 operator^(const Int128& o);
			Int128 operator&(const Int128& o);
			Int128 operator<<(unsigned char n);
			Int128 operator~();
			void operator=(const Int128& o);
			static Int128 fromString(std::string s);
		};
	}
}