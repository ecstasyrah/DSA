#include <stdio.h>

#define MAX 10

typedef struct{
    int elem[MAX];
    int count;
} List;

List initialize(List L);
List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int locate(List L, int data);
List insertSorted(List L, int data);
void display(List L);

int main(){
    List L;
    int data;
    int position;

    initialize(L);
    display(L);

    return 0;
}

List initialize(List L){
    L.count = 0;
    for(int i = 0; i < MAX;i++){
        printf("Element %d: ",L.count+1);
        scanf("%d", &L.elem[i]);
        printf("\n");
        L.count++;
    }

    printf("List initialized with %d elements.\n", L.count);
    return L;
}

void display(List L){
    printf("List elements: ");
    for(int i = 0; i < L.count; i++){
        printf("%d ", L.elem[i]);
    }
}