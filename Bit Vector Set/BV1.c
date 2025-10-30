#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Maximum number of elements that can be stored
#define MAX_ELEMENTS (8 * sizeof(unsigned char))

// Initialize set to empty
void initialize(unsigned char *set) {
    *set = 0;
}

// Insert an element into the set
void insert(unsigned char *set, int element) {
    // Safety check: ensure element is within valid range [0, MAX_ELEMENTS-1]
    if (element < 0 || element >= MAX_ELEMENTS) {
        printf("Error: Element %d out of range [0, %d]\n", element, MAX_ELEMENTS - 1);
        return;
    }
    
    // Create bitmask with bit set at element's position
    unsigned char mask = 1 << element;
    
    // Perform Bitwise OR assignment to set the bit
    *set |= mask;
}

// Delete an element from the set
void delete(unsigned char *set, int element) {
    // Safety check: ensure element is within valid range
    if (element < 0 || element >= MAX_ELEMENTS) {
        printf("Error: Element %d out of range [0, %d]\n", element, MAX_ELEMENTS - 1);
        return;
    }
    
    // Create mask for the element's position
    unsigned char mask = 1 << element;
    
    // Invert the mask (0 at target bit, 1s everywhere else)
    mask = ~mask;
    
    // Perform Bitwise AND assignment to clear the bit
    *set &= mask;
}

// Find if an element exists in the set
bool find(unsigned char set, int element) {
    // Check if element is within valid range
    if (element < 0 || element >= MAX_ELEMENTS) {
        return false;
    }
    
    // Create mask for the element's position
    unsigned char mask = 1 << element;
    
    // Use Bitwise AND to check if bit is set
    return (set & mask) != 0;
}

// Union of two sets (A ∪ B)
unsigned char set_union(unsigned char A, unsigned char B) {
    // Union is achieved by Bitwise OR
    return A | B;
}

// Intersection of two sets (A ∩ B)
unsigned char intersection(unsigned char A, unsigned char B) {
    // Intersection is achieved by Bitwise AND
    return A & B;
}

// Difference of two sets (A - B)
unsigned char difference(unsigned char A, unsigned char B) {
    // Difference is achieved by A AND (NOT B)
    return A & ~B;
}

// Display the set in human-readable format
void display(unsigned char set) {
    printf("{");
    bool first = true;
    
    // Iterate through all possible elements
    for (int i = 0; i < MAX_ELEMENTS; i++) {
        // Check if bit at position i is set
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

// Display set with decimal and binary representation
void display_full(unsigned char set) {
    printf("N=%d ", set);
    display(set);
    printf(" (");
    
    // Print binary representation (MSB to LSB)
    for (int i = MAX_ELEMENTS - 1; i >= 0; i--) {
        printf("%d", (set & (1 << i)) ? 1 : 0);
    }
    
    printf(")\n");
}

// Demo program
int main() {
    unsigned char A, B, C;
    
    printf("=== Bit Vector Set Demo ===\n\n");
    
    // Example 1: Insert operations
    printf("Example 1: Insert Operations\n");
    initialize(&A);
    printf("Initial: ");
    display_full(A);
    
    insert(&A, 1);
    printf("After insert(A, 1): ");
    display_full(A);
    
    insert(&A, 6);
    printf("After insert(A, 6): ");
    display_full(A);
    
    // Example 2: Delete operations
    printf("\nExample 2: Delete Operations\n");
    printf("Before delete: ");
    display_full(A);
    
    delete(&A, 6);
    printf("After delete(A, 6): ");
    display_full(A);
    
    delete(&A, 1);
    printf("After delete(A, 1): ");
    display_full(A);
    
    // Example 3: Union operation
    printf("\nExample 3: Union Operation\n");
    A = 66;  // {1, 6}
    B = 200; // {3, 6, 7}
    printf("A = ");
    display_full(A);
    printf("B = ");
    display_full(B);
    
    C = set_union(A, B);
    printf("C = union(A, B) = ");
    display_full(C);
    
    // Example 4: Intersection operation
    printf("\nExample 4: Intersection Operation\n");
    printf("A = ");
    display_full(A);
    printf("B = ");
    display_full(B);
    
    C = intersection(A, B);
    printf("C = intersection(A, B) = ");
    display_full(C);
    
    // Example 5: Difference operation
    printf("\nExample 5: Difference Operation\n");
    printf("A = ");
    display_full(A);
    printf("B = ");
    display_full(B);
    
    C = difference(A, B);
    printf("C = difference(A, B) = ");
    display_full(C);
    
    // Example 6: Find operation
    printf("\nExample 6: Find Operation\n");
    A = 202; // {1, 3, 6, 7}
    printf("A = ");
    display_full(A);
    printf("find(A, 3) = %s\n", find(A, 3) ? "true" : "false");
    printf("find(A, 5) = %s\n", find(A, 5) ? "true" : "false");
    
    return 0;
}