#include "Header.h"



FILE* ouvertureFichier(char* nom, char* mode){
  FILE* file=NULL;
  file = fopen(nom,mode);
  if(file == NULL){
    printf("Erreur lors de l'ouverture du fichier");
    exit(1);
  }
  return file;
}

int dateEnJours(Date d){
  
  int jours = (d.annee - 2010)*365;
  
  if (d.annee >= 2020){
    if (d.mois >= 3){
      jours += 3;
    }
    else {
      jours += 2;
    }
  }
  else if (d.annee >= 2016){
    if (d.mois >= 3){
      jours += 2;
    }
    else {
      jours ++;
    }
  }
  else if (d.annee >= 2012){
    if (d.mois >= 3){
      jours ++;
    }
  }

  if (d.mois >= 2){
    jours+=31;
  }
  if (d.mois >= 3){
    jours += 28;
  }
  if(d.mois >= 4){
    jours += 31; 
  }
  if (d.mois >= 5){
    jours+=30;
  }if (d.mois >= 6){
    jours+=31;
  }if (d.mois >= 7){
    jours+=30;
  }if (d.mois >= 8){
    jours+=31;
  }if (d.mois >= 9){
    jours+=31;
  }if (d.mois >= 10){
    jours+=30;
  }if (d.mois >= 11){
    jours+=31;
  }
  if (d.mois == 12){
    jours+=30;
  }
  jours += d.jour;
  return jours;
}






