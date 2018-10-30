#include <string>

std::string getCmdOption(int argc, char *argv[], const std::string& option);

std::string getCmdOption(int argc, char* argv[], const std::string& option){
    std::string cmd;
     for( int i = 1; i < argc; ++i){
          std::string arg = argv[i];
          if(0 == arg.find(option)){
               std::size_t found = arg.find_last_of(option);
               cmd =arg.substr(found + 1);
               return cmd;
          }
     }
     return cmd;
}
