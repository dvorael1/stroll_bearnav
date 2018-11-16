#check arguments
confidence=0.05

f="$1/consolidated/test"

rosrun stroll_bearnav map_match_info_listener ~/statistics.txt &
rm ~/statistics.txt ## smaze stary history file
rosparam set names_map  [$(for i in $(seq -w 0 178);do echo -ne D178,;done)]
rosparam set names_view [$(for i in $(seq -w 0 177);do echo -ne A$i,;done)]
roslaunch stroll_bearnav evaluate.launch  folder_map:=$f folder_view:=$f
