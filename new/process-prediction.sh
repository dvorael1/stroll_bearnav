#check arguments
confidence=0.05

f="$1/consolidated/test"

imp=0
mp=0
mps=(2 0 0 2 43200 2)
sps=(500)
st=First
statfile=~/statistics.txt

rosparam set names_map  [$(for i in $(seq -w 1 17);do echo -ne D017,;done)]
rosparam set names_view [$(for i in $(seq -w 1 17);do echo -ne A0$i,;done)]

for mt in Dummy #Histogram Sum W_Sum Mov_Avg Fremen
do
	mp=${mps[$imp]}
		for sp in ${sps[*]}
		do
       		echo "$mt $mp $st $sp"
       
		roslaunch stroll_bearnav evaluate.launch folder_map:=$f folder_view:=$f stc_file:=$statfile stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp 
	
		mv ~/.ros/Results.txt $p/results-preduction/"$mt"_"$mp"_"$st"_"$sp"_result.txt
	

		done
		st=Best
			
	((imp++))
done
