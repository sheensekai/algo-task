#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#define INF INT_MAX

struct AdjEdge {
    AdjEdge(int vert, int weight) :
            vert_(vert),
            weight_(weight) {}

    int vert_;
    int weight_;
};

struct Vertex {
    Vertex() :
            prev_path_(INF),
            curr_path_(INF),
            prev_walkable_(false),
            curr_walkable_(false),
            par(-1) {}

    int prev_path_;
    int curr_path_;
    bool prev_walkable_;
    bool curr_walkable_;
    int par;
    std::vector<AdjEdge> adj_list_;
};

void VertsCurrInit(std::vector<Vertex> &verts);

void BellFordK(std::vector<Vertex> &verts, int start, int k);

void VertRelax(std::vector<Vertex> &verts, int out_vert, AdjEdge &edge);

int main() {
    std::ifstream input("kpath.in");
    std::ofstream output("kpath.out");
    unsigned v = 0;
    unsigned e = 0;
    unsigned plength = 0 ;
    unsigned start = 0;
    std::cin >> v >> e >> plength >> start;
    --start;

    std::vector<Vertex> verts(v);

    int in_vert = 0;
    int out_vert = 0;
    int weight = 0;
    for (int i = 0; i < e; ++i) {
        std::cin >> out_vert >> in_vert >> weight;
        verts[out_vert - 1].adj_list_.emplace_back(in_vert - 1, weight);
    }

    BellFordK(verts, start, plength);

    for (int i = 0; i < v; ++i) {
        if (verts[i].prev_walkable_)
            std::cout << verts[i].prev_path_ << std::endl;
        else std::cout << -1 << std::endl;

    }

    input.close();
    output.close();
    return 0;
}

void BellFordK(std::vector<Vertex> &verts, int start, int k) {
    verts[start].prev_path_ = 0;
    verts[start].curr_path_ = INF;
    verts[start].prev_walkable_ = true;
    verts[start].curr_walkable_ = false;

    for (int cycle = 0; cycle < k; ++cycle) {
        for (int i = 0; i < verts.size(); ++i) {
            if (!verts[i].prev_walkable_)
                continue;

            for (auto edge : verts[i].adj_list_)
                VertRelax(verts, i, edge);
        }

        VertsCurrInit(verts);
    }
}

void VertRelax(std::vector<Vertex> &verts, int out_vert, AdjEdge &edge) {
    if (verts[out_vert].prev_path_ + edge.weight_ < verts[edge.vert_].curr_path_) {
        verts[edge.vert_].par = out_vert;
        verts[edge.vert_].curr_path_ = verts[out_vert].prev_path_ + edge.weight_;
        verts[edge.vert_].curr_walkable_ = true;
    }
}

void VertsCurrInit(std::vector<Vertex> &verts) {
    for (int i = 0; i < verts.size(); ++i) {
        verts[i].prev_path_ = verts[i].curr_path_;
        verts[i].curr_path_ = INF;
        verts[i].prev_walkable_ = verts[i].curr_walkable_;
        verts[i].curr_walkable_ = false;
    }
}