int main(int argv, char** argc){

  PChainon c = NULL;
  PArbre a = NULL;
  FILE *file = NULL;
  char line[1024];
  Element e={0};
  e.poids = 1;
  int h=0,poubelle,poubelle2;
  ouvertureFichier("tempfinal.txt", "w");

  

  if (argv != 3){
    printf("Erreur, arguments en quantité invalide\n");
    return 1;
  }
  if (*argc[TRI] < '1' || *argc[DONNEE] < '1' || *argc[TRI] > '3' || *argc[DONNEE] > '9'){

    printf("Erreur, arguments invalides");
    return 2;
  }
  
  
  
  


  switch ((int)(*argc[DONNEE])){
   
    case T1:  // Trié selon la station puis la donnée
      
    file = ouvertureFichier("Temperature.txt","r");
      
    while (fgets(line, 1024, file) != NULL) {
      e.station=0;e.donnee=0;

      
      sscanf(line, "%f;%f", &e.station, &e.donnee);
      if (e.donnee != 0){
        if ((int)*argc[TRI] == AVL){
          h=0;
          a = ajoutAVLS(a, e, &h);
        }
        else if ((int)*argc[TRI] == ABR){
          a = InsererABRS(a, e);
        
        }
        else if ((int)*argc[TRI] == TAB){
          a = insertionChainonC(a, e);
        }
      }
        
    }
  
    
      
      
    break;
    case T2: // Trié selon la Date puis la donnée
      file = ouvertureFichier("Temperature2.txt","r");

     while (fgets(line, 1024, file) != NULL) {
        e.date=0;e.donnee=0;

        sscanf(line, "%d-%d-%dT%d:00:00+%d:00;%f", &e.fulldate.annee, &e.fulldate.mois, &e.fulldate.jour, &poubelle, &poubelle2, &e.donnee);
        e.date = dateEnJours(e.fulldate);
        if (e.donnee != 0){
          if ((int)*argc[TRI] == AVL){
            h=0;
            a = ajoutAVLT(a, e, &h);
          }
          else if ((int)*argc[TRI] == ABR){
            a = InsererABRT(a, e);

          }
          else if ((int)*argc[TRI] == TAB){
            a = insertionChainonT(a, e);
          }

        }        
      }



    
    break;
    
    case P1: // Trié selon la Station puis la Donnée
      file = ouvertureFichier("Pression.txt","r");

      
      while (fgets(line, 1024, file) != NULL) {
        e.station=0;e.donnee=0;

        sscanf(line, "%f;%f", &e.station, &e.donnee);
        if (e.donnee != 0){
          if ((int)*argc[TRI] == AVL){
            h=0;
            a = ajoutAVLS(a, e, &h);
          }
          else if ((int)*argc[TRI] == ABR){
            a = InsererABRS(a, e);
        
          }
          else if ((int)*argc[TRI] == TAB){
            a = insertionChainonS(a, e);
          }
       
        }        
      }
    
      
  
      
    break;
    case P2: // Trié selon la Date puis la Donnée


      file = ouvertureFichier("Pression2.txt","r");

      
      while (fgets(line, 1024, file) != NULL) {
        e.date=0;e.donnee=0;

        sscanf(line, "%d-%d-%dT%d:00:00+%d:00;%f", &e.fulldate.annee, &e.fulldate.mois, &e.fulldate.jour, &poubelle, &poubelle2, &e.donnee);
        e.date = dateEnJours(e.fulldate);
        if (e.donnee != 0){
          if ((int)*argc[TRI] == AVL){
            h=0;
            a = ajoutAVLT(a, e, &h);
          }
          else if ((int)*argc[TRI] == ABR){
            a = InsererABRT(a, e);

          }
          else if ((int)*argc[TRI] == TAB){
            a = insertionChainonT(a, e);
          }

        }        
      }



    break;
    case W: // Trié selon la Station
      file = ouvertureFichier("Vent.txt","r");

       while (fgets(line, 1024, file) != NULL) {
        e.latitude=0;e.longitude=0;e.station=0;

        sscanf(line, "%f;%f;%f",&e.station,&e.latitude,&e.longitude);
        
        if (e.station != 0){
          if ((int)*argc[TRI] == AVL){
            h=0;
            a = ajoutAVLS(a, e, &h);
          }
          else if ((int)*argc[TRI] == ABR){
            a = InsererABRS(a, e);

          }
          else if ((int)*argc[TRI] == TAB){
            a = insertionChainonS(a, e);
          }

        }        
      }

    break;
    case M: // Trié selon la Donnée puis la Station
      file = ouvertureFichier("Humidité.txt","r");

      while (fgets(line, 1024, file) != NULL) {
        e.station=0;e.donnee=0;e.latitude=0;e.longitude=0;

        sscanf(line, "%f;%f;%f,%f", &e.station,&e.donnee,&e.latitude,&e.longitude);
        
        if (e.donnee != 0){
          if ((int)*argc[TRI] == AVL){
            h=0;
            a = ajoutAVLC(a, e, &h);
          }
          else if ((int)*argc[TRI] == ABR){
            a = InsererABRC(a, e);

          }
          else if ((int)*argc[TRI] == TAB){
            a = insertionChainonC(a, e);
          }

        }        
      }



    break;
    case H: // Trié selon la Donnée puis la Station
      file = ouvertureFichier("Altitude.txt","r");

       while (fgets(line, 1024, file) != NULL) {
        e.station=0;e.donnee=0;e.latitude=0;e.longitude=0;

        sscanf(line, "%f;%f,%f;%f", &e.station,&e.latitude,&e.longitude,&e.donnee);
        
        if (e.donnee != 0){
          if ((int)*argc[TRI] == AVL){
            h=0;
            a = ajoutAVLC(a, e, &h);
          }
          else if ((int)*argc[TRI] == ABR){
            a = InsererABRC(a, e);

          }
          else if ((int)*argc[TRI] == TAB){
            a = insertionChainonC(a, e);
          }

        }        
      }
    break;
    case T3: // Trié selon la Date puis la Station
      file = ouvertureFichier("Temperature3.txt","r");

        while (fgets(line, 1024, file) != NULL) {
        e.station=0;e.donnee=0;e.date=0;


       sscanf(line, "%f;%d-%d-%dT%d:00:00+%d:00;%f",&e.station, &e.fulldate.annee, &e.fulldate.mois, &e.fulldate.jour, &poubelle, &poubelle2, &e.donnee);
        e.date = dateEnJours(e.fulldate);
        
        if (e.donnee != 0){
          if ((int)*argc[TRI] == AVL){
            h=0;
            a = ajoutAVLTS(a, e, &h);
          }
          else if ((int)*argc[TRI] == ABR){
            a = InsererABRTS(a, e);

          }
          else if ((int)*argc[TRI] == TAB){
            a = insertionChainonT(a, e);
          }

        }        
      }
    break;
    case P3: // Trié selon la Date puis la Station
      file = ouvertureFichier("Pression3.txt","r");



      while (fgets(line, 1024, file) != NULL) {
      e.station=0;e.donnee=0;e.date=0;


      sscanf(line, "%f;%d-%d-%dT%d:00:00+%d:00;%f",&e.station, &e.fulldate.annee, &e.fulldate.mois, &e.fulldate.jour, &poubelle, &poubelle2, &e.donnee);
      e.date = dateEnJours(e.fulldate);
        
      if (e.donnee != 0){
        if ((int)*argc[TRI] == AVL){
          h=0;
          a = ajoutAVLTS(a, e, &h);
        }
        else if ((int)*argc[TRI] == ABR){
          a = InsererABRTS(a, e);
        }
        else if ((int)*argc[TRI] == TAB){
          a = insertionChainonT(a, e);
        }

      }        
    }

      
    break;
  }



  
    file = ouvertureFichier("tempfinal.txt", "a");
    traiterArbre(a,file);
    fclose(file);
  



  
  return 0;
}






