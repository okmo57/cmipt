#include <iostream>
#include <random>
#include <chrono>

class Crystal {
	int **map1;
    int ***map2;
    int size;
    bool adhesion;
    const int dir[4][2] = {{-1, 0},
                           {1,  0},
                           {0,  -1},
                           {0,  1}};

    void print() {
    	if(adhesion){
	    	for (int i = 0; i < size; i++) {
	            for (int j = 0; j < size; j++) {
	                std::cout << map1[i][j];
	            }
	            std::cout << std::endl;
	        }
	        for (int i = 0; i < size; i++) {
	            std::cout << '-';
	        }
	        std::cout << std::endl;
    	}
    	else{
	    	for (int i = 0; i < size; i++) {
	            for (int j = 0; j < size; j++) {
	            	bool dislocation_exists = false;
	            	for (int k = 0; k < size; k++){
	            		if(map2[i][j][k]){
	            			std::cout << map2[i][j][k];
	            			dislocation_exists = true;
	            			break;
	            		}
	            	}
	            	if(!dislocation_exists){
	            		std::cout << 0;
	            	}
	            }
	            std::cout << std::endl;
	        }
	        for (int i = 0; i < size; i++) {
	            std::cout << '-';
	        }
	        std::cout << std::endl;
    	}
    }

    int random(int min, int max) {
        std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    bool on_edge(int x, int y) {
        return !(x && y && (size - x - 1) && (size - y - 1));
    }
    
    bool has_neighbor(int x, int y) {
        return map1[x - 1][y] || map1[x + 1][y] || map1[x][y - 1] || map1[x][y + 1];
    }

    void check() {
    	if (adhesion){
	    	for (int i = 0; i < size; i++) {
	            for (int j = 0; j < size; j++) {
	                if ((map1[i][j] == 1) && (on_edge(i, j) || has_neighbor(i, j))) {
	                    map1[i][j] = 3;
	                }
	            }
	        }
    	}
    	else{
	    	for (int i = 0; i < size; i++) {
	            for (int j = 0; j < size; j++) {
	            	for(int k = 0; k < size; k++){
	            		if ((map2[i][j][k] == 1) && on_edge(i, j)) {
	                    	map2[i][j][k] = 3;
	            		}
	            	}
	            }
	        }
    	}
    }

    void move() {
    	if (adhesion){
	    	for (int i = 0; i < size; i++) {
	            for (int j = 0; j < size; j++) {
	                if (map1[i][j] == 1) {
	                    int rnd[2];
	                    int variant = random(0, 3);
	                    rnd[0] = dir[variant][0];
	                    rnd[1] = dir[variant][1];
	                    if (!map1[i + rnd[0]][j + rnd[1]]) {
	                        map1[i + rnd[0]][j + rnd[1]] = 2;
	                        map1[i][j] = 0;
	                    }
	                }
	            }
	        }
    	}
    	else{
	    	for (int i = 0; i < size; i++) {
	            for (int j = 0; j < size; j++) {
	            	for (int k = 0; k < size; k++) {
	                	if (map2[i][j][k] == 1) {
	                    	int rnd[2];
	                    	int variant = random(0, 3);
	                    	rnd[0] = dir[variant][0];
	                    	rnd[1] = dir[variant][1];
	                    	for(int x = 0; x < size; x++){
	                    		if(!map2[i + rnd[0]][j + rnd[1]][x]){
	                        		map2[i + rnd[0]][j + rnd[1]][x] = 2;
	                        		map2[i][j][k] = 0;
	                        		break;
	                    		}
	                    	}
	                	}
	                }
	            }
	        }
    	}
    }

    void stop() {
    	if (adhesion){
	    	for (int i = 0; i < size; i++) {
	            for (int j = 0; j < size; j++) {
	                if (map1[i][j] == 2) {
	                    map1[i][j] = 1;
	                }
	            }
	        }
    	}
    	else{
	    	for (int i = 0; i < size; i++) {
	            for (int j = 0; j < size; j++) {
	            	for (int k = 0; k < size; k++) {
		                if (map2[i][j][k] == 2) {
		                    map2[i][j][k] = 1;
		                }
	            	}
	            }
	        }
    	}
    }

    bool finished() {
    	if (adhesion){
	    	for (int i = 0; i < size; i++) {
	            for (int j = 0; j < size; j++) {
	                if (map1[i][j] - 3 && map1[i][j]) {
	                    return false;
	                }
	            }
	        }
	        return true;
    	}
    	else{
	    	for (int i = 0; i < size; i++) {
	            for (int j = 0; j < size; j++) {
	            	for (int k = 0; k < size; k++) {
		                if (map2[i][j][k] - 3 && map2[i][j][k]) {
		                    return false;
		                }
	            	}
	            }
	        }
	        return true;
    	}
    }

public:
    Crystal(int N, int number, int ad) {
        //statements:
        //0 - atom
        //1 - mobile dislocation, who didn't move on this move
        //2 - mobile dislocation, who moved on this move
        //3 - immobile dislocation
        size = N;
        adhesion = ad;
        if(adhesion){
	        map1 = new int *[size];
	        for (int i = 0; i < size; i++) {
	            map1[i] = new int[size];
	        }
	        for (int i = 0; i < size; i++) {
	            for (int j = 0; j < size; j++) {
	                map1[i][j] = 0;
	            }
	        }
	        while (number) {
	            int attempt = random(0, size * size - 1);
	            if (!map1[attempt / size][attempt % size]) {
	                map1[attempt / size][attempt % size] = 1;
	                number--;
	            }
	        }
        }
        else{
	        map2 = new int **[size];
	        for (int i = 0; i < size; i++) {
	            map2[i] = new int *[size];
	        }
	        for (int i = 0; i < size; i++){
	        	for(int j = 0; j < size; j++){
	        		map2[i][j] = new int [size * size];
	        	}
	        }
	        for (int i = 0; i < size; i++) {
	            for (int j = 0; j < size; j++) {
	            	for (int k = 0; k < size; k++){
	                	map2[i][j][k] = 0;
	            	}
	            }
	        }
	        while (number) {
	            int attempt = random(0, size * size - 1);
	            map2[attempt / size][attempt % size][0]++;
	            number--;
	        }
	        for (int i = 0; i < size; i++){
	        	for(int j = 0; j < size; j++){
	        		for(int k = 0; k < map2[i][j][0]; k++){
	        			map2[i][j][k] = 1;
	        		}
	        	}
	        }
        }
    }

    int mainloop() {
        int count = 0;
        while (!finished()) {
        	print();
            check();
            print();
            move();
            print();
            stop();
            count++;
        }
        return count;
    }

};

int main() {
    Crystal c(5, 10, false);
    c.mainloop();
    return 0;
}
