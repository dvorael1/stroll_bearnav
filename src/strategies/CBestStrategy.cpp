#include "CBestStrategy.h"

using namespace std;


CBestStrategy::CBestStrategy(int n_init){
  n = n_init;
}

CBestStrategy::CBestStrategy(){

}

CBestStrategy::~CBestStrategy(){

}

void CBestStrategy::filterFeatures(vector<KeyPoint> *keypoints, vector<double> score){
  if(n>=keypoints->size()){
    return;
  }
  ftr_stc features_stcs[(int)keypoints->size()];
  CStrategy::set_and_sort(features_stcs, score);
  vector<KeyPoint> tmp(*keypoints);
  keypoints->clear();
  for(int i = 0; i<n; i++){
      keypoints->push_back(tmp[features_stcs[i].index]);
  }
}
