#include "Header.h"


int min(int a,int b){
  if (a<b){
    return a;
  }
  return b;
}
int max(int a,int b){
  if (a>b){
    return a;
  }
  return b;
}


PArbre rotationGauche(PArbre A) {
	PArbre B = A->fd;
	int a = A->equilibre;
	int b = B->equilibre;
	A->fd = B->fg;			// Rotation
	B->fg = A;
	A->equilibre = a - max(b, 0) - 1;
	B->equilibre = min(min(a - 2, a + b -2), b - 1);
	return B;
}

PArbre rotationDroite(PArbre A) {
	PArbre B = A->fg;
	int a = A->equilibre;
	int b = B->equilibre;
	A->fg = B->fd;			// Rotation
	B->fd = A;
	A->equilibre = a - min(b, 0) + 1;
	B->equilibre = max(max(a + 2, a + b + 2), b + 1);
	return B;
}


PArbre doubleRotationGauche(PArbre A) {
	A->fd = rotationDroite(A->fd);
	return rotationGauche(A);
}


PArbre doubleRotationDroite(PArbre A) {
	A->fg = rotationGauche(A->fg);
	return rotationDroite(A);
}

PArbre equilibrerAVL(PArbre A) {
	if (A->equilibre == 2){
		if (A->fd->equilibre >= 0){
			return rotationGauche(A);
    }
		else{
			return doubleRotationGauche(A);
    }
  }
	else{
		if (A->equilibre == -2){
			if (A->fg->equilibre <= 0){
				return rotationDroite(A);
      }
			else {
				return doubleRotationDroite(A);
      }
    }
  }
	return A;
}




// Stations Croissantes
PArbre ajoutAVLS(PArbre A, Element e, int *h) {
	if (A == ARBRENULL) {
		*h = 1;
    A = malloc(sizeof(Arbre));
    A->fg = ARBRENULL;
    A->fd = ARBRENULL;
    A->elmt = e.station;
    A->suivant = NULL;
    A->suivant = insertionChainonSuivant(A->suivant, e); 
		return A;
	}
	if (e.station > A->elmt){
		A->fd = ajoutAVLS(A->fd, e, h);
  }
	else if (e.station < A->elmt) {
		A->fg = ajoutAVLS(A->fg, e, h);
		*h = -*h;
	} 
  else { // e.champ1 == A->elmt.champ1
    A->suivant=insertionChainonSuivant(A->suivant, e);
		*h = 0;
		return A;
	}
	if (*h != 0) { // sinon pas de changement d'équilibre
		A->equilibre = A->equilibre + *h;
		A = equilibrerAVL(A);
		if (A->equilibre == 0)
			*h = 0;
		else
			*h = 1;
	}
	return A;
}



// Données Croissantes
PArbre ajoutAVLC(PArbre A, Element e, int *h) {
	if (A == ARBRENULL) {
		*h = 1;
    A = malloc(sizeof(Arbre));
    A->fg = ARBRENULL;
    A->fd = ARBRENULL;
    A->elmt = e.donnee;
    A->suivant = NULL;
    A->suivant = insertionChainonSuivant(A->suivant, e); 
		return A;
	}
	if (e.donnee > A->elmt){
		A->fd = ajoutAVLC(A->fd, e, h);
  }
	else if (e.donnee < A->elmt) {
		A->fg = ajoutAVLC(A->fg, e, h);
		*h = -*h;
	} 
  else { // e.champ1 == A->elmt.champ1
    A->suivant=insertionChainonSuivant(A->suivant, e);
		*h = 0;
		return A;
	}
	if (*h != 0) { // sinon pas de changement d'équilibre
		A->equilibre = A->equilibre + *h;
		A = equilibrerAVL(A);
		if (A->equilibre == 0)
			*h = 0;
		else
			*h = 1;
	}
	return A;
}



// Chronologique
PArbre ajoutAVLT(PArbre A, Element e, int *h) {
	if (A == ARBRENULL) {
		*h = 1;
    A = malloc(sizeof(Arbre));
    A->fg = ARBRENULL;
    A->fd = ARBRENULL;
    A->elmt = e.date;
    A->suivant = NULL;
    A->suivant = insertionChainonSuivant(A->suivant, e); 
		return A;
	}
	if (e.date > A->elmt){
		A->fd = ajoutAVLT(A->fd, e, h);
  }
	else if (e.date < A->elmt) {
		A->fg = ajoutAVLT(A->fg, e, h);
		*h = -*h;
	} 
  else { // e.champ1 == A->elmt.champ1
    A->suivant=insertionChainonSuivant(A->suivant, e);
		*h = 0;
		return A;
	}
	if (*h != 0) { // sinon pas de changement d'équilibre
		A->equilibre = A->equilibre + *h;
		A = equilibrerAVL(A);
		if (A->equilibre == 0)
			*h = 0;
		else
			*h = 1;
	}
	return A;
}



// Chronologique et Stations Croissantes
PArbre ajoutAVLTS(PArbre A, Element e, int *h) {
	if (A == ARBRENULL) {
		*h = 1;
    A = malloc(sizeof(Arbre));
    A->fg = ARBRENULL;
    A->fd = ARBRENULL;
    A->elmt = e.date;
    A->suivant = NULL;
    A->suivant = insertionChainonTS(A->suivant, e); 
		return A;
	}
	if (e.date > A->elmt){
		A->fd = ajoutAVLTS(A->fd, e, h);
  }
	else if (e.date < A->elmt) {
		A->fg = ajoutAVLTS(A->fg, e, h);
		*h = -*h;
	} 
  else { // e.champ1 == A->elmt.champ1
    A->suivant=insertionChainonTS(A->suivant, e);
		*h = 0;
		return A;
	}
	if (*h != 0) { // sinon pas de changement d'équilibre
		A->equilibre = A->equilibre + *h;
		A = equilibrerAVL(A);
		if (A->equilibre == 0)
			*h = 0;
		else
			*h = 1;
	}
	return A;
}



