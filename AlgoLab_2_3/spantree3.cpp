#include <iostream>
#include <fstream>
#include <forward_list>
#include <ctime>
#include <queue>
#include <climits>

struct vertex;
struct edge {
    int vert = 0;
    int weight = 0;
};

struct vertex {
    int pos = 0;
    int key = INT_MAX;
    bool inQ = true;
    vertex * par = nullptr;
};

struct node {
    int key = 0;
    vertex * vert = nullptr;
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

    node * extractmin() {
        if (size == 1) {
            size--;
            return &nodes[0];
        }
        node tmp = nodes[0];
        nodes[0] = nodes[size - 1];
        nodes[size - 1] = tmp;
        size--;
        siftdown(0);
        return &nodes[size];
    }

    void insertkey(vertex *in_vert) {
        nodes[size].vert = in_vert;
        nodes[size].key = in_vert->key;
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
    std::ifstream input("spantree3.in");
    int V, E;
    input >> V >> E;
    vertex * verts = new vertex[V];
    for (int i = 0; i < V; i++)
        verts[i].pos = i;
    std::forward_list<edge> adj[V];
    int out, in, w;
    for (int i = 0; i < E; ++i) {
        input >> out >> in >> w;
        adj[out - 1].push_front({in - 1, w});
        adj[in - 1].push_front({out - 1, w});
    }

    input.close();

    PrQueue queue;
    queue.size = 0;
    queue.nodes = new node[E];
//    srand(time(0));
//    int r = rand() % V;
    int r = 0;
    verts[r].key = 0;
    queue.insertkey(&verts[r]);


    node * node = nullptr;
    vertex * in_vert;
    std::forward_list<edge>::iterator it;
    int exctracted = 0;
    while(exctracted != V) {
        node = queue.extractmin();
        if (!node->vert->inQ || node->key != node->vert->key)
            continue;
        node->vert->inQ = false;
        ++exctracted;

        it = adj[node->vert->pos].begin();
        while (it != adj[node->vert->pos].end()) {
            in_vert = &verts[it->vert];
            if (in_vert->inQ && it->weight < in_vert->key) {
                in_vert->par = node->vert;
                in_vert->key = it->weight;
                queue.insertkey(in_vert);
            }
            it++;
        }

    }

    std::ofstream output("spantree3.out");
    long long weight = 0;
    for (int i = 0; i < V; i++) {
        weight += verts[i].key;
    }

    output << weight;
    output.close();

    return 0;
}