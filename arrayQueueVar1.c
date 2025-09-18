#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5

typedef struct {
    int items[MAX];
    int count;
}List;

typedef struct{
    List list;
    int front;
    int rear;
}Queue;

Queue* initialize();
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

int main(){
    Queue* q = initialize();

    enqueue(q, 1);
    enqueue(q, 3);
    enqueue(q, 2);
    enqueue(q, 5);
    display(q);
    dequeue(q);
    display(q);

    free(q);
    return 0;
}

Queue* initialize(){
    Queue* q = (Queue*)malloc(sizeof(Queue));

    q->list.count = 0;
    q->front = q->rear = -1;

    return q;
}

bool isFull(Queue* q){
    if(q->list.count == MAX && (q->rear + 1)%MAX == q->front){
        return 1;
    }else{
        return 0;
    }
}
bool isEmpty(Queue* q){
    if(q->list.count == 0){
        return 1;
    }else{
        return 0;
    }
}
void enqueue(Queue* q, int value){
    if(isFull(q) == 1){
        //1. chfeck if its full
        printf("Queue is full.\n\n");
    }else if(isEmpty(q) == 1){
        //2. check if its empty
        q->rear = q->front = 0;
        q->list.items[q->rear] = value;
        q->list.count++;
    }else{
        //3. insert when it's not full and empty(just normal)
        q->rear = (q->rear+1)%MAX; // rear++ for circular queue;
        q->list.items[q->rear] = value;
        q->list.count++;
    }
}
int dequeue(Queue* q){
    int deqVal;
    if(isEmpty(q) == 1){
        //1. checj if empty
        printf("Underflow.\n\n");
    }else if(q->front == q->rear){
        //2. there is only 1 item inside the array
        q->rear = q->front = -1;
        q->list.count--;
    }else{
        deqVal = q->front;
        q->front = (q->front+1)%MAX;
        q->list.count--;
        return deqVal;
    }

    return 0;
}
int front(Queue* q){
    if(isEmpty(q) == 1){
        printf("Queue is empty\n\n");
        return 0;
    }else{
        return q->list.items[q->front];
    }
}
void display(Queue* q){
    printf("Display:\n\nitems: [ ");
    int i = q->front;
    for(;i != q->rear; i=(i+1) % MAX){
        printf("%d ", q->list.items[i]);
        if(i != q->list.count){
            printf(", ");
        }
    }
    printf("%d ]\n", q->list.items[q->rear]);
    printf("Count: %d\nFront: %d\nRear: %d\n\n", q->list.count
                                            ,front(q)
                                            ,q->list.items[q->list.count-1]);
}


