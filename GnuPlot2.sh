sed 's/;/ /g' tempfinal.txt > Temperature2.txt
gnuplot << END
set term png
set output "T2.png"
set view map
set xrange[2009:2025]
set yrange[-50:50]
plot "Temperature2.txt" using 1:2 lt 7 lc 0 w lp
END