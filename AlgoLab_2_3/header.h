#ifndef ALGOLAB_2_3_HEADER_H
#define ALGOLAB_2_3_HEADER_H

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define INFINITY 1000000001

struct VertexASD {
    int value;
    int timeOUT;
    int num_cond = 0;
    bool visited = false;
};

struct EdgeASD {
    int from;
    int to;
    int weight = INFINITY;
};

void dfsASD(int &current_vertex, vector<VertexASD> &vertices, vector<EdgeASD> &edges, int &count) {
    vertices[current_vertex].visited = true;
    count++;
    for (auto &edge : edges) {
        if (vertices[edge.from].value == vertices[current_vertex].value) {
            if (!vertices[edge.to].visited) {
                dfsASD(edge.to, vertices, edges, count);
            }
        }
    }
}

void dfsTime(int &current_vertex, vector<VertexASD> &vertices, vector<EdgeASD> &edges, int &current_time) {
    vertices[current_vertex].visited = true;
    for (auto &edge : edges) {
        if (vertices[edge.from].value == vertices[current_vertex].value) {
            if (!vertices[edge.to].visited) {
                dfsTime(edge.to, vertices, edges, current_time);
            }
        }
    }
    vertices[current_vertex].timeOUT = current_time++;
}

void dfsTrans(int &current_vertex, vector<VertexASD> &vertices, vector<EdgeASD> &edges, unsigned int &current_cond) {
    vertices[current_vertex].visited = true;
    vertices[current_vertex].num_cond = current_cond;
    for (auto &edge : edges) {
        if (vertices[edge.from].value == vertices[current_vertex].value) {
            if (!vertices[edge.to].visited) {
                dfsTrans(edge.to, vertices, edges, current_cond);
            }
        }
    }
}

bool compareVertices(const VertexASD &left_vertex, const VertexASD &right_vertex) {
    return left_vertex.timeOUT < right_vertex.timeOUT;
}

unsigned int condensation(vector<VertexASD> &vertices, vector<EdgeASD> &edges) {
    int n = vertices.size();
    int m = edges.size();
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        vertices[i].visited = false;
    }
    for (int i = 0; i < n; i++) {
        if (!vertices[i].visited) {
            dfsTime(i, vertices, edges, current_time);
        }
    }

    vector<VertexASD> vertices_T(n);
    vector<EdgeASD> edges_T(m);
    for (int i = 0; i < n; i++) {
        vertices_T[i].value = vertices[i].value;
        vertices_T[i].timeOUT = vertices[i].timeOUT;
    }
    sort(vertices_T.begin(), vertices_T.end(), compareVertices);
    vector<int> index_adjacency(n);
    for (int i = 0; i < n; ++i) {
        index_adjacency[vertices_T[i].value] = i;
    }
    for (int i = 0; i < m; i++) {
        edges_T[i].weight = edges[i].weight;
        edges_T[i].from = index_adjacency[edges[i].to];
        edges_T[i].to = index_adjacency[edges[i].from];
    }

    unsigned int currentCond = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (!vertices_T[i].visited) {
            dfsTrans(i, vertices_T, edges_T, ++currentCond);
        }
    }
    for (int i = 0; i < n; ++i) {
        vertices[i].num_cond = vertices_T[index_adjacency[i]].num_cond;
    }
    return currentCond;
}

long long findMSTASD(vector<EdgeASD> &edges, vector<VertexASD> &vertices, int &n_root) {
    int n = vertices.size();
    vector<int> min_edge(n,
                         INFINITY); // создаем массив минимумов, входящих в каждую компоненту, инициализируем бесконечностью.
    long long resultMST = 0;
    min_edge[n_root] = 0;
    for (auto edge : edges) {
        min_edge[edge.to] = min(edge.weight, min_edge[edge.to]);
    }
    for (int i = 0; i < n; i++) {
        if (i != n_root) {
            resultMST += min_edge[i]; //веса минимальных ребер точно будут в результате
        }
    }
    vector<EdgeASD> zero_edges; //создаем массив нулевых ребер
    for (auto edge : edges) {
        if (edge.weight == min_edge[edge.to]) {
            EdgeASD e1 = edge;
            e1.weight -= min_edge[edge.to];
            zero_edges.push_back(e1); // e1 - ребро е, уменьшенное на минимальный вес, входящий в e.to
        }
    }
    for (int i = 0; i < n; i++) {
        vertices[i].visited = false;
    }
    int count = 0;
    dfsASD(n_root, vertices, zero_edges, count); // проверяем, можно ли дойти до всех вершин по нулевым ребрам
    if (count == n) {
        return resultMST;
    }
    vector<VertexASD> new_components(condensation(vertices, zero_edges)); // будущие компоненты связности
    for (int i = 0; i < new_components.size(); i++) {
        new_components[i].value = i;
    }

    vector<EdgeASD> new_edges; //создаем массив ребер в новом графе с вершинами в полученных компонентах
    for (auto edge : edges) {
        if (vertices[edge.to].num_cond != vertices[edge.from].num_cond) { // e.to и e.from в разных компонентах
            EdgeASD new_edge;
            new_edge.from = vertices[edge.from].num_cond - 1;
            new_edge.to = vertices[edge.to].num_cond - 1;
            new_edge.weight = edge.weight - min_edge[edge.to];
            new_edges.push_back(
                    new_edge); // добавляем в newEdges ребро с концами в данных компонентах и весом e.w - minEdge[e.to]
        }
    }
    n_root = vertices[n_root].num_cond - 1;
    resultMST += findMSTASD(new_edges, new_components, n_root);
    return resultMST;
}

int play(std::string number) {
    std::string file_in = "chinese" + number + ".in";
    std::string file_out = "2chinese" + number + ".out";

    ifstream fin;
    ofstream fout;
    fin.open(file_in);
    fout.open(file_out);
    int n, m;
    fin >> n >> m;
    vector<VertexASD> vertices(n);
    vector<EdgeASD> edges(m);
    int u, v, w;
    for (int i = 0; i < m; i++) {
        fin >> u >> v >> w;
        vertices[u - 1].value = u - 1;
        vertices[v - 1].value = v - 1;
        edges[i].from = u - 1;
        edges[i].to = v - 1;
        edges[i].weight = w;
    }
    int count = 0;
    int root = 0;
    dfsASD(root, vertices, edges, count);
    if (count != n) {
        fout << "NO";
    } else {
        fout << "YES" << "\n";
        fout << findMSTASD(edges, vertices, root);
    }
    fout.close();
    return 0;
}

#endif //ALGOLAB_2_3_HEADER_H
