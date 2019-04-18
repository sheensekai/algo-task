#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#define INF (INT_MAX)

struct AdjEdge {
    AdjEdge(int vert, int out_vert, int cap, bool real) :
            vertex(vert),
            capacity(cap),
            real_edge(real),
            flow(0),
            out_vertex(out_vert),
            other_edge(-1) {}

    ~AdjEdge() = default;

    int vertex;
    int out_vertex;
    int capacity;
    int flow;
    bool real_edge;
    int other_edge;
};

struct Vertex {
    bool visited = false;
    AdjEdge *parent = nullptr;
    int pos = -1;
    int dist = INF;
    int real_ptr = 0;
    int rev_ptr = 0;
    std::vector<AdjEdge> adj_real;
    std::vector<AdjEdge> adj_rev;
};

int DinitzBFS(std::vector<Vertex> &verts, int s, int t);

int DinitzDFS(std::vector<Vertex> &verts, int s, int t);

int DinitzDFSVisit(std::vector<Vertex> &verts, int v, int t, int minC);

int DinitzMaxFlow(std::vector<Vertex> &verts, int s, int t);

int main() {
    std::ifstream input("decomposition.in");

    int v, e;
    input >> v >> e;

    int start = 0;
    int finish = v - 1;

    int out, in, capacity;
    std::vector<Vertex> verts;
    verts.resize(v);
    for (int i = 0; i < v; ++i)
        verts[i].pos = i;
    for (int i = 0; i < e; ++i) {
        input >> out >> in >> capacity;
        verts[out - 1].adj_real.emplace_back(in - 1, out - 1, capacity, true);
        verts[in - 1].adj_rev.emplace_back(out - 1, in - 1, 0, false);

        verts[in - 1].adj_rev.back().other_edge =
                verts[out - 1].adj_real.size() - 1;
        verts[out - 1].adj_real.back().other_edge =
                verts[in - 1].adj_rev.size() - 1;
    }
    input.close();

    std::ofstream output("maxflow.out");
    int maxflow = DinitzMaxFlow(verts, start, finish);
    output << maxflow;
    output.close();

    for (Vertex& vert : verts) {
        vert.adj_real.clear();
        vert.adj_rev.clear();
    }

    return 0;
}

int DinitzMaxFlow(std::vector<Vertex> &verts, int s, int t) {
    int maxflow = 0;
    while (DinitzBFS(verts, s, t)) {
        for (Vertex &vert : verts) {
            vert.real_ptr = 0;
            vert.rev_ptr = 0;
        }

        int flow = DinitzDFS(verts, s, t);
        while (flow) {
            maxflow += flow;
            flow = DinitzDFS(verts, s, t);
        }
    }

    return maxflow;
}

int DinitzBFS(std::vector<Vertex> &verts, int s, int t) {
    for (Vertex &vert : verts) {
        vert.dist = INF;
        vert.visited = false;
        vert.parent = nullptr;
    }
    verts[s].dist = 0;
    std::queue<Vertex *> queue;
    queue.push(&verts[s]);

    while (!queue.empty()) {
        Vertex *vert = queue.front();
        queue.pop();

        for (AdjEdge &edge : vert->adj_real) {
            if (verts[edge.vertex].visited || !(edge.capacity - edge.flow))
                continue;

            verts[edge.vertex].visited = true;
            verts[edge.vertex].dist = vert->dist + 1;
            queue.push(&verts[edge.vertex]);
        }

    }

    return verts[t].visited;
}

int DinitzDFS(std::vector<Vertex> &verts, int s, int t) {
    return DinitzDFSVisit(verts, s, t, INF);
}

int DinitzDFSVisit(std::vector<Vertex> &verts, int v, int t, int minC) {
    if (v == t || minC == 0)
        return minC;

    Vertex &vert = verts[v];
    for (; vert.real_ptr < vert.adj_real.size(); ++vert.real_ptr) {
        AdjEdge &edge = vert.adj_real[vert.real_ptr];
        if (vert.dist + 1 == verts[edge.vertex].dist) {
            int flow = DinitzDFSVisit(verts, edge.vertex, t,
                                      (minC < edge.capacity - edge.flow ? minC : edge.capacity - edge.flow));
            if (flow) {
                edge.flow += flow;
                verts[edge.vertex].adj_rev[edge.other_edge].flow -= flow;
                return flow;
            }
        }
    }

    for (; vert.rev_ptr < vert.adj_rev.size(); ++vert.rev_ptr) {
        AdjEdge &edge = vert.adj_rev[vert.real_ptr];
        if (vert.dist + 1 == verts[edge.vertex].dist + 1) {
            int flow = DinitzDFSVisit(verts, edge.vertex, t,
                                      (minC < edge.capacity - edge.flow ? minC : edge.capacity - edge.flow));
            if (flow) {
                edge.flow += flow;
                verts[edge.vertex].adj_real[edge.other_edge].flow -= flow;
                return flow;
            }
        }
    }

    return 0;
}