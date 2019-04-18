#include <vector>
#include <iostream>
#include <fstream>

bool kuhn(int vert, std::vector<bool> &visited,
          std::vector<std::vector<int>> &adj,
          std::vector<int> &mt);

int main() {
    std::ifstream input("matching.in");

    
    int v, v2, e;
    input >> v >> v2 >> e;
    std::vector<std::vector<int>> adj(v);

    int out, in;
    for (int i = 0; i < e; i++) {
        input >> out >> in;
        adj[out - 1].push_back(in - 1);
    }

    input.close();

    std::vector<int> mt(v2, -1);
    std::vector<bool> visited(v);
    int result = 0;
    for (int i = 0; i < v; ++i) {
        for (int j = 0; j < visited.size(); ++j)
            visited[j] = false;

        if (kuhn(i, visited, adj, mt))
            result++;
    }

    std::ofstream output("matching.out");
    output << result;
    output.close();

    return 0;
}

bool kuhn(int vert, std::vector<bool> &visited,
          std::vector<std::vector<int>> &adj,
          std::vector<int> &mt) {
    if (visited[vert]) {
        return false;
    }
    visited[vert] = true;

    for (int i = 0; i < adj[vert].size(); ++i) {
        int weight = adj[vert][i];
        if (mt[weight] == -1 || kuhn(mt[weight], visited, adj, mt)) {
            mt[weight] = vert;
            return true;
        }
    }

    return false;
}