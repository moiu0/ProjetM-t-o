#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum{
TRI=1,DONNEE
}Parametre;

typedef enum{
ABR='1',TAB,AVL
}Tri;


typedef enum{
T1='1',T2,T3,P1,P2,P3,W,M,H
}Donnee;

typedef struct{
  int jour;
  int mois;
  int annee;
}Date;


typedef struct{
  int poids;
  Date fulldate;
  float station;
  float date;
  float donnee;
  float latitude;
  float longitude;
}Element;


#define ARBRENULL NULL




// Structure Chainon

#define PChainon Chainon*
typedef struct Chainon{
  Element elmt;
  struct PChainon suivant;
}Chainon;


// Structure Arbre

#define PArbre Arbre*
typedef struct Arbre{
  float elmt;
  PChainon suivant;
  int equilibre;
  struct PArbre fg;
  struct PArbre fd;
}Arbre;


// Fonctions AVL

int min(int , int);
int max(int , int);
PArbre rotationGauche(PArbre );
PArbre rotationDroite(PArbre );
PArbre doubleRotationGauche(PArbre );
PArbre doubleRotationDroite(PArbre );
PArbre equilibrerAVL(PArbre );
PArbre ajoutAVL(PArbre , Element , int *);
PArbre ajoutAVLT(PArbre , Element , int *);
PArbre ajoutAVLS(PArbre , Element , int *);
PArbre ajoutAVLTS(PArbre , Element , int *);
PArbre ajoutAVLC(PArbre , Element , int *);

// Fonctions ABR


PArbre InsererABR(PArbre , Element );
PArbre InsererABRT(PArbre , Element );
PArbre InsererABRC(PArbre , Element );
PArbre InsererABRS(PArbre , Element );
PArbre InsererABRTS(PArbre , Element );
void traiterArbre(PArbre , FILE* );

// Fonctions Tableau Dynamique

void afficherElement(Element );
void traiterChainon(PChainon , FILE* );
PArbre insertionChainon(PArbre , Element );
PArbre insertionChainonC(PArbre , Element );
PArbre insertionChainonS(PArbre , Element );
PArbre insertionChainonT(PArbre , Element );
PChainon insertionChainonSuivant(PChainon , Element );
PChainon insertionChainonTS(PChainon , Element );