#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_NAME_LEN 100
#define MAX_ROUTE_ID_LEN 50

// Structure pour les Route ID
typedef struct RouteNode {
    char routeID[MAX_ROUTE_ID_LEN];
    struct RouteNode *left, *right;
} RouteNode;

// Structure pour les conducteurs
typedef struct DriverNode {
    char name[MAX_NAME_LEN];
    int uniqueTrips;
    struct RouteNode *routes;
    struct DriverNode *left, *right;
} DriverNode;

DriverNode* insertDriver(DriverNode **root, char *name) {
    if (*root == NULL) {
        *root = (DriverNode *)malloc(sizeof(DriverNode));
        strcpy((*root)->name, name);
        (*root)->uniqueTrips = 0;
        (*root)->routes = NULL;
        (*root)->left = (*root)->right = NULL;
        return *root;
    }
    int cmp = strcmp(name, (*root)->name);
    if (cmp < 0) {
        return insertDriver(&((*root)->left), name);
    } else if (cmp > 0) {
        return insertDriver(&((*root)->right), name);
    }
    return *root;
}

RouteNode* insertRoute(RouteNode **root, char *routeID) {
    if (*root == NULL) {
        *root = (RouteNode *)malloc(sizeof(RouteNode));
        strcpy((*root)->routeID, routeID);
        (*root)->left = (*root)->right = NULL;
        return *root;
    }
    int cmp = strcmp(routeID, (*root)->routeID);
    if (cmp < 0) {
        return insertRoute(&((*root)->left), routeID);
    } else if (cmp > 0) {
        return insertRoute(&((*root)->right), routeID);
    }
    return NULL;
}

int searchRoute(RouteNode *root, char *routeID) {
    if (root == NULL) {
        return 0; // Non trouvé
    }
    int cmp = strcmp(routeID, root->routeID);
    if (cmp == 0) {
        return 1; // Trouvé
    } else if (cmp < 0) {
        return searchRoute(root->left, routeID);
    } else {
        return searchRoute(root->right, routeID);
    }
}

void processCSV(DriverNode **root, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    char line[1024];
    while (fgets(line, 1024, file)) {
        char *routeID = strtok(line, ";");
        char *driverName = strtok(NULL, ";");
        for (int i = 0; i < 4 && driverName != NULL; i++) {
            driverName = strtok(NULL, ";");
        }
        if (driverName != NULL) {
            DriverNode *driver = insertDriver(root, driverName);
            if (!searchRoute(driver->routes, routeID)) {
                insertRoute(&(driver->routes), routeID);
                driver->uniqueTrips++;
            }
        }
    }
    fclose(file);
}

// Structure pour le second ABR
typedef struct SortedNode {
    char name[MAX_NAME_LEN];
    int uniqueTrips;
    struct SortedNode *left, *right;
} SortedNode;

// Insérer dans le second ABR (trié par uniqueTrips et nom)
SortedNode* insertSorted(SortedNode **root, char *name, int uniqueTrips) {
    if (*root == NULL) {
        *root = (SortedNode *)malloc(sizeof(SortedNode));
        strcpy((*root)->name, name);
        (*root)->uniqueTrips = uniqueTrips;
        (*root)->left = (*root)->right = NULL;
    } else if (uniqueTrips > (*root)->uniqueTrips || (uniqueTrips == (*root)->uniqueTrips && strcmp(name, (*root)->name) < 0)) {
        (*root)->left = insertSorted(&(*root)->left, name, uniqueTrips);
    } else {
        (*root)->right = insertSorted(&(*root)->right, name, uniqueTrips);
    }
    return *root;
}

// Parcourir l'ABR principal et insérer chaque conducteur dans le second ABR
void buildSortedTree(DriverNode *root, SortedNode **sortedRoot) {
    if (root != NULL) {
        buildSortedTree(root->left, sortedRoot);
        insertSorted(sortedRoot, root->name, root->uniqueTrips);
        buildSortedTree(root->right, sortedRoot);
    }
}

void cleanString(char *str) {
    char *p = str;
    while (*p) {
        if (*p == '\n' || *p == '\r') {
            *p = '\0';
            break;
        }
        p++;
    }
}

void printTop10(SortedNode *root, int *count, FILE *fp) {
    if (root != NULL && *count < 10) {
        printTop10(root->left, count, fp);
        if (*count < 10) {
            // S'assurer que les guillemets entourent le nom complet du conducteur
            cleanString(root->name);
            fprintf(fp, "\"%s\" %d\n", root->name, root->uniqueTrips);
            (*count)++;
        }
        printTop10(root->right, count, fp);
    }
}



// Libérer la mémoire allouée pour le second ABR
// Libérer la mémoire allouée pour les RouteNode
void freeRouteTree(RouteNode *root) {
    if (root != NULL) {
        freeRouteTree(root->left);
        freeRouteTree(root->right);
        free(root);
    }
}

// Libérer la mémoire allouée pour les DriverNode
void freeDriverTree(DriverNode *root) {
    if (root != NULL) {
        freeDriverTree(root->left);
        freeDriverTree(root->right);
        freeRouteTree(root->routes); // Utilisez freeRouteTree ici
        free(root);
    }
}

// La fonction freeSortedTree reste inchangée
void freeSortedTree(SortedNode *root) {
    if (root != NULL) {
        freeSortedTree(root->left);
        freeSortedTree(root->right);
        free(root);
    }
}


// ... le reste de votre code ...

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    DriverNode *root = NULL;
    processCSV(&root, "data.csv");

    // Construire l'ABR trié
    SortedNode *sortedRoot = NULL;
    buildSortedTree(root, &sortedRoot);
    
    FILE *fp = fopen("output.txt", "w"); // Ouvrir le fichier en mode écriture
    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        return 1;
    }

    int count = 0; // Déclarer count ici
    printTop10(sortedRoot, &count, fp); // Passer le fichier à la fonction

    fclose(fp); // Fermer le fichier

    // Libérer toute la mémoire allouée
    freeDriverTree(root);
    freeSortedTree(sortedRoot);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Temps d'exécution: %f secondes\n", cpu_time_used);

    return 0;
}

