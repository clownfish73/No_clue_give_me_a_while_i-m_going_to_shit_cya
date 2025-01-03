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

#define BUFFER_SIZE 10

void newLine(){
    printf("\n");
}

void space(){
    printf(" ");
}





int main(){
    float i, p;
    scanf("%f %f",&i, &p);

    float a = 0;
    float cur = 100;
    while(1){
        cur += i/100 * cur;
        if(cur < 50){
            break;
        }
        if(cur*(p/100) > 50){
            a += cur*(p/100);
            cur -= cur*(p/100);
        }
        else{
            cur -= 50;
            a += 50;
        }
    }
    printf("%.2f\n", a + cur);
    return 0;
}
