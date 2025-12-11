#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

int minDepth(Node* root) {
    if (root == NULL) return 0;

    if (root->left == NULL && root->right == NULL) return 1;

    if (root->left == NULL) return minDepth(root->right) + 1;

    if (root->right == NULL) return minDepth(root->left) + 1;

    int leftD = minDepth(root->left);
    int rightD = minDepth(root->right);

    if (leftD < rightD) {
        return leftD + 1;
    }else{
        return rightD + 1;
    }
}

int main() {
    Node* root = NULL;

    root = insert(root, 10);
    insert(root, 5);
    insert(root, 20);
    insert(root, 3);
    insert(root, 7);

    printf("Shortest path (Min Depth): %d\n", minDepth(root));

    return 0;
}