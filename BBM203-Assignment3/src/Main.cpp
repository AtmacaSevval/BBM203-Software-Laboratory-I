
#include "Reading.h"
#include <iostream>
#include <string.h>
using namespace std;


int main(int argc, char** argv) {
	Reading obj;
    strcpy (obj.desks,argv[1]);
    strcpy (obj.packages,argv[2]);
    strcpy (obj.trucks,argv[3]);
    strcpy (obj.missions,argv[4]);
    strcpy (obj.results,argv[5]);

    
    obj.ReadAllFile();
    return 0;
}
