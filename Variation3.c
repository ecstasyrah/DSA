#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

typedef struct{
    int *elemPtr;
    int count;
    int max;
}List;

List initialize(List L);
List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int locate(List L, int data);
List insertSorted(List L, int data);
void display(List L);
List resize(List L);
void select(List L);

int main(){
    List L = initialize(L);

    select(L);
}

List initialize(List L){
    L.elemPtr = (int *)malloc(LENGTH *sizeof(int));
    if(L.elemPtr == NULL){
        printf("Memory allocation failed!\n");
        exit(1);
    }

    L.max = LENGTH;
    L.count = 0;

    int i;
    printf("How many elements would you like to enter? ");
    scanf("%d", &L.count);
    for(i = 0; i < L.count;i++){
        printf("Element %d: ",i + 1);
        scanf("%d", &L.elemPtr[i]);
    }

    printf("List initialized with %d elements.\n", L.count);

    return L;
}
List insertPos(List L, int data,int position){
    if(position < 1 || position > L.count + 1){
        printf("Error: Invalid position. Must be between 1 and %d.\n", L.count + 1);
        return L;
    }

    if(L.count >= L.max){
        L = resize(L);
    }

    for(int i = L.count; i >= position; i--){
        L.elemPtr[i] = L.elemPtr[i - 1];
    }

    L.elemPtr[position - 1] = data;
    L.count++;

    printf("Inserted %d at position %d.\n", data, position);
    display(L);
    return L;
}

void display(List L){
    printf("list: [ ");
    for(int i = 0; i < L.count;i++){
        printf("%d", L.elemPtr[i]);
        if(i <L.count - 1){
            printf(", ");
        }
    }
    printf(" ]\n");
}

List deletePos(List L, int position){
    if(position < 1 || position > L.count){
        printf("Error: Invalid position. Must be between 1 and %d.\n", L.count);
        return L;
    }

    for(int i = position - 1; i< L.count - 1;  i++){
        L.elemPtr[i] = L.elemPtr[i + 1];
    }

    L.count--;

    printf("Deleted element at position %d. \n", position);
    display(L);
    return L;
}

int locate(List L, int data){
    for (int i = 0;i < L.count; i++){
        if(L.elemPtr[i] == data){
            return i + 1;
        }
    }

    return -1;
}

List insertSorted(List L, int data){
    int pos = L.count;

    if (L.count >= L.max) {
        L = resize(L);
    }

    for (int i = 0; i < L.count; i++) {
        if (L.elemPtr[i] > data) {
            pos = i;
            break;
        }
    }

    for (int i = L.count; i > pos; i--) {
        L.elemPtr[i] = L.elemPtr[i - 1];
    }

    L.elemPtr[pos] = data;
    L.count++;

    printf("Inserted %d into sorted list.\n", data);
    return L;
}

List resize(List L){
    int newMax;
    printf("Enter new size amount (Must be greater than 10): ");
    scanf("%d", &newMax);
    int *newArr = (int *)malloc(newMax * sizeof(int));
    if(newArr == NULL){
        printf("Error: Memory allocation failed in resize.\n");
        exit(1);
    }

    for(int i = 0; i < L.count; i++){
        newArr[i] = L.elemPtr[i];
    }

    free(L.elemPtr);

    L.elemPtr = newArr;
    L.max = newMax;

    printf("Resized list to capacity %d.\n", L.max);
    return L;
}

void select(List L){
    int sel;
    printf("\nChoose an option: "
           "\n 1. Insert Position\n "
           "2. Delete an element\n "
           "3. Locate an element\n "
           "4. Insert Sorted\n "
           "5. Resize list\n "
           "6. Display List\n "
           "7. Exit\n "
           "Enter number: ");
    scanf("%d", &sel);
    int data, position;
    switch (sel) {
        case 1:
            if(L.count != L.max){
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
            position = locate(L,data);
            if(position != -1){
                printf("Element found at position %d\n", position);
            }else{
                printf("Element not found\n");
            }
            select(L);
            break;
        case 4:
            printf("Insert sorted: ");
            printf("\nEnter data you want to insert: ");
            scanf("%d", &data);
            L = insertSorted(L, data);
            display(L);
            select(L);
            break;
        case 5:
            printf("Resize List: \n");
            resize(L);
            select(L);
            break;
        case 6:
            display(L);
            select(L);
            break;
        case 7:
            printf("Exiting...");
            break;
    }
}



