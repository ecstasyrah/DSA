#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PRIMARY_SIZE 10
#define TOTAL_SIZE 20
#define NULL_CURSOR -1

typedef struct {
    char code[4];
    int cursor;
    int occupied;
} HashNode;

HashNode hashTable[TOTAL_SIZE];
int AVAIL = PRIMARY_SIZE;

// Hash function
int hash(char *code) {
    int val = ((code[0] - 'A') * 26 * 26 +
               (code[1] - 'A') * 26 +
               (code[2] - 'A')) % PRIMARY_SIZE;
    return val;
}

void initHashTable() {
    for (int i = 0; i < TOTAL_SIZE; i++) {
        hashTable[i].code[0] = '\0';
        hashTable[i].cursor = NULL_CURSOR;
        hashTable[i].occupied = 0;
    }
    AVAIL = PRIMARY_SIZE;
}

void insert(char *code) {
    int hashVal = hash(code);

    printf("\nInserting %s (hash = %d):\n", code, hashVal);

    if (hashTable[hashVal].occupied == 0) {
        strcpy(hashTable[hashVal].code, code);
        hashTable[hashVal].occupied = 1;
        hashTable[hashVal].cursor = NULL_CURSOR;
        printf("  -> Inserted at index %d (primary slot)\n", hashVal);
        printf("  -> AVAIL = %d\n", AVAIL);
    }
    else {
        printf("  -> Collision detected at index %d\n", hashVal);

        int current = hashVal;
        while (hashTable[current].cursor != NULL_CURSOR) {
            current = hashTable[current].cursor;
        }

        if (AVAIL < TOTAL_SIZE) {
            strcpy(hashTable[AVAIL].code, code);
            hashTable[AVAIL].occupied = 1;
            hashTable[AVAIL].cursor = NULL_CURSOR;

            hashTable[current].cursor = AVAIL;

            printf("  -> Inserted at overflow index %d\n", AVAIL);
            printf("  -> Updated cursor of index %d to point to %d\n", current, AVAIL);

            printf("  -> AVAIL = %d\n", AVAIL);
        } else {
            printf("  -> ERROR: Hash table overflow! No more space.\n");
        }
    }
}

void displayHashTable() {
    printf("\n");
    printf("=======================================================\n");
    printf("           FINAL STATE OF VIRTUAL HEAP\n");
    printf("=======================================================\n");
    printf("AVAIL = %d\n\n", AVAIL);
    printf("Index | Airport Code | Cursor/Link | Status\n");
    printf("------|--------------|-------------|----------\n");

    for (int i = 0; i < TOTAL_SIZE; i++) {
        printf("  %2d  | ", i);

        if (hashTable[i].occupied) {
            printf("%-12s | ", hashTable[i].code);
            if (hashTable[i].cursor == NULL_CURSOR) {
                printf("%-11s | ", "null");
            } else {
                printf("%-11d | ", hashTable[i].cursor);
            }
            printf("Occupied\n");
        } else {
            printf("%-12s | %-11s | Empty\n", "(empty)", "null");
        }
    }
    printf("=======================================================\n");
}

void displayHashIndex() {
    printf("\n");
    printf("=======================================================\n");
    printf("              HASH INDEX TABLE\n");
    printf("=======================================================\n");
    printf("Airport Code | Hash Value | Final Index\n");
    printf("-------------|------------|-------------\n");

    for (int i = 0; i < TOTAL_SIZE; i++) {
        if (hashTable[i].occupied) {
            int hashVal = hash(hashTable[i].code);
            printf("%-12s | %-10d | %d", hashTable[i].code, hashVal, i);
            if (i >= PRIMARY_SIZE) {
                printf(" (overflow)");
            }
            printf("\n");
        }
    }
    printf("=======================================================\n");
}

// Display collision chains
void displayCollisionChains() {
    printf("\n");
    printf("=======================================================\n");
    printf("              COLLISION CHAINS\n");
    printf("=======================================================\n");

    for (int i = 0; i < PRIMARY_SIZE; i++) {
        if (hashTable[i].occupied) {
            printf("Hash %d: %s", i, hashTable[i].code);

            int current = hashTable[i].cursor;
            while (current != NULL_CURSOR) {
                printf(" -> %s", hashTable[current].code);
                current = hashTable[current].cursor;
            }
            printf("\n");
        }
    }
    printf("=======================================================\n");
}

int main() {
    // Airport codes from Set A
    char *airports[] = {
        "JFK", "LAX", "SFO", "CDG", "LHR", "NRT",
        "ATL", "DXB", "PEK", "MIA", "SYD", "ORD"
    };
    int numAirports = 12;

    printf("=======================================================\n");
    printf("  CLOSED HASHING DICTIONARY SIMULATION\n");
    printf("  Cursor-Based with Progressive Overflow\n");
    printf("=======================================================\n");

    initHashTable();

    for (int i = 0; i < numAirports; i++) {
        insert(airports[i]);
    }

    displayHashTable();
    displayHashIndex();
    displayCollisionChains();

    return 0;
}