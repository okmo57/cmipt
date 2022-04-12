#include <iostream>
#include <string>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::sort;

/*struct denom_array_t D_crutch(){
    int p, q;
    cin >> p >> q;
    int i = 0, j = 1;
    for(;p;i++){
        for(;p * j < q;j++);
        int p1 = p;
        int q1 = q;
        q = p1 * q1;
        p = p * j - q;
    }
    auto *sign = new unsigned [i];
    i = 0, j = 1;
    for(;p;i++){
        for(;p * j < q;j++);
        int p1 = p;
        int q1 = q;
        q = p1 * q1;
        p = p * j - q;
        sign[i] = j;
    }
    struct denom_array_t { unsigned *arr; unsigned den; };
    struct denom_array_t st;
    st.arr = sign;
    st.den = i;
}*/

void A(){
    int s, n;
    cin >> s >> n;
    int *users = new int[n];
    for(int i = 0; i < n; i++)
        cin >> users[i];
    sort(users, users + n);
    int count = 0;
    int i = 0;
    for(; i < n; i++){
        count += users[i];
        if(count > s) break;
    }
    cout << i << endl;
    delete[] users;
}

void B(){
    int n, k, s;
    cin >> n >> k >> s;
    int *petrol = new int[s + 3];
    petrol[0] = 0;
    petrol[s + 1] = n;
    petrol[s + 2] = 5757;
    for(int i = 1; i < s + 1; i++)
        cin >> petrol[i];
    int dist = 0;
    int i = 0;
    int count = -1;
    while(dist - n){
        for(; i < s + 2; i++){
            if(petrol[i] - dist > k){
                i--;
                if(petrol[i] == dist){
                    cout << -1 << endl;
                    return;
                }
                cout << i << endl;
                break;
            }
            cout << i << " " << petrol[i] << " " << dist << endl;
        }
        dist = petrol[i];
        cout <<
        count++;
    }
    cout << count << endl;
}

void C(){
    int n; cin >> n;
    int **lect = new int*[n];
    for(int i = 0; i < n; i++){
        lect[i] = new int[2];
    }
    for(int i = 0; i < n; i++)
        cin >> lect[i][0] >> lect[i][1];
    int time = 0;
    int count = 0;
    for(int i = 0; i < n; i++){
        if(lect[i][0] >= time){
            count++;
            time = lect[i][1];
        }
    }
    cout << count << endl;
    for(int i = 0; i < n; i++){
        delete[] lect[i];
    }
    delete[] lect;
}

void D(){

}

void E(){
    const int a[5] = {1, 5, 25, 50, 100};
    int q; cin >> q;
    int count = 0;
    for(int i = 4; i >= 0; i--){
        count += q / a[i];
        q %= a[i];
    }
    cout << count << endl;
}

int main(){
    //A();
    //B();
    //C();
    //D();
   // E();
    return 0;
}
