#!/bin/bash 

 
#check arguments
case $# in
    3);;
    *) echo "wrong number of argument! 1st: number of submaps. 2nd: path to file to save statistics. 3rd: path to folder containg folders with maps to collect statistic from."  1>&2
        exit -1
        ;;
esac

source ~/bc_ros/devel/setup.bash

#rosparam set use_sim_time true
rosrun stroll_bearnav map_match_info_listener $2 &
P2=$!




if [ ! -e $2 ]; then
    echo "File not found and creating new for statistics"
    touch $2
fi

cd $3/train

TXT_FILES=( `ls` )

for i in ${TXT_FILES[*]}
do
	
	if [[ -d $i ]]; then
        echo "setting time for: $i" #prida podminku pro i je int
		rosrun dynamic_reconfigure dynparam set /listener currentTime $i
	
        echo "using map in sub folder: $i"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/train/$i/ &            	 
		P1=$!							
	    
		rostopic echo navigationInfo/histogram -n $1
	    kill -2 $P1
		wait $P1
    fi 
	
done

kill -2 $P2

wait $P2

exit

cd $3/test

TXT_FILES=( `ls` )

for i in ${TXT_FILES[*]}
do
	
	if [[ -d $i ]]; then
		rm /home/eliska/stroll/datasets/super/X*
    	cp $3/test/$i/* /home/eliska/stroll/datasets/super
		
		rosrun stroll_bearnav tester_image_extractor /home/eliska/stroll/datasets/super/ SAB X
		
		mv /home/eliska/stroll/datasets/super/X_annotation.txt $3/test/$i/GT_annotation.txt
		
		
        echo "using map in sub folder: $i"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ &            	 
		P1=$!							
	    
		rostopic echo navigationInfo/histogram -n $1
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacement.txt $3/test/$i/without_annotation.txt
		
    fi 
	
done

exit 0