#include "headers.h"

#define BOARD_SIZE 5
#define DIRECTION_SIZE 8

#define E '.'
#define F 'F'
#define S 'S'
#define N '*'

#define F_row 4
#define S_row 0

typedef char Board[BOARD_SIZE][BOARD_SIZE];

int i_step[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int j_step[] = {0, 1, 1, 1, 0, -1, -1, -1};


typedef struct Cord{ int i; int j;} Cord;

Cord * newCords(int i, int j){
    Cord *new_cord = (Cord*)malloc(sizeof(Cord));
    new_cord->i = i;
    new_cord->j = j;
    return new_cord;
}

void newLine();

void displayBoard(Board Board);

void readInitCord(Cord *C[BOARD_SIZE], int row);

void fillRow(int row, char p, Board board);

bool inRange(int i, int j);

void Move(int *i, int *j, int d, Board board);

bool canMove(int i, int j, Board board);

bool canMoveDir(int i, int j, int d, Board board);

void copyBoard(Board curBoard, Board newBoard);

bool reachesRow(int i, int j, int d, int row, Board board);

int opposeRow(int i);

bool takeTurn(int round, Board board, Cord * Cn, Cord * Pn[BOARD_SIZE], int targetRow);


int main(){
    //initilize board
    Board board;
    char PiecePerRow[] = {S, E, E, E, F};
    for(int i = 0; i < BOARD_SIZE; i++){
        fillRow(i, PiecePerRow[i], board);
    }
    board[2][2] = N;

    //initilize cords
    Cord *Cn = newCords(2, 2);

    Cord *Fn[BOARD_SIZE];
    Cord *Sn[BOARD_SIZE];

    readInitCord(Fn, F_row);
    readInitCord(Sn, S_row);

    int round = 0;
    bool stop = 0;

    while(1){
        stop = takeTurn(round, board, Cn, Fn, F_row);
        if(round == 0 || stop == 1){
            displayBoard(board);
            newLine();
            if(stop == 1){break;}
        }
        stop = takeTurn(round, board, Cn, Sn, S_row);
        if(round == 0||stop == 1){
            displayBoard(board);
            newLine();
            if(stop == 1){break;}
        }
        round++;
    }

}

void newLine(){
    printf("\n");
}

void displayBoard(Board board){
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

void readInitCord(Cord *C[BOARD_SIZE], int row){
    int tj;
    for(int i = 0; i < BOARD_SIZE; i++){
        scanf("%d", &tj);
        tj--;
        C[i] = newCords(row, tj);
    }
}

void fillRow(int row, char p, Board board){
    for(int j = 0; j < BOARD_SIZE; j++){
        board[row][j] = p;
    }
}

bool inRange(int i, int j){
    if (i < 0||j < 0||i >= BOARD_SIZE||j >= BOARD_SIZE){return 0;}
    return 1;
}


bool canMove(int i, int j, Board board){
    for(int d = 0; d < DIRECTION_SIZE; d++){
        if(canMoveDir(i, j, d ,board) == 1){return true;}
    }
    return false;
}

bool canMoveDir(int i, int j, int d, Board board){
    int ti, tj;
    ti = i + i_step[d];
    tj = j + j_step[d];
    if(inRange(ti, tj) && board[ti][tj] == E){
        return true;
    }
    return false;
}

void Move(int *i, int *j, int d, Board board){
    char p = board[*i][*j];
    board[*i][*j] = E;
    int next_i, next_j;
    next_i = (*i) + i_step[d];
    next_j = (*j) + j_step[d];
    while (inRange(next_i, next_j) == 1 && board[next_i][next_j] == E){
        next_i += i_step[d];
        next_j += j_step[d];
        (*i) += i_step[d];
        (*j) += j_step[d];
    }
    board[*i][*j] = p;
}


void copyBoard(Board curBoard, Board newBoard){
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            newBoard[i][j] = curBoard[i][j];
        }
    }
}

bool reachesRow(int i, int j, int d, int row, Board board){
    Board tBoard;
    copyBoard(board, tBoard);
    Move(&i, &j, d, tBoard);
    if(i == row){
        return true;
    }
    return false;
}

int opposeRow(int i){return (i+4)%8;}

bool takeTurn(int round, Board board, Cord * Cn, Cord * Pn[BOARD_SIZE], int targetRow){
    int ti, tj;
    for(int d = 0; d < DIRECTION_SIZE; d++){
        if(reachesRow(Cn->i, Cn->j, d, targetRow, board) == 1){
            Move(&Cn->i, &Cn->j, d, board);
            return 1;
        }
    }

    Board tBoard;
    for(int d = 0; d < DIRECTION_SIZE; d++){
        ti = Cn->i;
        tj = Cn->j;
        if(canMoveDir(ti, tj, d, board) && reachesRow(ti, tj, d, opposeRow(targetRow), board) == 0){
            copyBoard(board, tBoard);
            Move(&ti, &tj, d, tBoard);
            if(canMove(Pn[round%BOARD_SIZE]->i, Pn[round%BOARD_SIZE]->j, tBoard)){
                for(int d2 = 0; d2 < DIRECTION_SIZE; d2++){
                    if(canMoveDir(Pn[round%BOARD_SIZE]->i, Pn[round%BOARD_SIZE]->j, d2, tBoard)){
                        Move(&Pn[round%BOARD_SIZE]->i, &Pn[round%BOARD_SIZE]->j, d2, tBoard);
                        copyBoard(tBoard, board);
                        Cn->i = ti;
                        Cn->j = tj;
                        return 0;
                    }
                }
            }
        }
    }
    for(int d = 0; d < DIRECTION_SIZE; d++){
        if(canMove(Cn->i, Cn->j, board)){Move(&Cn->i, &Cn->j, d, board);return 1;}
    }
    return 1;
        
}