#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}Node;

typedef struct{
    Node *head;
    int count;
}List;

List* initialize();
void empty(List *list);
void insertFirst(List *list, int data);
void insertLast(List *list, int data);
void insertPos(List *list, int data, int index);
void deleteStart(List *list);
// void deleteLast(List *list);
// void deletePos(List *list, int index);
// int retrieve(List *list, int index);
// int locate(List *list, int data);
void display(List *list);


int main(){
    List *list;
    
    list = initialize();

    insertFirst(list, 2);
    insertFirst(list, 6);
    insertFirst(list, 5);
    
    display(list);

    insertLast(list, 4);
    display(list);
    insertLast(list, 5);
    insertLast(list, 10);
    insertLast(list, 20);

    display(list);

    insertPos(list,200, 4);
    display(list);
    deleteStart(list);
    display(list);

}

List *initialize(){
    List *list = (List *)malloc(sizeof(List));
    if(list == NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    list->head = NULL;
    list->count = 0;

    return list;
}

void deleteStart(List *list){
    Node *trav = list->head;
    list->head = trav;

    free(trav);
    list->count--;
}
void display(List *list){
    Node *trav = list->head;
    printf("List: [ ");
    while(trav != NULL){
        printf("%d", trav->data);
        if(trav->next != NULL){
            printf(", ");
        }
        trav = trav->next;
    }
    printf(" ]");
    printf("\nList count = %d\n", list->count);
}

void empty(List *list){
    Node *trav = list->head;

    while(trav->next != NULL){
       trav->data =0;
       trav = trav->next;
    }

    printf("Emptying list\n");

    list->head = NULL;
    list->count = 0;
}

void insertFirst(List *list, int data){
    Node *newNode = (Node *)malloc(sizeof(Node));
    
    newNode->data = data;
    newNode->next = list->head;

    list->head = newNode;
    list->count++;
    
}

void insertLast(List *list, int data){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL; 

    if(list->head == NULL){
        list->head = newNode;
    }else{
        Node *trav = list->head;
        while (trav->next != NULL){
            trav = trav->next;
        }
        if(trav->next == NULL);
        trav->next = newNode;
        list->count++;
    }
        
}

void insertPos(List *list, int data, int index){
    if(index > list->count){
        printf("Invalid index. CHANGE IT");
        return;
    }else if(index == 0){
        insertFirst(list,data);
    }else if(index == list->count){
        insertLast(list,data);
    }else{
        Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    Node *trav = list->head;
    int count = 1;

    while(count != index - 1){
        trav = trav->next;
        count++;
    }
    newNode->next = trav->next;
    trav->next = newNode;
    list->count++;
    }
}