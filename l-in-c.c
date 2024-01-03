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

// Fonctions utilitaires pour l'arbre AVL
int height(TrajetNode *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

TrajetNode* newNode(int trajetID, double distance) {
    TrajetNode* node = (TrajetNode*)malloc(sizeof(TrajetNode));
    node->trajetID = trajetID;
    node->distanceTotale = distance;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

TrajetNode *rightRotate(TrajetNode *y) {
    TrajetNode *x = y->left;
    TrajetNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}

TrajetNode *leftRotate(TrajetNode *x) {
    TrajetNode *y = x->right;
    TrajetNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}

int getBalance(TrajetNode *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Insertion dans l'arbre AVL
TrajetNode* insert(TrajetNode* node, int trajetID, double distance) {
    if (node == NULL)
        return(newNode(trajetID, distance));

    if (trajetID < node->trajetID)
        node->left = insert(node->left, trajetID, distance);
    else if (trajetID > node->trajetID)
        node->right = insert(node->right, trajetID, distance);
    else {
        node->distanceTotale += distance;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && trajetID < node->left->trajetID)
        return rightRotate(node);

    if (balance < -1 && trajetID > node->right->trajetID)
        return leftRotate(node);

    if (balance > 1 && trajetID > node->left->trajetID) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && trajetID < node->right->trajetID) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Fonction pour stocker les trajets dans un tableau
void storeInOrder(TrajetNode *node, TrajetNode **array, int *index) {
    if (node != NULL) {
        storeInOrder(node->left, array, index);
        array[(*index)++] = node;
        storeInOrder(node->right, array, index);
    }
}

// Fonction comparatrice pour qsort
int compareTrajets(const void* a, const void* b) {
    double distanceA = (*((TrajetNode**)a))->distanceTotale;
    double distanceB = (*((TrajetNode**)b))->distanceTotale;
    return (distanceB > distanceA) - (distanceA > distanceB);
}

// Fonction pour imprimer les 10 trajets les plus longs
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

// Fonction pour libérer tous les nœuds de l'arbre AVL
void freeAVLTree(TrajetNode* root) {
    if (root != NULL) {
        freeAVLTree(root->left);
        freeAVLTree(root->right);
        free(root);
    }
}

int main() {
    TrajetNode *root = NULL;

    FILE *file = fopen("data.csv", "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        int trajetID;
        double distance;
        if (sscanf(line, "%d;%lf", &trajetID, &distance) == 2) {
            root = insert(root, trajetID, distance);
        }
    }

    fclose(file);

    printTopTrajets(root);

    freeAVLTree(root);

    return 0;
}


    fclose(file);

    // Print the top 10 longest trajets
    printTopTrajets(root);

    // Free the AVL tree
    freeAVLTree(root);

    return 0;
}
