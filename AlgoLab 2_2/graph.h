#ifndef ALGOLAB_2_2_GRAPH_H
#define ALGOLAB_2_2_GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cstddef>

struct Vertexes {
    struct Vertex;
    struct AdjMat;

    explicit Vertexes(size_t const &size = 10);
    ~Vertexes();

    size_t size;
    Vertex * verts;
    int num;

    int expand();
};
struct AdjNode {
    AdjNode *next = nullptr;
    Vertexes::Vertex *vert = nullptr;

    void del();
};
struct AdjList {
    AdjNode *first = nullptr;

    int add(Vertexes::Vertex *in);
    int del();
};
struct Vertexes::Vertex {
    Vertex();

    int pos;
    int color;
    int order;
    int dist;

    int deg;
    int deg_in;
    int deg_out;

    Vertex * par;
    AdjList adjlist;
};

struct Edges {
    struct Edge;

    explicit Edges(size_t const &size = 10);
    ~Edges();

    size_t size;
    Edge * edges;
    int num;

    int expand();
};
struct Edges::Edge {
    Edge();
    Edge(Vertexes::Vertex  *out, Vertexes::Vertex  *in);
    Edge(Vertexes::Vertex  &out, Vertexes::Vertex  &in);

    Vertexes::Vertex * out;
    Vertexes::Vertex * in;
};

class CGraph {
public:
    explicit CGraph(bool const &orient = false, size_t const &size_v = 10, size_t const &size_e = 10);

    int addvert();
    int addedge(int const & out, int const & in);
    int addedge(Vertexes::Vertex *out, Vertexes::Vertex *in);
    int addedge(Vertexes::Vertex &out, Vertexes::Vertex &in);

    int adjlist();
    int adjmatrix();

private:

    Vertexes verts;
    Edges edges;

    int * adjmat;
    int * incmat;

    bool const orient;
};

#endif //ALGOLAB_2_2_GRAPH_H
