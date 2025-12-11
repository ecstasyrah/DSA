#include <stdio.h>
#include <string.h>

#define MAX_SIZE 50
#define STRING_LEN 100

typedef struct {
    char term[STRING_LEN];
    char definition[STRING_LEN];
} Entry;

typedef struct {
    Entry entries[MAX_SIZE];
    int count;
} Dictionary;

void initDict(Dictionary *d) {
    d->count = 0;
}

void addTerm(Dictionary *d, const char *term, const char *def) {
    if (d->count >= MAX_SIZE) {
        printf("Dictionary is full.\n");
        return;
    }

    strcpy(d->entries[d->count].term, term);
    strcpy(d->entries[d->count].definition, def);
    d->count++;
}

void findDefinition(Dictionary *d, const char *target) {
    for (int i = 0; i < d->count; i++) {
        if (strcmp(d->entries[i].term, target) == 0) {
            printf("Found: %s means '%s'\n", target, d->entries[i].definition);
            return;
        }
    }
    printf("Term '%s' not found in dictionary.\n", target);
}

void displayAll(Dictionary *d) {
    printf("\n--- My Study Dictionary ---\n");
    for (int i = 0; i < d->count; i++) {
        printf("%d. %s: %s\n", i + 1, d->entries[i].term, d->entries[i].definition);
    }
    printf("---------------------------\n");
}

int main() {
    Dictionary myDict;
    initDict(&myDict);

    addTerm(&myDict, "Algorithm", "Step-by-step instructions");
    addTerm(&myDict, "Variable", "Container for data");
    addTerm(&myDict, "Pointer", "Stores memory address");
    addTerm(&myDict, "Array", "Collection of same type");

    displayAll(&myDict);

    printf("\n--- Quiz Mode ---\n");
    findDefinition(&myDict, "Pointer");
    findDefinition(&myDict, "Recursion");

    return 0;
}