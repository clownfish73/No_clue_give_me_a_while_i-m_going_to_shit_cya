#include "headers.h"

#define BUFFER_SIZE 12

#define K 5
#define N 25


typedef enum Light{off = 0, dim = 1, bright = 2} Light;

typedef Light V[N];
typedef Light aV[N + 1];

typedef Light M[N][N];
typedef Light aM[N][N + 1];

const int directions[5][2] = {{0,0},{1,0},{0,1},{-1,0},{0,-1}};

//helper functions----------------------------------------
void displayV(V v){
    for(int i = 0; i < N; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

void displayaV(aV v){
    for(int i = 0; i < N + 1; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

void displayM(M m){
    for(int i = 0; i < N; i++){
        displayV(m[i]);
    }
}

void displayaM(aM m){
    for(int i = 0; i < N; i++){
        displayaV(m[i]);
    }
}

void newLine(){printf("\n");}
//--------------------------------------------------------------

//a + b
int madd(int a, int b){
    return (a + b)%3;
}

//a - b
int msub(int a, int b){
    return (a - b + 3)%3;
}

//a * b
int mmul(int a, int b){
    return(a * b)%3;
}

//a / b
int mdiv(int a, int b){
    if(a == 0||b == 0){return 0;}
    if(a == b){return 1;}
    return 2;
}

bool isUpper(char a){return (a >= 65 && a <= 90);}

int getIndex(int i, int j){return i*K + j;}

bool inRange(int i, int j){return (i < K && j < K && i > -1 && j > -1);}

void swapRows(aM Ab, int r1, int r2){
    int t;
    for(int i = 0;i < N+1; i++){
        t = Ab[r1][i];
        Ab[r1][i] = Ab[r2][i];
        Ab[r2][i] = t;
    }

}

void mulAddRow(aV target, aV pivot, int p){
    if(target[p] == 0){return;}
    int factor = (target[p] == pivot[p]) ? 2 : 1;
    for(int i = p; i < N + 1; i++){
        target[i] = madd(target[i], mmul(pivot[i], factor));
    }
}

void setA(M A){
    for(int i = 0;i < N;i++){
        for(int j = 0; j < N; j++){
            A[i][j] = 0;
        }
    }
    int step_i, step_j;
    for(int i = 0;i < K;i++){
        for(int j = 0; j < K; j++){
            for(int d = 0; d < 5; d++){
                step_i = directions[d][0];
                step_j = directions[d][1];
                if(inRange(i + step_i, j + step_j)){
                    A[getIndex(i, j)][getIndex(i + step_i, j + step_j)] = 1;
                }
            }
        }
    }
}

void setB(V b){
    for(int i = 0; i < N; i++){
        b[i] = 0;
    }
    char buffer[BUFFER_SIZE];
    scanf("%s", buffer);
    for(int i = 0; i < strlen(buffer); i++){
        if(isUpper(buffer[i])){
            b[buffer[i] - 65] = 2;
        }
        else{
            b[buffer[i] - 97] = 1;
        }
    }
}

void setX(V x){
    for(int i = 0; i < N;i++){
        x[i] = 0;
    }
}

void setAb(aM Ab, M A, V b){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            Ab[i][j] = A[i][j];
        }
        Ab[i][N] = b[i];
    }
}

void Gelim(aM Ab){
    for(int p = 0; p < N; p++){
        int swap = -1;
        for(int j = p; j < N; j++){
            if(Ab[j][p] != 0){
                swap = j;
                break;
            }
        }
        if(swap == -1){continue;}
        if(swap != p){
            swapRows(Ab, p, swap);
        }
        for(int j = p + 1; j < N; j++){
            mulAddRow(Ab[j], Ab[p], p);
        }
    }
}

bool solveAble(aM Ab){
    for(int i = 0; i < N; i++){
        if(Ab[i][N] == 0){continue;}
        bool zero = true;
        for(int j = 0; j < N; j++){
            if (Ab[i][j] != 0){
                zero = false;
                break;
            }
        }
        if(zero){return false;}
    }
    return true;
}

void solve(aM Ab, V x){
    for(int i = N - 1; i > -1; i--){
        int cur = 0;
        for(int j = i + 1; j < N; j++){
            cur = madd(cur, mmul(Ab[i][j], x[j]));
        }
        x[i] = mdiv(Ab[i][i], msub(Ab[i][N], cur));
    }
}

int main(){
    M A;
    setA(A);

    V b;
    setB(b);

    V x;
    setX(x);

    aM Ab;
    setAb(Ab, A, b);
    Gelim(Ab);

    if (solveAble(Ab) == 0){
        printf("IMPOSSIBLE\n");
        return 0;
    }

    solve(Ab, x);
    for(int i = 0; i < N; i++){
        if(x[i] == 0){continue;}
        if(x[i] == 1){printf("%c", i + 65);}
        else{printf("%c",i + 97);}
    }
    printf("\n");

    return 0;
}