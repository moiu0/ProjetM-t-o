# Traite les options passées au script TYPES DE DONNEES et REGIONS
F=0
G=0
S=0
A=0
O=0
Q=0
echo -n "" > Région.txt #supprime le contenu de tri.txt
compteur=0 #comptre le nb de régions rentrées
compteur2=0 #compte le nb de paramètres entrés
compteur3=0
while getopts "t: p: d: w m h F G S A O Q T: H f:" option; do #librairie des arguments possibles
  case $option in
    t)#température
      if [ "$OPTARG" == 1 ]; then
        echo "température 1 sélectionnée"
        compteur2=$((compteur2 + 1))
        t1=1
      elif [ "$OPTARG" == 2 ]; then
        echo "température 2 sélectionnée"
        compteur2=$((compteur2 + 1))
        t2=1
      elif [ "$OPTARG" == 3 ]; then
        echo "température 3 sélectionnée"
        compteur2=$((compteur2 + 1))
        t3=1
      else  
        echo "erreur"
      fi
      ;;
    p)#pression
      if [ "$OPTARG" == 1 ]; then
        echo "pression 1 sélectionnée"
        compteur2=$((compteur2 + 1))
        p1=1
      elif [ "$OPTARG" == 2 ]; then
        echo "pression 2 sélectionnée"
        compteur2=$((compteur2 + 1))
        p2=1
      elif [ "$OPTARG" == 3 ]; then
        echo "pression 3 sélectionnée"
        compteur2=$((compteur2 + 1))
        p3=1
      else  
        echo "erreur"
      fi
      ;;
    d)#datemin
      compteur3=$((compteur3 + 1))
      if [ "$compteur3" == 1 ]; then
        min=$OPTARG
      elif [ "$compteur3" == 2 ]; then
        max=$OPTARG
      fi
      ;;
    
    w)#vent
      echo "vent sélectionné"
      compteur2=$((compteur2 + 1))
      w=1
      ;;
    m)#humidité
      echo "humidité sélectionnée"
      compteur2=$((compteur2 + 1))
      m=1
      ;;
    h)#altitude
      echo "altitude sélectionnée"
      compteur2=$((compteur2 + 1))
      h=1
      ;;
    F)#France métropolitaine
      echo "France métropolitaine sélectionnée"
      F=1
      compteur=$((compteur + 1)) #ajoute une valeur au compteur qui ne doit pas dépasser 1 sinon arrête le programme 
      ;;
    G)#Guyane française
      echo "Guyane française sélectionnée"
      G=1
      compteur=$((compteur + 1))
      ;;
    S)#Saint-Pierre et Miquelon
      echo "Saint-Pierre et Miquelon sélectionné"
      S=1
      compteur=$((compteur + 1))
      ;;
    A)#Antilles
      echo "Antilles sélectionné"
      A=1
      compteur=$((compteur + 1))
      ;;
    O)#Océan indien
      echo "Océan indien sélectionné"
      O=1
      compteur=$((compteur + 1))
      ;;
    Q)#Antartique
      echo "Antartique sélectionné"
      Q=1
      compteur=$((compteur + 1))
      ;;
    T)#tris
      tri=$OPTARG
      ;;
    f)#fichier
      echo "fichier enregistré"
      fichier=$OPTARG
      ;;
    H)
      echo "Utilisation: main.sh [-t arg (température)] [-p arg (pression)] (faire d'abbord le min puis le max [-d date min] [-d date max]) [-w vent] [-m humidité] [-h altitude] [-F France] [-G Guyane française] [-S Saint-Pierre et Miquelon sélectionné] [-A Antilles] [-O Océan indien] [-Q Antarctique] [-T tris] [-f arg (fichier)]"
      exit 0
      ;;
    :)
      echo "L'option $OPTARG requiert un argument"
      exit 1
      ;;
    ?)
      echo "erreur: -$OPTARG"
      exit 1
      ;;
  esac
done
################################### testeur d'arguments

if  (("$compteur" > 1 )); then  
  echo 'vous avez sélectionné plus de une région'
  exit
elif (( "$compteur2" == 0 )); then  
  echo "vous n'avez  pas sélectionné un paramètre"
  exit
elif (("$compteur3" == 1)); then
  echo "vous n'avez rentrer qu'un date"
  exit
