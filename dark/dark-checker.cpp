#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <num1> <num2>" << endl;
        return 1;
    }

    const double n1 = atof(argv[1]);
    const double n2 = atof(argv[2]);

    return fabs(n1-n2) > 1e-4;

}