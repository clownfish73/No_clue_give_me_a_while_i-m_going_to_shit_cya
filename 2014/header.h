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
#define $3 (int16)
#define $4 (int32)
#define $8 (int64)
#define $c (char *)
#define $i (int)
