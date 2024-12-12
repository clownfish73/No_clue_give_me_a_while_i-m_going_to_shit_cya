#include "headers.h"
 
#define MAX_SIZE 10200
 
typedef struct Node{
    int16 data;
    struct Node *next;
} Node;
 
Node * createNode(int16 data){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}
 
Node * generateOddNums(int max){
    Node* head = createNode(1);
    Node* cur = head;
    for (int i = 3; i < max; i +=2){
        cur->next = createNode($2 i);
        cur = cur->next;
    }
    return head;
}
 
void generateLuckyNums(Node *head, int16 *size){
    Node* cur = head;
    *size = 1;
    int i;
    int16 step;
    while (cur->next != NULL){
        cur = cur->next;
        step = cur->data;
        if(step > MAX_SIZE){
        *size ++;
        continue;
        }
        i = 2;
        Node *prevTemp = head;
        Node *curTemp = head->next;
        while(curTemp->next != NULL){
            if (i%step == 0){
                prevTemp->next = curTemp->next;
            }
            prevTemp = curTemp;
            curTemp = curTemp->next;
            ;
            i++;
        }
        (*size)++;
    }
}
 
void FindNums(Node *luckyHead, int16 target, int16 *less, int16 * greater){
    Node * prev = luckyHead;
    Node * cur = prev->next;
    while (cur->data < target){
        prev = cur;
        cur = cur->next;
    }
    *less = prev->data;
    if (cur->data == target){
        *greater = cur->next->data;
    }else{
        *greater = cur->data;
    }
}
 
int main(){
    int16 target;
    scanf("%hd", &target);
    Node *luckyHead = generateOddNums(MAX_SIZE);
    int16 size;
    generateLuckyNums(luckyHead, &size);
    Node * temp = luckyHead;
    int16 less;
    int16 greater;
 
    FindNums(luckyHead, target, &less, &greater);
 
    printf("%hd %hd\n", less, greater);
 
    return 0;
 
}