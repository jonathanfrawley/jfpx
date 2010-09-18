#set term post enh  		 # enhanced PostScript, essentially PostScript
set terminal png size 1200,800

set out 'gplt.png'

set title "x86 vs CUDA timing, No Rendering"

set xlabel 'Number of Spheres'
set ylabel 'Time Taken (secs)'

set key left top


plot "cuda_times.dat" with linespoints lw 5, "x86_times.dat" with linespoints lw 5
