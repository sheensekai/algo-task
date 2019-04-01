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
    void adjlist();

    void topsort();
    void ts_visit(vertex & vert, int & order);

    void findcyc();
    void fc_visit(vertex & vert);
    void fc_makeway(vertex * start, vertex * finish);

    bool bprt();
    void bprt_visit(vertex & vert);

    int const getpos(int &pos) const;
    int const getverts() const;
    int const getedges() const;
    std::string const getway() const;

    bool const & isorient() const;
    bool const & isacyclic() const;
private:
    bool orient = false;
    bool acyclic;
    bool bipartite;

    vertex * verts;
    int * ordered;
    size_t v_size;

    edge * edges;
    size_t e_size;

    int * adjm;
    std::string way;
};

struct graph::adj_list {
    void add_node(vertex * vert);

    struct adj_node {
        adj_node * next = nullptr;
        vertex * vert = nullptr;
    };

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
    int degree;
    vertex * par;
    adj_list list;
};


struct graph::edge {
    int out;
    int in;
};

void graph::edgread(std::ifstream &input) {
    input >> v_size >> e_size;
    verts = new vertex[v_size];
    edges = new edge[e_size];

    for (int i = 0; i < e_size; i++)
        input >> edges[i].out >> edges[i].in;
}

bool const & graph::isorient() const {
    return this->orient;
}
bool const & graph::isacyclic() const {
    return this->acyclic;
}

void graph::adjlist() {
    int out, in;
    for (int i = 0; i < e_size; i++) {
        out = edges[i].out;
        in = edges[i].in;

        verts[out - 1].list.add_node(&verts[in - 1]);
        if (!orient)
            verts[in - 1].list.add_node(&verts[out - 1]);
    }
}

void graph::topsort() {
    ordered = new int[v_size];

    for(int i = 0; i < v_size; i++)
        verts[i].search_set(i);
    acyclic = true;

    int order = v_size;
    for (int i = 0; i < v_size; i++) {
        if (!acyclic)
            break;
        if (verts[i].color)
            continue;

        ts_visit(verts[i], order);
    }
}

void graph::ts_visit(vertex & vert, int & order) {
    vert.color = 1;

    adj_list::adj_node * node = vert.list.first;
    while (node != nullptr && acyclic) {
        if (node->vert->color == 1) { // found grey -> cycle
            acyclic = false;
            break;
        }

        if (!node->vert->color)
            ts_visit(*node->vert, order);
        node = node->next;
    }

    vert.color = 2;
    vert.order = order--;
    ordered[vert.order - 1] = vert.pos;
}

void graph::findcyc() {
    way = "";
    for(int i = 0; i < v_size; i++)
        verts[i].search_set(i);
    acyclic = true;

    for (int i = 0; i < v_size; i++) {
        if (!acyclic)
            break;
        if (verts[i].color)
            continue;

        fc_visit(verts[i]);
    }

}

void graph::fc_visit(vertex & vert) {
    vert.color = 1;

    adj_list::adj_node * node = vert.list.first;
    while (node != nullptr && acyclic) {
        if (node->vert->color == 1) { // found grey -> cycle
            acyclic = false;
            node->vert->par = &vert;
            fc_makeway(&vert, node->vert);
            break;
        }

        if (!node->vert->color) {
            node->vert->par = &vert;
            fc_visit(*node->vert);
        }

        node = node->next;
    }

    vert.color = 2;
}

void graph::fc_makeway(vertex * start, vertex * finish) {
    if (finish != start)
        fc_makeway(start->par, finish);
    char num[10];
    itoa(start->pos + 1, num, 10);
    way += num;
    way += " ";
};

bool graph::bprt() {
    bipartite = true;
    for (int i = 0; i < v_size; i++)
        verts[i].search_set(i);

    for (int i = 0; i < v_size; i++) {
        if (!bipartite)
            break;
        if (verts[i].color)
            continue;

        bprt_visit(verts[i]);
    }

    return bipartite;
}

void graph::bprt_visit(vertex & vert) {
    if (!vert.color)
        vert.color = 1;

    adj_list::adj_node * node = vert.list.first;
    while (node != nullptr && bipartite) {
        if (!node->vert->color) {
            node->vert->color = (vert.color == 1 ? 2 : 1);
            bprt_visit(*node->vert);
        }
        else if (node->vert->color == vert.color) {
            bipartite = false;
            break;
        }

        node = node->next;
    }

}


int const graph::getverts() const {
    return v_size;
}
int const graph::getedges() const {
    return e_size;
}
int const graph::getpos(int &pos) const {
    return ordered[pos];
}
std::string const graph::getway() const {
    return way;
}

void graph::vertex::search_set(int num) {
    color = 0;
    order = 0;
    pos = num;
    dist = -1;
    comp = 0;
    degree = 0;
    par = nullptr;
}

void graph::adj_list::add_node(vertex * vert) {
    if (this->first == nullptr) {
        this->first = new adj_node;
        this->first->vert = vert;
        return;
    }

    adj_node * node = this->first;
    while (node->next != nullptr)
        node = node->next;

    node->next = new adj_node;
    node->next->vert = vert;
}

int main() {
    std::ifstream input("input.txt");
    graph gr;
    gr.edgread(input);
    gr.adjlist();
    input.close();

    std::ofstream output("output.txt");
    output << (gr.bprt() ? "YES" : "NO");
    output.close();

    return 0;
}