fi

################################### sélection par date

a=1
var=0

if (("$compteur3" == 2)); then
  echo -n "" > d.txt
  echo -n "" > Temps.txt #efface le fichier
  echo $min >> d.txt
  echo $max >> d.txt #rentre min et max dans un fichier
  sed 's/-//g' d.txt > d2.txt #supprime le caratère '-' du fichier
  min=$(awk "NR==1" d2.txt)
  max=$(awk "NR==2" d2.txt) #redonne leur valeur a min et max
  if [ "$min" -gt "$max" ]; then
    echo "dates rentrées incorectes"
    exit
  fi
  if [ "$min" -lt 20100101 ]; then
    echo "date min rentrée incorecte"
    exit
  fi
  if [ "$max" -gt 20210318 ]; then
    echo "date max rentrée incorecte"
    exit
  fi
  cut -d ";" -f 2 $fichier > temp3.txt #récupère la 2ere collone du fichier
  cut -d "T" -f 1 temp3.txt > temp4.txt #récupère la 1ere collone du fichier
  sed 's/-//g' temp4.txt > temp3.txt
  for i in $(awk '{print}' temp3.txt); do #pour i parcourant temp3
    ((var++))
    if [ "$i" -ge "$min " ] ; then
      if (( "$i" <= "$max" )) ; then
        temp=$(awk "NR==$var" $fichier) #récupère la ligne à copier
        echo $temp >> Temps.txt
      fi
    fi
  done
fi

################################### Récupération des données prises en france métropolitaines
var=0

if (("$F" == "$a"));  then #si france métrop sélectionée
  if (( "$compteur3" == 2 )); then #si date entrée
    cut -d ";" -f 1 Temps.txt > temp5.txt #récupère la 1ere collone du fichier
    for i in $(awk '{print}' temp5.txt); do #pour i parcourant temp2
      ((var++))
      if  [ "$i" -lt 8000 ]; then #si les données sont en france métrop
        temp=$(awk "NR==$var" Temps.txt) #récupère la ligne à copier
        echo $temp >> Région.txt #écrit dans France
      fi
    done
  else 
    cut -d ";" -f 1 $fichier > temp.txt #récupère la 1ere collone du fichier
    for i in $(awk '{print}' temp.txt); do #pour i parcourant temp2
      ((var++))
      if  [ "$i" -lt 8000 ]; then #si les données sont en france métrop
        temp=$(awk "NR==$var" $fichier) #récupère la ligne à copier
        echo $temp >> Région.txt #écrit dans Region
      fi
    done
  fi
fi

################################### Récupération des données prises dans la guyane
var=0

if (("$G" == "$a")); then #si Guyane sélectionée
  if (( "$compteur3" == 2 )); then #si date entrée
    cut -d ";" -f 1 Temps.txt > temp5.txt #récupère la 1ere collone du fichier
    for i in $(awk '{print}' temp5.txt); do #pour i parcourant temp2
      ((var++))
      if  [ "$i" -gt 81400 ]; then
        if [ "$i" -lt 81420 ]; then #si les données sont en guyane
          temp=$(awk "NR==$var" Temps.txt) #récupère la ligne à copier
          echo $temp >> Région.txt #écrit dans le fichier
        fi
      fi
    done
  else 
    cut -d ";" -f 1 $fichier > temp.txt #récupère la 1ere collone du fichier
    for i in $(awk '{print}' temp.txt); do #pour i parcourant temp2
      ((var++))
      if  [ "$i" -gt 81400 ]; then
        if [ "$i" -lt 81420 ]; then #si les données sont en guyane
          temp=$(awk "NR==$var" $fichier) #récupère la ligne à copier
          echo $temp >> Région.txt #écrit dans le fichier
        fi
      fi
    done
  fi
