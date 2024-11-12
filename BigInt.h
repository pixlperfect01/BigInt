//
// Created by J.R. Williams on 11/12/2024.
//

#ifndef BIGINT_H
#define BIGINT_H
#include <bitset>
#include <cstdint>

template<size_t SIZE>
class BigInt
{
public:
    std::bitset<SIZE> bits;
public:
    BigInt();
    BigInt(const BigInt<SIZE>&);
    BigInt(uint64_t);
    template<size_t SIZE1>
    explicit BigInt(const BigInt<SIZE1>&);

    BigInt<SIZE>& operator=(const BigInt<SIZE>&);
    BigInt<SIZE>& operator=(uint64_t);

    BigInt<SIZE> operator~() const;
    BigInt<SIZE> operator-() const;

    bool operator==(const BigInt<SIZE>&) const;
    bool operator!=(const BigInt<SIZE>&) const;
    bool operator>(const BigInt<SIZE>&) const;
    bool operator<(const BigInt<SIZE>&) const;
    bool operator>=(const BigInt<SIZE>&) const;
    bool operator<=(const BigInt<SIZE>&) const;

    BigInt<SIZE> operator<<(const size_t) const;
    BigInt<SIZE> operator>>(const size_t) const;
    BigInt<SIZE>& operator<<=(const size_t);
    BigInt<SIZE>& operator>>=(const size_t);

    BigInt<SIZE> operator&(const BigInt<SIZE>&) const;
    BigInt<SIZE> operator|(const BigInt<SIZE>&) const;
    BigInt<SIZE> operator^(const BigInt<SIZE>&) const;
    BigInt<SIZE> operator&=(const BigInt<SIZE>&);
    BigInt<SIZE> operator|=(const BigInt<SIZE>&);
    BigInt<SIZE> operator^=(const BigInt<SIZE>&);

    BigInt<SIZE> operator+(const BigInt<SIZE>&) const;
    BigInt<SIZE> operator-(const BigInt<SIZE>&) const;
    BigInt<SIZE>& operator+=(const BigInt<SIZE>&);
    BigInt<SIZE>& operator-=(const BigInt<SIZE>&);

    BigInt<SIZE> operator*(const BigInt<SIZE>&) const;
    BigInt<SIZE> operator/(const BigInt<SIZE>&) const;
    BigInt<SIZE>& operator*=(const BigInt<SIZE>&);
    BigInt<SIZE>& operator/=(const BigInt<SIZE>&);
};

template <size_t SIZE>
BigInt<SIZE>::BigInt()
{
    bits = { 0 };
}

template <size_t SIZE>
BigInt<SIZE>::BigInt(const BigInt<SIZE>& RHS)
{
    bits = RHS.bits;
}

template <size_t SIZE>
BigInt<SIZE>::BigInt(uint64_t RHS)
{
    bits = RHS;
}

template <size_t SIZE>
template <size_t SIZE1>
BigInt<SIZE>::BigInt(const BigInt<SIZE1>& RHS)
{
    bits = { 0 };
    if(SIZE > SIZE1)
    {
        for(unsigned int i = 0; i < SIZE1; i++)
        {
            bits[i] = RHS.bits[i];
        }
    } else {
        for(unsigned int i = 0; i < SIZE; i++)
        {
            bits[i] = RHS.bits[i];
        }
    }
}

template <size_t SIZE>
BigInt<SIZE>& BigInt<SIZE>::operator=(const BigInt<SIZE>&) = default;

template <size_t SIZE>
BigInt<SIZE>& BigInt<SIZE>::operator=(uint64_t RHS)
{
    bits = RHS;
    return *this;
}

template <size_t SIZE>
BigInt<SIZE> BigInt<SIZE>::operator~() const
{
    auto out = *this;
    out.bits.flip();
    return out;
}

template <size_t SIZE>
BigInt<SIZE> BigInt<SIZE>::operator-() const
{
    return ~*this + 1;
}

template <size_t SIZE>
bool BigInt<SIZE>::operator==(const BigInt<SIZE>& RHS) const
{
    return bits == RHS.bits;
}

template <size_t SIZE>
bool BigInt<SIZE>::operator!=(const BigInt<SIZE>& RHS) const
{
    return bits != RHS.bits;
}

template <size_t SIZE>
bool BigInt<SIZE>::operator>(const BigInt<SIZE>& RHS) const
{
    if(bits[SIZE-1] && !RHS.bits[SIZE-1])
        return false;
    if(!bits[SIZE-1] && RHS.bits[SIZE-1])
        return true;
    if(bits[SIZE-1] && RHS.bits[SIZE-1])
        return (-*this) < (-RHS);

    for(size_t i = 0; i < SIZE && i < i+1; i++)
    {
        size_t i1 = SIZE - i - 1;
        if(bits[i1] && !RHS.bits[i1])
            return true;
        if(!bits[i1] && RHS.bits[i1])
            return false;
    }
    return false;
}

template <size_t SIZE>
bool BigInt<SIZE>::operator<(const BigInt<SIZE>& RHS) const
{
    return !(*this > RHS) && !(*this == RHS);
}

template <size_t SIZE>
bool BigInt<SIZE>::operator>=(const BigInt<SIZE>& RHS) const
{
    return (*this > RHS) || (*this == RHS);
}

template <size_t SIZE>
bool BigInt<SIZE>::operator<=(const BigInt<SIZE>& RHS) const
{
    return !(*this > RHS);
}


