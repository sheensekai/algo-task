#include <iostream>
#include <fstream>
#include <forward_list>
#include <climits>
#include <vector>
#include <cmath>
#include <random>
#include <string>
#include <stack>
#include <ctime>
#define INF INT_MAX

struct AdjEdge {
    AdjEdge(int in = 0, int w = 0) :
            in(in),
            w(w) {}

    AdjEdge(AdjEdge const &edge) :
            in(edge.in),
            w(0) {}

    int in;
    int w;
};
struct Edge : AdjEdge {
    Edge(int out = 0, int in = 0, int w = 0) :
            AdjEdge(in, w),
            out(out) {}

    Edge(Edge const &edge) :
            AdjEdge(edge.in, edge.w),
            out(edge.out) {}

    int out;
};
typedef AdjEdge adj_edge;
typedef Edge edge;

struct Vertex {
    Vertex * par = nullptr;
    int color = 0;
    int comp = 0;
    int order = 0;
    std::forward_list<adj_edge> adj;
};
typedef Vertex vert;

long long int findMST(std::vector<edge> &edges, std::vector<vert> &verts, int const &root);

bool check_graph(std::vector<vert> &verts, std::vector<edge> &edges, int const &root);

void check_vis(std::vector<vert> &verts, int const &pos, int &visited);

int cond_graph(std::vector<vert> &verts, int const &root, std::vector<edge> &edges, std::vector<vert> &comps);

void cond_vis(std::vector<vert> &verts, int const &pos);

void topsort(std::vector<vert> &verts, std::vector<edge> &edges, int const &root, std::stack<int> &ordered);

void ts_vis(std::vector<vert> &verts, int const &pos, std::stack<int> &ordered);

int main() {
    std::ifstream input("chinese.in");
    std::ofstream output("chinese.out");

    size_t V, E;
    input >> V >> E;
    std::vector<vert> verts(V);
    std::vector<edge> edges(E);

    int in, out, w;
    for (int i = 0; i < E; ++i) {
        input >> out >> in >> edges[i].w;
        edges[i].out = out - 1;
        edges[i].in = in  -1;
    }

    if (!check_graph(verts, edges, 0)) {
        output << "NO";
        return 0;
    }

    output << "YES" << std::endl << findMST(edges, verts, 0);
    input.close();
    output.close();

    std::cout << clock();

    return 0;
}

long long findMST(std::vector<edge> &edges, std::vector<vert> &verts, int const &root) {
    long long result = 0;

    std::vector<int> min_edges(verts.size(), INF);
    for (int i = 0; i < edges.size(); ++i)
        min_edges[edges[i].in] = (edges[i].w < min_edges[edges[i].in] ? edges[i].w : min_edges[edges[i].in]);
    min_edges[root] = 0;
    for (int i = 0; i < verts.size(); ++i)
        result += min_edges[i];

    std::vector<edge> zero_edges;
    for (int i = 0; i < edges.size(); ++i) {
        if (edges[i].w == min_edges[edges[i].in])
            zero_edges.emplace_back(edges[i].out, edges[i].in, 0);
    }

    if (check_graph(verts, zero_edges, root))
        return result;

    std::vector<vert> comps;
    int comp_root = cond_graph(verts, root, zero_edges, comps);
    std::vector<edge> comp_edges;
    int out, in;
    for (int i = 0; i < edges.size(); ++i) {
        out = edges[i].out;
        in = edges[i].in;
        if (verts[edges[i].out].comp != verts[edges[i].in].comp)
            comp_edges.emplace_back(verts[out].comp, verts[in].comp, edges[i].w - min_edges[in]); // - min_edges[in]
    }

    result += findMST(comp_edges, comps, comp_root);
    return result;
}

bool check_graph(std::vector<vert> &verts, std::vector<edge> &edges, int const &root) {
    for (int i = 0; i < verts.size(); ++i) {
        verts[i].color = 0;
        if (!verts[i].adj.empty())
            verts[i].adj.clear();
    }

    for (int i = 0; i < edges.size(); ++i)
        verts[edges[i].out].adj.emplace_front(edges[i].in, edges[i].w);

    int visited = 0;
    check_vis(verts, root, visited);

    return visited == verts.size();
}

void check_vis(std::vector<vert> &verts, int const &pos, int &visited) {
    ++visited;
    vert & vert = verts[pos];
    vert.color = 1;
    std::forward_list<AdjEdge>::iterator it = vert.adj.begin();
    while (it != vert.adj.end()) {
        if (!verts[it->in].color)
            check_vis(verts, it->in, visited);
        it++;
    }
    vert.color = 2;
}

int cond_graph(std::vector<vert> &verts, int const &root, std::vector<edge> &edges, std::vector<vert> &comps) {
    std::stack<int> ordered;
    topsort(verts, edges, root, ordered);
    for (int i = 0; i < verts.size(); ++i) {
        verts[i].color = 0;
        if (!verts[i].adj.empty())
            verts[i].adj.clear();
    }

    for (int i = 0; i < edges.size(); ++i)
        verts[edges[i].in].adj.emplace_front(edges[i].out, edges[i].w);

    int comps_n = 0;
    int pos = 0;
    while (!ordered.empty()) {
        pos = ordered.top();
        ordered.pop();

        if (!verts[pos].color) {
            verts[pos].comp = comps_n;
            ++comps_n;
            cond_vis(verts, pos);
        }
    }

    comps.resize(comps_n);
    return verts[root].comp;
}

void cond_vis(std::vector<vert> &verts, int const &pos) {
    vert &vert = verts[pos];
    vert.color = 1;
    std::forward_list<AdjEdge>::iterator it = vert.adj.begin();
    while (it != vert.adj.end()) {
        if (!verts[it->in].color) {
            verts[it->in].comp = vert.comp;
            cond_vis(verts, it->in);
        }
        it++;
    }
    vert.color = 2;
}

void topsort(std::vector<vert> &verts, std::vector<edge> &edges, int const &root, std::stack<int> &ordered) {
    for (int i = 0; i < verts.size(); ++i) {
        verts[i].color = 0;
        verts[i].order = 0;
        if (!verts[i].adj.empty())
            verts[i].adj.clear();
    }

    for (int i = 0; i < edges.size(); ++i)
        verts[edges[i].out].adj.emplace_front(edges[i].in, edges[i].w);

    int order = verts.size();
    ts_vis(verts, root, ordered);
    for (int i = 0; i < verts.size(); ++i){
        if (!verts[i].color)
            ts_vis(verts, i, ordered);
    }

}

void ts_vis(std::vector<vert> &verts, int const &pos, std::stack<int> &ordered) {
    vert &vert = verts[pos];
    vert.color = 1;
    std::forward_list<AdjEdge>::iterator it = vert.adj.begin();
    while (it != vert.adj.end()) {
        if (!verts[it->in].color)
            ts_vis(verts, it->in, ordered);
        it++;
    }
    vert.color = 2;
    ordered.push(pos);
}