fi
################################### Récupération des données prises a saint pierre
var=0
if (("$S" == "$a")); then #si saint pierre sélectioné
  if (( "$compteur3" == 2 )); then #si date entrée
    cut -d ";" -f 1 Temps.txt > temp5.txt #récupère la 1ere collone du fichier
    for i in $(awk '{print}' temp5.txt); do #pour i parcourant temp2
      ((var++))
      if  [ "$i" -eq 71805 ]; then #si les données sont à st pierre
          temp=$(awk "NR==$var" Temps.txt) #récupère la ligne à copier
          echo $temp >> Région.txt #écrit dans Region
      fi
    done
  else 
    cut -d ";" -f 1 $fichier > temp.txt #récupère la 1ere collone du fichier
    for i in $(awk '{print}' temp.txt); do #pour i parcourant temp
      ((var++))
      if  [ "$i" -eq 71805 ]; then #si les données sont à st pierre
        temp=$(awk "NR==$var" $fichier) #récupère la ligne à copier
        echo $temp >> Région.txt #écrit dans fichier
      fi
    done
  fi
fi

################################### Récupération des données prises dans les antilles
var=0
if (("$A" == "$a")); then #si Antilles sélectionés
  if (( "$compteur3" == 2 )); then #si date entrée
    cut -d ";" -f 1 Temps.txt > temp5.txt #récupère la 1ere collone du fichier
    for i in $(awk '{print}' temp5.txt); do #pour i parcourant temp5
      ((var++))
      if  [ "$i" -gt 78889 ]; then
        if [ "$i" -lt 78995 ]; then #si les données sont dans les Antilles
          temp=$(awk "NR==$var" Temps.txt) #récupère la ligne à copier
          echo $temp >> Région.txt #écrit dans le fichier
        fi
      fi
    done
  else 
    cut -d ";" -f 1 $fichier > temp.txt #récupère la 1ere collone du fichie
    for i in $(awk '{print}' temp.txt); do #pour i parcourant temp
      ((var++))
      if  [ "$i" -gt 78889 ]; then
        if [ "$i" -lt 78995 ]; then #si les données sont dans les Antilles
          temp=$(awk "NR==$var" $fichier) #récupère la ligne à copier
          echo $temp >> Région.txt #écrit dans le fichier
        fi
      fi
    done
  fi
fi

################################### Récupération des données prises dans l'océan indien
var=0
if (("$O" == "$a")); then #si océan indien sélectioné
  if (( "$compteur3" == 2 )); then #si date entrée
    cut -d ";" -f 1 Temps.txt > temp5.txt #récupère la 1ere collone du fichier
    for i in $(awk '{print}' temp5.txt); do #pour i parcourant temp2
      ((var++))
      if  [ "$i" -gt 61967 ]; then
        if [ "$i" -lt 61981 ]; then #si les données sont dans l'océan indien
          temp=$(awk "NR==$var" Temps.txt) #récupère la ligne à copier
          echo $temp >> Région.txt #écrit dans le fichier
        fi
      fi
    done
  else 
    cut -d ";" -f 1 $fichier > temp.txt #récupère la 1ere collone du fichier
    for i in $(awk '{print}' temp.txt); do #pour i parcourant temp2
      ((var++))
      if  [ "$i" -gt 61967 ]; then
        if [ "$i" -lt 61981 ]; then #si les données sont dans l'océan indien
          temp=$(awk "NR==$var" $fichier) #récupère la ligne à copier
          echo $temp >> Région.txt #écrit dans le fichier
        fi
      fi
    done
  fi
fi

################################### Récupération des données prises en antarctique
var=0
if (("$Q" == "$a")); then #si Antartique sélectioné
  if (( "$compteur3" == 2 )); then #si date entrée
    cut -d ";" -f 1 Temps.txt > temp5.txt #récupère la 1ere collone du fichier
    for i in $(awk '{print}' temp5.txt); do #pour i parcourant temp2
      ((var++))
      if [ "$i" -gt 61981 ]; then
        if [ "$i" -lt 61999 ]; then #si les données sont en Antarctique
          temp=$(awk "NR==$var" Temps.txt) #récupère la ligne à copier
          echo $temp >> Région.txt #écrit dans le fichier
        fi
      fi
    done
  else 
    cut -d ";" -f 1 $fichier > temp.txt #récupère la 1ere collone du fichier
    for i in $(awk '{print}' temp.txt); do #pour i parcourant temp2
      ((var++))
      if [ "$i" -gt 61981 ]; then
        if [ "$i" -lt 61999 ]; then #si les données sont en Antarctique
          temp=$(awk "NR==$var" $fichier) #récupère la ligne a copier
          echo $temp >> Région.txt #écrit dans le fichier
        fi
      fi
    done
  fi
