#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 8

typedef bool Set[ARRAY_SIZE];

void initialize(Set set) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        set[i] = false;
    }
}

void insert(Set set, int element) {
    if (element < 0 || element >= ARRAY_SIZE) {
        printf("Error: Element %d out of range [0, %d]\n", element, ARRAY_SIZE - 1);
        return;
    }

    set[element] = true;
}

void delete(Set set, int element) {
    if (element < 0 || element >= ARRAY_SIZE) {
        printf("Error: Element %d out of range [0, %d]\n", element, ARRAY_SIZE - 1);
        return;
    }

    set[element] = false;
}

bool find(Set set, int element) {
    if (element < 0 || element >= ARRAY_SIZE) {
        return false;
    }

    return set[element];
}

void union_set(Set A, Set B, Set C) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        C[i] = A[i] || B[i];
    }
}

void intersection(Set A, Set B, Set C) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        C[i] = A[i] && B[i];
    }
}

void difference(Set A, Set B, Set C) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        C[i] = A[i] && !B[i];
    }
}

void display(Set set) {
    printf("{");
    bool first = true;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (set[i]) {
            if (!first) {
                printf(", ");
            }
            printf("%d", i);
            first = false;
        }
    }

    printf("}");
}

void display_array(Set set) {
    printf("[");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d", set[i] ? 1 : 0);
        if (i < ARRAY_SIZE - 1) {
            printf(",");
        }
    }
    printf("]");
}

void display_full(Set set) {
    printf("// ");
    display_array(set);
    printf(" ");
    display(set);
    printf("\n");
}

int main() {
    Set A, B, C;

    printf("=== Boolean Array Set Demo ===\n\n");

    printf("Example 1: Initialize\n");
    printf("Set A;\n");
    initialize(A);
    printf("initialize(A); ");
    display_full(A);
    printf("\n");

    printf("Example 2: Insert Operations\n");
    insert(A, 0);
    printf("insert(A, 0); ");
    display_full(A);

    insert(A, 2);
    printf("insert(A, 2); ");
    display_full(A);

    insert(A, 7);
    printf("insert(A, 7); ");
    display_full(A);

    printf("\n// Final set: ");
    display(A);
    printf("\n\n");

    printf("Example 3: Delete Operations\n");
    display_full(A);
    printf("\n");

    delete(A, 0);
    printf("delete(A, 0); ");
    display_full(A);

    delete(A, 7);
    printf("delete(A, 7); ");
    display_full(A);

    printf("\n// Final set: ");
    display(A);
    printf("\n\n");

    printf("Example 4: Union Operation\n");
    initialize(A);
    insert(A, 0);
    insert(A, 2);
    insert(A, 7);
    printf("// A = ");
    display_full(A);

    initialize(B);
    insert(B, 2);
    insert(B, 4);
    insert(B, 5);
    printf("// B = ");
    display_full(B);

    printf("\nSet C;\n");
    union_set(A, B, C);
    printf("union(A, B, C);\n");
    printf("// C = ");
    display_full(C);
    printf("\n");

    printf("Example 5: Intersection Operation\n");
    printf("// A = ");
    display_full(A);
    printf("// B = ");
    display_full(B);

    printf("\nSet C;\n");
    intersection(A, B, C);
    printf("intersection(A, B, C);\n");
    printf("// C = ");
    display_full(C);
    printf("\n");

    printf("Example 6: Difference Operation\n");
    printf("// A = ");
    display_full(A);
    printf("// B = ");
    display_full(B);

    printf("\nSet C;\n");
    difference(A, B, C);
    printf("difference(A, B, C);\n");
    printf("// C = ");
    display_full(C);
    printf("\n");

    printf("Example 7: Find Operation\n");
    printf("// A = ");
    display_full(A);
    printf("\nfind(A, 2) = %s\n", find(A, 2) ? "true" : "false");
    printf("find(A, 5) = %s\n", find(A, 5) ? "true" : "false");
    printf("\n");

    printf("Example 8: Display\n");
    initialize(A);
    insert(A, 1);
    insert(A, 3);
    insert(A, 6);
    insert(A, 7);

    printf("display(A): ");
    display(A);
    printf("\n");

    return 0;
}