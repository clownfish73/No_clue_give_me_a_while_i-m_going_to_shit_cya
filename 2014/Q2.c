#include "headers.h"

typedef enum Direction{
    up,
    down,
    left,
    right,
} Direction;

typedef struct Tile{
    Direction in[2];
    Direction out[2];
} Tile;

Tile * newTile(Direction in1, Direction in2, Direction out1, Direction out2){
    Tile * newTile = (Tile*)malloc(sizeof(Tile));
    newTile->in[0] = in1;
    newTile->in[1] = in2;
    newTile->out[0] = out1;
    newTile->out[1] = out2;
    return newTile;
}

void updateDirection(Direction * d, Tile * tile){
    if(tile->in[0] == *d){(*d) = tile->out[0];}
    else{(*d) = tile->out[1];}
}

void incrementIndexes(int *i, int *j, Direction d){
    switch(d){
        case 0:{
            (*i)--;
            break;
        }
        case 1:{
            (*i)++;
            break;
        }
        case 2:{
            (*j)--;
            break;
        }
        case 3:{
            (*j)++;
            break;
        }
    }
}

int countLoops(Tile * tiles[7], int i, int j, int n, int **board, bool used[36]){
    if (used[i + 6*j] == 1){used[i + 6*j] = 1;return 0;}
    used[i + 6*j] = 1;
    Tile * curTile = tiles[board[i][j]];
    Direction d = 0;
    updateDirection(&d, curTile);
    int target = i + 6*j;
    int count = 1;
    while(1){
        incrementIndexes(&i, &j, d);
        if (i >= n || i < 0 || j >= n || j < 0){return 0;}
        curTile = tiles[board[i][j]];
        if ((curTile->in[0] == d || curTile->in[1] == d) != 1){return 0;}
        updateDirection(&d, curTile);
        if (i + j*6 == target){return count;}
        count++;
        used[i + j*6] = 1;
    }
}

void tilesRed2Green(Tile * tiles[7]){
    int pairs[3][2] = {{1,2},{3,5},{4,6}};
    Tile * temp;
    int x;
    int y;
    for (int i = 0; i < 3; i ++){
        x = pairs[i][0];
        y = pairs[i][1];
        temp = tiles[x];
        tiles[x] = tiles[y];
        tiles[y] = temp;
    }
}

int getHighest(int **board, Tile ** tiles, int n){
    int cur = 0;
    int highest = 0;
    bool used[36] = {false};
    for (int i = 0;i < n; i++){
        for (int j = 0;j < n; j ++){
            cur = countLoops(tiles, i, j, n ,board, used);
            highest += cur;
        }
    }
    return highest;
}

int main(){
    Tile *tiles[7];
    tiles[1] = newTile(0,1,0,1);
    tiles[2] = newTile(2,3,2,3);
    tiles[3] = newTile(3,1,0,2);
    tiles[4] = newTile(2,1,0,3);
    tiles[5] = newTile(0,2,3,1);
    tiles[6] = newTile(3,0,1,2);

    int n;
    scanf("%d", &n);

    int ** board = (int **)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++){
        board[i] = (int *)malloc(sizeof(int) * n);
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &board[i][j]);
        }
    }
    int highestRed = 0;
    int highestGreen = 0;
    
    highestRed = getHighest(board, tiles, n);
    tilesRed2Green(tiles);
    highestGreen = getHighest(board, tiles, n);

    printf("%d %d\n", highestRed, highestGreen);
    free(board);
    return 0;

}