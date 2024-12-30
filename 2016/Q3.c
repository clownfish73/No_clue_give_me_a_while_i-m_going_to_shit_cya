#define _GNU_SOURCE
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

void seive(bool *P, int32 n){
    memset(P, 1, n);
    P[0] = 0;
    P[1] = 0;
    for(int i = 2; i < n; i++){
        if(P[i]){
            for(int j = i* i; j < n; j+= i){
                P[j] = 0;
            }
        }
    }
}

int bfs(bool *P, int32 p, int32 q, int32 n){
    int32 *queue = (int32*)malloc(sizeof(int32) * n);
    int32 curLen = 1;
    int32 newLen = 0;
    bool *visited = (bool*)malloc(sizeof(bool) * n);
    memset(visited, 0, n);
    visited[p] = 1;
    int32 *newQueue = (int32*)malloc(sizeof(int32) * n);
    int32 step, cur;
    int32 depth = 2;
    queue[0] = p;
    while(depth < 100){
        for(int32 i = 0; i < curLen; i++){
            step = 1;
            while(queue[i] + step < n){
                if(P[queue[i] + step] && visited[queue[i] + step] == 0){
                    if(queue[i] + step == q){
                       return depth;
                    }
                    newQueue[newLen++] = queue[i] + step;
                    visited[queue[i] + step] = 1;
                }
                step *= 2;
            }
            step = 1;
            while(step < queue[i]){
                if(P[queue[i] - step] && visited[queue[i] - step] == 0){
                    if(queue[i] - step == q){
                       return depth;
                    }
                    newQueue[newLen++] = queue[i] - step;
                    visited[queue[i] - step] = 1;
                }
                step *= 2;
            }
        }
        depth++;
        memcpy(queue, newQueue, newLen * sizeof(int32));
        curLen = newLen;
        newLen = 0;
    }
    return -1;
}

int main(){
    int32 n,p,q;
    scanf("%d %d %d", &n, &p, &q);
    n++;
    bool*P = (bool*)malloc(sizeof(bool) * n);
    seive(P, n);
    printf("%d\n", bfs(P, p, q, n));

}