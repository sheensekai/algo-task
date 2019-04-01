#include <iostream>
#include <fstream>

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int n, m;
    input >> n >> m;
    int ** adj = new int * [n];
    for (int k = 0; k < n; k++)
        adj[k] = new int[n];

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++)
            adj[k][i] = 0;
    }

    int i, j;
    for (int k = 0; k < m; k++) {
        input >> i >> j;
        adj[i - 1][j - 1] = 1;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++)
            output << adj[k][i] << " ";
        output << std::endl;
    }

    for (int k = 0; k < n; k++)
        delete[] adj[k];
    delete[] adj;

    input.close();
    output.close();
    return 0;
}