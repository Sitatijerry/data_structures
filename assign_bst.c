#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Function prototypes
struct Node* insertBST(struct Node* root, int data);
struct Node* deleteNode(struct Node* root, int key);
int getHeight(struct Node* root);
int getNodeHeight(struct Node* root, int key);
void printLevel(struct Node* root, int level);
void printLevelAndHeight(struct Node* root, int key);

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to insert a node in BST
struct Node* insertBST(struct Node* root, int data) {
    if (root == NULL)
        return newNode(data);
    if (data < root->data)
        root->left = insertBST(root->left, data);
    else if (data > root->data)
        root->right = insertBST(root->right, data);
    return root;
}

// Function to find the minimum value node in a tree
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node in BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to get the height of a tree
int getHeight(struct Node* root) {
    if (root == NULL)
        return -1;
    else {
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        if (leftHeight > rightHeight)
            return leftHeight + 1;
        else
            return rightHeight + 1;
    }
}

// Function to get the height of a node in a tree
int getNodeHeight(struct Node* root, int key) {
    if (root == NULL)
        return -1;
    if (root->data == key)
        return getHeight(root);
    if (key < root->data)
        return getNodeHeight(root->left, key);
    return getNodeHeight(root->right, key);
}

// Function to print nodes at a given level
void printLevel(struct Node* root, int level) {
    if (root == NULL)
        return;
    if (level == 0)
        printf("%d ", root->data);
    else if (level > 0) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

// Function to print level and height of a node
void printLevelAndHeight(struct Node* root, int key) {
    int level = 0;
    while (root != NULL) {
        if (key == root->data) {
            printf("Level of node %d is %d\n", key, level);
            printf("Height of node %d is %d\n", key, getNodeHeight(root, key));
            return;
        } else if (key < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
        level++;
    }
    printf("Node %d not found in the tree.\n", key);
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node* root = NULL;

    // Creating the BST
    for (int i = 0; i < n; i++)
        root = insertBST(root, arr[i]);

    // Deleting a node
    int keyToDelete = 20;
    printf("Deleting node %d\n", keyToDelete);
    root = deleteNode(root, keyToDelete);

    // Printing the height of the BST
    printf("Height of BST: %d\n", getHeight(root));

    // Printing the level and height of any node
    int nodeToCheck = 25;
    printLevelAndHeight(root, nodeToCheck);

    return 0;
}
