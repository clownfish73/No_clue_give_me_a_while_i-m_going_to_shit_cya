#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define BUFFER_SIZE 8

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

#define DIAL_SIZE 26

typedef char D[DIAL_SIZE];

void displayD(D d){
    for(int i = 0; i < DIAL_SIZE; i++){
        printf("%c ", d[i]);
    }
    newLine();
}

void twistD(D d){
    char t = d[0];
    for(int i = 1; i < DIAL_SIZE; i++){
        d[i-1] = d[i];
    }
    d[DIAL_SIZE - 1] = t;
}

void initDefaultDial(D d){
    for(int i = 0; i < DIAL_SIZE; i++){
        d[i] = i + 65;
    }
}

void genDial(D d, int n){
    D ref;
    initDefaultDial(ref);
    int cur = 0;
    int idx = 0;
    int m = 0;
    while(idx < DIAL_SIZE){
        if(ref[cur] != 0){
            m++;
            if(m == n){
                d[idx++] = ref[cur];
                m = 0;
                ref[cur] = 0;
            }
        }
        cur++;
        cur %= DIAL_SIZE;
    }   
}

void encode(D d2, char word[BUFFER_SIZE]){
    for(int i = 0; i < strlen(word); i++){
        printf("%c", d2[word[i] - 65]);
        twistD(d2);
    }
}

int main(){
    int n;
    char word[BUFFER_SIZE];
    scanf("%d %s",&n, word);
    D d2;
    genDial(d2, n);
    for(int i = 0; i < 6;i++){
        printf("%c", d2[i]);
    }
    newLine();
    encode(d2, word);
    newLine();
    return 0;
}