#!/bin/bash 

case $# in
    2);;
    *) #echo "wrong number of argument! 1st: number of submaps. 2nd: path to file to save statistics. 3rd: path to folder containg folders with maps to collect statistic from."  1>&2
        #exit -1
        ;;
esac

source ~/bc_ros/devel/setup.bash

#training-history observation listening

rosrun stroll_bearnav map_match_info_listener $1 &
P2=$!

rm $1

if [ ! -e $1 ]; then
    echo "File not found and creating new for statistics"
    touch $1
fi



view=[A0
map=[S57
for i in {1..57}
do
	view=${view},A$i
	map=${map},S57
	
done

view=${view}]
map=${map}]

echo $view;
echo $map;

rosparam set /names_map  $map
rosparam set /names_view  $view
        
roslaunch stroll_bearnav evaluate.launch 

read -n 1

kill -2 $P2

wait $P2
exit 0

#testing
view=[A58
map=[B56
for i in {59..87}
do
	view=${view},A$i
	map=${map},B56
	
done

view=${view}]
map=${map}]


rosparam set /tester/names_map  $map
rosparam set /tester/names_view  $view

imp=0
mp=0
mps=(0 2)
sps=(500)


for mt in  Fremen #Sum W_Sum Mov_Avg
do
	mp=${mps[$imp]}
	for st in First Best #Monte_Carlo #Quantile
	do
		for sp in ${sps[*]}
		do
       		echo "$mt $mp $st $sp"
       
			roslaunch stroll_bearnav evaluate.launch stc_file:=$1 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp 
	
			mv /home/eliska/.ros/Results.txt $2/"$mt"_"$mp"_"$st"_"$sp"_result.txt
	

		done
		
			
	done	
	((imp++))
done

exit 0
