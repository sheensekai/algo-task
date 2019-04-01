#include <iostream>
#include "handmade_graph.h"
#include <fstream>


int main() {
    std::ifstream input("input.txt");
    graph gr;
    std::ofstream output("output.txt");
    output << (gr.game(input) == 1 ? "First" : "Second") << " player wins";

    return 0;
}