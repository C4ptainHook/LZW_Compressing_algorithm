#include "Dictionary.hpp"
#include <iostream>
#include <fstream>

using namespace std;

class BitStreamWriter final
{
private:
    uint64_t bitBuffer = 0;
    int bitsInBuffer = 0;
public:
    BitStreamWriter()=default;
    void appendBuffer(uint64_t code, int bitCount);
    uint8_t getByte();
    int size();
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
    int bitsProcessed();
};