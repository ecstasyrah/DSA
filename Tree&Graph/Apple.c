#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct apple {
   char name[20];
   char color[10];
   int hardness;
   int size_cm;
   bool ripe;
} Apple;

typedef struct node {
   Apple *app;
   struct node *LC;
   struct node *RC;
} Node, *BST;

typedef struct box {
   Apple apples[50];
   int count;
   int capacity;
} Box;

BST createNode(Apple *a) {
   BST newNode = (BST)malloc(sizeof(Node));
   newNode->LC = NULL;
   newNode->RC = NULL;

   newNode->app = (Apple*)malloc(sizeof(Apple));
   *newNode->app = *a; 

   return newNode;
}

BST insertBST(BST root, Apple *a) {
   if (root == NULL) {
      return createNode(a);
   }

   if (strcmp(a->name, root->app->name) < 0) {
      root->LC = insertBST(root->LC, a);
   } else if (strcmp(a->name, root->app->name) > 0) {
      root->RC = insertBST(root->RC, a);
   }
   return root;
}

BST makeAppleTree(Apple apples[], int n) {
   BST root = NULL;
   for (int i = 0; i < n; i++) {
       root = insertBST(root, &apples[i]);
   }
   return root;
}

void inorderTraversal(BST root) {
    if (root != NULL) {
        inorderTraversal(root->LC);
        printf("%s ", root->app->name);
        inorderTraversal(root->RC);
    }
}

void preorderTraversal(BST root) {
    if (root != NULL) {
        printf("%s ", root->app->name);
        preorderTraversal(root->LC);
        preorderTraversal(root->RC);
    }
}

void initBox(Box *box, int capacity) {
    box->count = 0;
    box->capacity = capacity;
}

BST harvestRecursive(BST root, Box *box) {
    if (root == NULL) return NULL;

    harvestRecursive(root->LC, box);

    if (root->app->ripe && box->count < box->capacity) {
        box->apples[box->count] = *(root->app);
        box->count++;
        printf("Collected Ripe: %s\n", root->app->name);
    }

    harvestRecursive(root->RC, box);
    return root;
}

BST harvestRotten(BST root, Box *box) {
    if (root == NULL) return NULL;

    harvestRotten(root->LC, box);

    if (!root->app->ripe) {
        printf("Found Rotten: %s\n", root->app->name);
    }

    harvestRotten(root->RC, box);
    return root;
}

int main() {
   Box box;
   initBox(&box, 10);

   Apple apples[10] = {
       {"Fuji", "red", 7, 8, true},
       {"Gala", "green", 6, 7, true},
       {"Honeycrisp", "red", 5, 6, false},
       {"Golden", "yellow", 8, 9, true},
       {"RedDel", "red", 6, 7, true},
       {"Granny", "green", 7, 8, true},
       {"Jonathan", "red", 8, 9, true},
       {"McIntosh", "red", 4, 7, true},
       {"PinkLady", "pink", 6, 7, true},
       {"Empire", "red", 7, 8, false}
   };

   BST tree = makeAppleTree(apples, 10);

   printf("In-order traversal of BST:\n");
   inorderTraversal(tree);

   printf("\n\nPre-order traversal of BST:\n");
   preorderTraversal(tree);

   printf("\n\nHarvested Ripe Apples:\n");
   harvestRecursive(tree, &box);

   printf("\n\nRotten Apples:\n");
   harvestRotten(tree, &box);

   return 0;
}