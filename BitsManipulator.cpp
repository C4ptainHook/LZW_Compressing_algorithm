#include "BitsManipulator.hpp"

void BitStreamWriter::appendBit(const int bit)
{
    const uint16_t mask = uint16_t(1) << nextBitPos;
    mainBuffer = (mainBuffer & ~mask) | (-bit & mask);
    ++nextBitPos;
}

void BitStreamWriter::appendBuffer(ofstream& file, const uint64_t num, const int bitCount)
{
    assert(bitCount <= 64);
    for (int b = 0; b < bitCount; ++b)
    {
        const uint64_t mask = uint64_t(1) << b;
        if(nextBitPos==8*sizeof(bufferType)) {
            for (int i = 0; i < sizeof(bufferType); ++i) {
                file.put(static_cast<char>(mainBuffer & 0xFF));
                mainBuffer>>=8;
            }
            mainBuffer=0;
            nextBitPos=0;
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

//void BitStreamWriter::appendBuffer(const uint64_t code, const int bitCount)
//{
//    assert(bitCount <= 17);
//    bitBuffer = (bitBuffer << bitCount) | code;
//    bitsInBuffer += bitCount;
//}
//
//uint8_t BitStreamWriter::getByte() {
//    uint8_t byte;
//    if (bitsInBuffer>0 && bitsInBuffer<8)
//    {
//        byte = bitBuffer << (8 - bitsInBuffer);
//    }
//    byte = (bitBuffer >> (bitsInBuffer - 8)) & 0xFF;
//    bitsInBuffer -= 8;
//    return byte;
//}
//
//int BitStreamWriter::size() {
//    return bitsInBuffer;
//}

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
