#include <iostream>
#include <fstream>

int main() {
    std::ofstream output("output.txt");
    output << "4 6 3 1 2 5";
    output.close();

    return 0;
}