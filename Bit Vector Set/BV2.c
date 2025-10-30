#include <stdio.h>
#include <stdbool.h>

typedef struct {
    unsigned int field : 8;
} Set;

void initialize(Set *set) {
    set->field = 0;
}

void insert(Set *set, int element) {
    if (element < 0 || element > 7) {
        printf("Error: Element %d out of range [0, 7]\n", element);
        return;
    }

    unsigned int mask = 1 << element;

    set->field |= mask;
}
void delete(Set *set, int element) {
    if (element < 0 || element > 7) {
        printf("Error: Element %d out of range [0, 7]\n", element);
        return;
    }
    
    unsigned int mask = 1 << element;
    
    mask = ~mask;
    
    set->field &= mask;
}

bool find(Set set, int element) {
    if (element < 0 || element > 7) {
        return false;
    }
    
    unsigned int mask = 1 << element;
    
    return (set.field & mask) != 0;
}

Set union_set(Set A, Set B) {
    Set result;
    result.field = A.field | B.field;
    return result;
}

Set intersection(Set A, Set B) {
    Set result;
    result.field = A.field & B.field;
    return result;
}

Set difference(Set A, Set B) {
    Set result;
    result.field = A.field & ~B.field;
    return result;
}

void display(unsigned char set) {
    printf("{");
    bool first = true;
    
    for (int i = 0; i <= 7; i++) {
        if (set & (1 << i)) {
            if (!first) {
                printf(", ");
            }
            printf("%d", i);
            first = false;
        }
    }
    
    printf("}");
}

void display_full(Set set) {
    printf("-> A.field = %d ", set.field);
    display(set.field);
    printf("\n");
}

int main() {
    Set A, B, C;
    
    printf("=== Bit Field Set Demo ===\n\n");
    
    printf("Example 1: Insert Operations\n");
    initialize(&A);
    printf("Set A;\ninitialize(A); // A.field = 0\n\n");
    
    insert(&A, 0);
    printf("insert(A, 0); // A.field = %d\n", A.field);
    
    insert(&A, 4);
    printf("insert(A, 4); // A.field = %d\n", A.field);
    
    insert(&A, 5);
    printf("insert(A, 5); ->A.field = %d\n", A.field);
    
    printf("\n Final set: ");
    display(A.field);
    printf("\n\n");
    
    printf("Example 2: Delete Operations\n");
    printf("// A.field = %d\n\n", A.field);
    
    delete(&A, 5);
    printf("delete(A, 5); // A.field = %d\n", A.field);
    
    delete(&A, 4);
    printf("delete(A, 4); // A.field = %d\n", A.field);
    
    printf("\n// Final set: ");
    display(A.field);
    printf("\n\n");
    
    printf("Example 3: Union Operation\n");
    A.field = 49;
    B.field = 36;
    
    printf("// A.field = %d ", A.field);
    display(A.field);
    printf("\n");
    
    printf("// B.field = %d ", B.field);
    display(B.field);
    printf("\n\n");
    
    C = union_set(A, B);
    printf("Set C = union(A, B);\n");
    printf("// C.field = %d ", C.field);
    display(C.field);
    printf("\n\n");
    
    // Example 4: Intersection operation
    printf("Example 4: Intersection Operation\n");
    printf("// A.field = %d ", A.field);
    display(A.field);
    printf("\n");
    
    printf("// B.field = %d ", B.field);
    display(B.field);
    printf("\n\n");
    
    C = intersection(A, B);
    printf("Set C = intersection(A, B);\n");
    printf("// C.field = %d ", C.field);
    display(C.field);
    printf("\n\n");

    printf("Example 5: Difference Operation\n");
    printf("// A.field = %d ", A.field);
    display(A.field);
    printf("\n");
    
    printf("// B.field = %d ", B.field);
    display(B.field);
    printf("\n\n");
    
    C = difference(A, B);
    printf("Set C = difference(A, B);\n");
    printf("// C.field = %d ", C.field);
    display(C.field);
    printf("\n\n");

    printf("Example 6: Find Operation\n");
    A.field = 49;
    printf("// A.field = %d ", A.field);
    display(A.field);
    printf("\n");
    
    printf("find(A, 4) = %s\n", find(A, 4) ? "true" : "false");
    printf("find(A, 3) = %s\n", find(A, 3) ? "true" : "false");

    printf("\nExample 7: Display\n");
    A.field = 202;
    printf("A.field = %d\n", A.field);
    printf("display(A): ");
    display(A.field);
    printf("\n");
    
    return 0;
}