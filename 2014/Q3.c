#include "headers.h"

#define length 36

int64 nCr(int64 n, int64 r) {
    if (r > n) return 0;
    int64 res = 1;
    for (int64 i = 1; i <= r; i++) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

int64 getLength(int n){
   int64 r = 1;
   int64 cur = 0;
    while (cur < n){
        cur += nCr(length,r);
        r++;
    }
    r--;
    return r;

}

int main(){
    char letters[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9'};
    int64 n;
    //scanf("%d", &n);
    n = 37;
    printf("%lld\n", nCr(36,2));
    printf("%lld\n", getLength(n));
    return 0;
}