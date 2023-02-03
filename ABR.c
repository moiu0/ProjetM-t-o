#include "Header.h"



void traiterArbre(PArbre A, FILE* f){  // GRD
  
  if (A != ARBRENULL){  
  
    
    if (A->fg != ARBRENULL){   
  
      traiterArbre(A->fg,f);
    }
    
    traiterChainon(A->suivant,f);

    
    if (A->fd != ARBRENULL){
      traiterArbre(A->fd,f);
    }
  }
}


// Données Croissantes

PArbre InsererABRC(PArbre A, Element e){
	if (A == NULL){
    A = malloc(sizeof(Arbre));
    A->elmt = e.donnee;
    A->fg = NULL;
    A->fd = NULL;
    A->suivant = NULL;
    A->suivant = insertionChainonSuivant(A->suivant, e);
    return A;
  }
	if (e.donnee < A->elmt){ 
	  A->fg = InsererABRC(A->fg, e);
  }
	else if (e.donnee > A->elmt){
			A->fd = InsererABRC(A->fd, e);
  }
  else {
    A->suivant=insertionChainonSuivant(A->suivant, e);
  }

  
	return A;
}


// Données Décroissantes

PArbre InsererABRD(PArbre A, Element e){
	if (A == NULL){
    A = malloc(sizeof(Arbre));
    A->elmt = e.date;
    A->fg = NULL;
    A->fd = NULL;
    A->suivant = NULL;
    A->suivant = insertionChainonSuivant(A->suivant, e);
    return A;
  }
	if (e.date > A->elmt){ 
	  A->fg = InsererABRD(A->fg, e);
  }
	else if (e.date < A->elmt){
			A->fd = InsererABRD(A->fd, e);
  }
  else {
    A->suivant=insertionChainonSuivant(A->suivant, e);
  }

  
	return A;
}

// Stations Croissantes

PArbre InsererABRS(PArbre A, Element e){
	if (A == NULL){
    A = malloc(sizeof(Arbre));
    A->elmt = e.station;
    A->fg = NULL;
    A->fd = NULL;
    A->suivant = NULL;
    A->suivant = insertionChainonSuivant(A->suivant, e);
    return A;
  }
	if (e.station < A->elmt){ 
	  A->fg = InsererABRS(A->fg, e);
  }
	else if (e.station > A->elmt){
			A->fd = InsererABRS(A->fd, e);
  }
  else {
    A->suivant=insertionChainonSuivant(A->suivant, e);
  }

  
	return A;
}

// Chronologique

PArbre InsererABRT(PArbre A, Element e){
	if (A == NULL){
    A = malloc(sizeof(Arbre));
    A->elmt = e.date;
    A->fg = NULL;
    A->fd = NULL;
    A->suivant = NULL;
    A->suivant = insertionChainonSuivant(A->suivant, e);
    return A;
  }
	if (e.date < A->elmt){ 
	  A->fg = InsererABRT(A->fg, e);
  }
	else if (e.date > A->elmt){
		A->fd = InsererABRT(A->fd, e);
  }
  else {
    A->suivant=insertionChainonSuivant(A->suivant, e);
  }

  
	return A;
}

// Chronologique puis Stations Croissantes

PArbre InsererABRTS(PArbre A, Element e){
	if (A == NULL){
    A = malloc(sizeof(Arbre));
    A->elmt = e.date;
    A->fg = NULL;
    A->fd = NULL;
    A->suivant = NULL;
    A->suivant = insertionChainonTS(A->suivant, e);
    return A;
  }
	if (e.date < A->elmt){ 
	  A->fg = InsererABRT(A->fg, e);
  }
	else if (e.date > A->elmt){
			A->fd = InsererABRT(A->fd, e);
  }
  else {
    A->suivant = insertionChainonTS(A->suivant, e);
  }

  
	return A;
}


