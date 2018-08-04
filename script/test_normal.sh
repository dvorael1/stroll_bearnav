#!/bin/bash 

 
#check arguments 1531825980 1531853700 1531855080


case $# in
    3);;
    *) echo "wrong number of argument! 1st: number of submaps. 2nd: path to file to save statistics. 3rd: path to folder containg folders with maps to collect statistic from."  1>&2
        #exit -1
        ;;
esac

source ~/bc_ros/devel/setup.bash


#for i in {58..87}
#do
#	cat $1/A${i}_annotation.txt  |awk '{print $3" "$4}' > $1/A${i}_GT.txt
	
#done



cd $2/train

view=[A58
map=[B56
for i in {59..87}
do
	view=${view},A$i
	map=${map},B56
	
done

view=${view}]
map=${map}]

echo $view;
echo $map;

rosparam set /tester/names_map  $map
rosparam set /tester/names_view  $view
        
roslaunch stroll_bearnav evaluate.launch 

mv /home/eliska/.ros/Results.txt $1/without_result.txt


exit