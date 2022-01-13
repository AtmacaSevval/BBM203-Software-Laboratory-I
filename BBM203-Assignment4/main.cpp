#include <iostream>
#include "Reading.h"

int main(int argc,char* argv[]) {
    Reading obj;

    if(argc == 4){
        std::string arg2(argv[2]);

        std::string arg3(argv[3]);
        if(arg3 == "-encode"){
            obj.callEncode(arg2);
        }

        else if(arg3 == "-decode"){
            obj.callDecode(arg2);
        }
    }
    else if(argc == 3){
        std::string arg2(argv[2]);
        obj.callCharacter(arg2);
    }

    return 0;
}
