sed 's/,/;/g' tempfinal.txt > a.txt
sed 's/;/ /g' a.txt > Vent.txt
gnuplot << EOF
set term png
set output "vent.png"
set view map
plot "Vent.txt" using 5:4:( $3*cos($2)):($3*sin($2)) with vectors lc 50 filled
#(si ne fonctionne pas à executer directement dans le terminal gnuplot )
EOF