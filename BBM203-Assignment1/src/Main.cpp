#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>

#include "ArrayClass.h"
#include "ReadingClass.h"
#include "OutputFile.h"

using namespace std;


int main(int argc, char** argv) {
    strcpy (ReadingClass::deck,argv[1]);
        strcpy (ReadingClass::commands,argv[2]);
strcpy (ReadingClass::output,argv[3]);

    ReadingClass obj;
    obj.readDeck();
    obj.readCommands();
    return 0;
}
