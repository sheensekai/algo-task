#include <iostream>
#include <fstream>

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int n, m;
    input >> n >> m;

    int ** adj = new int * [n];
    for (int i = 0; i < n; i++)
        adj[i] = new int[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;
    }

    int i, j;
    for (int k = 0; k < m; k++) {
        input >> i >> j;
        if (i == j)
            adj[i - 1][j - 1]++;
        else {
            adj[i - 1][j - 1]++;
            adj[j - 1][i - 1]++;
        }
    }

    bool no_paral = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (adj[i][j] > 1) {
                no_paral = false;
                break;
            }
    }

    if (no_paral)
        output << "NO";
    else output << "YES";

    for (int i = 0; i < n; i++)
        delete[] adj[i];
    delete[] adj;

    input.close();
    output.close();
    return 0;
}