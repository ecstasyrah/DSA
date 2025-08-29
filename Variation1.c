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
void select(List L);

int main(){
    List L = initialize(L);


    select(L);

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
    for(i = L.count; i>=position - 1;i--){
        if(position > L.count){
            L.elem[L.count] = L.elem[i];
        }else {
            L.elem[i] = L.elem[i-1];
        }
    }
    L.elem[position - 1] = data;
    L.count++;

    printf("\nNew List: \n\t");
    display(L);
    return L;
}

List deletePos(List L, int position) {
    int i;
    for (i = position - 1; i <= L.count-1; i++) {
        if(i == L.count-1){
            L.count--;
        }else {
            L.elem[i] = L.elem[i+1];
        }
    }
    printf("\nNew List: \n\t");
    display(L);
    return L;
}

List insertSorted(List L, int data) {
    int pos = 0;
    if (L.count != MAX) {
        for (int i = 0; i < L.count;i++) {
            if(L.elem[i] > data) {
                pos = i+1;
                break;
            }
        }
        insertPos(L,data,pos);

    }else if (L.count == MAX){
        printf("\nNeed to delete a value first");
        int position;
        printf("\nWhat position do you want to delete? ");
        scanf("%d", &position);
        deletePos(L,position);
        L.count--;
        insertSorted(L,data);
    }

}

void select(List L) {
    int sel;
    printf("\nChoose an option: \n 1. Insert Position\n 2. Delete an element\n 3. Locate an element\n 4. Insert Sorted\n 5. Display list\n 6. Exit\n Enter number: ");
    scanf("%d", &sel);
    int data, position;
    switch (sel) {
        case 1:
            if(L.count != MAX){
                printf("\nInsert Position: ");
                printf("\nEnter Position to be inserted: ");
                scanf("%d", &position);
                printf("Enter Data to be inserted: ");
                scanf("%d", &data);
                L = insertPos(L,data, position);
            }else {
                printf("\nYOU CAN'T ENTER IN ANY POSITION !! ARRAY FULL\n Delete an element in position: ");
                scanf("%d", &position);
                L = deletePos(L,position);
            }
            select(L);
            break;
        case 2:
            printf("Delete\n");
            int pos;
            printf("Delete an element in position: ");
            scanf("%d", &pos);
            L = deletePos(L, pos);
            select(L);
            break;
        case 3:
            printf("\nLocate data: ");
            printf("\nEnter element you want to find: ");
            scanf("%d", &data);
             locate(L,data);
            select(L);
            break;
        case 4:
            printf("Insert sorted: ");
            printf("\nEnter data you want to insert: ");
            L = insertSorted(L, data);
            select(L);
            break;
        case 5:
            printf("Display list: \n");
            display(L);
            select(L);
            break;
        case 6:

            break;
    }

}