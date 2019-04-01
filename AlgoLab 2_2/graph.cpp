#include "graph.h"

Edges::Edge::Edge() :
        out(nullptr),
        in(nullptr)
{}

Edges::Edge::Edge(Vertexes::Vertex *out, Vertexes::Vertex *in) :
        out(out),
        in(in)
{}

Edges::Edge::Edge(Vertexes::Vertex &out, Vertexes::Vertex &in) :
        out(&out),
        in(&in)
{}

Edges::Edges(size_t const &size) :
    size(size),
    edges(new Edge[size]),
    num(0)
{}

Edges::~Edges() {
    delete[] edges;
}

int Edges::expand() {
    size_t new_size = size * 2;
    Edge *new_edges = new Edge[new_size];
    if (new_edges == nullptr)
        return 1;

    size = new_size;

    for (int i = 0; i < num; i++)
        new_edges[i] = edges[i];

    delete[] edges;
    edges = new_edges;

    return 0;
}

Vertexes::Vertex::Vertex() :
        pos(0),
        color(0),
        order(0),
        dist(-1),
        deg(0),
        deg_in(0),
        deg_out(0),
        par(nullptr)
{}

Vertexes::Vertexes(size_t const &size) :
    size(size),
    verts(new Vertex[size]),
    num(0)
{}

Vertexes::~Vertexes() {
    delete[] verts;
}

int Vertexes::expand() {
    size_t new_size = size * 2;
    Vertex *new_verts = new Vertex[new_size];
    if (new_verts == nullptr)
        return 1;

    size = new_size;
    for (int i = 0; i < num; i++)
        new_verts[i] = verts[i];

    delete[] verts;
    verts = new_verts;

    return 0;
}

CGraph::CGraph(bool const &orient, size_t const &size_v, size_t const &size_e) :
    verts(Vertexes(size_v)),
    edges(Edges(size_e)),
    orient(orient)
{}

int CGraph::addvert() {
    if (verts.num >= verts.size * 0.7) {
        if (verts.expand() == 1)
            return 1;
    }

    verts.num++;
    return 0;
}

int CGraph::addedge(int const &out, int const &in) {
    if (out > verts.num || in > verts.num)
        return 1;
    else return addedge(&verts.verts[out - 1], &verts.verts[in - 1]);
}

int CGraph::addedge(Vertexes::Vertex *out, Vertexes::Vertex *in) {
    if (edges.num >= edges.size * 0.7) {
        if (edges.expand() == 1)
            return 1;
    }

    edges.num++;
    edges.edges[edges.num - 1].out = out;
    edges.edges[edges.num - 1].in = in;
    return 0;
}

int CGraph::addedge(Vertexes::Vertex &out, Vertexes::Vertex &in) {
    return addedge(&out, &in);
}

int CGraph::adjlist() {
//    Придумать, в кк сит. возвращать 1
    Vertexes::Vertex *out, *in;
    for (int i = 0; i < edges.num; i++) {
        out = edges.edges[i].out;
        in = edges.edges[i].in;

        if (!orient) {
            out->adjlist.add(in);
            out->deg++;
            in->adjlist.add(out);
            in->deg++;
        }

        else {
            out->adjlist.add(in);
            out->deg_out++;
            in->deg_in++;
        }

    }

    return 0;
}

int CGraph::adjmatrix() {

    return 0;
}

int AdjList::add(Vertexes::Vertex *in) {
//    Придумать, в кк сит. возвращать 1
    if (first == nullptr) {
        first = new AdjNode;
        first->vert = in;
        return 0;
    }

    AdjNode * node = first;
    while (node->next != nullptr)
        node = node->next;

    node->next = new AdjNode;
    node->next->vert = in;
    return 0;
}

int AdjList::del() {
//    Придумать, в кк сит. возвращать 1
    if (first != nullptr)
        first->del();
    delete first;

    return 0;
}

void AdjNode::del() {
    if (next != nullptr)
        next->del();
    delete next;
}
