#include <iostream>
#include <random>
#include <string>

class Sortings {
    int *array;
    int n;

    void swap(int &a, int &b) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    void heap_step(int i){
        int j = i;
        if(2 * i + 1 < n && array[2 * i + 1] > array[i]) {
            j = 2 * i + 1;
        }
        if (2 * i + 2 < n && array[2 * i + 2] > array[i] && array[2 * i + 2] > array[2 * i + 1]) {
            j = 2 * i + 2;
        }
        if(j == i) {
            return;
        }
        swap(array[i], array[j]);
        heap_step(j);
    }

    void _quick_sort(int l, int r) {
        int L = l;
        int R = r;
        int pivot = array[R];
        if (R - L > 0) {
            while (l < r) {
                for (; l < r && array[l] <= pivot; l++);
                for (; l < r && array[r] >= pivot; r--);
                swap(array[l], array[r]);
            }
            swap(array[l], array[R]);
            _quick_sort(L, l - 1);
            _quick_sort(l + 1, R);
        }
    }

public:
    Sortings(int N) {
        n = N;
        array = new int[n];
    }

    void fill(int seed) {
        std::mt19937 rng(seed);
        std::uniform_int_distribution<int> dist(0, n - 1);
        for (int i = 0; i < n; i++) {
            array[i] = dist(rng);
        }
    }

    void print() {
        for (int i = 0; i < n; i++) {
            std::cout << array[i];
        }
        std::cout << std::endl;
    }

    void select_sort() {
        for (int i = 0; i < n; i++) {
            int max_index = 0;
            for (int j = 0; j < n - i; j++) {
                if (array[j] > array[max_index]) max_index = j;
            }
            swap(array[n - i - 1], array[max_index]);
        }
    }

    void quick_sort(){
        _quick_sort(0, n - 1);
    }

    void heap_sort() {
        for(int i = n / 2 - 1; i >= 0; i--){
            heap_step(i);
        }
        int tn = n;
        n--;
        for(; n > 0; n--){
            swap(array[0], array[n]);
            heap_step(0);
        }
        n = tn;
    }
};

int main() {
    Sortings s(10);
    s.fill(1);
    s.print();
    s.select_sort();
    s.print();
    s.fill(1);
    s.quick_sort();
    s.print();
    s.fill(1);
    s.heap_sort();
    s.print();
    return 0;
}
