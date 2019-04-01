#ifndef ALGOLAB_2_2_HANDMADE_GRAPH_H
#define ALGOLAB_2_2_HANDMADE_GRAPH_H

#include <cstddef>
#include <fstream>
#include <string>
#include <queue>

class graph {
private:
    struct vertex;
    struct adj_list;
    struct edge;
public:
    void edgread(std::ifstream &input);
    void add_edge(int & out, int & in);
    void adjlist();
    void rev_adjlist();
    void adjmat();
    void setpos();

    void topsort();
    void ts_visit(vertex & vert, int & order);
    void cond();
    void cond_visit(vertex & vert);

    void findcyc();
    void fc_visit(vertex & vert);
    void fc_makeway(vertex * start, vertex * finish);

    bool bprt();
    void bprt_visit(vertex & vert);

    bool isgamway();
    void gm_topsort();
    void gm_ts_visit(vertex & vert, int & order);
    bool gm_check(vertex & vert);

    int game(std::ifstream &input);
    vertex * find_vert(int deg);

    int const getpos(int &pos) const;
    int const getverts() const;
    int const getedges() const;
    int const getcomp(int &pos) const;
    int const getcomps() const;
    std::string const getway() const;

    bool const & isorient() const;
    bool const & isacyclic() const;
private:
    bool orient = true;
    bool acyclic;
    bool bipartite;
    bool cond_on = false;

    vertex * verts;
    int * ordered = nullptr;
    size_t v_size;

    edge * edges;
    size_t e_size;

    int comps;

    int ** adjm;
    std::string way;
};

struct graph::adj_list {
    struct adj_node {
        adj_node * next = nullptr;
        vertex * vert = nullptr;
    };

    void add_node(vertex * vert);
    void del();
    void del_node(adj_node * node);

    int nods = 0;
    adj_node * first = nullptr;
};

struct graph::vertex {
    void search_set(int num);

    int color; // 0 - white; 1 - grey; 2 - black;
    int order;
    int pos;
    int dist;
    int comp;
    int deg_in;
    int deg_out;
    vertex * par;
    adj_list list;
};

struct graph::edge {
    int out;
    int in;
};

#endif //ALGOLAB_2_2_HANDMADE_GRAPH_H
