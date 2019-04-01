#include <fstream>
#include <vector>
#include <forward_list>
#include <climits>
#define INF INT_MAX


struct Edge {
    Edge(int vert, int w) :
            vert(vert),
            w(w) {}
    int vert;
    long long w;
};

struct Vertex {
    int pos = 0;
    bool inQ = true;
    long long dist = INF;
    std::forward_list<Edge> adj_list_;
};

int main() {
    std::ifstream input("pathsg.in");
    std::ofstream output("pathsg.out");

    int v, e;
    input >> v >> e;
    std::vector<Vertex> verts(v);

    int out = 0;
    int in = 0;
    long long w = 0;
    for (int i = 0; i < e; ++i) {
        input >> out;
        input >> in;
        input >> w;
        --out;
        --in;
        if (out == in)
            continue;
        verts[out].adj_list_.emplace_front(in, w);
    }

    for (int k = 0; k < v; k++) {
        std::vector<bool> color(v);
        for (int i = 0; i < v; ++i)
            verts[i].dist = INF;
        verts[k].dist = 0;

        for (int i = 0; i < v; i++) {
            int vert = -1;
            for (int j = 0; j < v; j++) {
                if (!color[j] && (vert == -1 || verts[j].dist < verts[vert].dist)) {
                    vert = j;
                }
            }

            if (verts[vert].dist == INF) {
                break;
            }

            color[vert] = true;

            for (auto it = verts[vert].adj_list_.begin(); it != verts[vert].adj_list_.end(); it++) {
                Vertex *in_vert = &verts[it->vert];
                long long weight = it->w;
                if (in_vert->inQ && (verts[vert].dist + weight < in_vert->dist)) {
                    in_vert->dist = verts[vert].dist + weight;
                }
            }
        }

        for (int i = 0; i < v; i++)
            output << verts[i].dist << " ";
        output << std::endl;
    }

}