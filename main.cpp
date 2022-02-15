#include <random>
#include <iostream>
class Crystal{
public:
	static const int size = 10;
	int map[size][size];
	Crystal(int number){
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				map[i][j] = 0;
			}
		}
		for(int i = 0; i < number; i++){
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<int> dist(0, size * size - 1);
			int chosen = dist(rng);
			if(map[chosen / size][chosen % size]){
				map[chosen / size][chosen % size] = 1;
			} else {
				i--;
			}
		}
	}
	bool on_edge(int i, int j){
		return !(i && j && (size - i - 1) && (size - j - 1));
	}
	bool has_neighbor(int i, int j){
		return map[i - 1][j] || map[i + 1][j] || map[i][j - 1] || map[i][j + 1];
	}
	void mobility_check(){
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				if(map[i][j] == 1 && (on_edge(i, j) || has_neighbor(i, j))){
					map[i][j] = -1;
				}
			}
		}
	}
	void direction(int &x_y){
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<int> dist(0, 3);
		int chosen = dist(rng);
		int result[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
		x_y = result[chosen];
	}
	void move(){
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				if(map[i][j] == 1){
					int dir[2];
					direction(dir);
					if(!map[i + dir[0]][j + dir[1]]){
						map[i + dir[0]][j + dir[1]] = 1;
						map[i][j] = 0;
					}
				}
			}
		}
	}
	void print(){
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				std::cout << map[i][j] ? '*' : '0';
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;
	}
	bool in_process(){
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				if(map[i][j] == 1) return true;
			}
		}
		return false;
	}
};

int main() {
	Crystal c(1);
	while(c.in_process()){
		c.mobility_check();
		c.move();
		c.print();
	}
	return 0;
}
