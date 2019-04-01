#include <fstream>
#include <iostream>
#include <vector>
#include <forward_list>
#include <climits>
#define INF INT_MAX

struct Edge {
    Edge(int vert, int w) :
        vert(vert),
        w(w) {}
    int vert;
    int w;
};

struct Vertex {
    int pos = 0;
    bool inQ = true;
    long long dist = INF;
    std::forward_list<Edge> adj_list_;
};

struct node {
    long long key = 0;
    Vertex * vert = nullptr;
};

struct PrQueue {

    void siftdown(int pos) {
        node tmp;
        while (2 * pos + 1 < size) {
            int j = 2 * pos + 1;
            if (j + 1 < size && nodes[j + 1].key <  nodes[j].key)
                j++;

            if (nodes[pos].key < nodes[j].key)
                break;

            tmp = nodes[pos];
            nodes[pos] = nodes[j];
            nodes[j] = tmp;
            pos = j;
        }

    }

    void siftup(int pos) {
        node tmp;
        while (nodes[pos].key < nodes[(pos - 1) / 2].key) {
            tmp = nodes[pos];
            nodes[pos] = nodes[(pos - 1) / 2];
            nodes[(pos - 1) / 2] = tmp;
            pos = (pos - 1) / 2;
        }
    }

    node extractmin() {
        if (size == 1) {
            size--;
            return nodes[0];
        }
        node tmp = nodes[0];
        nodes[0] = nodes[size - 1];
        nodes[size - 1] = tmp;
        size--;
        siftdown(0);
        return nodes[size];
    }

    void insertkey(Vertex *in_vert) {
        nodes[size].vert = in_vert;
        nodes[size].key = in_vert->dist;
        size++;
        siftup(size - 1);
    }

    void makeque() {
        for (int pos = size / 2; pos >= 0; pos--)
            siftdown(pos);
    }

    node * nodes;
    int size;

};



int main() {
    std::ifstream input("pathbgep.in");

    unsigned v = 0;
    unsigned e = 0;
    input >> v >> e;

    std::vector<Vertex> verts(v);
    for (int i = 0; i < v; ++i)
        verts[i].pos = i;

    int out = 0;
    int in = 0;
    int w = 0;
    for (int i = 0; i < e; ++i) {
        input >> out;
        input >> in;
        input >> w;
        if (out == in)
            continue;
        verts[out - 1].adj_list_.emplace_front(in - 1, w);
        verts[in - 1].adj_list_.emplace_front(out - 1, w);

    }

    input.close();

    int r = 0;
    verts[r].dist = 0;
    PrQueue queue;
    queue.size = 0;
    queue.nodes = new node[2 * e];
    queue.insertkey(&verts[r]);

    node qnode;
    Edge * edge = nullptr;
    Vertex * in_vert;
    while(queue.size != 0) {
        qnode = queue.extractmin();
        if (!qnode.vert->inQ || qnode.key != qnode.vert->dist)
            continue;
        qnode.vert->inQ = false;

        for (auto it = qnode.vert->adj_list_.begin(); it != qnode.vert->adj_list_.end(); it++) {
            in_vert = &verts[it->vert];
            long long weight = it->w;
            if (in_vert->inQ && (qnode.vert->dist + weight < in_vert->dist)) {
                in_vert->dist = qnode.vert->dist + weight;
                queue.insertkey(in_vert);
            }
        }

    }

    std::ofstream output("pathbgep.out");
    for (int i = 0; i < v; ++i) {
        output << verts[i].dist << " ";
    }
    output.close();

}