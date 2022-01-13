#include <iostream>
#include <fstream>
#include "CommandReading.h"
#include "LibrarySystem.h"
#include <string.h>

std::ofstream outputFile;

int main(int argc, char** argv) {
    strcpy (CommandReading::commands,argv[1]);
    outputFile.open(argv[2]);
    CommandReading obj;
    obj.reading();

    return 0;
}