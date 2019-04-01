#include <fstream>
#include <iostream>

int main() {
    std::ifstream input("hamiltonian.in");
    std::ofstream output("hamiltonian.out");
//    std::ifstream input("input.txt");
//    std::ofstream output("output.txt");


    int v_size, e_size;
    int out, in;
    input >> v_size >> e_size;

    struct Vertex {
        int deg_in = 0;
        int deg_out = 0;
    };

    Vertex * verts = new Vertex[v_size];
    for (int i = 0; i < e_size; i++) {
        input >> out;
        input >> in;

        verts[out - 1].deg_out++;
        verts[in - 1].deg_in++;
    }

    in = 0;
    out = 0;
    for(int i = 0; i < v_size; i++) {
        if (!verts[i].deg_out)
            out++;
        if (!verts[i].deg_in)
            in++;
    }

    if (in == 1 && out == 1)
        output << "YES";
    else output << "NO";

    return 0;
}