fi

################################### Choix des tris
if [ "$tri" = "abr" ]; then
  T=1
elif [ "$tri" = "tab" ]; then
  T=2
elif [ "$tri" = "avl" ]; then
  T=3
else
  T=3
fi
################################### Actions a effectuer pour la TEMPERATURE en fonction de l'option choisie

if [ "$t1" == 1 ]; then #si option température 1 entrée 

  if ((("$compteur" == 1 )) && (("$compteur3" == 2))) || (("$compteur" == 1)); then #si région et temps ou région sélectionné
    cut -d ";" -f 1,11 Région.txt > Temperature.txt 
    make
    ./mainC "$T" 1
    ./GnuPlot1.sh -t1
    
  elif (("$compteur3" == 2)); then
    cut -d ";" -f 1,11 Temps.txt > Temperature.txt 
    make
    ./mainC "$T" 1
    ./GnuPlot1.sh -t1
  else
    cut -d ";" -f 1,11 $fichier > Temperature.txt 
    make
    ./mainC "$T" 1
    ./GnuPlot1.sh -t1
  fi
  #dans l’ordre croissant du numéro de station.
  
fi

if [ "$t2" == 1 ]; then
  if ((("$compteur" == 1 )) && (("$compteur3" == 2))) || (("$compteur" == 1)); then #si région et temps ou région sélectionné
    cut -d ";" -f 2,11 Région.txt > Temperature2.txt 
    make
    ./mainC "$T" 2
    ./GnuPlot2.sh -t2
  elif (("$compteur3" == 2)); then
    cut -d ";" -f 2,11 Temps.txt > Temperature2.txt
    make
    ./mainC "$T" 2
    ./GnuPlot2.sh -t2
  else
     cut -d ";" -f 2,11 $fichier > Temperature2.txt 
     make
    ./mainC "$T" 2
    ./GnuPlot2.sh -t2
  fi
  #trier dans l’ordre chronologique.
fi

if [ "$t3" == 1 ]; then
  if ((("$compteur" == 1 )) && (("$compteur3" == 2))) || (("$compteur" == 1)); then #si région et temps ou région sélectionné
    cut -d ";" -f 1,2,11 Région.txt > Temperature3.txt 
    make
    ./mainC "$T" 3
    ./GnuPlot3.sh -t3
  elif (("$compteur3" == 2)); then
    cut -d ";" -f 1,2,11 Temps.txt > Temperature3.txt 
    make
    ./mainC "$T" 3
    ./GnuPlot3.sh -t3
  else
     cut -d ";" -f 1,2,11 $fichier > Temperature3.txt 
     make
    ./mainC "$T" 3
    ./GnuPlot3.sh -t3
  fi
  #trier d’abord par ordre chronologique, puis par ordre croissant de l’identifiant de la station
fi

################################### Actions a effectuer pour la PRESSION en fonction de l'option choisie

if [ "$p1" == 1 ]; then
  if ((("$compteur" == 1 )) && (("$compteur3" == 2))) || (("$compteur" == 1)); then #si région et temps ou région sélectionné
    cut -d ";" -f 1,7 Région.txt> Pression.txt
    make
    ./mainC "$T" 4
    ./GnuPlot4.sh -p1
  elif (("$compteur3" == 2)); then
    cut -d ";" -f 1,7 Temps.txt > Pression.txt
    make
    ./mainC "$T" 4
    ./GnuPlot4.sh -p1
  else
    cut -d ";" -f 1,7 $fichier > Pression.txt
    make
    ./mainC "$T" 4
    ./GnuPlot4.sh -p1
  fi
fi
  #dans l’ordre croissant du numéro de station.
  
if [ "$p2" == 1 ]; then
  if ((("$compteur" == 1 )) && (("$compteur3" == 2))) || (("$compteur" == 1)); then #si région et temps ou région sélectionné
    cut -d ";" -f 2,7 Région.txt> Pression2.txt 
    make
    ./mainC "$T" 5
    ./GnuPlot5.sh -p2
  elif (("$compteur3" == 2)); then
    cut -d ";" -f 2,7 Temps.txt > Pression2.txt
    make
    ./mainC "$T" 5
    ./GnuPlot5.sh -p2
  else
    cut -d ";" -f 2,7 $fichier > Pression2.txt
    make
    ./mainC "$T" 5
    ./GnuPlot5.sh -p2
  fi
  #triées dans l’ordre chronologique.
