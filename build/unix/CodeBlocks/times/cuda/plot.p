set terminal latex
set output "plot.tex"
set format xy "$%g$"
set title "This is another plot"
set xlabel "$x$ axis"
set ylabel "$y$ axis"
#set key 15,-10
plot x with lines, "CollisionDetectionTimes.dat" with linespoints
