#include <iostream>
#include <random>
#include <chrono>

class Crystal {
    int **map;
    int size;
    const int dir[4][2] = {{-1, 0},
                           {1,  0},
                           {0,  -1},
                           {0,  1}};

    void print() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << map[i][j];
            }
            std::cout << std::endl;
        }
        for (int i = 0; i < size; i++) {
            std::cout << '-';
        }
        std::cout << std::endl;
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
        return map[x - 1][y] || map[x + 1][y] || map[x][y - 1] || map[x][y + 1];
    }

    void check() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if ((map[i][j] == 1) && (on_edge(i, j) || has_neighbor(i, j))) {
                    map[i][j] = 3;
                }
            }
        }
    }

    void move() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (map[i][j] == 1) {
                    int rnd[2];
                    int variant = random(0, 3);
                    rnd[0] = dir[variant][0];
                    rnd[1] = dir[variant][1];
                    if (!map[i + rnd[0]][j + rnd[1]]) {
                        map[i + rnd[0]][j + rnd[1]] = 2;
                        map[i][j] = 0;
                    }
                }
            }
        }
    }

    void stop() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (map[i][j] == 2) {
                    map[i][j] = 1;
                }
            }
        }
    }

    bool finished() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (map[i][j] - 3 && map[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    ~Crystal(){
        for(int i = 0; i < size; i++) delete map[i];
        delete map;
    }

public:
    Crystal(int N, int number) {
        //statements:
        //0 - atom
        //1 - mobile dislocation, who didn't move on this move
        //2 - mobile dislocation, who moved on this move
        //3 - immobile dislocation
        size = N;
        map = new int *[size];
        for (int i = 0; i < size; i++) {
            map[i] = new int[size];
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                map[i][j] = 0;
            }
        }
        while (number) {
            int attempt = random(0, size * size - 1);
            if (!map[attempt / size][attempt % size]) {
                map[attempt / size][attempt % size] = 1;
                number--;
            }
        }
    }

    int mainloop() {
        int count = 0;
        while (!finished()) {
            check();
            move();
            stop();
            count++;
        }
        return count;
    }

    void bottleneck() {
        map[1][1] = 1;
        map[2][2] = 1;
        print();
        move();
        print();
    }
};

class Crystal_1d {
    int *map;
    int size;

    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << map[i];
        }
        std::cout << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << '-';
        }
        std::cout << std::endl;
    }

    int random(int min, int max) {
        std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    bool on_edge(int x) {
        return !(x && (size - x - 1));
    }

    bool has_neighbor(int x) {
        return map[x - 1] || map[x + 1];
    }

    void check() {
        for (int i = 0; i < size; i++) {
            if ((map[i] == 1) && (on_edge(i) || has_neighbor(i))) {
                map[i] = 3;
            }
        }
    }

    void move() {
        for (int i = 0; i < size; i++) {
            if (map[i] == 1) {
                int rnd = random(0, 1) * 2 - 1;
                if (!map[i + rnd]) {
                    map[i + rnd] = 2;
                    map[i] = 0;
                }
            }
        }
    }

    void stop() {
        for (int i = 0; i < size; i++) {
            if (map[i] == 2) {
                map[i] = 1;
            }

        }
    }

    bool finished() {
        for (int i = 0; i < size; i++) {
            if (map[i] - 3 && map[i]) {
                return false;
            }
        }
        return true;
    }

public:

    Crystal_1d(int N, int number) {
        //statements:
        //0 - atom
        //1 - mobile dislocation, who didn't move on this move
        //2 - mobile dislocation, who moved on this move
        //3 - immobile dislocation
        size = N;
        map = new int[size];
        for (int i = 0; i < size; i++) {
            map[i] = 0;
        }
        while (number) {
            int attempt = random(0, size - 1);
            if (!map[attempt]) {
                map[attempt] = 1;
                number--;
            }
        }
    }

    int mainloop() {
        int count = 0;
        while (!finished()) {
            check();
            move();
            stop();
            count++;
        }
        return count;
    }

};

void first_task() {
    int result;
    for (int i = 1; i < 30; i++) {
        result = 0;
        for (int j = 0; j < 1000; j++) {
            Crystal c(i, 1);
            result += c.mainloop();
        }
        std::cout << i << " " << result / 1000.0 << std::endl;
    }
}

void second_task() {
    int result;
    for (int i = 1; i < 100; i++) {
        result = 0;
        for (int j = 0; j < 1000; j++) {
            Crystal c(10, i);
            result += c.mainloop();
        }
        std::cout << i << " " << result / 1000.0 << std::endl;
    }
}

void third_task(){
    int result1;
    for (int i = 1; i < 30; i++) {
        result1 = 0;
        for (int j = 0; j < 1000; j++) {
            Crystal_1d d(i, 1);
            result1 += d.mainloop();
        }
        std::cout << i << " " << result1 / 1000.0 << std::endl;
    }
    int result2;
    for (int i = 1; i < 10; i++) {
        result2 = 0;
        for (int j = 0; j < 1000; j++) {
            Crystal_1d d(10, i);
            result2 += d.mainloop();
        }
        std::cout << i << " " << result2 / 1000.0 << std::endl;
    }
}

int main() {
    Crystal c(5, 0);
    c.bottleneck();
    return 0;
}
