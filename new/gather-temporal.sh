#check arguments
confidence=0.05

f="$1/consolidated/test"
mkdir "results_prediction"

if [ 1 == 1 ] #tvorba history file
then
rosrun stroll_bearnav map_match_info_listener ~/statistics.txt &
P2=$!
rm ~/statistics.txt ## smaze stary history file
rosparam set names_map  [$(for i in $(seq -w 1 17);do echo -ne D017,;done)]
rosparam set names_view [$(for i in $(seq -w 1 17);do echo -ne A0$i,;done)]
roslaunch stroll_bearnav evaluate.launch  folder_map:=$f folder_view:=$f
kill -2 $P2
wait $P2
fi
