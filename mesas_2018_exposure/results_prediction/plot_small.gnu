set terminal fig color
set size 0.8,0.6
set key right bottom
set xlabel 'Registration error [px]'
set ylabel 'Probability [-]'
set ytics 0.2
stats 'All.srt' prefix "A"

plot [0:70] [:]\
'All.srt' 	using 1:(1-$0/A_records) with lines title "Standard map"lw 2,\
'tmp.srt' 	using 1:(1-$0/A_records) with lines title "Predicted map"lw 2,\
