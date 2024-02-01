#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 350000 

typedef struct info {
    char *ville;
    int occ;
    int occd;
} inf2;

typedef struct node {
    struct info city;
    int height;
    struct node *fd;
    struct node *fg;
    int *TID;  // Dynamically allocated array
    int maxTIDSize;
    int idxTID;
    char dataTab[MAXSIZE][60];
    int occdTab[MAXSIZE];
    int idx;
} node;

#define IGN1 1

int counter;

//création d'une structure pour chaque ville, occ : occurence de chaque ville, occd : occurence où la ville est une ville de départ.
inf2 *newinf2o(char *ville, int occd) { 
    inf2 *new = malloc(sizeof(inf2));
    if(new != NULL) {
        new->ville = malloc(60*sizeof(char));
        strcpy(new->ville, ville);
        new->occd = occd;
        new->occ = 0;
        return new;
    }
    else {
        printf("newinf2o is NULL for %s\n", ville);
        return NULL;
    }
}

//création d'un noeud d'avl, dataTab permet de stocker les noms des villes qui ont la meme occurence que d'autre ville, ce qui permet de régler la question des doublons dans un avl
node *newNode(inf2 *city) {
    node *new = malloc(sizeof(node));
    if(new == NULL) {
        printf("newNode is NULL for %s\n", city->ville);
        return NULL;
    }

    new->city = *city;
    new->height = -1;
    new->fd = NULL;
    new->fg = NULL;
    new->TID = malloc(1000 * sizeof(int));  // Initial size, peut être augmenté si nécessaire
    new->maxTIDSize = 1000;
    new->idxTID = 0;
    new->idx = 0;
    return new;
}

int stringComp(char *s1, char*s2) {

        return strcmp(s1, s2);
}

int max(int a, int b) {
if (a > b) {
return a;
}
else {
return b;
} 
}

int getH(node *avl) {
if(avl == NULL) {
return 0;
}
return avl->height;
}

int getB(node *avl) {
if(avl == NULL) {
return 0;
}
return getH(avl->fg) - getH(avl->fd);
}

node *RRotate(node *y) {
    node *x = y->fg;
    node *T2 = x->fd;

    // Perform rotation
    x->fd = y;
    y->fg = T2;

    // Update heights
    y->height = 1 + max(getH(y->fg), getH(y->fd));
    x->height = 1 + max(getH(x->fg), getH(x->fd));

    return x;  // New root
}

node *LRotate(node *x) {
    node *y = x->fd;
    node *T2 = y->fg;

    // Perform rotation
    y->fg = x;
    x->fd = T2;

    // Update heights
    x->height = 1 + max(getH(x->fg), getH(x->fd));
    y->height = 1 + max(getH(y->fg), getH(y->fd));

    return y;  // New root
}

//fonction de comparaison pour les trajets, TID : trajet ID
int compID(int *tab, int TID, int size) {
    for (int i = 0; i < size; i++) {
        if (tab[i] == TID) {
            return 0; // Doublon trouvé
        }
    }
    return 1; // Pas de doublon
}



// Redimensionnement dynamique du tableau TID si nécessaire
int *resizeTIDArray(int *array, int *capacity) {
    int newCapacity = (*capacity) * 2;
    int *newArray = realloc(array, newCapacity * sizeof(int));
    if (newArray == NULL) {
        perror("Erreur lors du redimensionnement du tableau TID");
        exit(EXIT_FAILURE);
    }
    *capacity = newCapacity;
    return newArray;
}

// Fonction d'insertion dans l'AVL
node *insert(node *avl, inf2 *city, int TID) {
    if (avl == NULL) {
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL) {
            perror("Erreur lors de l'allocation de newNode");
            exit(EXIT_FAILURE);
        }
        newNode->city = *city;
        newNode->height = 1;
        newNode->fd = NULL;
        newNode->fg = NULL;
        newNode->TID = malloc(1000 * sizeof(int));  // Taille initiale
        newNode->maxTIDSize = 1000;
        newNode->idxTID = 0;
        newNode->TID[newNode->idxTID++] = TID;
        newNode->city.occ = 1;
        return newNode;
    }

    int key = stringComp(city->ville, avl->city.ville);

    if (key > 0) {
        avl->fd = insert(avl->fd, city, TID);
    } else if (key < 0) {
        avl->fg = insert(avl->fg, city, TID);
    } else if (key == 0) {
        if (compID(avl->TID, TID, avl->idxTID) == 0) {
            // Doublon trouvé, ne pas insérer
            free(city->ville);
            free(city);
        } else {
            // Ajout de TID au tableau, avec redimensionnement si nécessaire
            if (avl->idxTID >= avl->maxTIDSize) {
                avl->TID = resizeTIDArray(avl->TID, &avl->maxTIDSize);
            }
            avl->TID[avl->idxTID++] = TID;
            avl->city.occ++;
            avl->city.occd += city->occd;
            free(city->ville);
            free(city);
        }
    }

    // Mettre à jour la hauteur de l'AVL et équilibrer
    avl->height = 1 + max(getH(avl->fg), getH(avl->fd));
    int balance = getB(avl);
    // Appliquer des rotations si nécessaire
    // ...

    return avl;
}


