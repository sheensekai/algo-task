#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <climits>
#define LIM (ULONG_LONG_MAX)

void StringMatch(std::string &needle, std::string &heystag, std::vector<int> &ans);

int main() {

    std::ifstream input("search2.in");
    std::string heystag, needle;
    input >> needle >> heystag;
    input.close();

    std::ofstream output("search2.out");

    if (needle.size() > heystag.size()) {
        output << 0;
        return 0;
    }

    std::vector<int> ans;
    StringMatch(needle, heystag, ans);


    output << ans.size() << '\n';
    if (!ans.empty()) {
        for (int pos : ans)
            output << pos + 1 << ' ';
    }

    return 0;
}

void StringMatch(std::string &needle, std::string &heystag, std::vector<int> &ans) {
    int h_size = heystag.size();
    int n_size = needle.size();
    int diff_size = h_size - n_size;

    unsigned long long p = 20; // осн. системы счисления
    std::vector<long long> pows(h_size); // степени p
    pows[0] = 1;
    for (int i = 1; i < h_size; ++i)
        pows[i] = pows[i - 1] * p;

    std::vector<unsigned long long> hashes(h_size);
    hashes[0] = heystag[0] - 'A' + 1;
    for (int i = 1; i < h_size; ++i)
        hashes[i] = (heystag[i] - 'A' + 1) * pows[i] + hashes[i - 1];

    unsigned long long needle_hash = 0;
    for (int i = 0; i < n_size; ++i)
        needle_hash += (needle[i] - 'A' + 1) * pows[i];

    for (int i = 0; i <= diff_size; ++i) {
        unsigned long long pre_hash = hashes[i + n_size - 1];
        if (i)
            pre_hash -= hashes[i - 1];
        if (pre_hash == needle_hash * pows[i])
            ans.push_back(i);
    }
}