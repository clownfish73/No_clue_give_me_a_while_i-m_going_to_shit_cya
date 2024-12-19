#include "headers.h"

#define BUFFER_SIZE 6

int power(int b, int e){
    int r = b;
    for(int i = 1;i < e; i++){
        r *= b;
    }
    return r;
}

int main(){
    char nums[BUFFER_SIZE];
    scanf("%s", nums);
    int n = 0;
    for(int i = 0; i < strlen(nums) - 2; i++){
        n += (nums[i + 2] - 48) * power(10, 3 - i);
    }
    int factors[8] = {2,2,2,2,5,5,5,5};
    int d = 10000;
    for(int i = 0; i < 8; i++){
        if(n%factors[i] == 0){
            n/=factors[i];
            d/=factors[i];
        }
    }
    printf("%d / %d\n",n,d);
    return 0;
    

}