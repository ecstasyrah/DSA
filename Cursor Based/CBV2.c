#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int elem;
    int next;
} HeapSpace;

typedef struct {
    HeapSpace *Nodes;
    int avail;
} VHeap;

void initialize(VHeap *V);
int allocSpace(VHeap *V);
void deallocSpace(VHeap *V, int index);
void insertFirst(int *L, VHeap *V, int elem);
void insertLast(int *L, VHeap *V, int elem);
void insertPos(int *L, VHeap *V, int elem, int pos);
void insertSorted(int *L, VHeap *V, int elem);
void delete(int *L, VHeap *V, int elem);
void deleteAllOccurrence(int *L, VHeap *V, int elem);
void display(int L, VHeap V);
void displayVHeap(VHeap V);

void initialize(VHeap *V) {
    V->Nodes = (HeapSpace *)malloc(MAX * sizeof(HeapSpace));
    V->avail = 0;
    for (int i = 0; i < MAX - 1; i++) {
        V->Nodes[i].next = i + 1;
    }
    V->Nodes[MAX - 1].next = -1;
}

int allocSpace(VHeap *V) {
    if (V->avail == -1) {
        return -1;
    }
    int allocated = V->avail;
    V->avail = V->Nodes[V->avail].next;
    return allocated;
}

void deallocSpace(VHeap *V, int index) {
    V->Nodes[index].next = V->avail;
    V->avail = index;
}

void insertFirst(int *L, VHeap *V, int elem) {
    int newCell = allocSpace(V);
    if (newCell == -1) {
        printf("Memory full! Cannot insert %d\n", elem);
        return;
    }
    V->Nodes[newCell].elem = elem;
    V->Nodes[newCell].next = *L;
    *L = newCell;
}

void insertLast(int *L, VHeap *V, int elem) {
    int newCell = allocSpace(V);
    if (newCell == -1) {
        printf("Memory full! Cannot insert %d\n", elem);
        return;
    }
    V->Nodes[newCell].elem = elem;
    V->Nodes[newCell].next = -1;
    if (*L == -1) {
        *L = newCell;
    } else {
        int trav = *L;
        while (V->Nodes[trav].next != -1) {
            trav = V->Nodes[trav].next;
        }
        V->Nodes[trav].next = newCell;
    }
}

void insertPos(int *L, VHeap *V, int elem, int pos) {
    int newCell = allocSpace(V);
    if (newCell == -1) {
        printf("Memory full! Cannot insert %d\n", elem);
        return;
    }
    V->Nodes[newCell].elem = elem;
    if (pos == 1) {
        V->Nodes[newCell].next = *L;
        *L = newCell;
        return;
    }
    int trav = *L;
    int count = 1;
    while (trav != -1 && count < pos - 1) {
        trav = V->Nodes[trav].next;
        count++;
    }
    if (trav == -1) {
        printf("Position %d is out of bounds\n", pos);
        deallocSpace(V, newCell);
        return;
    }
    V->Nodes[newCell].next = V->Nodes[trav].next;
    V->Nodes[trav].next = newCell;
}

void insertSorted(int *L, VHeap *V, int elem) {
    int newCell = allocSpace(V);
    if (newCell == -1) {
        printf("Memory full! Cannot insert %d\n", elem);
        return;
    }
    V->Nodes[newCell].elem = elem;
    if (*L == -1 || V->Nodes[*L].elem >= elem) {
        V->Nodes[newCell].next = *L;
        *L = newCell;
        return;
    }
    int trav = *L;
    while (V->Nodes[trav].next != -1 &&
           V->Nodes[V->Nodes[trav].next].elem < elem) {
        trav = V->Nodes[trav].next;
    }
    V->Nodes[newCell].next = V->Nodes[trav].next;
    V->Nodes[trav].next = newCell;
}

