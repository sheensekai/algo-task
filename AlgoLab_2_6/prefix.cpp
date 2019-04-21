#include <fstream>
#include <vector>

void PrefixFunc(std::string &heystag, std::vector<int> &borders);

int main() {
    std::ifstream input("prefix.in");
    std::string heystag;
    input >> heystag;
    input.close();

    std::vector<int> borders(heystag.length());
    PrefixFunc(heystag, borders);

    std::ofstream output("prefix.out");
    for (int pref_val : borders)
        output << pref_val << ' ';
}

void PrefixFunc(std::string &heystag, std::vector<int> &borders) {
    borders[0] = 0;
    for (int i = 1; i < heystag.length(); ++i) {
        int k = borders[i - 1];
        while (k > 0 && heystag[i] != heystag[k])
            k = borders[k - 1];
        if (heystag[i] == heystag[k])
            ++k;
        borders[i] = k;
    }
}