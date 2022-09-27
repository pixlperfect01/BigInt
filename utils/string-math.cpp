#include "string-math.hpp"
#include <string>
#include <vector>
#include <algorithm>

std::string subtractString(std::string a, std::string b){
	std::string out;
	std::string c;
	std::string d;
	if(a.length() >= b.length()){
		c = a;
		d = b;
	} else {
		c = b;
		d = a;
	}
	
	unsigned short borrow = 0;

	while(c.length() > d.length()){
		d = "0" + d;
	}
	
	c = std::string(c.rbegin(), c.rend());
	d = std::string(d.rbegin(), d.rend());
	// printf("%u, %u\n", c.length(), d.length());
	
	for(unsigned long i = 0; i < d.length(); i++){
		char num = (c[i]-'0') - (d[i]-'0');
		if(num < 0){
			c[i+1] -= 1;
			num += 10;
		}
		std::string numS = std::to_string(num);
		if(num < 10)
			numS = "0" + numS;
		out += numS[1];
	}

	out = std::string(out.rbegin(), out.rend());
	unsigned long lastLeadingZero = 0;
	for(char cur : out){
		if(cur != '0')
			break;
		lastLeadingZero++;
	}
	out = out.substr(lastLeadingZero, out.length()-lastLeadingZero);
	return out;
}

std::string addString(std::string a, std::string b){
	std::string out;
	std::string c;
	std::string d;
	if(a.length() > b.length()){
		c = a;
		d = b;
	} else {
		c = b;
		d = a;
	}
	
	unsigned short carry = 0;

	while(c.length() > d.length()){
		d = "0" + d;
	}
	
	c = std::string(c.rbegin(), c.rend());
	d = std::string(d.rbegin(), d.rend());
	// printf("%u, %u\n", c.length(), d.length());
	
	for(unsigned long i = 0; i < d.length(); i++){
		unsigned char num = (c[i]-'0') + (d[i]-'0') + carry;
		std::string numS = std::to_string(num);
		if(num < 10)
			numS = "0" + numS;
		carry = numS[0] - '0';
		out += numS[1];
	}

	out = std::string(out.rbegin(), out.rend());
	unsigned long lastLeadingZero = 0;
	for(char cur : out){
		if(cur != '0')
			break;
		lastLeadingZero++;
	}
	out = out.substr(lastLeadingZero, out.length()-lastLeadingZero);
	return out;
}

std::string multString1(std::string a, char b){
	std::string out;
	unsigned char fac = b - '0';
	unsigned char carry = 0;
	std::string c = "" + a;
	std::reverse(c.begin(), c.end());
	for(char cur : c){
		unsigned char prod = (cur - '0') * fac + carry;
		std::string prodS = std::to_string(prod);
		if(prod < 10)
			prodS = "0" + prodS;
		out += prodS[1];
		carry = prodS[0] - '0';
	}
	out += std::to_string(carry);
	std::reverse(out.begin(), out.end());
	unsigned long lastLeadingZero = 0;
	for(char cur : out){
		if(cur != '0')
			break;
		lastLeadingZero++;
	}
	// out = out.substr(lastLeadingZero, out.length()-lastLeadingZero);
	return out;
}

std::string multString(std::string a, std::string b){
	std::string out = "0";
	std::string c;
	std::string d;
	std::vector<std::string> ims; // list of intermediates
	std::string im; // current intermediate
	if(a.length() > b.length()){
		c = "" + a;
		d = "" + b;
	} else {
		c = "" + b;
		d = "" + a;
	}

	// c = "0" + c;
	// d = "0" + c;

	unsigned char carry = 0;
	unsigned long l1 = c.length();
	std::string zeroAcc = "";
	c = std::string(c.rbegin(), c.rend());
	for(unsigned long i1 = 0; i1 < l1; i1++){
		// printf("%s, %c\n", d.data(), c[i1]);
		im = multString1(d, c[i1]) + zeroAcc;
		// printf("%s\n", im.data());
		zeroAcc += "0";
		ims.push_back(im);
	}

	unsigned long numDigits = ims.back().length();

	for(auto& s : ims){
		// printf("%s\n", s.data());
		for(unsigned long z = 0; z < numDigits-s.length(); z++){
			// printf("0");
		}
		// printf("%u, %u\n", out.length(), s.length());
		out = addString(out, s);
	}

	return out;
}

std::string stringDiv(std::string number, int divisor, int &rem)
{
    // As result can be very large store it in string
    std::string ans;
 
    // Find prefix of number that is larger
    // than divisor.
    int idx = 0;
    int temp = number[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (number[++idx] - '0');
 
    // Repeatedly divide divisor with temp. After
    // every division, update temp to include one
    // more digit.
    while (number.size() > idx) {
        // Store result in answer i.e. temp / divisor
        ans += (temp / divisor) + '0';
 
        // Take next digit of number
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    }
	
	rem = std::stoi(subtractString(number, multString(ans, std::to_string(divisor))));
	
    // If divisor is greater than number
    if (ans.length() == 0)
        return "0";
	
	// printf("%i\n", rem);
 
    // else return ans
    return ans;
}

std::string stringDiv(std::string a, int b){
	int tmp;
	return stringDiv(a, b, tmp);
}

std::string stringPow(std::string x, unsigned long y){
	std::string out = "1";
	for(unsigned long i = 0; i < y; i++){
		out = multString(out, x);
	}
	return out;
}