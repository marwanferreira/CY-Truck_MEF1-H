#include <stdio.h>
#include <stdlib.h>

typedef struct TrajetNode {
    int routeID;
    double distanceTotale;
    struct TrajetNode *left, *right;
} TrajetNode;

TrajetNode *createNode(int routeID, double distance) {
    TrajetNode *newNode = (TrajetNode*) malloc(sizeof(TrajetNode));
    newNode->routeID = routeID;
    newNode->distanceTotale = distance;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TrajetNode *insertNode(TrajetNode *node, int routeID, double distance) {
    if (node == NULL) 
        return createNode(routeID, distance);

    if (routeID < node->routeID)
        node->left = insertNode(node->left, routeID, distance);
    else if (routeID > node->routeID)
        node->right = insertNode(node->right, routeID, distance);
    else 
        node->distanceTotale += distance;

    return node;
}

void findTopTrajets(TrajetNode *node, TrajetNode **topTrajets, int *size, double minDistance) {
    if (node == NULL || *size >= 10)
        return;

    findTopTrajets(node->left, topTrajets, size, minDistance);

    if (node->distanceTotale > minDistance) {
        if (*size < 10) {
            topTrajets[*size] = node;
            (*size)++;
        } else if (node->distanceTotale > topTrajets[0]->distanceTotale) {
            topTrajets[0] = node;
        }
    }

    findTopTrajets(node->right, topTrajets, size, minDistance);
}

int compareByRouteID(const void *a, const void *b) {
    TrajetNode *nodeA = *(TrajetNode**)a;
    TrajetNode *nodeB = *(TrajetNode**)b;
    return nodeB->routeID - nodeA->routeID; // Tri décroissant
}

void freeTree(TrajetNode* node) {
    if (node != NULL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

int main() {
    FILE *file = fopen("data.csv", "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[10000000];
    int routeID;
    double distance;
    TrajetNode *root = NULL;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d;%*[^;];%*[^;];%*[^;];%lf", &routeID, &distance) == 2) {
            root = insertNode(root, routeID, distance);
        }
    }

    fclose(file);

    TrajetNode *topTrajets[10] = {0};
    int size = 0;
    findTopTrajets(root, topTrajets, &size, 0.0);

    qsort(topTrajets, size, sizeof(TrajetNode*), compareByRouteID);

    printf("Top 10 trajets with longest distances:\n");
    for (int i = 0; i < size; i++) {
        printf("Route ID: %d, Total Distance: %.2f\n", topTrajets[i]->routeID, topTrajets[i]->distanceTotale);
    }

    freeTree(root);
    return 0;
}
