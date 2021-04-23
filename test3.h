#ifndef TEST3_H
#define TEST3_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

#include "graph.h"

void test3(void)
{
    const std::string path = "/home/vorart/workspace/qt projects/DSA_HW_3/input_3.txt";
    std::ifstream in(path);
    assert(in.is_open() && "file is not found");

    Graph<std::string,std::string> graph;
    std::string	line;
    while(getline(in, line,'\n'))
    {

    }
}


#endif // TEST3_H
