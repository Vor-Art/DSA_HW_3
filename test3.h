#ifndef TEST3_H
#define TEST3_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

#include "networkgraph.h"
using std::cin;
void test3(void)
{
    std::cout << "start"  << std::endl;
    const std::string file_path = "/home/vorart/workspace/qt projects/DSA_HW_3/CodeForce1_2.txt";
    std::ifstream cin(file_path);
    assert(cin.is_open() && "file is not found");
    std::stringstream stream;
    NWG::NetWorkGraph<int> graph;
    uint32_t N; uint32_t M;
    cin >> N >> M;
    for(size_t i=1; i <= N; i++) graph.addVertex(i);
    for(size_t i=0; i < M; i++){
        int V1,V2,L,B;
        cin>>V1>>V2>>L>>B;
        auto from =  graph.addVertex(V1);
        auto to =  graph.addVertex(V2);
        graph.addEdge(from, to, NWG::Wire(L,B));
    }
    int S, F, min;
    cin >> S >> F >> min;
    auto source =  graph.findVertex(S);
    auto target =  graph.findVertex(F);
    auto path = graph.findMinPathWithMinBandwidth(source, target, min);
    if(path.second.empty()){
        stream<<"IMPOSSIBLE"<<std::endl;
    }else{
        stream<< path.second.size() <<" "<< path.first.length <<" "<< path.first.bwidth <<std::endl;
        for(const auto& vertex :path.second)
            stream<<vertex<<" ";
        stream<<std::endl;
    }

    std::ofstream fout("output.txt");
    fout << stream.str();
    fout.close();
    std::cout << stream.str();
    std::cout << "end \n";
}


#endif // TEST3_H
