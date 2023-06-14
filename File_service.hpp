#include <iostream>
#include <fstream>

namespace fs {
    const std::string format = ".mgzip";
    size_t GetFileSize(std::string filename) {
        std::ifstream file(filename, std::ios::binary);
        if(!file.is_open())
            throw std::runtime_error("File for compression wasn`t opened");
        file.seekg(0, std::ios::end);
        size_t size_of_file = file.tellg();
        file.close();
        return size_of_file;
    }
     std::string GetOutputFileName(std::string input_file_name){
        size_t pos = input_file_name.rfind('.');
        std::string compressed_file_name = input_file_name.substr(0,pos)+format;
        return compressed_file_name;
    }
}

