
sed 's/,/;/g' tempfinal.txt > a.txt
sed 's/;/ /g' a.txt > Altitude.txt
gnuplot << EOF
set term png
set output "Altitude.png"
set view map
plot "Altitude.txt" with image
set palette defined (0 "blue", 1 "red")
EOF