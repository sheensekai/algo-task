#include <fstream>
#include <vector>
#include <climits>
#include <queue>

#define INF (INT_MAX / 2)

struct AdjEdge {
    int vertex;
    int capacity;
    int flow;
    bool real_edge;
};

struct Vertex {
    bool visited = false;
    AdjEdge *parent = nullptr;
    int dist = 0;
    int edge_prt = 0;
    std::vector<int> adj;
};

void ReadEdges(std::vector<Vertex> &verts, std::vector<AdjEdge> &edges, std::string const &stream);

void WriteAnswer(std::vector<Vertex> &verts, std::vector<AdjEdge> &edges, std::string const &stream);

void InitEdge(AdjEdge &edge, int vert, int cap, bool real);

int DinitzBFS(std::vector<Vertex> &verts, std::vector<AdjEdge> &edges);

int DinitzDFS(std::vector<Vertex> &verts, std::vector<AdjEdge> &edges);

int DinitzDFSVisit(std::vector<Vertex> &verts, std::vector<AdjEdge> &edges, int v, int min_cap);

int DinitzMaxFlow(std::vector<Vertex> &verts, std::vector<AdjEdge> &edges);

int main() {
    std::vector<Vertex> verts;
    std::vector<AdjEdge> edges;

    ReadEdges(verts, edges, "circulation.in");

    DinitzMaxFlow(verts, edges);

    WriteAnswer(verts, edges, "circulation.out");

    return 0;
}

void ReadEdges(std::vector<Vertex> &verts, std::vector<AdjEdge> &edges, std::string const &stream) {
    std::ifstream input(stream);
    int v, e;
    input >> v >> e;
    verts.resize(v + 2);
    edges.resize(6 * e);

    int first = 0;
    int last = v + 1;
    int out, in, min_cap, max_cap;
    int new_e = e * 6;
    for (int i = 0; i < new_e; i += 6) {
        input >> out >> in >> min_cap >> max_cap; // read (u,v) edge

        InitEdge(edges[i], in, min_cap, true); // (s, v) new edge
        verts[first].adj.push_back(i);
        InitEdge(edges[i + 1], first, 0, false); // (v,s) new rev edge
        verts[in].adj.push_back(i + 1);

        InitEdge(edges[i + 2], in, max_cap - min_cap, true); // (u, v) updated edge
        verts[out].adj.push_back(i + 2);
        InitEdge(edges[i + 3], out, 0, false); // (v, u) new rev edge
        verts[in].adj.push_back(i + 3);

        InitEdge(edges[i + 4], last, min_cap, true); // (u,t) new edge
        verts[out].adj.push_back(i + 4);
        InitEdge(edges[i + 5], out, 0, false); // (t, u) new edge
        verts[last].adj.push_back(i + 5);
    }

    input.close();
}

void WriteAnswer(std::vector<Vertex> &verts, std::vector<AdjEdge> &edges, std::string const &stream) {
    bool circ_exists = true;
    for (int pos : verts[0].adj) {
        AdjEdge &edge = edges[pos];
        if (edges[pos].flow != edges[pos].capacity) {
            circ_exists = false;
            break;
        }
    }

    std::ofstream output(stream);
    if (!circ_exists)
        output << "NO";
    else {
        output << "YES" << '\n';
        for (int i = 2; i < edges.size(); i += 6) {
            output << edges[i].flow + edges[i - 2].capacity << '\n';
        }
    }

}

void InitEdge(AdjEdge &edge, int vert, int cap, bool real) {
    edge.vertex = vert;
    edge.capacity = cap;
    edge.flow = 0;
    edge.real_edge = real;
}

int DinitzMaxFlow(std::vector<Vertex> &verts, std::vector<AdjEdge> &edges) {
    int maxflow = 0;
    while (DinitzBFS(verts, edges)) {
        for (Vertex &vert : verts)
            vert.edge_prt = 0;

        int flow = DinitzDFS(verts, edges);
        while (flow) {
            maxflow += flow;
            flow = DinitzDFS(verts, edges);
        }

    }

    return maxflow;
}

int DinitzBFS(std::vector<Vertex> &verts, std::vector<AdjEdge> &edges) {
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

        for (int pos : vert->adj) {
            AdjEdge &edge = edges[pos];
            if (!(edge.capacity - edge.flow) || verts[edge.vertex].visited)
                continue;

            verts[edge.vertex].dist = vert->dist + 1;
            verts[edge.vertex].visited = true;
            queue.push(&verts[edge.vertex]);

        }

    }

    return verts[last].visited;
}

int DinitzDFS(std::vector<Vertex> &verts, std::vector<AdjEdge> &edges) {
    return DinitzDFSVisit(verts, edges, 0, INF);
}

int DinitzDFSVisit(std::vector<Vertex> &verts, std::vector<AdjEdge> &edges, int v, int min_cap) {
    if (v == (verts.size() - 1) || min_cap == 0)
        return min_cap;

    Vertex &vert = verts[v];
    for (; vert.edge_prt < vert.adj.size(); ++vert.edge_prt) {
        AdjEdge &edge = edges[vert.adj[vert.edge_prt]];
        if (!(edge.capacity - edge.flow))
            continue;

        if ((vert.dist + 1) == verts[edge.vertex].dist) {
            int flow = DinitzDFSVisit(verts, edges, edge.vertex,
                                      (min_cap < edge.capacity - edge.flow ? min_cap : edge.capacity - edge.flow));
            if (flow) {
                edge.flow += flow;
                AdjEdge *other_edge = &edge;
                if (edge.real_edge)
                    ++other_edge;
                else --other_edge;

                other_edge->flow -= flow;
                return flow;
            }
        }
    }


    return 0;
}