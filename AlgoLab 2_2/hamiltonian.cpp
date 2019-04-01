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
    bool cond_on;

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

void graph::edgread(std::ifstream &input) {
    input >> v_size >> e_size;
    verts = new vertex[v_size];
    edges = new edge[e_size];

    for (int i = 0; i < e_size; i++)
        input >> edges[i].out >> edges[i].in;
}
void graph::adjlist() {
    for (int i = 0; i < v_size; i++) {
        verts[i].deg_in = 0;
        verts[i].deg_out = 0;
    }

    int out, in;
    for (int i = 0; i < e_size; i++) {
        out = edges[i].out;
        in = edges[i].in;

        verts[out - 1].list.add_node(&verts[in - 1]);
        verts[out - 1].deg_out++;
        verts[in - 1].deg_in++;
        if (!orient) {
            verts[in - 1].list.add_node(&verts[out - 1]);
            verts[out - 1].deg_in++;
            verts[in - 1].deg_out++;
        }
    }
}
void graph::adjmat() {
    adjm = new int*[v_size];
    for (int i = 0; i < v_size; i++)
        adjm[i] = new int[v_size];
    for (int i = 0; i < v_size; i++) {
        for (int j = 0; j < v_size; j++)
            adjm[i][j] = 0;
    }

    int out, in;
    for (int i = 0; i < e_size; i++) {
        out = edges[i].out;
        in = edges[i].in;

        adjm[out - 1][in - 1]++;
        if (!orient)
            adjm[in - 1][out - 1]++;
    }
}
void graph::vertex::search_set(int num) {
    color = 0;
    dist = -1;
    par = nullptr;
}
void graph::setpos() {
    for (int i = 0; i < v_size; i++)
        verts[i].pos = i;
}

void graph::topsort() {
    if (ordered != nullptr) {
        delete[] ordered;
        ordered = nullptr;
    }
    ordered = new int[v_size];
    setpos();

    for(int i = 0; i < v_size; i++)
        verts[i].search_set(i);
    acyclic = true;

    int order = v_size;
    for (int i = 0; i < v_size; i++) {
        if (!acyclic && !cond_on)
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
        if (node->vert->color == 1 && !cond_on) { // found grey -> cycle
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
void graph::cond() {
    cond_on = true;
    topsort();

    for (int i = 0; i < v_size; i++)
        verts[i].list.del();
    int in, out;
    for (int i = 0; i < e_size; i++) {
        in = edges[i].in;
        out = edges[i].out;

        verts[in - 1].list.add_node(&verts[out - 1]);
    }

    for (int i = 0; i < v_size; i++)
        verts[i].search_set(i);

    int comp = 0;
    vertex * vert = nullptr;
    for (int i = 0; i < v_size; i++) {
        vert = &(verts[ordered[i]]);

        if (vert->color)
            continue;

        vert->comp = ++comp;
        cond_visit(*vert);
    }

    comps = comp;
    cond_on = false;
}
void graph::cond_visit(vertex & vert) {
    vert.color = 1;

    adj_list::adj_node * node = vert.list.first;
    while (node != nullptr) {
        if (!node->vert->color) {
            node->vert->comp = vert.comp;
            cond_visit(*node->vert);
        }

        node = node->next;
    }

    vert.color = 2;
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

bool graph::isgamway() {
    gm_topsort();
    return gm_check(verts[ordered[0]]);
}
void graph::gm_topsort() {
    if (ordered != nullptr) {
        delete[] ordered;
        ordered = nullptr;
    }
    ordered = new int[v_size];
    setpos();

    for(int i = 0; i < v_size; i++)
        verts[i].search_set(i);

    int order = v_size - 1;
    for (int i = 0; i < v_size; i++) {
        if (verts[i].color)
            continue;

        gm_ts_visit(verts[i], order);
    }
}
void graph::gm_ts_visit(vertex & vert, int & order) {
    vert.color = 1;

    adj_list::adj_node * node = vert.list.first;
    while (node != nullptr) {
        if (!node->vert->color)
            gm_ts_visit(*node->vert, order);
        node = node->next;
    }

    vert.color = 2;
    vert.order = order--;
    ordered[vert.order] = vert.pos;
}
bool graph::gm_check(vertex & vert) {
    if (vert.order == v_size - 1)
        return true;

    adj_list::adj_node * node = vert.list.first;

    while(node != nullptr) {
        if ((vert.order + 1) == node->vert->order)
            return gm_check(verts[node->vert->pos]);

        node = node->next;
    }

    return false;
}

bool const & graph::isorient() const {
    return this->orient;
}
bool const & graph::isacyclic() const {
    return this->acyclic;
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
int const graph::getcomp(int &pos) const {
    return verts[pos].comp;
}
int const graph::getcomps() const {
    return comps;
}
std::string const graph::getway() const {
    return way;
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
void graph::adj_list::del() {
    if (first != nullptr)
        del_node(first);
    first = nullptr;
}
void graph::adj_list::del_node(adj_node * node) {
    if (node->next != nullptr)
        del_node(node->next);
    delete node;
}

int main() {
    std::ifstream input("input.txt");
    graph gr;
    gr.edgread(input);
    input.close();
    gr.adjlist();

    std::ofstream output("output.txt");
    if (gr.isgamway())
        output << "YES";
    else output << "NO";
    return 0;
}
