#!/bin/bash 

 
#check arguments
case $# in
    3);;
    *) echo "wrong number of argument! 1st: number of submaps. 2nd: path to file to save statistics. 3rd: path to folder containg folders with maps to collect statistic from."  1>&2
        exit -1
        ;;
esac

source ~/bc_ros/devel/setup.bash

mt=Sum
mp=0
st=Best
sp=100

cd $3/test

TXT_FILES=( `ls` )

for i in ${TXT_FILES[*]}
do
	
	if [[ -d $i ]]; then
		mt=Sum
		mp=0
		st=Best
		sp=100
        echo "using map in sub folder: $i"
        echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp  &            	 
		P1=$!		
		
		rostopic echo /distance -n 5
		echo "listened $1 times"
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=250
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=500
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		st=Monte_Carlo
		sp=100
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=250
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=500
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		
		st=Quantile
		sp=0.25
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=0.5
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=0.75
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		mt=W_Sum
		mp=2
		st=Best
		sp=100
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=250
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=500
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		st=Monte_Carlo
		sp=100
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=250
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=500
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		
		st=Quantile
		sp=0.25
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=0.5
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=0.75
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		mt=Mov_Avg
		mp=43200
		st=Best
		sp=100
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=250
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=500
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		st=Monte_Carlo
		sp=100
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=250
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=500
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		
		st=Quantile
		sp=0.25
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=0.5
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
		sp=0.75
		
		echo "$mt $mp $st $sp"
        
		roslaunch stroll_bearnav evaluate.launch folder_view:=$3/test/$i/ stc_file:=$2 stc_model_type:=$mt stc_model_param:=$mp stc_strategy_type:=$st stc_strategy_param:=$sp &            	 
		P1=$!							
		
		rostopic echo /distance -n 5
	    kill -2 $P1
		wait $P1
		
		mv $3/test/$i/displacements.txt $3/test/$i/"$mt"_"$mp"_"$st"_"$sp"_annotation.txt
		
    fi 
	
done

exit 0