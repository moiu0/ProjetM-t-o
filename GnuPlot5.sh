sed 's/;/ /g' tempfinal.txt > Pression2.txt
gnuplot << END
set term png
set output "P2.png"
set view map
set xrange[2009:2025]
plot "Pression2.txt" using 1:2 lt 7 lc 0 w lp
END