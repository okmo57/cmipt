long long matrix_chain(const int *p, int size){
    if(size < 3) return 0;
    int Min = 10000000;
    int Ind = -1;
    long long answer = 0;
    for(int i = 1; i < size - 1; i++){
        if(p[i] < Min){
            Min = p[i];
            Ind = i;
        }
    }
    for(int i = Ind + 1; i < size - 1; i++)
        answer += p[i] * p[i + 1];
    for(int i = Ind - 1; i > 0; i--)
        answer += p[i] * p[i - 1];
    answer *= p[Ind];
    answer += p[0] * p[Ind] * p[size - 1];
    return answer;
}
