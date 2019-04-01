#include <iostream>
#include <fstream>
#include <forward_list>
#include <queue>
#include <climits>
#include <cmath>

struct vertex;
struct edge {
    int vert = 0;
    double weight = 0;
};

struct vertex {
    int x = 0;
    int y = 0;
    bool checked = false;
    double key = 0;
    vertex * par = nullptr;
};

double dist(vertex & vert1, vertex & vert2) {
    return sqrt(pow(vert1.x - vert2.x, 2) + pow(vert1.y - vert2.y, 2));
}

int main() {
    std::ifstream input("spantree.in");
    int V;
    input >> V;
    vertex * verts = new vertex[V];
    for (int i = 0; i < V; i++) {
        input >> verts[i].x;
        input >> verts[i].y;
    }

    input.close();

    double d = 0;
    int pos = 0;
    verts[0].checked = true;
    for (int i = 1; i < V; i++)
        verts[i].key = dist(verts[0], verts[i]);

    for (int i = 1; i < V - 1; i++) {
        d = INT_MAX;
        for (int j = 0; j < V; j++) {
            if (!verts[j].checked && verts[j].key < d) {
                pos = j;
                d = verts[pos].key;
            }
        }

        verts[pos].checked = true;
        for (int j = 0; j < V; j++) {
            if (j == pos || verts[j].checked)
                continue;

            d = dist(verts[pos], verts[j]);
            if (d < verts[j].key) {
                verts[j].key = d;
                verts[j].par = &verts[pos];
            }
        }

    }

    std::ofstream output("spantree.out");
    double weight = 0;
    for (int i = 0; i < V; i++) {
        std::cout << i << "-st height " << verts[i].key << std::endl;
        weight += verts[i].key;
    }
//    std::cout.precision(10);
    output.precision(20);
    output << weight;
    output.close();

    return 0;
}