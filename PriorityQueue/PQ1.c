#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    char name[50];
    int priority;
    struct node* next;
}Node;

typedef struct {
    Node *front;
}PQ;

PQ* initialize() {
    PQ* prio = (PQ*)malloc(sizeof(PQ));

    prio->front = NULL;

    return prio;
}

Node* createNewNode() {
    Node* newNode = malloc(sizeof(Node));

    newNode->next = NULL;
    return newNode;
}

void enqueue(PQ* prio, char* name, int priority) {
    Node* newNode = createNewNode();
    strcpy(newNode->name, name);
    newNode->priority = priority;

    if (prio->front == NULL || newNode->priority < prio->front->priority) {
        newNode->next = prio->front;
        prio->front = newNode;
    }else {
        Node* temp = prio->front;
        while(temp->next!=NULL && temp->next->priority <= newNode->priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

char* dequeue(PQ* prio) {
    if(prio->front == NULL) {
        return NULL;
    }

    Node* temp = prio->front;
    char* removedName = malloc(50);
    strcpy(removedName, temp->name);
    prio->front = prio->front->next;

    return removedName;

}

bool isPatientInQueue(PQ* prio, char* targetName) {
    Node* temp = prio->front;

    while (temp!=NULL) {
        if (strcmp(temp->name,targetName) == 0) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void findPatientsLike(PQ* prio, char* fragment) {
    Node* temp = prio->front;
    printf("\n------ FINDING '%s' PATIENTS ------\n\n %-12s | %-20s\n", fragment, "Priority #", "Patient Name");
    while (temp->next != NULL) {
        char* result = strstr(temp->name, fragment);
        if (result !=NULL) {
            printf("%-12d | %-20s\n", temp->priority, temp->name);
        }
        temp = temp->next;
    }
}

void display(PQ* prio) {
    if (prio->front == NULL) {
        printf("You currently have 0 patients");
    }

    Node* temp = prio->front;
    printf("------ PRIORITY QUEUE ------\n\n %-12s | %-20s\n", "Priority #", "Patient Name");
    while (temp!=NULL) {
        printf(" %-12d | %-20s \n", temp->priority, temp->name);
        temp = temp->next;
    }
}

int main() {
    PQ* prio = initialize();

    enqueue(prio, "Sarah", 20);
    enqueue(prio, "Dot", 10);
    enqueue(prio, "eyee", 15);
    enqueue(prio, "eye2", 40);

    display(prio);

    printf("\n%s is done\n\n", dequeue(prio));

    char name[50];
    printf("Find name: ");
    scanf("%s", name);

    if (isPatientInQueue(prio, name) == 1) {
        printf("%s is here\n", name);
    }else {
        printf("%s is not here\n",name);
    }

    char* remove = dequeue(prio);
    printf("\n%s is done\n\n", remove);

    display(prio);
    enqueue(prio, "Sachi", 30);
    enqueue(prio, "soooo", 50);
    enqueue(prio, "esee", 12);
    enqueue(prio, "ese2", 41);
    display(prio);

    char fragment[50];

    printf("\n\nFind patients with: ");
    scanf("%s", fragment);

    findPatientsLike(prio, fragment);
    free(prio);
    free(remove);

    return 0;
}