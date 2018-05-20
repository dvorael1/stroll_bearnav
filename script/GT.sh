#!/bin/bash 

source ~/bc_ros/devel/setup.bash

cd $1



TXT_FILES=

for i in {0..5}
do
		
		rosrun stroll_bearnav tester_image_extractor $1 SAB T$i
		
done

exit 0
