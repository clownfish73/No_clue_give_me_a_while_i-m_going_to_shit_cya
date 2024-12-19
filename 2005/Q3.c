#include "headers.h"

void copyState(int * target, int * cur, int n){
    for(int i = 0; i < n; i++){
        target[i] = cur[i];
    }
}

int dfs(int * schedule, int n, int * cur){
    int *tcur = (int*)malloc(sizeof(int) * n);
    int max = 100;
    int count = 0;
    bool flag = true;
    for(int i = 0; i < n; i++){
        if(cur[i] < schedule[i] && cur[i] < max){
            flag = false;
            max = cur[i];
            copyState(tcur, cur, n);
            tcur[i] ++;
            count += dfs(schedule, n, tcur);
        }
    }
    
    if(flag){return 1;}
    return count;
}

int main(){
    int n;
    scanf("%d", &n);
    int *schedule = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        scanf("%d", &schedule[i]);
    }
    int *cur = (int *)malloc(sizeof(int)  *n);
    for(int i = 0; i < n; i++){
        cur[i] == 0;
    }

    int res = dfs(schedule, n, cur);
    printf("%d\n",res);
    return 0;




}