template <size_t SIZE>
BigInt<SIZE> BigInt<SIZE>::operator<<(const size_t n) const
{
    BigInt<SIZE> out;
    for(unsigned int i = n; i < SIZE && i < i+1; i++)
    {
        out.bits[i] = bits[i - n];
    }

    return out;
}

template <size_t SIZE>
BigInt<SIZE> BigInt<SIZE>::operator>>(const size_t n) const
{
    BigInt<SIZE> out;
    for(unsigned int i = n; i < SIZE && i < i+1; i++)
    {
        out.bits[i - n] = bits[i];
    }

    return out;
}

template <size_t SIZE>
BigInt<SIZE>& BigInt<SIZE>::operator<<=(const size_t n)
{
    bits = (*this << n).bits;
    return *this;
}

template <size_t SIZE>
BigInt<SIZE>& BigInt<SIZE>::operator>>=(const size_t n)
{
    bits = (*this >> n).bits;
    return *this;
}


template <size_t SIZE>
BigInt<SIZE> BigInt<SIZE>::operator&(const BigInt<SIZE>& RHS) const
{
    BigInt<SIZE> out = 0;
    for(unsigned int i = 0; i < SIZE && i < i+1; i++)
        out.bits.set(i, bits[i] & RHS.bits[i]);

    return out;
}

template <size_t SIZE>
BigInt<SIZE> BigInt<SIZE>::operator|(const BigInt<SIZE>& RHS) const
{
    BigInt<SIZE> out = 0;
    for(unsigned int i = 0; i < SIZE && i < i+1; i++)
        out.bits.set(i, bits[i] | RHS.bits[i]);

    return out;
}

template <size_t SIZE>
BigInt<SIZE> BigInt<SIZE>::operator^(const BigInt<SIZE>& RHS) const
{
    BigInt<SIZE> out = 0;
    for(unsigned int i = 0; i < SIZE && i < i+1; i++)
        out.bits.set(i, bits[i] ^ RHS.bits[i]);

    return out;
}

template <size_t SIZE>
BigInt<SIZE> BigInt<SIZE>::operator&=(const BigInt<SIZE>& RHS)
{
    bits = (*this & RHS).bits;
    return *this;
}

template <size_t SIZE>
BigInt<SIZE> BigInt<SIZE>::operator|=(const BigInt<SIZE>& RHS)
{
    bits = (*this | RHS).bits;
    return *this;
}

template <size_t SIZE>
BigInt<SIZE> BigInt<SIZE>::operator^=(const BigInt<SIZE>& RHS)
{
    bits = (*this ^ RHS).bits;
    return *this;
}

template <size_t SIZE>
BigInt<SIZE> BigInt<SIZE>::operator+(const BigInt<SIZE>& RHS) const
{
    BigInt<SIZE> a = *this, b = RHS, carry = 0;

    while(b != 0)
    {
        carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }

    return a;
}

template <size_t SIZE>
BigInt<SIZE> BigInt<SIZE>::operator-(const BigInt<SIZE>& RHS) const
{
    return *this + (~RHS + 1);
}

template <size_t SIZE>
BigInt<SIZE>& BigInt<SIZE>::operator+=(const BigInt<SIZE>& RHS)
{
    bits = (*this + RHS).bits;
    return *this;
}

template <size_t SIZE>
BigInt<SIZE>& BigInt<SIZE>::operator-=(const BigInt<SIZE>& RHS)
{
    bits = (*this - RHS).bits;
    return *this;
}

template <size_t SIZE>
BigInt<SIZE> BigInt<SIZE>::operator*(const BigInt<SIZE>& RHS) const
{
    BigInt<SIZE> a = *this, b = RHS, out = 0;

    while(b != 0)
    {
        if((b & 1) == 1)
        {
            out += a;
        }
        a <<= 1;
        b >>= 1;
    }

    return out;
}

template <size_t SIZE>
BigInt<SIZE> BigInt<SIZE>::operator/(const BigInt<SIZE>& RHS) const
{
    if(RHS == 0)
    {
        throw std::invalid_argument("Divide by zero");
    }



    BigInt<SIZE> n = *this, d = RHS, q = 0;

    bool isNeg = (n < 0) ^ (d < 0);

    if(n < 0)
    {
        n = -n;
    }

    if(d < 0)
    {
        d = -d;
    }
    // n is dividend, d is divisor
    // store the result in q: q = n / d

    // as long as the divisor fits into the remainder there is something to do
    while (n >= d) {
        uint32_t i = 0;
        BigInt<SIZE> d_t = d;
        // determine to which power of two the divisor still fits the dividend
        //
        // i.e.: we intend to subtract the divisor multiplied by powers of two
        // which in turn gives us a one in the binary representation
        // of the result
        while (n >= (d_t << 1) && ++i)
            d_t <<= 1;
        // set the corresponding bit in the result
        q |= BigInt(1) << i;
        // subtract the multiple of the divisor to be left with the remainder
        n -= d_t;
        // repeat until the divisor does not fit into the remainder anymore
    }
    return isNeg ? -q : q;
}

template <size_t SIZE>
BigInt<SIZE>& BigInt<SIZE>::operator*=(const BigInt<SIZE>& RHS)
{
    bits = (*this * RHS).bits;
    return *this;
}

template <size_t SIZE>
BigInt<SIZE>& BigInt<SIZE>::operator/=(const BigInt<SIZE>& RHS)
{
    bits = (*this / RHS).bits;
    return *this;
}



#endif //BIGINT_H
