#echo digraph 
#echo { 
#	echo node [penwidth="2" fontname=\"palatino bold\"]; 
#	echo edge [penwidth="2"]; 
#	echo node1 [shape="underline",label=\"Comparative performace of temporal methods.\\n\\n Arrow from A to B indicates that method A\\n has a lower classification error than method B \"];
#	echo node2 [shape="underline",label=\"Best performing models that were used in this test:\\n FreMEn order $1\\n  GMM with $2 gaussians \\n Adaptive intervals with $3 samples \\n Interval with $4 minute bin width \\n \"];
#	echo node1 '->' node2 [color=white];


n=38
for i in $(seq 1 $n);
do 
a=$(ls *.txt|sed -n $i\p);
r1=0
r2=0
for j in $(seq 1 $n);
do 
b=$(ls *.txt|sed -n $j\p);
grep Displa $a|awk '{a=$21-$23;print sqrt(a*a)}' >a.tmp;
grep Displa $b|awk '{a=$21-$23;print sqrt(a*a)}' >b.tmp;
if [ $(paste a.tmp b.tmp|tr \\t ' '|./t-test|grep -c higher) == 1 ];
then
#echo $a '->' $b ;
r1=$(($r1+1))
fi
if [ $(paste b.tmp a.tmp|tr \\t ' '|./t-test|grep -c higher) == 1 ];
then
r2=$(($r2+1))
fi
done
echo $a $r1 $r2 $(($r2-$r1))
done
	
#echo }
