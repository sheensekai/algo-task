#include "handmade_graph.h"

void graph::edgread(std::ifstream &input) {
    input >> v_size >> e_size;
    verts = new vertex[v_size];
    edges = new edge[e_size];

    for (int i = 0; i < e_size; i++)
        input >> edges[i].out >> edges[i].in;
}
void graph::add_edge(int &out, int &in) {

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
void graph::rev_adjlist() {
    for (int i = 0; i < v_size; i++) {
        verts[i].deg_in = 0;
        verts[i].deg_out = 0;
    }

    int out, in;
    for (int i = 0; i < e_size; i++) {
        out = edges[i].out;
        in = edges[i].in;

        verts[in - 1].list.add_node(&verts[out - 1]);
        verts[out - 1].deg_out++;
        verts[in - 1].deg_in++;
        if (!orient) {
            verts[in - 1].list.add_node(&verts[out - 1]);
            verts[out - 1].deg_in++;
            verts[in - 1].deg_out++;
        }
    }
}
    size_t abc;
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
    pos = num;
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

int graph::game(std::ifstream &input) {
    int start;
    input >> v_size >> e_size >> start;
    start -= 1;
    verts = new vertex[v_size];
    edges = new edge[e_size];

    for (int i = 0; i < e_size; i++)
        input >> edges[i].out >> edges[i].in;
    rev_adjlist();

    vertex * vert = find_vert(0);
    if (vert == nullptr)
        return 0;

    for (int i = 0; i < v_size; i++)
        verts[i].search_set(i);

    vert->color = 2;
    std::queue<vertex *> queue;
    queue.push(vert);

    vert = nullptr;
    adj_list::adj_node * node = nullptr;
    while(!queue.empty()) {
        vert = queue.front();
        queue.pop();

        node = vert->list.first;
        while(node != nullptr) {
            if (!node->vert->color) {
                if (vert->color == 1)
                    node->vert->color = 2;
                else node->vert->color = 1;

                queue.push(node->vert);
            }
            else if (vert->color == 2 && node->vert->color == 2)
                node->vert->color = 1;

            if (node->vert->pos == start && node->vert->color == 1)
                return 1;

            node = node->next;
        }
    }

    return 2;
}
graph::vertex * graph::find_vert(int deg) {
    for (int i = 0; i < v_size; i++) {
        if (verts[i].deg_out == deg)
            return &verts[i];
    }

    return nullptr;
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

