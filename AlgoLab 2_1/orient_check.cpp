#include <iostream>
#include <fstream>

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int n;
    input >> n;
    int ** adj = new int * [n];

    for (int i = 0; i < n; i++)
        adj[i] = new int[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            input >> adj[i][j];
    }

    bool not_orient = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j && adj[i][j] == 1 || adj[i][j] != adj[j][i]) { // simple graph check
                not_orient = false;
                break;
            }
        }
    }

    if (not_orient)
        output << "YES" << std::endl;
    else output << "NO" << std::endl;

    for (int i = 0; i < n; i++)
        delete[] adj[i];
    delete[] adj;

    input.close();
    output.close();
    return 0;
}