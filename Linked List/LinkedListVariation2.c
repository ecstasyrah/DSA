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
void deleteLast(List *list);
void deletePos(List *list, int index);
int retrieve(List *list, int index);
int locate(List *list, int data);
void display(List *list);


int main(){
    List *list;
    
    list = initialize();

    printf("Insert first: \n");

    insertFirst(list, 2);
    insertFirst(list, 6);
    insertFirst(list, 5);
    
    display(list);
    printf("\nInsert Last: \n");
    insertLast(list, 4);
    insertLast(list, 5);
    insertLast(list, 10);
    insertLast(list, 20);

    display(list);
    printf("\nInsert Position: \n");
    insertPos(list,200, 4);
    display(list);

    printf("\nDelete Start: \n");
    deleteStart(list);
    display(list);

    printf("\nDelete Last: \n");
    deleteLast(list);
    display(list);

    printf("\nDelete Position: \n");
    deletePos(list, 5);
    display(list);

    printf("\nRetrieve data: \n");
    printf("Index %d has data %d", 4, retrieve(list,4));

    printf("\n\nLocate data: \n");
    printf("Data %d is in index %d", 200, locate(list,200));

    printf("\n\nEmpty list: \n");
    empty(list);
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

void deletePos(List *list, int index){
    if(index == 0){
        deleteStart(list);
    }else{
        Node *trav= list->head;
        int count = 1;
        while(count != index - 1){
            trav = trav->next;
            count++;
        }
        Node *temp = trav->next;
        trav->next = temp->next;
        free(temp);
        list->count--;
    }
}

void deleteLast(List *list){
    if(list->head->next == NULL){
        free(list->head);
        list->head = NULL;
        list->count--;
    }else{
        Node *trav = list->head;
        int count = 0;
        while(count != list->count -2){
            trav = trav->next;
            count++;
        }
        free(trav->next);
        trav->next = NULL;
        list->count--;
    }
}


void deleteStart(List *list){
    Node *trav = list->head;
    list->head = trav->next;

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

int retrieve(List *list, int index){
    if(index > list->count){
        printf("Invalid index choose another(Must be less than %d): ", list->count);
    }
    Node *trav = list->head;
    int count = 1;
    while(count != index){
        trav = trav->next;
        count++;
    }
    return trav->data;
}

int locate(List *list, int data){
    if(list->head == NULL){
        printf("No data found\n");
        return -1;
    }
    Node *trav = list->head;
    int index = 0;
    while(trav->next != NULL){
        if(data == trav->data){
            return index + 1;
        }
        index++;
        trav = trav->next;
    }
}