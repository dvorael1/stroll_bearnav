#check arguments
confidence=0.05
case $# in
    1) echo "history file: '$1'" ;;
    *) echo "wrong number of argument! 1st: path to history file."  1>&2
        exit -1
        ;;
esac

p=`pwd`

mkdir "results_prediction"

if [ 1 == 0] #tvorba history file
then
source ~/bc_ros/devel/setup.bash

rosrun stroll_bearnav map_match_info_listener $1 &
P2=$!
rm $1 ## smaze stary history file


rosparam set names_map  [$(for i in $(seq -w 0 178);do echo -ne B178,;done)]

rosparam set names_view [$(for i in $(seq -w 0 99);do echo -ne A0$i,;done;for i in $(seq -w 100 178);do echo -ne A$i,;done)]
        
roslaunch stroll_bearnav evaluate.launch 

kill -2 $P2

wait $P2
fi

if [ 1 = 1 ] # spusteni testovani
then
rosparam set names_map  [$(for i in $(seq -w 0 87);do echo -ne L087,;done)]
rosparam set names_view [$(for i in $(seq -w 0 87);do echo -ne A0$i,;done)]


imp=0
mp=0
mps=(2 0 0 2 43200 2)
sps=(500)
st=First


for mt in Dummy  #Dummy Histogram Sum W_Sum Mov_Avg Fremen
do
	mp=${mps[$imp]}
		for sp in ${sps[*]}
		do
       		echo "$mt $mp $st $sp"
       
			roslaunch stroll_bearnav evaluate.launch stc_file:=$1 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp 
	
			mv /home/eliska/.ros/Results.txt $p/results_prediction/"$mt"_"$mp"_"$st"_"$sp"_result.txt
	

		done
		st=Best
			
	((imp++))
done
fi



imp=0
mp=0
mps=(0 0 2 43200 2)
#sps=(250 500 1000)
sps=(500)
st=Best

cd results_prediction

rm results.txt

grep reports Dummy_2*.txt|awk '($23<5000){a=$21-$23;b=(sqrt(a*a)+384)%768-384;print sqrt(b*b)}'| tee All.err|sort -nr > All.srt

for mt in  Histogram Sum W_Sum Mov_Avg Fremen 
do
	mp=${mps[$imp]}
		for sp in ${sps[*]}
		do
			rm tmp.*
       		echo "$mt $mp $st $sp"	
			

			grep reports "$mt"_"$mp"_"$st"_"$sp"_result.txt|awk '($23<5000){a=$21-$23;b=(sqrt(a*a)+384)%768-384;print sqrt(b*b)}'| tee tmp.err|sort -nr > tmp.srt
			
			cat tmp.err > "$mt"_"$mp"_"$st"_"$sp".err 			
			cat tmp.srt > "$mt"_"$mp"_"$st"_"$sp".srt 			

			gnuplot plot_small.gnu >"$mt"_"$mp"_"$st"_"$sp".fig
	   		echo "$mt $mp $st $sp" >> results.txt

			paste All.err tmp.err |./t-test >> results.txt
			
		done
			
		
	((imp++))
done

cat results.txt
