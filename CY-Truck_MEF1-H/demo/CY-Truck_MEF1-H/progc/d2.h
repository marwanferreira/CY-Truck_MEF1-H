#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LEN 100
#define INITIAL_CAPACITY 1000  // Taille initiale adaptative pour le tableau

typedef struct DriverNode {
    char name[MAX_NAME_LEN];
    double totalDistance;
    struct DriverNode *left, *right;
} DriverNode;
DriverNode* createNode(char *name, double distance);
DriverNode* insertOrUpdate(DriverNode *root, char *name, double distance);
void processCSV(const char *filename, DriverNode **root);
void collectData(DriverNode *root, DriverNode ***array, int *size, int *capacity);
int compareDrivers(const void *a, const void *b);
void freeTree(DriverNode *root);
void printTop10(DriverNode **drivers, int size, FILE *file);