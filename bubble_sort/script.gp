set terminal pngcairo size 800,600
set output 'bubble_sort_plot.png'

set title "Bubble Sort Time Complexity"
set xlabel "Number of Elements"
set ylabel "Time (seconds)"
set grid

plot "outputAvg.txt" using 1:2 with linespoints title "AvgCase", \
     "outputBest.txt" using 1:2 with linespoints title "BestCase", \
     "outputWorst.txt" using 1:2 with linespoints title "WorstCase"