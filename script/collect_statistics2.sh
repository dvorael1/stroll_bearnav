#!/bin/bash 

 
#check arguments
case $# in
    3);;
    *) echo "wrong number of argument! 1st: path to folder containing maps. 2nd: path to file to save statistics. 3rd: path to folder containg rosbags to be played."  1>&2
        exit -1
        ;;
esac

source ~/bc_ros/devel/setup.bash

#rosparam set use_sim_time true
rosrun stroll_bearnav map_match_info_listener $2 &
P2=$!


roslaunch stroll_bearnav evaluate.launch folder:=$1 &            	 
P1=$!




#rosrun dynamic_reconfigure dynparam set /navigator matchingRatio 1.0
#rosrun dynamic_reconfigure dynparam set /feature_extraction detector 2
#rosrun dynamic_reconfigure dynparam set /feature_extraction descriptor 2

#rostopic pub -1 /map_preprocessor/goal stroll_bearnav/loadMapActionGoal '{ header: { seq: 1, stamp: now , frame_id: ""}, goal_id: { stamp: now, id: "/Action_client_loader-1-0.000"}, goal: {prefix: "day_hostibejk_0"}}' &
#rostopic echo /map_preprocessor/feedback -n 1
if [ ! -e $2 ]; then
    echo "File not found! and creating new for statistics"
    touch $2
fi

cd $3

TXT_FILES=( `ls` )

for i in ${TXT_FILES[*]}
do
	
	end=${i##*.}
	if [ "$end" = "bag" ]; then
		rosservice call setDistance "distance: 0.0"
        echo "playing rosbag $i"
        rostopic pub -1 /navigator/goal stroll_bearnav/navigatorActionGoal '{ header: { seq: 1, stamp: now, frame_id: ""}, goal_id: { stamp: now, id: "/Action_client_navigator-1-0.000"}, goal: {traversals: 0}}' 
        rosbag play $i --clock &
	    P4=$!
	    
		rostopic echo navigationInfo/histogram -n 3
		#rostopic pub -1 /navigator/cancel actionlib_msgs/GoalID '{ stamp: now, id: "/Action_client_navigator-1-0.000"}' 
	    kill $P4
    fi 
	
done

kill -2 $P2
kill $P1

exit 0