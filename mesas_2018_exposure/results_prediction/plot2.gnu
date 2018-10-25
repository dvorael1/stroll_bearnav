set terminal pngcairo size 800,350 enhanced 
set multiplot
set key bottom right font "Arial,8" samplen 1
set xtics 0,10,40
set size 0.43,1.0
set title "Quantile 0.75"
N = 42 
set xlabel "Registration error [px]"
set ylabel "Probability [-]"
plot [0:49] [0:1.001] \
'All.err' 	 using r0:(($0+1)/N) with lines title "None + All",\
'Sum_0_Quantile_0.75.err' 	 using r0:(($0+1)/N) with lines title "Sum",\
'W_Sum_2_Quantile_0.75.err' 	 using r0:(($0+1)/N) with lines title "Weighted Sum 2",\
'Mov_Avg_43200_Quantile_0.75.err' 	 using r0:(($0+1)/N) with lines title "Sliding Average 43200",\
'Fremen_0_Quantile_0.75.err' 	 using r0:(($0+1)/N) with lines title "FreMEn" lw 2,\


set size 0.35,1.0
set origin 0.38,0.0
set title "Quantile 0.5" 
set format y ''
unset ylabel
plot [0:49] [0:1.001] \
'All.err' 	 using r0:(($0+1)/N) with lines title "None + All",\
'Sum_0_Quantile_0.5.err' 	 using r0:(($0+1)/N) with lines title "Sum",\
'W_Sum_2_Quantile_0.5.err' 	 using r0:(($0+1)/N) with lines title "Weighted Sum 2",\
'Mov_Avg_43200_Quantile_0.5.err' 	 using r0:(($0+1)/N) with lines title "Sliding Average 43200",\
'Fremen_0_Quantile_0.5.err' 	 using r0:(($0+1)/N) with lines title "FreMEn" lw 2,\


set origin 0.68,0.0
set title "Quantile 0.25" 
set format y ''
unset ylabel
plot [0:49] [0:1.001] \
'All.err' 	 using r0:(($0+1)/N) with lines title "None + All",\
'Sum_0_Quantile_0.25.err' 	 using r0:(($0+1)/N) with lines title "Sum",\
'W_Sum_2_Quantile_0.25.err' 	 using r0:(($0+1)/N) with lines title "Weighted Sum 2",\
'Mov_Avg_43200_Quantile_0.25.err' 	 using r0:(($0+1)/N) with lines title "Sliding Average 43200",\
'Fremen_0_Quantile_0.25.err' 	 using r0:(($0+1)/N) with lines title "FreMEn" lw 2,\

