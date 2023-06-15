#include "BitsManipulator.hpp"

void BitStreamWriter::appendBit(const int bit)
{
    const uint16_t mask = uint16_t(1) << nextBitPos;
    mainBuffer = (mainBuffer & ~mask) | (-bit & mask);
    --nextBitPos;
}

void BitStreamWriter::appendBuffer(ofstream& file, const uint16_t num, const int bitCount)
{
    const uint16_t leftmask = ~0xFF;
    const uint16_t rightmask = 0xFF;
    assert(bitCount <= 16);
    for (int b = bitCount-1; b >= 0; --b)
    {
        const uint64_t mask = uint64_t(1) << b;
        if(nextBitPos<0) {
            file.put(static_cast<char>((mainBuffer & leftmask)>>8));
            file.put(static_cast<char>(mainBuffer & rightmask));
            mainBuffer=0;
            nextBitPos=8*sizeof(bufferType)-1;
        }
            int bit = !!(num & mask);
            appendBit(bit);
    }
}

void BitStreamWriter::putResidue(ofstream& file) {
    if(nextBitPos!=0){
        mainBuffer<<=(8-nextBitPos);
        file.put(static_cast<char>(mainBuffer));
    }
}
//////////////////////////////////////////////////////////////////////////////////////
//                      Reader for DECOMPRESSION BELOW                              //
/////////////////////////////////////////////////////////////////////////////////////
uint32_t BitStreamReader::readBits(ifstream&  file, const int bitCount) {
    uint32_t code;
    auto loadMoreBits = [&]() {
        char byte;
        if (file.get(byte)) {
            bitBuffer = (bitBuffer << 8) | static_cast<uint8_t>(byte);
            bitsInBuffer += 8;
            numBitsRead += 8;
        } else {
            bitsInBuffer = -1;
        }
    };

    while (bitsInBuffer < bitCount) {
        loadMoreBits();
        if (bitsInBuffer == -1) break;
    }

    code = static_cast<int>((bitBuffer >> (bitsInBuffer - bitCount)) & ((1 << bitCount) - 1));
    bitsInBuffer -= bitCount;
    return code;
}

int BitStreamReader::bitsProcessed() {
    return numBitsRead;
}
