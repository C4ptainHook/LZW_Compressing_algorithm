#include "LZW_Archiver.hpp"
#include "File_service.hpp"

namespace lzw
{
    void Compress(std::string filename)
    {
        size_t uncompressedSizeBytes = fs::GetFileSize(filename);
        fs::validateReadFile(filename);
        ifstream input_file(filename, ios::binary);
        string output_file_name = fs::GetOutputFileName(filename);
        fs::validateWriteFile(output_file_name);
        ofstream output_file(output_file_name, ios::binary);

        int code = Nil;
        int codeBitsWidth = StartBits;
        Dictionary dictionary;
        BitStreamWriter writer;


        for (; uncompressedSizeBytes > 0; --uncompressedSizeBytes)
        {
            const int value = static_cast<uint8_t>(input_file.get());
            const int index = dictionary.findIndex(code, value);

            if (index != Nil)
            {
                code = index;
                continue;
            }

           writer.appendBuffer(output_file, code, codeBitsWidth);
//
//            while (writer.size() >= 8)
//            {
//                output_file.put(static_cast<char>(writer.getByte()));
//            }

            if (!dictionary.flush(codeBitsWidth))
            {
                dictionary.add(code, value);
            }
            code = value;
        }

        if (code != Nil)
        {
            writer.appendBuffer(output_file, code, codeBitsWidth);;
        }

//        if (writer.size() > 0)
//        {
//            output_file.put(static_cast<char>(writer.getByte()));
//        }
        writer.putResidue(output_file);
        input_file.close();
        output_file.close();
    }

    static void outputByte(int code, const string& _output)
    {
        assert(code >= 0 && code < 256);
        ofstream out(_output,  ios::app);
        out.put(static_cast<char>(code));
        out.close();
    }

    static void outputSequence(const Dictionary & dict, int code, const string&  output, int & firstByte)
    {
        int i = 0;
        uint8_t sequence[MaxDictEntries];
        do
        {
            assert(i < MaxDictEntries - 1 && code >= 0);
            sequence[i++] = dict.entries[code].value;
            code = dict.entries[code].code;
        }
        while (code >= 0);

        firstByte = sequence[--i];
        for (; i >= 0; --i)
        {
            outputByte(sequence[i], output);
        }
    }

    void Decompress(std::string filename)
    {
        int code;
        int prevCode = Nil;
        int firstByte = 0;
        int codeBitsWidth = StartBits;
        fs::validateExtension(filename);
        fs::validateReadFile(filename);
        size_t sizeBits = 8*fs::GetFileSize(filename);
        string output_file = filename + "DECODED.txt";
        fs::validateWriteFile(output_file);
        Dictionary dictionary;
        BitStreamReader reader;
        ifstream input_file(filename, ios::binary);

        while (sizeBits != reader.bitsProcessed()) {
            code = static_cast<int>(reader.readBits(input_file, codeBitsWidth));

            if (prevCode == Nil) {
                outputByte(code, output_file);
                firstByte = code;
                prevCode = code;
                continue;
            }

            if (code >= dictionary.size) {
                outputSequence(dictionary, prevCode, output_file,  firstByte);
                outputByte(firstByte, output_file);
            } else {
                outputSequence(dictionary, code, output_file,  firstByte);
            }

            dictionary.add(prevCode, firstByte);

            if (dictionary.flush(codeBitsWidth)) {
                prevCode = Nil;
            } else {
                prevCode = code;
            }
        }
    }
}