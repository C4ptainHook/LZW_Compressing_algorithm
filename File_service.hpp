#include <iostream>
#include <fstream>

namespace fs {
    static const std::string format = ".Bzip";

    void validateReadFile(const std::string &filename) {
        std::ifstream inputFile(filename);
        if (!inputFile) {
            inputFile.close();
            throw std::runtime_error("ERROR DURING READING ATTEMPT: " + filename + " \n");
        }

        inputFile.close();
    }

    void validateWriteFile(const std::string &filename) {

        std::ofstream outputFile(filename);
        if (!outputFile) {
            outputFile.close();
            throw std::runtime_error("ERROR DURING CREATION: " + filename + " \n");
        }

        outputFile.close();
    }

    size_t GetFileSize(std::string filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open())
            throw std::runtime_error("File for compression wasn`t opened");
        file.seekg(0, std::ios::end);
        size_t size_of_file = file.tellg();
        file.close();
        return size_of_file;
    }

    std::string GetOutputFileName(std::string input_file_name) {
        size_t pos = input_file_name.rfind('.');
        std::string compressed_file_name = input_file_name.substr(0, pos) + format;
        return compressed_file_name;
    }

    void validateExtension(const std::string &filename, bool isInput) {

        std::size_t pos = filename.find_last_of('.');

        if (pos == std::string::npos) {
            throw std::invalid_argument("in filename " + filename +
                                        " there is no extension .myzip\n");
        }

        std::string extension = filename.substr(pos + 1);

        if (extension != "myzip") {
            throw std::invalid_argument("In FILE" + filename +
                                        " INCORRECT EXTENSION" + extension + ", !!!must be .Bzip!!!\n");
        }

    }
}
