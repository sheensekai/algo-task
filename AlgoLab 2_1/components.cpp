#include <iostream>
#include <fstream>
#include <queue>

struct vertex;
struct adj_node {
    adj_node * next = nullptr;
    vertex * vert = nullptr;
};

struct vertex {
    int number = 0;

    int color = 0; // 0 - white; 1 - grey; 2 - black
    int dist = 0;
    int comp = 0;

    int pos = 0;

    bool visited = false;

    int degree = 0;
    adj_node * adj_first = nullptr;
    vertex * parent = nullptr;
};

void adj_add(vertex * verts, int i, int j);
int dfs(vertex * verts, int n);
void dfs_visit(vertex * vert, int n);

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    int m, n;
    input >> n >> m;
    vertex verts[n];

    for (int k = 0; k < n; k++)
        verts[k].number = k + 1;
    int i, j;
    for (int k = 0; k < m; k++) {
        input >> i >> j;
        adj_add(verts, i - 1, j - 1);
    }

    output << dfs(verts, n) << std::endl;
    for (int k = 0; k < n; k++)
        output << verts[k].comp << " ";

    output << std::endl;

    for (int k = 0; k < n; k++)
        output << k + 1 << " " << verts[k].pos << std::endl;


    input.close();
    output.close();
    return 0;
}

void adj_add(vertex * verts, int i, int j) {
    verts[i].degree++;
    verts[j].degree++;


    adj_node * node = verts[i].adj_first;
    while(node != nullptr && node->next != nullptr)
        node = node->next;
    if (node == nullptr) {
        verts[i].adj_first = new adj_node;
        verts[i].adj_first->vert = &verts[j];
    }
    else {
        node->next = new adj_node;
        node->next->vert = &verts[j];
    }

}

int dfs(vertex * verts, int n) {
    int comp = 0;
    for (int i = 0; i < n; i++)
        if (verts[i].color == 0) {
            verts[i].comp = ++comp;
            dfs_visit(&verts[i], n);
        }

    return comp;
}
int count = 0;
void dfs_visit(vertex * vert, int n) {
    vert->color = 1;

    adj_node * node = vert->adj_first;
    while (node != nullptr) {
        if (node->vert->color == 0) {
            node->vert->parent = vert;
            node->vert->comp = vert->comp;
            dfs_visit(node->vert, n);
        }

        node = node->next;
    }

    vert->color = 2;
    vert->pos = n - count++;

}