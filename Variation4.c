#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LENGTH 10

typedef struct{
    int *elemPtr;
    int count;
    int max;
}List;

void initialize(List *L);
void insertPos(List *L, int data, int position);
void deletePos(List *L, int position);
int locate(List *L, int data);
int retrieve(List *L, int position);
void insertSorted(List *L, int data);
void display(List *L);
void resize(List *L);
void makeNULL(List *L);
void select(List *L);

int main(){
    List *L;
    initialize(L);
    select(L);

    return 0;
}

void initialize(List *L){
    L->elemPtr = (int *)malloc(LENGTH * sizeof(int));
    if (L->elemPtr == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    L->max = LENGTH;
    L->count = 0;

    int i;
    printf("How many elements would you like to enter? ");
    scanf("%d", &L->count);

    if (L->count > L->max) {
        printf("Error: Too many elements! Maximum is %d.\n", L->max);
        L->count = L->max; // prevent overflow
    }

    for (i = 0; i < L->count; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &L->elemPtr[i]);
    }

    printf("List initialized with %d elements.\n", L->count);
}

void insertPos(List *L, int data, int position) {
    if (position < 1 || position > L->count + 1) {
        printf("Error: Invalid position. Must be between 1 and %d.\n", L->count + 1);
        return;
    }

    if (L->count >= L->max) {
        resize(L);
    }

    for(int i = L->count; i>=position - 1;i--){
        if(position > L->count){
            L->elemPtr[L->count] = L->elemPtr[i];
        }else {
            L->elemPtr[i] = L->elemPtr[i-1];
        }
    }

    L->elemPtr[position - 1] = data;
    L->count++;

}

void deletePos(List *L, int position) {
    if (position < 1 || position > L->count) {
        printf("Error: Invalid position. Must be between 1 and %d.\n", L->count);
        return;
    }

    for (int i = position - 1; i < L->count - 1; i++) {
        L->elemPtr[i] = L->elemPtr[i + 1];
    }

    L->count--;
}

int locate(List *L, int data) {
    for (int i = 0; i < L->count; i++) {
        if (L->elemPtr[i] == data) {
            return i + 1; // return 1-based position
        }
    }
    return -1;
}

int retrieve(List *L, int position) {
    if (position < 1 || position > L->count) {
        printf("Error: Invalid position. Must be between 1 and %d.\n", L->count);
        return -1;
    }
    return L->elemPtr[position - 1];
}

void insertSorted(List *L, int data) {
    if (L->count >= L->max) {
        resize(L);
    }

    int pos = L->count;
    for (int i = 0; i < L->count; i++) {
        if (L->elemPtr[i] > data) {
            pos = i;
            break;
        }
    }

    for (int i = L->count; i > pos; i--) {
        L->elemPtr[i] = L->elemPtr[i - 1];
    }

    L->elemPtr[pos] = data;
    L->count++;
}

void display(List *L) {
    printf("[ ");
    for (int i = 0; i < L->count; i++) {
        printf("%d", L->elemPtr[i]);
        if (i < L->count - 1) {
            printf(", ");
        }
    }
    printf(" ]\n");
}

void resize(List *L) {
    int newMax;
    printf("Enter new size amount (Must be greater than 10): ");
    scanf("%d", &newMax);
    int *newArr = (int *)malloc(newMax * sizeof(int));
    if (newArr == NULL) {
        printf("Error: Memory allocation failed during resize.\n");
        exit(1);
    }

    for (int i = 0; i < L->count; i++) {
        newArr[i] = L->elemPtr[i];
    }

    free(L->elemPtr);
    L->elemPtr = newArr;
    L->max = newMax;

    printf("Resized list to capacity %d.\n", L->max);
}

void makeNULL(List *L) {
    free(L->elemPtr);
    L->elemPtr = NULL;
    L->count = 0;
    L->max = 0;
}

void select(List *L) {
    int sel;
    do {
        printf("\nChoose an option: "
               "\n 1. Insert Position"
               "\n 2. Delete an element"
               "\n 3. Locate an element"
               "\n 4. Insert Sorted"
               "\n 5. Resize list"
               "\n 6. Display List"
               "\n 7. Exit"
               "\nEnter number: ");
        scanf("%d", &sel);

        int data, position;

        switch (sel) {
            case 1:
                if (L->count < L->max) {
                    printf("\nEnter Position to be inserted: ");
                    scanf("%d", &position);
                    printf("Enter Data to be inserted: ");
                    scanf("%d", &data);
                    insertPos(L, data, position);
                } else {
                    printf("\nARRAY FULL! Delete an element first.\n");
                    printf("Enter position to delete: ");
                    scanf("%d", &position);
                    deletePos(L, position);
                }
                break;

            case 2:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deletePos(L, position);
                display(L);
                break;

            case 3:
                printf("\nEnter element you want to find: ");
                scanf("%d", &data);
                position = locate(L, data);
                if (position != -1) {
                    printf("Element found at position %d\n", position);
                } else {
                    printf("Element not found\n");
                }
                break;

            case 4:
                printf("\nEnter data you want to insert sorted: ");
                scanf("%d", &data);
                insertSorted(L, data);
                display(L);
                break;

            case 5:
                resize(L);
                break;

            case 6:
                display(L);
                break;

            case 7: // Exit
                printf("Exiting...\n");
                makeNULL(L);
                break;

            default:
                printf("Invalid option! Try again.\n");
        }
    } while (sel != 7);
}
