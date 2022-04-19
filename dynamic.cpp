#include <iostream>
#include <string>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::max;
using std::min;
using std::to_string;

void A(int n){
    int *nav = new int[n + 1];
    auto *way = new string[n + 1];
    const int prices[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    for(int i = 0; i < n; i++){
        nav[i] = -1;
        way[i] = "";
    }
    for(int i = 0; i < 11 && i <= n; i++){
        nav[i] = prices[i];
        way[i] += to_string(i);
        way[i] += " ";
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; i + j <= n; j++){
            if((nav[i + j]) < nav[i] + nav[j]){
                (nav[i + j]) = nav[i] + nav[j];
                way[i + j] = way[i] + way[j];
            }
        }
    }
    cout << nav[n] << endl << way[n] << endl;
    delete[] nav;
    delete[] way;
}

void B(int n){
    auto trib = new unsigned long long[n + 1];
    trib[0] = 0;
    trib[1] = 1;
    trib[2] = 1;
    for(int i = 3; i <= n; i++){
        trib[i] = trib[i - 1] + trib[i - 2] + trib[i - 3];
    }
    cout << trib[n] << endl;
    delete[] trib;
}

void C(string A, string B){
    const int ans[2][2][2] = {0, 1, 1, 1, 1, 1, 1, 1};
    int a = A.size() + 1;
    int b = B.size() + 1;
    auto **table = new int*[a];
    for(int i = 0; i < a; i++)
        table[i] = new int[b];
    for(int i = 0; i < a; i++)
        table[i][0] = 0;
    for(int i = 0; i < b; i++)
        table[0][i] = 0;
    for(int i = 1; i < a; i++){
        for(int j = 1; j < b; j++){
            table[i][j] = table[i - 1][j - 1] + ans[table[i][j - 1] - table[i - 1][j - 1]][table[i - 1][j] - table[i - 1][j - 1]][int(A[i - 1] == B[j - 1])];
        }
    }
    cout << 100 * table[a - 1][b - 1] / min(a - 1, b - 1) << endl;
    for(int i = 0; i < a; i++)
        delete[] table[i];
    delete[] table;
}

int main(){
    A(8);
    B(37);
    C("ACCGGTCGAG", "GTCGTTCGGA");
    return 0;
}
