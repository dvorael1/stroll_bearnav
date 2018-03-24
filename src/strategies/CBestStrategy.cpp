#include "CBestStrategy.h"

using namespace std;


CBestStrategy::CBestStrategy(int n_init){
  n = n_init;
}

CBestStrategy::CBestStrategy(){

}

CBestStrategy::~CBestStrategy(){

}

vector<KeyPoint> CBestStrategy::filterFeatures(vector<KeyPoint> keypoints, vector<double> score){
  if(n>=keypoints.size()){
    return keypoints;
  }
  ftr_stc features_stcs[(int)keypoints.size()];
  CStrategy::set_and_sort(features_stcs, score);
  vector<KeyPoint> out;
  for(int i = 0; i<n; i++){
      out.push_back(keypoints[features_stcs[i].index]);
      printf("pushing %d\n", i);
  }
  return out;
}
