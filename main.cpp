#include "LZW_Archiver.hpp"
#include <functional>

int main(int argc, char* argv[]) {
    std::string cmp = "--compress";
    std::string dcmp = "--decompress";

    std::function action = [=] (int argc, char* argv[]){
        if(argc<3){
            throw runtime_error("Too few arguments");
        }
        if(argv[1]!=cmp&&argv[1]!=dcmp)
        {throw runtime_error("Program does not support "+string(argv[1])+"argument");}
        return argv[1];
    };

   if(action(argc,argv)==cmp)
   {
       for (int i = 2; i < argc; ++i) {
           lzw::Compress(argv[i]);
       }
   }
   else if(action(argc,argv)==dcmp)
   {
       for (int i = 2; i < argc; ++i) {
           lzw::Decompress(argv[i]);
       }
   }
}
