reset
set ylabel 'time(sec)'
set style fill solid
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot [:][:0.100]'output.txt' using 2:xtic(1) with histogram title 'original', \
'' using ($0-0.06):($2+0.002):2 with labels title ' ', \
'' using 3:xtic(1) with histogram title 'optimized'  , \
'' using ($0+0.08):($3+0.01):3 with labels title ' ', \
'' using 4:xtic(1) with histogram title 'hash' , \
'' using ($0+0.35):($4+0.002):4 with labels title ' ', \
'' using 5:xtic(1) with histogram title 'memory' , \
'' using ($0+0.65):($5+0.0025):5 with labels title ' ', \
'' using 6:xtic(1) with histogram title 'thread' , \
'' using ($0+0.7):($6+0.003):6 with labels title ' ', \
