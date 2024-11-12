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

    bool operator==(BigInt<SIZE>&) const;
    bool operator!=(BigInt<SIZE>&) const;

    BigInt<SIZE> operator&(const BigInt<SIZE>&) const;
    BigInt<SIZE> operator|(const BigInt<SIZE>&) const;
    BigInt<SIZE> operator^(const BigInt<SIZE>&) const;
    BigInt<SIZE> operator&=(const BigInt<SIZE>&);
    BigInt<SIZE> operator|=(const BigInt<SIZE>&);
    BigInt<SIZE> operator^=(const BigInt<SIZE>&);

    BigInt<SIZE> operator+(const BigInt<SIZE>&) const;
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
bool BigInt<SIZE>::operator==(BigInt<SIZE>& RHS) const
{
    return bits == RHS.bits;
}

template <size_t SIZE>
bool BigInt<SIZE>::operator!=(BigInt<SIZE>& RHS) const
{
    return bits != RHS.bits;
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
        // b = carry << 1;
    }

    return a;
}


#endif //BIGINT_H
