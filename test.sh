
compteur=1
compteur3=2
compt=0
compt2=0
if ((("$compteur" == 1 )) && (("$compteur3" == 2))) || (("$compteur" == 1)); then
  echo $(cut -d ";" -f 1 Région.txt) > tempT.txt 
  awk '{for(i=1;i<=NF;i+=1)print $i}' tempT.txt > tempT2.txt
  echo $(cut -d ";" -f 11 Région.txt) > t.txt 
  awk '{for(i=1;i<=NF;i+=1)print $i}' t.txt > t2.txt
elif (("$compteur3" == 2)); then
  echo $(cut -d ";" -f 1 Temps.txt) > tempT.txt 
  awk '{for(i=1;i<=NF;i+=1)print $i}' tempT.txt > tempT2.txt
  echo $(cut -d ";" -f 11 Temps.txt) > t.txt 
  awk '{for(i=1;i<=NF;i+=1)print $i}' t.txt > t2.txt
fi
echo -n '' > tempT.txt
echo -n '' > minTemperature.txt
echo -n '' > maxTemperature.txt
echo -n '' > moyTemperature.txt
# Créez un tableau pour stocker les nombres
declare -a numbers
for i in $(awk {'print'} tempT2.txt); do
  compt=0
  for j in "${numbers[@]}" ; do
    if (("$i" == "$j")); then
      ((compt++))
    fi
  done
  if (("$compt" == 0 )); then
    numbers+=($i)
    echo $i >> tempT.txt
  fi
done
for i in $(awk {'print'} tempT.txt); do
  moy=0
  max=0
  min=1000000
  for j in $(awk {'print'} tempT2.txt); do
    if (("$i" == "$j")); then
      ((compt2++))
      if (( $(echo "$(awk "NR==$compt2" t2.txt) $min" | awk '{print ($1 <= $2)}') )); then
        min="$(awk "NR==$compt2" t2.txt)"
      fi
      if (( $(echo "$(awk "NR==$compt2" t2.txt) $max" | awk '{print ($1 >= $2)}') )); then
        max="$(awk "NR==$compt2" t2.txt)"
      fi
      moy=$(echo "$moy $(awk "NR==$compt2" t2.txt)" | awk '{print $1 + $2}')
    fi
  done
  moy=$(echo "$moy $compt2" | awk '{print $1 / $2}')
  echo $min >> minTemperature.txt
  echo $max >> maxTemperature.txt
  echo $moy >> moyTemperature.txt
done