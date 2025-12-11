#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    char title[50];
    char artist[50];
    struct node* next;
}Node;

typedef struct {
    Node* front;
    Node* rear;
}Playlist;

Playlist* initialize() {
    Playlist* p = (Playlist*)malloc(sizeof(Playlist));

    p->front = NULL;
    p->rear = NULL;

    return p;
}

Node* createNode() {
    Node* newNode = malloc(sizeof(Node));

    newNode->next = NULL;

    return newNode;
}
bool isSongInPlaylist(Playlist* p, char* newTitle) {
    Node* temp = p->front;

    while (temp!=NULL) {
        if (strcmp(temp->title, newTitle)== 0) {
            return true;
        }
        temp = temp->next;
    }

    return false;
}

void display(Playlist* p) {

    if (p->front == NULL) {
        printf("You currently have 0 Songs in Queue");
    }

    Node* temp = p->front;
    printf("\n------ Queue Songs ------\n %-8s | %-20s \n-------------------------\n", "Title", "Artist");

    while (temp != NULL) {
        printf(" %-8s | %-20s \n", temp->title, temp->artist);
        temp = temp->next;
    }
}
void addSong(Playlist* p, char* title, char* artist) {
    Node* newP = createNode();

    strcpy(newP->artist,artist);
    strcpy(newP->title,title);

    Node* temp = p->front;

    while (temp != NULL) {
        if (strcmp(temp->title, newP->title) == 0 && strcmp(temp->artist, newP->artist) == 0) {
            printf("\nSong already added to playlist. Find another song \n");
            return;
        }
        temp = temp->next;
    }

    if (p->rear == NULL) {
        //empty
        p->front = newP;
        p->rear = newP;
    }else{
        p->rear->next = newP; // next ni rear should point to newP (making it the legit rear and not losing the current rear)
        p->rear = newP; // update rear to newP
    }

}
void playNext(Playlist* p) {

    if (p->front == NULL) {
        printf("\n------ No current songs playing ------\n");
        return;
    }
    p->front = p->front->next;
    Node* temp = p->front;
    printf("\n------ Playing next song ------\n %-10s - %10s\n", temp->artist, temp->title);


}
void showSongsByArtist(Playlist* p, char* artistFragment);


int main() {
    Playlist* p = initialize();

    addSong(p, "Hey", "Taylor");
    addSong(p, "oo", "Swift");
    addSong(p, "Ayoko", "Rico");

    display(p);

    re


    free(p);
    return 0;
}