//fonction de lecture du fichier CSV et lance l'insértion dans le premier avl
node *proCsv(const char *csv, node *avl) { 
    FILE *file = fopen(csv, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    char buff[256];
    char townA[100], townB[100];
    int tid, step;

    fgets(buff, sizeof(buff), file); // Ignorer la première ligne (en-têtes)

    while (fgets(buff, sizeof(buff), file) != NULL) {
        if (sscanf(buff, "%d;%d;%[^;];%[^;];%*s", &tid, &step, townA, townB) == 4) {
            inf2 *cityA = newinf2o(townA, (step == 1) ? 1 : 0);
            avl = insert(avl, cityA, tid);
            inf2 *cityB = newinf2o(townB, 0);
            avl = insert(avl, cityB, tid);
        } else {
            fprintf(stderr, "Ligne mal formatée : %s\n", buff);
        }
    }

    fclose(file);
    return avl;
}






//fonction d'insertion dans le second avl en fonction du nombre d'occurence de chaque ville, si doublon (meme nb de passage par ville) on ajoute dans le tableau dataTAB
node *insert2(node *avl, inf2 *city) {
    if(avl == NULL) { 
        return newNode(city);
    }

    int key = city->occ;

    if(key > avl->city.occ) {
avl->fd = insert2(avl->fd, city);
    }
    else if(key < avl->city.occ) {
        avl->fg = insert2(avl->fg, city);

    }
    else if(key == avl->city.occ) {        
strcpy(avl->dataTab[avl->idx], city->ville);
        avl->occdTab[avl->idx] = city->occd;
        avl->idx++;
    }
    
           int balance = getB(avl);
//ici rotations
if (balance > 1 && key < avl->fg->city.occ) {
return RRotate(avl);
}

if (balance < -1 && key > avl->fd->city.occ){
return LRotate(avl);
}

if (balance > 1 && key > avl->fg->city.occ) {
avl->fg = LRotate(avl->fg);
return RRotate(avl);
}

if (balance < -1 && key < avl->fd->city.occ) {
avl->fd = RRotate(avl->fd);
return LRotate(avl);
}
if (balance > 1 && key > avl->fg->city.occ) {
avl->fg = LRotate(avl->fg);
return RRotate(avl);
}

if (balance < -1 && key < avl->fd->city.occ) {
avl->fd = RRotate(avl->fd);
return LRotate(avl);
}

return avl;
}


//fonction qui parcours le premier avl puis provoque l'insertion dans le second
void parseAvl(node *avl1, node **avl2) {
    if (avl1 == NULL) {
        return;
    }

    parseAvl(avl1->fg, avl2);
    if ((avl1->city.occ > 1 && IGN1) || IGN1 == 0) {
        // Créez une nouvelle instance de inf2 pour l'insertion dans avl2
        inf2 *newCity = newinf2o(avl1->city.ville, avl1->city.occd);
        newCity->occ = avl1->city.occ;  // Copiez les données de occ
        *avl2 = insert2(*avl2, newCity);
    }
    parseAvl(avl1->fd, avl2);
}


//fonction qui lit le second avl et qui tient compte du nombre de ville à output, lit le contenu de dataTAB pour chaque noeud de l'avl
void parcours(node *avl, int *a1, int *a2, char a3[][60], int *counter) {
    if (avl == NULL || *counter >= 10) {
        return;
    }

    parcours(avl->fd, a1, a2, a3, counter);
    if (*counter < 10) {
        strcpy(a3[*counter], avl->city.ville);
        a1[*counter] = avl->city.occ;
        a2[*counter] = avl->city.occd;
        (*counter)++;
    }
    parcours(avl->fg, a1, a2, a3, counter);
}


//fonction d'échange des tableau pour le 
void swapTAB(char a3[][60], int a1[], int a2[], int j, int j2) {

    char temp[60];
    strcpy(temp, a3[j]);
    strcpy(a3[j], a3[j2]);
    strcpy(a3[j2], temp);

    int temp1 = a1[j];
    a1[j] = a1[j2];
    a1[j2] = temp1;

    int temp2 = a2[j];
    a2[j] = a2[j2];
    a2[j2] = temp2;

}

//fonction de tri par ordre alphabétique
void sort(int n, int a1[], int a2[], char a3[][60]) {

    for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
    if (strcmp(a3[j], a3[j + 1]) > 0) {
    swapTAB(a3, a1, a2, j, j + 1);
  }
}
}

}



void freeAVL(node *avl) {
    if (avl == NULL) {
        return;
    }

    freeAVL(avl->fg);
    freeAVL(avl->fd);
    free(avl->TID);
    free(avl);
}

void printToFile(const char* filename, int n, int *occ, int *occd, char cities[][60]);

int main() {   
    char csvFilePath[] = "data.csv";  // Chemin vers le fichier CSV
    node *avl1 = NULL;  // Premier arbre AVL
    node *avl2 = NULL;  // Deuxième arbre AVL pour le tri

    // Traitement du fichier CSV et construction du premier AVL
    avl1 = proCsv(csvFilePath, avl1);
    if (avl1 == NULL) {
        fprintf(stderr, "Erreur lors de la construction de l'AVL à partir du CSV.\n");
        return 1;
    }

    // Parcours du premier AVL et construction du deuxième AVL
    parseAvl(avl1, &avl2);

    // Parcours du deuxième AVL et collecte des données
    int occdTAB[10], occTAB[10];
    char villeTAB[10][60];
    counter = 0;
    parcours(avl2, occTAB, occdTAB, villeTAB, &counter);

    // Tri des villes par ordre alphabétique
    sort(10, occTAB, occdTAB, villeTAB);

    // Écriture des résultats dans un fichier pour Gnuplot
    printToFile("output_t.txt", counter, occTAB, occdTAB, villeTAB);

    // Libération de la mémoire
    freeAVL(avl1);
    freeAVL(avl2);

    // Pas besoin de fermer stdout ici
    return 0;
}

void printToFile(const char* filename, int n, int *occ, int *occd, char cities[][60]) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Unable to open file for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; ++i) {
        fprintf(file, "%s;%d;%d\n", cities[i], occ[i], occd[i]);
    }

    fclose(file);
}
