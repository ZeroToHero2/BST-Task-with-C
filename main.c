#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Author: Bahadir Unal*/
/*CMPE326 HMW2 BST Implementation*/
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

int findParentNode(struct Node *parent, int data) { 
    if (parent == NULL)
        return NULL;

    if (parent->left == NULL && parent->right == NULL)
        return NULL;

    if ((parent->left != NULL && parent->left->data == data)
        || (parent->right != NULL && parent->right->data == data))
        return parent->data;

    if (parent->data > data)
        return findParentNode(parent->left, data);

    if (parent->data < data)
        return findParentNode(parent->right, data);
}

struct Node *insertNode(struct Node *root, int x) {
    if (root == NULL) {
        root = malloc(sizeof(struct Node));
        root->data = x;
        root->left = NULL;
        root->right = NULL;
    } else if (root->data < x)
        root->right = insertNode(root->right, x);
    else if (root->data > x)
        root->left = insertNode(root->left, x);
    else root->left = insertNode(root->left, x);
    return root; 
}

struct Node *findMin(struct Node *root) {
    if (root == NULL)
        return NULL;
    else if (root->left == NULL)
        return root;
    else
        return findMin(root->left);
}

struct Node *deleteNode(struct Node *root, int x) {
    // Hibbard Deletion Algorithm
    struct Node *temp;
    if (root == NULL)
        return NULL;
    else if (x < root->data)
        root->left = deleteNode(root->left, x);
    else if (x > root->data)
        root->right = deleteNode(root->right, x);
    else if (root->left && root->right) {
        temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, root->data);
    } else {
        temp = root;
        if (root->left == NULL)
            root = root->right;
        else if (root->right == NULL)
            root = root->left;
        free(temp);
    }
    return root;
}

void listBSTinOrder(struct Node *root) {
    if (root == NULL)
        return;
    listBSTinOrder(root->left);
    printf("%d ", root->data);
    listBSTinOrder(root->right);
}
 
int main() {
    struct Node *root;
    struct Node *temp;
    int tempVal = 0;
    root = NULL;
    while (1) {
        char line[1024];
        gets(line);
        if (strcmp(line, "EXIT") == 0) {
            break;
        }
        char *firsttoken = strtok(line, " ");
        if (strcmp(firsttoken, "CONSTRUCT") == 0) {
            firsttoken = strtok(NULL, " ");
            char *secondtoken = strtok(firsttoken, "[");
            char *thirdtoken = strtok(secondtoken, "]");
            char *lasttoken = strtok(thirdtoken, ",");
            while (lasttoken != NULL) {
                int insertedNodeValue;
                insertedNodeValue = atoi(lasttoken);
                root = insertNode(root, insertedNodeValue);
                lasttoken = strtok(NULL, ",");
            }
        } else if (strcmp(firsttoken, "INSERT") == 0) {
            firsttoken = strtok(NULL, " ");
            int insertedNodeValue;
            int result;
            insertedNodeValue = atoi(firsttoken);
            root = insertNode(root, insertedNodeValue);
            result = findParentNode(root, insertedNodeValue);
            printf("The parent of %d is %d\n", insertedNodeValue, result);
        } else if (strcmp(firsttoken, "LIST") == 0) {
            listBSTinOrder(root);
            printf("\n");
        } else if (strcmp(firsttoken, "PARENT") == 0) {
            firsttoken = strtok(NULL, " ");
            int searchForParent;
            int result;
            searchForParent = atoi(firsttoken);
            if (searchForParent == root->data) {
                printf("It is a root node\n");
            } else {
                result = findParentNode(root, searchForParent);
                printf("The parent of %d is %d\n", searchForParent, result);
            }
        } else if (strcmp(firsttoken, "DELETE") == 0) {
            firsttoken = strtok(NULL, " ");
            int deletedNodeValue;
            deletedNodeValue = atoi(firsttoken);
            int oldRootValue = root->data;
            root = deleteNode(root, deletedNodeValue);
            if (root->data != oldRootValue) {
                printf("Root changed. The new root is %d\n", root->data);
            }
        }
    }
    return 0;
}