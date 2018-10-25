set terminal pngcairo size 800,350 enhanced 
set multiplot
set key bottom right font "Arial,8" samplen 1
set xtics 0,10,40
set size 0.43,1.0
set title "Monte-Carlo 250"
N = 42 
set xlabel "Registration error [px]"
set ylabel "Probability [-]"
plot [0:49] [0:1.001] \
'All.err' 	 using r0:(($0+1)/N) with lines title "None + All",\
'Fremen_0_Monte_Carlo_250.err' 	 using r0:(($0+1)/N) with lines title "Sliding Average 43200",\


set size 0.35,1.0
set origin 0.38,0.0
set title "Monte-Carlo 500" 
set format y ''
unset ylabel
plot [0:49] [0:1.001] \
'All.err' 	 using r0:(($0+1)/N) with lines title "None + All",\
'Fremen_0_Monte_Carlo_500.err' 	 using r0:(($0+1)/N) with lines title "Sliding Average 43200",\


set origin 0.68,0.0
set title "Monte-Carlo 1000" 
set format y ''
unset ylabel
plot [0:49] [0:1.001] \
'All.err' 	 using r0:(($0+1)/N) with lines title "None + All",\
'Fremen_0_Monte_Carlo_1000.err' 	 using r0:(($0+1)/N) with lines title "Sliding Average 43200",\

