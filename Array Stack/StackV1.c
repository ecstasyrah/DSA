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
}

Stack* initialize(){
    Stack *S = (Stack*)malloc(sizeof(Stack));

    S->top = -1;

    return S;
}

void display(Stack* s){
    isEmpty(s);
    printf("\nDisplay: [ ");
    for(int i = 0; i <= s->top; i++){
        printf("%d", s->items[i]);
        if(i < s->top){
            printf(", ");
        }
    }

    printf(" ]\n Top: %d", s->top);
}

void push(Stack* s, int value){
    if(isFull(s) == 1){
        s->top++;
    }else{
        s->top++;
        s->items[s->top] = value;
    }
}

int pop(Stack* s){
    isEmpty(s);
    int value = s->items[s->top];
    s->top--;
    return value;
}

int peek(Stack* s) {
    isEmpty(s);
    int value = s->items[s->top];

    return value;
}

bool isFull(Stack* S) {
    if (S->top == MAX - 1) {
        return 1;
    }
}
void isEmpty(Stack* S) {
    if (S->top == - 1) {
        printf("Stack is empty.");
    }
}
