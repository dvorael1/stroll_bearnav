#!/bin/bash 

 
#check arguments
case $# in
    3);;
    *) #echo "wrong number of argument! 1st: number of submaps. 2nd: path to file to save statistics. 3rd: path to folder containg folders with maps to collect statistic from."  1>&2
        #exit -1 Mov_Avg 43200 Quantile 0.25
        ;;
esac

source ~/bc_ros/devel/setup.bash

view=[A58
map=[T57
for i in {59..80}
do
	view=${view},A$i
	map=${map},T57
	
done

view=${view}]
map=${map}]
echo $view

rosparam set names_map  $map
rosparam set names_view  $view

imp=0
mp=0
mps=(2 0 0 2 43200 2)
sps=(500)
st=First


for mt in Dummy Histogram Sum W_Sum Mov_Avg Fremen
do
	mp=${mps[$imp]}
		for sp in ${sps[*]}
		do
       		echo "$mt $mp $st $sp"
       
			roslaunch stroll_bearnav evaluate.launch stc_file:=$1 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp 
	
			mv /home/eliska/.ros/Results.txt $2/"$mt"_"$mp"_"$st"_"$sp"_result.txt
	

		done
		st=Best
			
	((imp++))
done

exit 0
