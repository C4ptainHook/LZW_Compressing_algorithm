#include "LZW_Archiver.hpp"
#include "File_service.hpp"

int main(int argc, char* argv[]) {
   std::string action = fs::validateArguments(argc, argv);
   if(action=="--compress")
   {
       for (int i = 2; i < argc; ++i) {
           lzw::Compress(argv[i]);
       }
   }
   else if(action=="--decompress")
   {
       for (int i = 2; i < argc; ++i) {
           lzw::Decompress(argv[i]);
       }
   }
}
