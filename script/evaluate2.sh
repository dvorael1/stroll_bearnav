#!/bin/bash 

 
#check arguments
case $# in
    3);;
    *) #echo "wrong number of argument! 1st: number of submaps. 2nd: path to file to save statistics. 3rd: path to folder containg folders with maps to collect statistic from."  1>&2
        #exit -1 Mov_Avg 43200 Quantile 0.25
        ;;
esac

source ~/bc_ros/devel/setup.bash


imp=0
mp=0
mps=(0 2 43200 0)
sps=(250 500 1000)

cd $1

for mt in  Fremen #Sum W_Sum Mov_Avg
do
	mp=${mps[$imp]}
	for st in Best Quantile Monte_Carlo
	do
		for sp in ${sps[*]}
		do
       		echo "$mt $mp $st $sp"
       
			roslaunch stroll_bearnav evaluate.launch fstc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
			P1=$!		
			read -n 1
	   		kill -2 $P1
			wait $P1
	
			mv /home/eliska/.ros/Results.txt $1/"$mt"_"$mp"_"$st"_"$sp"_result.txt
	

		done
		
		if [ $st == "Best" ]; then
			sps=(0.25 0.5 0.75)
		fi
		
		if [ $st == "Quantile" ]; then
			sps=(250 500 1000)
		fi
			
	done	
	((imp++))
done

mt=W_Sum
mp=2
st=Best
sp=250
exit 0