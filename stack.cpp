#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stoi;

template <class T>
class Stack{
    T mass[1000];
    int p = 0;
public:
    bool empty(){
        return p == 0;
    }
    void add(T elem){
        mass[p] = elem;
        p++;
    }
    void del(){
        if(p){
            p--;
        } else {
            cout << "out of range!" << endl;
        }
    }
    T last(){
        if(p){
            return mass[p - 1];
        } else {
            cout << "out of range!" << endl;
            return mass[p];
        }
    }
};

int brackets(string s){
    Stack<char> st;
    const char br[8] = {'(', '[', '<', '{', ')', ']', '>', '}'};
    for(int i = 0; i < s.size(); i++){
        int j = 0;
        for(; j < 8; j++){
            if(br[j] == s[i]) break;
        }
        if(j < 4){
            st.add(s[i]);
        } else {
            if(st.empty()) return -1;
            if(st.last() == br[j - 4]){
                st.del();
            }
            else {
                return -1;
            }
        }
    }
    if(st.empty()) return 0;
    return -1;
}

int curroper(int l, int r, string s){
    int ans = -1;
    int brackets = 0;
    for(;l <= r; r--){
        if(brackets == 0){
            if((s[r] == '+' || s[r] == '-') && l < r && s[r - 1] != '+' && s[r - 1] != '-' && s[r - 1] != '*' &&
               s[r - 1] != '/') return r;
            if((s[r] == '*' || s[r] == '/') && ans == -1) ans = r;
        }
        if(s[r] == ')') brackets++;
        if(s[r] == '(') brackets--;
    }
    return ans;
}

string mathstep(int l, int r, string s){
    while(s[l] == '(' && s[r] == ')'){
        bool del = true;
        for(int i = r; i > l;i--){
            if(s[i] == '('){
                for(int j = i - 1; j >= l; j--){
                    if(s[j] != '(') del = false;
                }
            }
        }
        if(del){
            l++;
            r--;
        } else break;
    }
    int c = curroper(l, r, s);
    if(c == -1) {
        return s.substr(l, r - l + 1);
    }
    else{
        return mathstep(l, c - 1, s) + " " + mathstep(c + 1, r, s) + " " + s[c];
    }
}

string math(string s){
    return mathstep(0, s.size() - 1, s);
}

int count(string s){
    Stack<int> st;
    int l = 0;
    for(int i = 0; i <= s.size(); i++){
        if(s[i] == ' ' || i == s.size()){
            string t = s.substr(l, i - l);
            switch (t[t.size() - 1]) {
                case '+':
                {
                    int b = st.last();
                    st.del();
                    int a = st.last();
                    st.del();
                    st.add(a + b);
                    break;
                }
                case '-':
                {
                    int b = st.last();
                    st.del();
                    int a = st.last();
                    st.del();
                    st.add(a - b);
                    break;
                }
                case '*':
                {
                    int b = st.last();
                    st.del();
                    int a = st.last();
                    st.del();
                    st.add(a * b);
                    break;
                }
                case '/':
                {
                    int b = st.last();
                    st.del();
                    int a = st.last();
                    st.del();
                    st.add(a / b);
                    break;
                }
                default:
                {
                    st.add(stoi(t));
                    break;
                }
            }
            l = i + 1;
        }
    }
    return st.last();
}

int main() {
    //cout << brackets("") << endl;
    string postf = math("1+2*(11/5)");
    cout << postf << endl;
    cout << count(postf) << endl;
    return 0;
}
