#include "Header.h"


void traiterChainon(PChainon c, FILE* f){
  int bol=0;
  if ((c->elmt.station != 0 && c->elmt.latitude != 0) || (c->elmt.station != 0 && c->elmt.donnee != 0)){
    fprintf(f, "%f;", c->elmt.station);
    bol=1;
  }
  if (c->elmt.date != 0){
    fprintf(f, "%d:%d:%d;", c->elmt.fulldate.annee,c->elmt.fulldate.mois,c->elmt.fulldate.jour);
    bol=1;
  }
  if (c->elmt.donnee != 0){
    fprintf(f, "%f;", c->elmt.donnee);
    bol=1;
  }
  if (c->elmt.latitude != 0){
    fprintf(f, "%f;", c->elmt.latitude);
    bol=1;
  }
  if (c->elmt.longitude != 0){
    fprintf(f, "%f;", c->elmt.longitude);
    bol=1;
  }
  if (bol == 1){
    fprintf(f, "\n");
  }
  traiterChainon(c->suivant,f);
  
}


// Données Croissantes ou Décroissantes
PArbre insertionChainonC(PArbre a, Element elmt){

  if (a == NULL){
    a = malloc(sizeof(Arbre));
    a->suivant = NULL;
    a->fg = NULL;
    a->fd = NULL;
    a->elmt = elmt.donnee;
    a->suivant=insertionChainonSuivant(a->suivant, elmt);
    return a;
  }


  if (a->elmt == elmt.donnee){
     a->suivant=insertionChainonSuivant(a->suivant,elmt);
    return a;
  }

  else if (a->elmt > elmt.donnee){
    PArbre temp = malloc(sizeof(Arbre));
    temp->fd = a;
    temp->elmt = elmt.donnee;
    return temp;
  }

  else if (a->fd == NULL){
    PArbre temp = malloc(sizeof(Arbre));
    a->fd = temp;
    temp->fd = NULL;
    temp->elmt = elmt.donnee;
    return a;
  }

  else if (a->fd->elmt > elmt.donnee){
    
    PArbre temp = malloc(sizeof(Arbre));
    temp->elmt = elmt.donnee;
    temp->fd = a->fd;
    a->fd = temp;
    return a;
  }

  else {
    a->fd = insertionChainonC(a->fd, elmt);
    return a;
  }
  
}


// Stations Croissantes 
PArbre insertionChainonS(PArbre a, Element elmt){

  if (a == NULL){
    a = malloc(sizeof(Arbre));
    a->suivant = NULL;
    a->fg = NULL;
    a->fd = NULL;
    a->elmt = elmt.station;
    a->suivant = insertionChainonSuivant(a->suivant, elmt);
    return a;
  }


  if (a->elmt == elmt.station){
    a->suivant=insertionChainonSuivant(a->suivant,elmt);
    return a;
  }

  else if (a->elmt > elmt.station){
    PArbre temp = malloc(sizeof(Arbre));
    temp->fd = a;
    temp->elmt = elmt.station;
    return temp;
  }

  else if (a->fd == NULL){
    PArbre temp = malloc(sizeof(Arbre));
    a->fd = temp;
    temp->fd = NULL;
    temp->elmt = elmt.station;
    return a;
  }

  else if (a->fd->elmt > elmt.station){
    
    PArbre temp = malloc(sizeof(Arbre));
    temp->elmt = elmt.station;
    temp->fd = a->fd;
    a->fd = temp;
    return a;
  }

  else {
    a->fd = insertionChainonS(a->fd, elmt);
    return a;
  }
  
}


// Chronologique
PArbre insertionChainonT(PArbre a, Element elmt){

  if (a == NULL){
    a = malloc(sizeof(Arbre));
    a->suivant = NULL;
    a->fg = NULL;
    a->fd = NULL;
    a->elmt = elmt.date;
    a->suivant = insertionChainonSuivant(a->suivant, elmt);
    return a;
  }


  if (a->elmt == elmt.date){
    a->suivant=insertionChainonSuivant(a->suivant,elmt);
    return a;
  }

  else if (a->elmt > elmt.date){
  
    PArbre temp = malloc(sizeof(Arbre));
    temp->fd = a;
    temp->elmt = elmt.date;
    return temp;
  }

  else if (a->fd == NULL){
    PArbre temp = malloc(sizeof(Arbre));
    a->fd = temp;
    temp->fd = NULL;
    temp->elmt = elmt.date;
    return a;
  }

  else if (a->fd->elmt > elmt.date){
    
    PArbre temp = malloc(sizeof(Arbre));
    temp->elmt = elmt.date;
    temp->fd = a->fd;
    a->fd = temp;
    return a;
  }

  else {
    a->fd = insertionChainonT(a->fd, elmt);
    return a;
  }
  
}

PChainon insertionChainonTS(PChainon c, Element elmt){

  if (c == NULL){
    c = malloc(sizeof(Chainon));
    c->suivant = NULL;
    c->elmt = elmt;
    return c;
  }


  if (c->elmt.station == elmt.station){
    return c;
  }

  else if (c->elmt.station > elmt.station){
    PChainon temp = malloc(sizeof(Chainon));
    temp->suivant = c;
    temp->elmt = elmt;
    return temp;
  }

  else if (c->suivant == NULL){
    PChainon temp = malloc(sizeof(Chainon));
    c->suivant = temp;
    temp->suivant = NULL;
    temp->elmt = elmt;
    return c;
  }

  else if (c->suivant->elmt.station > elmt.station){
    
    PChainon temp = malloc(sizeof(Chainon));
    temp->elmt = elmt;
    temp->suivant = c->suivant;
    c->suivant = temp;
    return c;
  }

  else {
    c->suivant = insertionChainonTS(c->suivant, elmt);
    return c;
  }
  
}


PChainon insertionChainonSuivant(PChainon c, Element elmt){

  if (c == NULL){
    c = malloc(sizeof(Chainon));
    c->suivant = NULL;
    c->elmt = elmt;
    return c;
  }

    if (elmt.donnee == c->elmt.donnee && elmt.station == c->elmt.station && elmt.date == c->elmt.date && elmt.latitude == c->elmt.latitude && elmt.longitude == c->elmt.longitude){
      c->elmt.poids++;
    }
    else {
      c->suivant = insertionChainonSuivant(c->suivant, elmt);
    }
  return c;
  
  
}