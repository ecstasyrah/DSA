#include <stdio.h>
#include <stdbool.h>

#define MAX 5

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
    List L = initialize(L);
    int data = 0;
    int position = 0;

    display(L);

    // printf("\nEnter Position to be inserted: ");
    // scanf("%d", &position);
    // printf("Enter Data to be inserted: ");
    // scanf("%d", &data);
    L = insertPos(L,8,2);
    printf("\nEnter element you want to find: ");
    scanf("%d", &data);
    locate(L,data);

    return 0;
}

List initialize(List L){
    printf("How many elements would you like to enter? ");
    scanf("%d", &L.count);
    for(int i = 0; i < L.count;i++){
        printf("Element %d: ",i + 1);
        scanf("%d", &L.elem[i]);
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

int locate(List L, int data){
    for(int i = 0 ;i < L.count; i++){
        if(L.elem[i] == data){
            printf("Element is in position %d", i+1);
            return 0;
        }
    }
    printf("Data not found");
    return 0;
}

List insertPos(List L, int data, int position){
    int i;
    if(L.count != MAX){
        for(i = L.count-1; i!=position-1;i--){
            L.elem[L.count-1] = L.elem[i];
        }
        }else if(L.count == MAX){
            printf("\nYOU CAN'T ENTER IN A ANY POSITION ARRAY FULL\n Delete an element\n");
        }
        L.elem[i] = L.elem[position-1];
            L.count++;
    printf("\nNew List: \t");
    display(L);
    return L;
}