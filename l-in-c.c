#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_TOP_TRAJETS 10

// Structure pour les trajets
typedef struct TrajetNode {
    int trajetID;
    double distanceTotale;
    int height;
    struct TrajetNode *left, *right;
} TrajetNode;

// A utility function to get the height of the tree
int height(TrajetNode *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Helper function to allocate a new node
TrajetNode* newNode(int trajetID, double distance) {
    TrajetNode* node = (TrajetNode*)malloc(sizeof(TrajetNode));
    node->trajetID = trajetID;
    node->distanceTotale = distance;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

// A utility function to right rotate subtree rooted with y
TrajetNode *rightRotate(TrajetNode *y) {
    TrajetNode *x = y->left;
    TrajetNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
TrajetNode *leftRotate(TrajetNode *x) {
    TrajetNode *y = x->right;
    TrajetNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(TrajetNode *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a trajetID and distance in the subtree rooted
// with node and returns the new root of the subtree.
TrajetNode* insert(TrajetNode* node, int trajetID, double distance) {
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(trajetID, distance));

    if (trajetID < node->trajetID)
        node->left = insert(node->left, trajetID, distance);
    else if (trajetID > node->trajetID)
        node->right = insert(node->right, trajetID, distance);
    else { // Equal trajetIDs are not allowed in BST, update distance if same
        node->distanceTotale += distance;
        return node;
    }

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right));

    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && trajetID < node->left->trajetID)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && trajetID > node->right->trajetID)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && trajetID > node->left->trajetID) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && trajetID < node->right->trajetID) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

// Function to insert all nodes of AVL tree into an array
void storeInOrder(TrajetNode *node, TrajetNode **array, int *index) {
    if (node != NULL) {
        storeInOrder(node->left, array, index);
        array[(*index)++] = node;
        storeInOrder(node->right, array, index);
    }
}

// Comparator function for qsort
int compareTrajets(const void* a, const void* b) {
    double distanceA = (*((TrajetNode**)a))->distanceTotale;
    double distanceB = (*((TrajetNode**)b))->distanceTotale;
    return (distanceB > distanceA) - (distanceA > distanceB);
}

// Function to print top 10 longest trajets
void printTopTrajets(TrajetNode *root) {
    int count = 0;
    TrajetNode **array = (TrajetNode **)malloc(sizeof(TrajetNode *) * MAX_TOP_TRAJETS);
    storeInOrder(root, array, &count);

    qsort(array, count, sizeof(TrajetNode *), compareTrajets);

    printf("Top %d longest trajets:\n", MAX_TOP_TRAJETS);
    for (int i = 0; i < count && i < MAX_TOP_TRAJETS; i++) {
        printf("Trajet ID: %d, Distance Totale: %.2f km\n", array[i]->trajetID, array[i]->distanceTotale);
    }

    free(array);
}

// Free all nodes in AVL tree
void freeAVLTree(TrajetNode* root) {
    if (root != NULL) {
        freeAVLTree(root->left);
        freeAVLTree(root->right);
        free(root);
    }
}

int main() {
    TrajetNode *root = NULL;  // the AVL tree

    // Open and read the file
    FILE *file = fopen("data.csv", "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        int trajetID;
        double distance;
        // Assurez-vous que votre format correspond à celui de votre fichier CSV.
        if (sscanf(line, "%d;%lf", &trajetID, &distance) == 2) {
            root = insert(root, trajetID, distance);
        }
    }

    fclose(file);

    // Print the top 10 longest trajets
    printTopTrajets(root);

    // Free the AVL tree
    freeAVLTree(root);

    return 0;
}
