#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace chrono;
int main() {
    auto start = high_resolution_clock::now();
    system("./gray_scale.sh");
    auto end = high_resolution_clock::now();
    duration<double> total = end - start;
    cout << "This program took " << total.count() << " sec" << endl;
    return 0;
}
