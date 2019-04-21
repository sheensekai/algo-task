#include <fstream>
#include <vector>
#include <string>

void StringMatch(std::string &needle, std::string &heystag, std::vector<int> &ans);

int main() {

    std::ifstream input("search1.in");
    std::string heystag, needle;
    input >> needle >> heystag;
    input.close();

    std::vector<int> ans;
    StringMatch(needle, heystag, ans);

    std::ofstream output("search1.out");
    output << ans.size() << '\n';
    if (!ans.empty()) {
        int size = ans.size();
        for (int i = 0; i < size; ++i)
            output << ans[i] + 1 << ' ';
    }

    return 0;
}

void StringMatch(std::string &needle, std::string &heystag, std::vector<int> &ans) {
    int h_size = heystag.size();
    int n_size = needle.size();
    int diff_size = h_size - n_size;

    for (int i = 0; i <= diff_size; ++i) {
        bool str_match = true;

        for (int j = 0; j < n_size && str_match; ++j) {
            if (needle[j] != heystag[i + j])
                str_match = false;
        }

        if (str_match)
            ans.push_back(i);
    }

}