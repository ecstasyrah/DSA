#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int elem[MAX];
    int count;
}Etype, *EPtr;

void initialize(EPtr *L);
void insertPos(EPtr L, int data, int position);
void deletePos(EPtr L, int position);
int locate(EPtr L, int data);
int retrieve(EPtr L, int position);
void insertSorted(EPtr L, int data);
void display(EPtr L);
void makeNULL(EPtr L);
void select(EPtr L);

int main() {
    EPtr L;

    initialize(&L);

    select(L);

    return 0;
}

void initialize(EPtr *L) {
    int count = 0;
    printf("How many elements would you like to enter? ");
    scanf("%d", &count);

    *L = (EPtr)malloc(sizeof(Etype));
    if (*L == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    (*L)->count = count;

    for(int i = 0; i < (*L)->count; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &(*L)->elem[i]);
    }

    printf("List initialized with %d elements.\n", (*L)->count);
    display(*L);
}
void insertPos(EPtr L, int data, int position) {
    int i;
    for(i = L->count; i>=position - 1;i--){
        if(position > L->count){
            L->elem[L->count] = L->elem[i];
        }else {
            L->elem[i] = L->elem[i-1];
        }
    }
    L->elem[position - 1] = data;
    L->count++;

    printf("\nNew List: \t");
    display(L);
}

void deletePos(EPtr L, int position) {
    if (L->count == 0) {
        printf("\nError: The list is empty. Cannot delete.\n");
        return;
    }

    if (position < 1 || position > L->count) {
        printf("\nError: Invalid position. Please enter a position between 1 and %d.\n", L->count);
        return;
    }

    for (int i = position - 1; i < L->count - 1; i++) {
        L->elem[i] = L->elem[i + 1];
    }
    L->count--;
    printf("\nElement at position %d deleted successfully.\n", position);
    display(L);
}

int locate(EPtr L, int data) {
    for (int i = 0; i < L->count; i++) {
        if (L->elem[i] == data) {
            return i + 1; // Return the 1-based position
        }
    }
    return -1; // Not found
}

int retrieve(EPtr L, int position) {
    if (position < 1 || position > L->count) {
        printf("Error: Invalid position. Cannot retrieve element.\n");
        return -9999; // Return an error value
    }
    return L->elem[position - 1];
}

void insertSorted(EPtr L, int data) {
    if (L->count >= MAX) {
        printf("Error: The list is full. Cannot insert.\n");
        return;
    }

    int i = L->count - 1;
    while (i >= 0 && L->elem[i] > data) {
        L->elem[i + 1] = L->elem[i];
        i--;
    }
    L->elem[i + 1] = data;
    L->count++;
    printf("Data %d inserted into sorted list.\n", data);
    display(L);
}

void display(EPtr L) {
    if (L->count == 0) {
        printf("List is empty.\n");
        return;
    }

    printf("\nList elements: [ ");
    for (int i = 0; i < L->count; i++) {
        printf("%d", L->elem[i]);
        if(i < L->count - 1){
            printf(", ");
        }
    }
    printf(" ]\n\n");
}

void makeNULL(EPtr L) {
    free(L);
    printf("Memory is FREEEEEE. Exiting program.\n");
}

void select(EPtr L) {
    int choice, data, position;
    do {
        printf("--- List Operations Menu ---");
        printf("\n1. Insert at Position");
        printf("\n2. Delete at Position");
        printf("\n3. Locate an Element");
        printf("\n4. Retrieve an Element");
        printf("\n5. Insert in a Sorted List");
        printf("\n6. Exit(makeNULL)");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position to insert at: ");
                scanf("%d", &position);
                insertPos(L, data, position);
                break;
            case 2:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deletePos(L, position);
                break;
            case 3:
                printf("Enter data to locate: ");
                scanf("%d", &data);
                position = locate(L, data);
                if (position != -1) {
                    printf("Element %d found at position %d.\n", data, position);
                } else {
                    printf("Element %d not found in the list.\n", data);
                }
                break;
            case 4:
                printf("Enter position to retrieve: ");
                scanf("%d", &position);
                int retrieved_data = retrieve(&L, position);
                if (retrieved_data != -9999) {
                    printf("Element at position %d is: %d\n", position, retrieved_data);
                }
                break;
            case 5:
                printf("Enter data to insert into sorted list: ");
                scanf("%d", &data);
                insertSorted(L, data);
                break;
            case 6:
                makeNULL(L);
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 0);
}