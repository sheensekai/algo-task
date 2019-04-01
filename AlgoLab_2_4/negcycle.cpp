#include <fstream>
#include <iostream>
#include <vector>
#include <forward_list>
#include <climits>
#define INF (LONG_LONG_MAX / 2)
struct Edge {
    Edge(int vert, long long w) :
        vert(vert),
        weight(w) {}

    int vert;
    long long weight;
};
struct BellFord {

    void SetSize() {
        dist.resize(v);
        par.resize(v);
        ans.resize(v);
        ans.clear();
        adj_lists.resize(v);
    }

    void Init() {
        for (int i = 0; i < v; ++i) {
            dist[i] = INF;
            par[i] = -1;
        }
        dist[start] = 0;
    }

    void Relax(int out, int in, long long w) {
        if (dist[out] + w < dist[in]) {
            dist[in] = dist[out] + w;
            par[in] = out;
        }

    }

    std::vector<long long> dist;
    std::vector<int> par;
    std::vector<int> ans;
    std::vector<std::forward_list<Edge>> adj_lists;
    int start = 0;
    int cycle_len = 0;
    unsigned v = 0;

};

int main() {

    std::ifstream input("negcycle.in");
    BellFord info;
    input >> info.v;
    info.start = 0;

    info.SetSize();
    info.Init();

    long long weight = 0;
    for (int i = 0; i < info.v; ++i) {
        for (int j = 0; j < info.v; ++j) {
            input >> weight;

            if (weight != 1000000000)
                info.adj_lists[i].emplace_front(j, weight);
        }
    }

    input.close();

    for (int k = 0; k < info.v; ++k) {
        for (int i = 0; i < info.v; ++i) {
            for (std::forward_list<Edge>::iterator it = info.adj_lists[i].begin();
                 it != info.adj_lists[i].end(); ++it) {
                info.Relax(i, it->vert, it->weight);
            }
        }
    }

    bool found = false;
    for (int i = 0; i < info.v; ++i) {
        if (found)
            break;
        for (std::forward_list<Edge>::iterator it = info.adj_lists[i].begin();
             it != info.adj_lists[i].end(); ++it) {
            int out = i;
            int in = it->vert;
            long long w = it->weight;
            if (info.dist[in] > info.dist[out] + w) {
                for (int i = 0; i < info.v - 1; ++i)
                    in = info.par[in];
                int tmp = in;
                info.ans.push_back(in);
                ++info.cycle_len;
                in = info.par[in];
                while (in != tmp) {
                    info.ans.push_back(in);
                    ++info.cycle_len;
                    in = info.par[in];
                }
                info.ans.push_back(in);
                ++info.cycle_len;
                found = true;
                break;
            }
        }
    }

    std::ofstream output("negcycle.out");
    if (info.cycle_len) {
        output << "YES" << std::endl;
        output << info.cycle_len << std::endl;
        for (int i = info.cycle_len - 1; i >= 0; --i)
            output << info.ans[i] + 1 << " ";
    } else output << "NO";

    return 0;

}