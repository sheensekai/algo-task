#include <fstream>
#include <vector>
#include <forward_list>
#include <climits>
#define INF LONG_LONG_MAX


int main() {
    std::ifstream input("pathmgep.in");

    int v = 0;
    int start = 0;
    int finish = 0;
    input >> v >> start >> finish;
    --start;
    --finish;
    std::vector<std::vector<int>> adj_mat(v, std::vector<int>(v));

    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            input >> adj_mat[i][j];
        }
    }

    input.close();

    std::vector<long long>dist(v, INF);
    std::vector<bool>color(v);
    dist[start] = 0;

    for (int i = 0; i < v; i++) {
        int vert = -1;
        for (int j = 0; j < v; j++) {
            if (!color[j] && (vert == -1 || dist[j] < dist[vert])) {
                vert = j;
            }
        }

        if (dist[vert] == INF) {
            break;
        }

        color[vert] = true;
        for (int j = 0; j < v; j++) {
            if (vert != j && adj_mat[vert][j] != -1 && dist[j] > dist[vert] + adj_mat[vert][j]) {
                dist[j] = dist[vert] + adj_mat[vert][j];
            }
        }
    }

    std::ofstream output("pathmgep.out");
    if (dist[finish] != INF) {
        output << dist[finish];
    }
    else output << -1;
    output.close();

    return 0;
}