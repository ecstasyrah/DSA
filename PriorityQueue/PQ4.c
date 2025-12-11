#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- STRUCTS ---
typedef struct Job {
    char filename[50];
    int priority;       // 1 (Admin/Critical) to 5 (Standard User)
    struct Job* next;
} Job;

typedef struct PrintQueue {
    Job* head;      // Points to the most important file
} PrintQueue;

// --- PROTOTYPES ---
Job* createJob(char* filename, int priority);
void initQueue(PrintQueue* pq);
void addFile(PrintQueue* pq, char* filename, int priority); // <--- TODO: ENQUEUE
void printNext(PrintQueue* pq);                             // <--- TODO: DEQUEUE
void showSpooler(PrintQueue* pq);

// --- MAIN ---
int main() {
    PrintQueue pq;
    initQueue(&pq);

    printf("--- PRINTER SYSTEM ONLINE ---\n");

    // 1. Users send files
    addFile(&pq, "Recipe.docx", 5);       // Standard User
    addFile(&pq, "Meme.jpg", 5);          // Standard User
    addFile(&pq, "Payroll.xlsx", 1);      // Admin (Must become HEAD)
    addFile(&pq, "MeetingNotes.txt", 3);  // Manager

    // 2. Verify Order (Should be: Payroll -> MeetingNotes -> Recipe -> Meme)
    showSpooler(&pq);

    // 3. Print files
    printf("\n--- PRINTING STARTED ---\n");
    printNext(&pq); // Prints Payroll
    printNext(&pq); // Prints MeetingNotes

    showSpooler(&pq);

    return 0;
}

// --- HELPERS ---
void initQueue(PrintQueue* pq) {
    pq->head = NULL;
}

Job* createJob(char* filename, int priority) {
    Job* newJ = (Job*)malloc(sizeof(Job));
    strcpy(newJ->filename, filename);
    newJ->priority = priority;
    newJ->next = NULL;
    return newJ;
}

void showSpooler(PrintQueue* pq) {
    if (pq->head == NULL) {
        printf("Print spooler is empty.\n");
        return;
    }
    Job* temp = pq->head;
    printf("\n[ PRINT SPOOLER ]\n");
    while (temp != NULL) {
        printf("Priority %d : %s\n", temp->priority, temp->filename);
        temp = temp->next;
    }
    printf("----------------\n");
}

// ==========================================
// YOUR TASKS START HERE
// ==========================================
// typedef struct Job {
//     char filename[50];
//     int priority;       // 1 (Admin/Critical) to 5 (Standard User)
//     struct Job* next;
// } Job;
//
// typedef struct PrintQueue {
//     Job* head;      // Points to the most important file
// } PrintQueue;

// * TODO: ADD FILE (Enqueue)

void addFile(PrintQueue* pq, char* filename, int priority) {
    Job* newJ = createJob(filename, priority);
    Job* temp = pq->head;

    if (pq->head == NULL || pq->head->priority > newJ->priority){
        newJ->next = pq->head;
        pq->head = newJ;
    }else {
        while (temp->next != NULL && temp->next->priority <= newJ->priority) {
            temp = temp->next;
        }
        newJ->next = temp->next;
        temp->next = newJ;
    }
}

/* * TODO: PRINT NEXT (Dequeue)
 * 1. Check if empty.
 * 2. Save the current head to temp.
 * 3. Print "Printing [filename]..."
 * 4. Move the head to the next file.
 * 5. Free the temp pointer.
 */
void printNext(PrintQueue* pq) {
    // WRITE YOUR CODE HERE
    Job* temp = pq->head;

    printf("Printing %s...\n", pq->head->filename);
    pq->head = pq->head->next;


}