#include <iostream>
#include <fstream>
#include <queue>
#include <forward_list>

struct vertex {
    bool visited = false;
    int dist = -1;
    std::forward_list<int> adj;
};

int bfs(vertex * verts, int n);

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    int m, n;
    input >> n >> m;
    vertex verts[n];

    int i, j;
    for (int k = 0; k < m; k++) {
        input >> i >> j;
        verts[i - 1].adj.push_front(j - 1);
        if (i != j)
            verts[j - 1].adj.push_front(i - 1);
    }

    bfs(verts, n);

    for (int k = 0; k < n; k++)
        output << verts[k].dist << " ";

    input.close();
    output.close();
    return 0;
}


int bfs(vertex *verts, int n) {
    std::queue<int> queue;

    int vert = 0;
    verts[vert].visited = true;
    verts[vert].dist = 0;
    queue.push(vert);

    int comp;
    while (!queue.empty()) {
        vert = queue.front();
        queue.pop();

        while (!verts[vert].adj.empty()) {
            comp = verts[vert].adj.front();
            verts[vert].adj.pop_front();

            if (!verts[comp].visited) {
                verts[comp].visited = true;
                verts[comp].dist = verts[vert].dist + 1;
                queue.push(comp);
            }

        }

    }

    return 0;
}