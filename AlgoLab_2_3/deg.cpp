#include <iostream>
#include <fstream>

struct vertex {
    vertex() :
        deg(0) {}

    int deg;
};

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int V, E;
    input >> V >> E;
    vertex * verts = new vertex[V];

    int out, in;
    for (int i = 0; i < E; ++i) {
        input >> out >> in;
        verts[out - 1].deg++;
        verts[in - 1].deg++;
    }

    for (int i = 0; i < V; i++)
        output << verts[i].deg << " ";

    delete[] verts;
    input.close();
    output.close();

    return 0;
}