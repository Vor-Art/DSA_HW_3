#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

#include "graph.h"
#include "test1.h"
#include "test2.h"
#include "test3.h"


int main()
{

    test1(); // edgeFrom, edgeTo, transpose;
    test2(); // from input.txt (according to 2.2)
    test3();

    return 0;
}
