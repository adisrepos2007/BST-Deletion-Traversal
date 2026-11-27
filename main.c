
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

// Create a new node
struct Node* createNode(int data) {
    struct Node* newNode =
        (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Build a binary tree using level-order array
// -1 represents NULL
struct Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1)
        return NULL;

    struct Node* root = createNode(arr[0]);

    struct Node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;
    int i = 1;

    while (front < rear && i < n) {
        struct Node* current = queue[front++];

        if (i < n && arr[i] != -1) {
            current->left = createNode(arr[i]);
            queue[rear++] = current->left;
        }
        i++;

        if (i < n && arr[i] != -1) {
            current->right = createNode(arr[i]);
            queue[rear++] = current->right;
        }
        i++;
    }

    return root;
}

// Calculate height of the tree
int getHeight(struct Node* root) {
    if (root == NULL)
        return 0;

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return 1 + (leftHeight > rightHeight
                ? leftHeight : rightHeight);
}

// Level-order traversal
void levelOrder(struct Node* root) {
    if (root == NULL)
        return;

    struct Node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        struct Node* current = queue[front++];

        printf("%d ", current->data);

        if (current->left != NULL)
            queue[rear++] = current->left;

        if (current->right != NULL)
            queue[rear++] = current->right;
    }
}

// Find minimum node in a BST
struct Node* findMin(struct Node* root) {
    while (root->left != NULL)
        root = root->left;

    return root;
}

// Delete a node from BST
struct Node* delNode(struct Node* root, int key) {
    if (root == NULL)
        return NULL;

    if (key < root->data) {
        root->left = delNode(root->left, key);
    }
    else if (key > root->data) {
        root->right = delNode(root->right, key);
    }
    else {
        // Case 1: No child
        if (root->left == NULL &&
            root->right == NULL) {
            free(root);
            return NULL;
        }

        // Case 2: One child
        else if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Two children
        struct Node* temp = findMin(root->right);

        root->data = temp->data;
        root->right = delNode(root->right, temp->data);
    }

    return root;
}

int main() {
    int arr[] = {8, 3, 10, 1, 6, -1, 14, -1, -1, 4, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    struct Node* root = buildTree(arr, n);

    printf("Original Tree (Level Order): ");
    levelOrder(root);

    printf("\nHeight of Tree: %d", getHeight(root));

    int key = 3;
    root = delNode(root, key);

    printf("\nAfter Deleting %d: ", key);
    levelOrder(root);

    printf("\n");

    return 0;
}
