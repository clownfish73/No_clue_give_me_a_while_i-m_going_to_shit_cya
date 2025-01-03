#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;


#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $c (char *)
#define $i (int)

void newLine(){
    printf("\n");
}

void space(){
    printf(" ");
}

int power(int b, int e){
    int res = 1;
    for(int i = 0; i < e;i++){
        res *= b;
    }
    return res;
}

int factorial(int n){
    int res = 1;
    for(int i = 1; i <= n; i++){
        res*= i;
    }
    
    return res;
}

int hash(int *cur, int n){
    int res = 0;
    for(int i = 0; i < n-1;i++){
        res += power(n, i) * (cur[i]);
    }
    return res;
}


int getMaxSize(int n){
    int *arr = (int*)malloc(sizeof(int)* n);
    for(int i = 0; i < n-1;i++){
        arr[i] = i + 1;
    }
    arr[n-1] = 0;
    return hash(arr, n);
}

void displayA(int *cur, int n){
    for(int i= 0; i < n; i++){
        printf("%d ", cur[i] + 1);
    }
    newLine();
}

bool* initDict(int n){
    int s = getMaxSize(n);
    bool*dict = (bool*)malloc(sizeof(bool) * s);
    for(int i = 0; i < s; i++){
        dict[i] = 0;
    }   
    return dict;
}


int** initS(int n){
    int**s = (int **)malloc(sizeof(int *)*factorial(n));
    for(int i = 0; i < factorial(n); i++){
        s[i] = (int *)malloc(sizeof(int) * n);
    }
    return s;
}

void freeS(int **s, int n){
    for(int i = 0; i < factorial(n); i++){
        free(s[i]);
    }
    free(s);
}

bool canSwap(int *cur, int n, int i){
    int a, b;
    a = cur[i];
    b = cur[i+1];
    if(a < b){
        int t = a;
        a = b;
        b = t;
    }
    // a  > b
    if(i > 0 && a > cur[i-1] && b < cur[i-1]){
        return true;
    } 
    if(i >= n-2){
        return false;
    }
    return a > cur[i+2] && b < cur[i+2];
}

void swap(int * dest, int *target, int i, int n){
    for(int i = 0; i < n; i++){
        dest[i] = target[i];
    }
    dest[i]= target[i + 1];
    dest[i + 1] = target[i];
}

int bfs(int *cur, int n){
    bool * dict = initDict(n);
    int **curS = initS(n);
    int **nextS = initS(n);
    memcpy(curS[0], cur, n*sizeof(int));
    int l = 1;
    int nl = 0;
    int *t = (int *)malloc(sizeof(int) * n);
    int h;
    dict[hash(cur, n)] = 1;
    int distance = 0;
    while(l != 0){
        for(int i = 0; i < l; i++){
            for(int j = 0; j < n-1; j++){
                if(canSwap(curS[i], n, j)){
                    swap(t, curS[i], j, n);
                    h = hash(t, n);
                    if(h >= getMaxSize(n)){displayA(t, n); exit(1);}
                    if(dict[h]){continue;}
                    memcpy(nextS[nl++], t, n * sizeof(int));
                    if(nl >= factorial(n)){printf("error\n"); exit(1);}
                    dict[h] = true;
                }
            }
        }
        for(int i = 0; i < nl;i++){
            memcpy(curS[i], nextS[i], n * sizeof(int));
        }
        l = nl;
        if(l == 0){
            return distance;
        }
        nl = 0;
        distance++;
    }
    free(dict);
    freeS(nextS, n);
    freeS(curS,n);
    return distance;
}

int main(){
    int n;
    scanf("%d", &n);
    int *cur = (int*)malloc(sizeof(int) * n);
    
    for(int i = 0; i < n; i++){
        scanf("%1d", &cur[i]);
        cur[i]--;
    }

    printf("%d\n",bfs(cur, n));

    free(cur);
}