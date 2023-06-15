#pragma once
#include "Dictionary.hpp"
#include <iostream>
#include <fstream>

using namespace std;

typedef uint16_t bufferType;

class BitStreamWriter final
{
private:
    bufferType mainBuffer = 0;
    int nextBitPos = 8*sizeof(bufferType)-1;
    void appendBit(int bit);
public:
    BitStreamWriter()=default;
    void appendBuffer(ofstream&  file, uint16_t code, int bitCount);
    void putResidue(ofstream& file);
};

class BitStreamReader final
{
private:
    uint64_t bitBuffer = 0;
    int bitsInBuffer = 0;
    int numBitsRead = 0;
public:
    BitStreamReader()=default;
    uint32_t readBits(ifstream& file, int bitCount);
    int bitsProcessed() const;
};