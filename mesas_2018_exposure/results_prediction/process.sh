#!/bin/bash 
imp=0
mp=0
mps=(0 0 2 43200 2)
#sps=(250 500 1000)
sps=(500)
st=Best

rm results.txt

grep reports without.txt|awk '($23<5000){a=$21-$23;b=(sqrt(a*a)+384)%768-384;print sqrt(b*b)}'| tee All.err|sort -nr > All.srt

for mt in  Histogram Sum W_Sum Mov_Avg Fremen 
do
	mp=${mps[$imp]}
		for sp in ${sps[*]}
		do
			rm tmp.*
       		echo "$mt $mp $st $sp"	
			

			grep reports "$mt"_"$mp"_"$st"_"$sp"_result.txt|awk '($23<5000){a=$21-$23;b=(sqrt(a*a)+384)%768-384;print sqrt(b*b)}'| tee tmp.err|sort -nr > tmp.srt
			
			cat tmp.err > "$mt"_"$mp"_"$st"_"$sp".err 			
			cat tmp.srt > "$mt"_"$mp"_"$st"_"$sp".srt 			

			gnuplot plot_small.gnu >"$mt"_"$mp"_"$st"_"$sp".fig
	   		echo "$mt $mp $st $sp" >> results.txt

			paste All.err tmp.err |./t-test >> results.txt
			
		done
			
		
	((imp++))
done

cat results.txt



