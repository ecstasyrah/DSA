#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

Stack* initialize() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s == NULL) return NULL;
    s->top = NULL;
    return s;
}

bool isFull(Stack* s) {
    return false;
}

bool isEmpty(Stack* s) {
    return (s->top == NULL);
}

void push(Stack* s, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return;

    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        return -1;
    }

    Node* temp = s->top;
    int data = temp->data;

    s->top = s->top->next;
    free(temp);
    
    return data;
}

int peek(Stack* s) {
    if (isEmpty(s)) {
        return -1;
    }
    return s->top->data;
}

void display(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return;
    }

    Node* temp = s->top;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Stack* S = initialize();

    push(S, 1);
    push(S, 3);
    push(S, 5);
    display(S);

    push(S, 4);
    display(S);

    pop(S);
    display(S);

    return 0;
}