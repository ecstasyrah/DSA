#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct{
    int items[MAX];
    int top;
}Stack;

Stack* initialize();
bool isFull(Stack* S);
void isEmpty(Stack* S);
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
void display(Stack* s);

int main(){
    Stack *S = initialize();

    push(S, 1);
    push(S, 3);
    push(S, 2);
    push(S, 5);
    push(S, 4);

    display(S);

    printf("\n\nPop:");
    int value = pop(S);
    printf("\nLast top value was %d\n New top: %d", value, S->top);

    printf("\n\nPeek:\nTop: %d\t\tValue: %d", S->top, peek(S));

    return 0;
}

Stack* initialize(){
    Stack *S = (Stack*)malloc(sizeof(Stack));

    S->top = MAX;  // Initialize as MAX indicating empty

    return S;
}

void display(Stack* s){
    isEmpty(s);
    printf("\nDisplay: [ ");

    // Display from right to left (from MAX-1 down to top)
    for(int i = MAX - 1; i >= s->top; i--){
        printf("%d", s->items[i]);
        if(i > s->top){
            printf(", ");
        }
    }

    printf(" ]\n Top: %d", s->top);
}

void push(Stack* s, int value){
    if(isFull(s)){
        printf("Stack overflow! Cannot push %d\n", value);
    } else {
        s->top--;  // Move top to the left
        s->items[s->top] = value;
    }
}

int pop(Stack* s){
    if(s->top == MAX){
        printf("Stack is empty. Cannot pop.\n");
        return -1;  // Return sentinel value for empty stack
    }

    int value = s->items[s->top];
    s->top++;  // Move top to the right (back toward MAX)
    return value;
}

int peek(Stack* s) {
    if(s->top == MAX){
        printf("Stack is empty. Cannot peek.\n");
        return -1;  // Return sentinel value for empty stack
    }

    int value = s->items[s->top];
    return value;
}

bool isFull(Stack* S) {
    return (S->top == 0);  // Stack is full when top reaches position 0
}

void isEmpty(Stack* S) {
    if (S->top == MAX) {
        printf("Stack is empty.");
    }
}