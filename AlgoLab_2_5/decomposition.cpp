#include <iostream>
#include <fstream>
#include <vector>
#include <forward_list>
#include <queue>
#include <stack>
#include <climits>
#define INF (INT_MAX / 2)

struct AdjEdge {
    AdjEdge(int pos, int vert, int out_vert, int cap, bool real) :
            vertex(vert),
            capacity(cap),
            capacity_copy(cap),
            real_edge(real),
            flow(0),
            pos(pos),
            out_vertex(out_vert),
            other_edge(-1) {}

    int vertex;
    int out_vertex;
    int capacity;
    int capacity_copy;
    int flow;
    int pos;
    bool real_edge;
    int other_edge;
};

struct Vertex {
    bool visited = false;
    AdjEdge * parent = nullptr;
    int pos = -1;
    int dist = 0;
    int real_ptr = 0;
    int rev_ptr = 0;
    std::vector<AdjEdge> adj_real;
    std::vector<AdjEdge> adj_rev;
};

struct Path {
    Path() :
            len(0),
            flow() {}
    std::vector<int> edges;
    int len;
    int flow;
};

int DinitzBFS(std::vector<Vertex> &verts);

int DinitzDFS(std::vector<Vertex> &verts);

int DinitzDFSVisit(std::vector<Vertex> &verts, int v, int minC);

int DinitzMaxFlow(std::vector<Vertex> &verts);

int FullDecomposition(std::vector<Vertex> &verts, std::vector<Path> &paths);

int FindPath(std::vector<Vertex> &verts, std::vector<Path> &paths);

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);

    std::ifstream input("decomposition.in");
    if (!input.is_open()) {
        std::cout << "Didn't open";
        return 1;
    }

    int v, e;
    input >> v >> e;

    int out, in, capacity;
    std::vector<Vertex> verts(v);
    for (int i = 0; i < v; ++i)
        verts[i].pos = i;
    for (int i = 0; i < e; ++i) {
        input >> out >> in >> capacity;
        verts[out - 1].adj_real.emplace_back(i, in - 1, out - 1, capacity, true);
        verts[in - 1].adj_rev.emplace_back(i, out - 1, in - 1, 0, false);

        verts[in - 1].adj_rev.back().other_edge =
                verts[out - 1].adj_real.size() - 1;
        verts[out - 1].adj_real.back().other_edge =
                verts[in - 1].adj_rev.size() - 1;
    }
    input.close();

    int max_flow = DinitzMaxFlow(verts);
    std::vector<Path> paths;
    int size = FullDecomposition(verts, paths);

    std::ofstream output("decomposition.out");
    output << size << '\n';
    for (int i = 0; i < size; ++i) {
        output << paths[i].flow << " ";
        output << paths[i].len << " ";

        for (int j = paths[i].len - 1; j >= 0; --j) {
            output << paths[i].edges[j] + 1 << " ";
        }

        output << '\n';
    }

    output.close();

    return 0;
}

int DinitzMaxFlow(std::vector<Vertex> &verts) {
    int maxflow = 0;
    while (DinitzBFS(verts)) {
        for (Vertex &vert : verts) {
            vert.real_ptr = 0;
            vert.rev_ptr = 0;
        }

        int flow = DinitzDFS(verts);
        while (flow) {
            maxflow += flow;
            flow = DinitzDFS(verts);
        }

    }

    return maxflow;
}

int DinitzBFS(std::vector<Vertex> &verts) {
    for (Vertex &vert : verts) {
        vert.dist = INF;
        vert.visited = false;
    }

    verts[0].dist = 0;
    verts[0].visited = true;
    
    int last = verts.size() - 1;
    std::queue<Vertex *> queue;
    queue.push(&verts[0]);

    while (!queue.empty()) {
        Vertex *vert = queue.front();
        queue.pop();

        for (AdjEdge &edge : vert->adj_rev) {
            if (!(edge.capacity - edge.flow) || verts[edge.vertex].visited)
                continue;

            verts[edge.vertex].dist = vert->dist + 1;
            verts[edge.vertex].visited = true;
            queue.push(&verts[edge.vertex]);
        }

        for (AdjEdge &edge : vert->adj_real) {
            if (!(edge.capacity - edge.flow) || verts[edge.vertex].visited)
                continue;

            verts[edge.vertex].dist = vert->dist + 1;
            verts[edge.vertex].visited = true;
            queue.push(&verts[edge.vertex]);
        }

    }

    return verts[last].visited;
}

int DinitzDFS(std::vector<Vertex> &verts) {
    return DinitzDFSVisit(verts, 0, INF);
}

int DinitzDFSVisit(std::vector<Vertex> &verts, int v, int minC) {
    if (v == (verts.size() - 1) || minC == 0)
        return minC;

    Vertex &vert = verts[v];
    for (; vert.rev_ptr < vert.adj_rev.size(); ++vert.rev_ptr) {
        AdjEdge &edge = vert.adj_rev[vert.rev_ptr];
        if (!(edge.capacity - edge.flow))
            continue;
        if ((vert.dist + 1) == verts[edge.vertex].dist) {
            int flow = DinitzDFSVisit(verts, edge.vertex,
                                      (minC < edge.capacity - edge.flow ? minC : edge.capacity - edge.flow));
            if (flow) {
                edge.flow += flow;
                verts[edge.vertex].adj_real[edge.other_edge].flow -= flow;
                return flow;
            }
        }
    }

    for (; vert.real_ptr < vert.adj_real.size(); ++vert.real_ptr) {
        AdjEdge &edge = vert.adj_real[vert.real_ptr];
        if (!(edge.capacity - edge.flow))
            continue;
        if ((vert.dist + 1) == verts[edge.vertex].dist) {
            int flow = DinitzDFSVisit(verts, edge.vertex,
                                      (minC < edge.capacity - edge.flow ? minC : edge.capacity - edge.flow));
            if (flow) {
                edge.flow += flow;
                verts[edge.vertex].adj_rev[edge.other_edge].flow -= flow;
                return flow;
            }
        }
    }

    return 0;
}

int FullDecomposition(std::vector<Vertex> &verts, std::vector<Path> &paths) {
    int last = verts.size() - 1;
    for (Vertex &vert : verts) {
        vert.parent = nullptr;
    }

    while (true) {
        int flow = FindPath(verts, paths);
        if (!flow)
            return paths.size();

        paths.emplace_back();
        paths.back().flow = flow;
        AdjEdge *edge = verts[last].parent;
        while (edge != nullptr) {
            paths.back().edges.push_back(edge->pos);
            paths.back().len += 1;
            edge->flow -= flow;
            Vertex &tmp = verts[edge->out_vertex];
            edge = verts[edge->out_vertex].parent;
        }
    }
}

int FindPath(std::vector<Vertex> &verts, std::vector<Path> &paths) {

    int pos = 0;
    int last = verts.size() - 1;
    AdjEdge *next_edge = nullptr;
    int min_flow = INF;
    while (true) {

        for (AdjEdge &edge : verts[pos].adj_real) {
            if (edge.flow) {
                next_edge = &edge;
                break;
            } else next_edge = nullptr;
        }
        if (next_edge == nullptr)
            return 0;
        if (min_flow > next_edge->flow)
            min_flow = next_edge->flow;

        verts[next_edge->vertex].visited = true;
        verts[next_edge->vertex].parent = next_edge;
        pos = next_edge->vertex;

        if (pos == last)
            break;
    }

    return min_flow;
}