#include <iostream>
#include <fstream>
#include <vector>
#include <forward_list>
#include <queue>
#include <stack>
#include <climits>

#define INF INT_MAX
#define START -5
#define FINISH -10

struct AdjEdge {
    AdjEdge(int vert, int out_vert, int cap, bool real) :
            vertex(vert),
            capacity(cap),
            real_edge(real),
            flow(0),
            out_vertex(out_vert),
            other_edge(-1) {}

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
    std::vector<AdjEdge> adj_real;
};

int DFS(std::vector<Vertex> &left, std::vector<Vertex> &right, Vertex &start, Vertex &finish);

int DFSVisit(Vertex &vert, std::vector<Vertex> &left,
             std::vector<Vertex> &right,
             Vertex &start, Vertex &finish);

int CountFlowBFS(std::vector<Vertex> &verts, int s, int t);

int EdmondsKarp(std::vector<Vertex> &left, std::vector<Vertex> &right);

void CalcResidue(std::vector<Vertex> &left, std::vector<Vertex> &right, Vertex &start, Vertex &finish);

int main() {
    std::ifstream input("matching.in");
    if (!input.is_open()) {
        std::cout << "Didn't open";
        return 1;
    }

    int v_left, v_right, e;
    input >> v_left >> v_right >> e;

    std::vector<Vertex> verts_left(v_left);
    std::vector<Vertex> verts_right(v_right);

    for (int i = 0; i < v_left; ++i)
        verts_left[i].pos = i;
    for (int i = 0; i < v_right; ++i)
        verts_right[i].pos = i;

    int out, in;
    for (int i = 0; i < e; ++i) {
        input >> out >> in;

        verts_left[out - 1].adj_real.emplace_back(in - 1, out - 1, 1, true);
        verts_right[in - 1].adj_real.emplace_back(out - 1, in - 1, 0, false);

        verts_left[out - 1].adj_real.back().other_edge =
                verts_right[in - 1].adj_real.size() - 1;
        verts_right[in - 1].adj_real.back().other_edge =
                verts_left[out - 1].adj_real.size() - 1;
    }
    input.close();

    std::ofstream output("matching.out");
    output << EdmondsKarp(verts_left, verts_right);
    output.close();

    return 0;
}

int EdmondsKarp(std::vector<Vertex> &left, std::vector<Vertex> &right) {
    int flow = 0;
    Vertex start;
    Vertex finish;

    for (int i = 0; i < left.size(); ++i) {
        start.adj_real.emplace_back(i, START, 1, true);
        left[i].adj_real.emplace_back(START, i, 0, false);

        start.adj_real.back().other_edge = left[i].adj_real.size() - 1;
        left[i].adj_real.back().other_edge = start.adj_real.size() - 1;
    }

    for (int i = 0; i < right.size(); ++i) {
        right[i].adj_real.emplace_back(FINISH, i, 1, true);
        finish.adj_real.emplace_back(i, FINISH, 0, false);

        right[i].adj_real.back().other_edge = finish.adj_real.size() - 1;
        finish.adj_real.back().other_edge = right[i].adj_real.size() - 1;
    }

    while (DFS(left, right, start, finish)) {
        ++flow;
        AdjEdge *edge = finish.parent;
        edge->flow += 1;
        finish.adj_real[edge->other_edge].flow -= 1;
        edge = right[edge->out_vertex].parent;
        while (edge != nullptr) {
            if (edge->out_vertex == START) {
                edge->flow += 1;
                left[edge->vertex].adj_real[edge->other_edge].flow -= 1;
                edge = nullptr;
                break;
            }
            if (edge->real_edge) {
                edge->flow += 1;
                right[edge->vertex].adj_real[edge->other_edge].flow -= 1;
                edge = left[edge->out_vertex].parent;
            } else {
                edge->flow -= 1;
                left[edge->vertex].adj_real[edge->other_edge].flow += 1;
                edge = right[edge->out_vertex].parent;
            }
        }

        CalcResidue(left, right, start, finish);
    }

    return flow;
}

int DFS(std::vector<Vertex> &left,
        std::vector<Vertex> &right,
        Vertex &start, Vertex &finish) {

    for (Vertex &vert : left) {
        vert.parent = nullptr;
        vert.visited = false;
    }
    for (Vertex &vert : right) {
        vert.parent = nullptr;
        vert.visited = false;
    }

    start.parent = nullptr;
    start.visited = false;
    finish.parent = nullptr;
    finish.visited = false;

    for (AdjEdge &edge : start.adj_real) {
        if (left[edge.vertex].visited || !edge.capacity)
            continue;

        left[edge.vertex].visited = true;
        left[edge.vertex].parent = &edge;
        if (DFSVisit(left[edge.vertex], left, right, start, finish))
            return 1;
    }

    return 0;
}

int DFSVisit(Vertex &vert, std::vector<Vertex> &left,
             std::vector<Vertex> &right,
             Vertex &start, Vertex &finish) {

    for (AdjEdge &edge : vert.adj_real) {
        if (!edge.capacity || edge.vertex == START)
            continue;

        if (edge.vertex == FINISH) {
            finish.visited = true;
            finish.parent = &edge;
            return 1;
        }

        if ((edge.real_edge && right[edge.vertex].visited) ||
            (!edge.real_edge && left[edge.vertex].visited)) {
            continue;
        }

        if (edge.real_edge) {
            right[edge.vertex].visited = true;
            right[edge.vertex].parent = &edge;
           if (DFSVisit(right[edge.vertex], left, right, start, finish))
               return 1;
        } else {
            left[edge.vertex].visited = true;
            left[edge.vertex].parent = &edge;
            if (DFSVisit(left[edge.vertex], left, right, start, finish))
                return 1;

        }

    }

    return 0;
}

int CountFlowBFS(std::vector<Vertex> &verts, int s, int t) {
    int flow = 0;

    for (auto vert : verts) {
        vert.parent = nullptr;
        vert.visited = false;
    }

    std::queue<Vertex *> queue;
    queue.push(&verts[s]);

    while (!queue.empty()) {
        auto popped = queue.front();
        queue.pop();

        popped->visited = true;
        for (auto edge : popped->adj_real) {
            if (verts[edge.vertex].visited || !edge.real_edge)
                continue;

            flow += edge.flow;
            verts[edge.vertex].parent = &edge;
        }
    }

    return flow;
}

void CalcResidue(std::vector<Vertex> &left, std::vector<Vertex> &right, Vertex &start, Vertex &finish) {
    for (Vertex &vert : left) {
        for (AdjEdge &edge : vert.adj_real) {
            edge.capacity = edge.capacity - edge.flow;
            edge.flow = 0;
        }
    }

    for (Vertex &vert : right) {
        for (AdjEdge &edge : vert.adj_real) {
            edge.capacity = edge.capacity - edge.flow;
            edge.flow = 0;
        }
    }

    for (AdjEdge &edge : start.adj_real) {
        edge.capacity = edge.capacity - edge.flow;
        edge.flow = 0;
    }

    for (AdjEdge &edge : finish.adj_real) {
        edge.capacity = edge.capacity - edge.flow;
        edge.flow = 0;
    }

}