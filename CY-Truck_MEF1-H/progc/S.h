#include<stdio.h>
#include <stdlib.h>

//Structure de l'Arbre 
typedef struct ABR{
  int route_ID;
  int etape_ID;
  float distance;
  float min;
  float max;
  int n;
  struct ABR* fG;
  struct ABR* fD;
}ABR;


//Structure AVL
typedef struct AVL{
    int route_ID;
    float min;
    float max;
    float moy;
    float diff;
    int eq;
    struct AVL* fG;
    struct AVL* fD;
}AVL;
ABR* insertionABR(ABR* abr, int route_ID, int etape_ID, float distance);
ABR* lectureCSV(const char* data, ABR* abr);
void inversion(AVL* avl, FILE* fichier2);
void infixtestABR(ABR* p);
void infixtestAVL(AVL* p);
AVL* creationNoeudAVL(ABR* abr);
int min3(int a, int b, int c);
int max2(int a, int b);
AVL* RotationG(AVL* avl);
int min2(int a, int b);
int max3(int a, int b, int c);
AVL* RotationD(AVL* avl);
AVL* doubleRotationG(AVL* avl);
AVL* doubleRotationD(AVL* avl);
AVL* equilibrageAVL(AVL* avl);
AVL* insertionAVL(AVL* avl, int* h, ABR* abr);
AVL* parcoursAVL(ABR* abr, AVL* avl, int h);
void freeABR(ABR* abr);
void freeAVL(AVL* avl);
