#include "LZW_Archiver.hpp"

int main(int argc, char* argv[]) {
    std::string filename_for_comp = "C:/Users/boyko/Desktop/WolfCODE.txt";
    std::string filename_for_decomp = "C:/Users/boyko/Desktop/WolfCODE.mgzip";
    lzw::Compress(filename_for_comp);
    lzw::Decompress(filename_for_decomp);
}
