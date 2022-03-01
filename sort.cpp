#include <iostream>
#include <random>

void swap(int &a, int &b){
	int tmp = a;
	a = b;
	b = tmp;
}

void fill(int array[], int n){
	std::mt19937 rng(1234);
	std::uniform_int_distribution<int> dist(0, n);
	for(int i = 0; i < n; i++){
		array[i] = dist(rng);
	}
}

void print(int array[], int n){
	for(int i = 0; i < n; i++){
		std::cout << array[i];
	}
	std::cout <<std::endl;
}

void select_sort(int array[], int n){
	for(int i = 0; i < n; i++){
		int max_index = 0;
		for(int j = 0; j < n - i; j++){
			if(array[j] > array[max_index]) max_index = j;
		}
		swap(array[n - i - 1], array[max_index]);
	}
}

void quick_sort(int array[], int n){
	if(n > 1){
		int l = 0, r = n - 2;
		while(l < r){
			for(;array[l] < array[n];l++);
			for(;array[r] > array[n];r--);
		}
	}
}

void heat_sort(int array[], int n){
	for(int i = n / 2 - 1; i >= 0; i--){
		if(array[i] < array[2 * i + 1]){
			if(2 * i + 2 < n && array[2 * i + 2] > array[2 * i + 1]){
				swap(array[2 * i + 2], array[i]);
			} else {
				swap(array[2 * i + 1], array[i]);
			}
		}
	}
	for(; n > 0; n--){
		int index = 0;
		swap(array[0], array[n - 1]);
		while(index <= n / 2 - 1){
			if(array[index] < array[2 * index + 1]){
			if(2 * index + 2 < n && array[2 * index + 2] > array[2 * index + 1]){
				swap(array[2 * index + 2], array[index]);
			} else {
				swap(array[2 * index + 1], array[index]);
			}
		}
		}
	}
}

int main() {
	int n = 10;
	int *array = new int [n];
	fill(array, n);
	print(array, n);
	quick_sort(array, n);
	print(array, n);
	return 0;
}
