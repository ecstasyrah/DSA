#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- STRUCTS ---
typedef struct Node {
    char task[50];
    int priority;
    struct Node* next;
} Node;

typedef struct PriorityQueue {
    Node* front;
} PriorityQueue;

// --- FUNCTION PROTOTYPES ---
Node* createNode(char* task, int priority);
void initQueue(PriorityQueue* pq);
void enqueue(PriorityQueue* pq, char* task, int priority); // <--- TODO: KEY PRACTICE
void dequeue(PriorityQueue* pq);                           // <--- TODO: KEY PRACTICE
void display(PriorityQueue* pq);

// --- MAIN (TESTING) ---
int main() {
    PriorityQueue pq;
    initQueue(&pq);

    // Test Case 1: Add mixed priorities
    printf("Adding tasks...\n");
    enqueue(&pq, "Do laundry", 3);
    enqueue(&pq, "Pay bills", 1);      // Should be 1st
    enqueue(&pq, "Play games", 5);
    enqueue(&pq, "Cook dinner", 2);    // Should be 2nd

    // EXPECTED ORDER: Pay bills(1) -> Cook dinner(2) -> Do laundry(3) -> Play games(5)
    printf("\nCurrent Queue (Should be sorted 1->5):\n");
    display(&pq);

    // Test Case 2: Dequeue
    printf("\nServing highest priority...\n");
    dequeue(&pq); // Should remove "Pay bills"
    display(&pq);


    return 0;
}
//STRUCTURE
// typedef struct Node {
//     char task[50];
//     int priority;
//     struct Node* next;
// } Node;
//
// typedef struct PriorityQueue {
//     Node* front;
// } PriorityQueue;

// --- IMPLEMENTATION HELPERS (DONE FOR YOU) ---

void initQueue(PriorityQueue* pq) {
    pq->front = NULL;
}
// --- YOUR TURN: IMPLEMENT THESE —

Node* createNode(char* task, int priority) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    strcpy(newNode->task, task);
    newNode->priority = priority;
    newNode->next = NULL;

    return newNode;
}

void display(PriorityQueue* pq) {
    if (pq->front == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    Node* temp = pq->front;
    printf("--------------------------------\n");
    printf(" Prio | Task\n");
    printf("--------------------------------\n");
    while (temp != NULL) {
        printf("  %d   | %s \n", temp->priority, temp->task);
        temp = temp->next;
    }
    printf("--------------------------------\n");
}

/* * TODO: Insert the node in the correct position based on priority.
 * Case 1: List is empty (new node becomes front).
 * Case 2: New node has higher priority (smaller number) than front (new node becomes new front).
 * Case 3: New node goes somewhere in the middle or end.
 */
void enqueue(PriorityQueue* pq, char* task, int priority) {
    Node* newNode = createNode(task, priority);
    
    // CODE HERE
    if (pq->front == NULL) {
        pq->front = newNode;
    }else {
        Node* temp = pq->front;
        while(temp->next!=NULL && newNode->priority >= temp->next->priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

}

/*
 * TODO: Remove the node at the front of the list.
 * Remember to free() the memory!
 */
void dequeue(PriorityQueue* pq) {
    if (pq->front == NULL) {
        printf("------ List Empty ------");
    }

    pq->front = pq->front->next;
}