fi
if [ "$p3" == 1 ]; then

  if ((("$compteur" == 1 )) && (("$compteur3" == 2))) || (("$compteur" == 1)); then #si région et temps ou région sélectionné
    cut -d ";" -f 1,2,7 Région.txt> Pression3.txt 
    make
    ./mainC "$T" 6
    ./GnuPlot6.sh -p3
  elif (("$compteur3" == 2)); then
    cut -d ";" -f 1,2,7 Temps.txt > Pression3.txt
    make
    ./mainC "$T" 6
    ./GnuPlot6.sh -p3
  else
    cut -d ";" -f 1,2,7 $fichier > Pression3.txt
    make
    ./mainC "$T" 6
    ./GnuPlot6.sh -p3
  fi
  #triées d’abord par ordre chronologique, puis par ordre croissant de l’identifiant de la station
fi
################################### Actions a effectuer pour le VENT en fonction de l'option choisie

if [ "$w" == 1 ]; then
  if (("$compteur" == 1 )) && (("$compteur3" == 2)); then #si il y a les 2
    cut -d ";" -f 1,4,5,10 Région.txt > Vent.txt
    make
    ./mainC "$T" 7
    ./GnuPlot7.sh -w
  elif (("$compteur" == 1)); then #si une région est en paramètre
    cut -d ";" -f 1,4,5,10 Région.txt > Vent.txt
    make
    ./mainC "$T" 7
    ./GnuPlot.sh -w
  elif (("$compteur3" == 2)); then #si une plage de date est en paramètre
    cut -d ";" -f 1,4,5,10 Temps.txt > Vent.txt
    make
    ./mainC "$T" 7
    ./GnuPlot7.sh -w
  else #aucun des deux
    cut -d ";" -f 1,4,5,10 $fichier > Vent.txt
    make
    ./mainC "$T" 7
    ./GnuPlot7.sh -w
  fi
fi

#a trier en ordre croissant des stations

################################### Actions a effectuer pour l'HUMIDITE 

if [ "$m" == 1 ]; then
  if (("$compteur" == 1 )) && (("$compteur3" == 2)); then #si il y a les 2
    cut -d ";" -f 6,10 Région.txt > Humidité.txt
    make
    ./mainC "$T" 8
    ./GnuPlot8.sh -m
  elif (("$compteur" == 1)); then #si une région est en paramètre
    cut -d ";" -f 6,10 Région.txt > Humidité.txt
    make
    ./mainC "$T" 8
    ./GnuPlot8.sh -m
  elif (("$compteur3" == 2)); then #si une plage de date est en paramètre
    cut -d ";" -f 6,10 Temps.txt > Humidité.txt
    make
    ./mainC "$T" 8
    ./GnuPlot8.sh -m
  else  
    cut -d ";" -f 6,10 $fichier > Humidité.txt
    make
    ./mainC "$T" 8
    ./GnuPlot8.sh -m
  fi
fi

#A trier par odre décroissant
    
################################### Actions a effectuer pour l'ALTITUDE 

if [ "$h" == 1 ]; then
  if (("$compteur" == 1 )) && (("$compteur3" == 2)); then #si il y a les 2
    cut -d ";" -f 14,10 Région.txt > Altitude.txt
    make
    ./mainC "$T" 9
    ./GnuPlot9.sh -h
  elif (("$compteur" == 1)); then #si une région est en paramètre
    cut -d ";" -f 14,10 Région.txt > Altitude.txt
    make
    ./mainC "$T" 9
    ./GnuPlot9.sh -h
  elif (("$compteur3" == 2)); then #si une plage de date est en paramètre
     cut -d ";" -f 14,10 Temps.txt > Altitude.txt
     make
    ./mainC "$T" 9
    ./GnuPlot9.sh -h
  else 
    cut -d ";" -f 14,10 $fichier > Altitude.txt
    make
    ./mainC "$T" 9
    ./GnuPlot9.sh -h
    
  fi
fi

#A trier par odre décroissant

################################### Programme c execution

#gcc c.c -o c
#./c 

###################################


echo 'complete'