void delete(int *L, VHeap *V, int elem) {
    if (*L == -1) {
        printf("List is empty!\n");
        return;
    }
    if (V->Nodes[*L].elem == elem) {
        int toDelete = *L;
        *L = V->Nodes[*L].next;
        deallocSpace(V, toDelete);
        return;
    }
    int trav = *L;
    while (V->Nodes[trav].next != -1 &&
           V->Nodes[V->Nodes[trav].next].elem != elem) {
        trav = V->Nodes[trav].next;
    }
    if (V->Nodes[trav].next == -1) {
        printf("Element %d not found\n", elem);
        return;
    }
    int toDelete = V->Nodes[trav].next;
    V->Nodes[trav].next = V->Nodes[toDelete].next;
    deallocSpace(V, toDelete);
}

void deleteAllOccurrence(int *L, VHeap *V, int elem) {
    if (*L == -1) {
        printf("List is empty!\n");
        return;
    }
    while (*L != -1 && V->Nodes[*L].elem == elem) {
        int toDelete = *L;
        *L = V->Nodes[*L].next;
        deallocSpace(V, toDelete);
    }
    int trav = *L;
    while (trav != -1 && V->Nodes[trav].next != -1) {
        if (V->Nodes[V->Nodes[trav].next].elem == elem) {
            int toDelete = V->Nodes[trav].next;
            V->Nodes[trav].next = V->Nodes[toDelete].next;
            deallocSpace(V, toDelete);
        } else {
            trav = V->Nodes[trav].next;
        }
    }
}

void display(int L, VHeap V) {
    if (L == -1) {
        printf("List is empty\n");
        return;
    }
    printf("List: ");
    int trav = L;
    while (trav != -1) {
        printf("%d", V.Nodes[trav].elem);
        if (V.Nodes[trav].next != -1) {
            printf(" -> ");
        }
        trav = V.Nodes[trav].next;
    }
    printf("\n");
}

void displayVHeap(VHeap V) {
    printf("\n=== Virtual Heap Structure ===\n");
    printf("Index | Element | Next\n");
    printf("------|---------|-----\n");
    for (int i = 0; i < MAX; i++) {
        printf("  %d   |   %d     |  %d\n", i, V.Nodes[i].elem, V.Nodes[i].next);
    }
    printf("Available index (avail): %d\n\n", V.avail);
}

int main() {
    VHeap myHeap;
    int list1 = -1;
    int list2 = -1;

    initialize(&myHeap);

    printf("=== Testing Cursor-Based List ===\n\n");

    printf("--- Insert First ---\n");
    insertFirst(&list1, &myHeap, 10);
    insertFirst(&list1, &myHeap, 20);
    insertFirst(&list1, &myHeap, 30);
    display(list1, myHeap);

    printf("\n--- Insert Last ---\n");
    insertLast(&list1, &myHeap, 5);
    insertLast(&list1, &myHeap, 3);
    display(list1, myHeap);

    printf("\n--- Insert at Position 3 ---\n");
    insertPos(&list1, &myHeap, 25, 3);
    display(list1, myHeap);

    printf("\n--- Insert Sorted (new list) ---\n");
    insertSorted(&list2, &myHeap, 15);
    insertSorted(&list2, &myHeap, 5);
    insertSorted(&list2, &myHeap, 25);
    insertSorted(&list2, &myHeap, 10);
    insertSorted(&list2, &myHeap, 20);
    display(list2, myHeap);

    printf("\n--- Delete element 25 from list1 ---\n");
    delete(&list1, &myHeap, 25);
    display(list1, myHeap);

    printf("\n--- Add duplicates and delete all occurrences ---\n");
    insertLast(&list1, &myHeap, 10);
    insertLast(&list1, &myHeap, 10);
    printf("Before: ");
    display(list1, myHeap);
    deleteAllOccurrence(&list1, &myHeap, 10);
    printf("After deleting all 10s: ");
    display(list1, myHeap);

    displayVHeap(myHeap);

    free(myHeap.Nodes);

    return 0;
}