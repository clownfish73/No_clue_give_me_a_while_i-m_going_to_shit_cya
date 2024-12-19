#include "headers.h"

typedef struct Triplet{
    int8 w;
    int d;
    int8 t;
}Triplet;

Triplet* readTriplet(){
    Triplet *new_triplet = (Triplet*)malloc(sizeof(Triplet));
    int w,t;
    char d;
    scanf("%d%c%d",&w,&d,&t);
    new_triplet->w = w;
    new_triplet->d = (d == 'R') ? 1: -1;
    new_triplet->t = t;

}

int main(){
    int8 n;
    scanf("%hhd", &n);
    Triplet ***instructions = (Triplet***)malloc(sizeof(Triplet**)*n);
    for(int i =0; i <n;i++){
        instructions[i] = (Triplet**)malloc(sizeof(Triplet *) * 2);
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2; j++){
            instructions[i][j] = readTriplet();            
        }
    }
    int m;
    scanf("%d",&m);
    
    int8 *tape = (int8 *)malloc(sizeof(int8)*(m*2 + 1));
    for(int i = 0; i < m*2 + 1; i++){
        tape[i] == 0;
    }
    int i = m;
    int8 state = 1;
    int iter = 0;
    int8 curVal;
    
    while (iter < m && state != 0){
        curVal = tape[i];
        tape[i] = instructions[state-1][curVal]->w;
        i += instructions[state-1][curVal]->d;
        state = instructions[state-1][curVal]->t;
        iter++;
    }

    for(int j = i - 3; j <= i+3; j++){
        printf("%hhd",tape[j]);
    }
    printf("\n%d\n", iter);
    return 0;
}