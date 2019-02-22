#include "CBestStrategy.h"
#include <ros/ros.h>

using namespace std;


CBestStrategy::CBestStrategy(float n_init){
  n = (int)n_init;
  if(n<=0){
    n=100;
  }
}

CBestStrategy::CBestStrategy(){

}

CBestStrategy::~CBestStrategy(){

}


vector<bool> CBestStrategy::select_features( vector<double> score,vector<bool> selected){
  selected.clear();
  if(n>=score.size()){
    for (size_t i = 0; i < score.size(); i++) {
      selected.push_back(true);
    }
    return selected;
  }

  ftr_stc features_stcs[(int)score.size()];
  CStrategy::set_and_sort(features_stcs, score);
  double last = score[n-1];
  int chosen = 0;
  for(int i = 0; i<score.size(); i++){
      if(score[i]>=last && chosen<n){
        chosen++;
        selected.push_back(true);
      }else{
        selected.push_back(false);
      }
  }
  return selected;
}
