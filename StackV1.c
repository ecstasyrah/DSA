#include <stdio.h>
#include<stdlib.h>

#define MAX 10

typedef struct{
    int items[MAX];
    int top;
}Stack;

Stack* initialize();
void push(Stack* s, int value);
int pop(Stack* s);
// int peek(Stack* s);
void display(Stack* s);

int main(){
    Stack *S = initialize();

    push(S, 5);
    push(S, 2);
    push(S, 6);
    push(S, 8);
    push(S, 3);
    push(S, 4);
    push(S, 5);

    display(S);

    int value = pop(S);
    printf("\n\nLast top value was %d\n New top: %d", value, S->top);
}

Stack* initialize(){
    Stack *S = (Stack*)malloc(sizeof(Stack));
    // if(S==NULL){
    //     printf("Data allocation unsuccessful");
    //     return NULL;
    // }else{
    //     printf("SUMAKSES KA!!\n\n");
    // }

    S->top = -1;

    return S;
}

void display(Stack* s){
    if(s->top == -1){
        printf("Stack is empty\n");
    }
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
    if(s->top == MAX - 1){
        s->top++;
    }else{
        s->top++;
        s->items[s->top] = value;
    }
}

int pop(Stack* s){
    if(s->top == -1){
        printf("Stack is empty");
    }
    int value = s->items[s->top];
    s->top--;
    return value;
}