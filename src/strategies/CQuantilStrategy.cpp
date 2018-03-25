#include "CQuantilStrategy.h"

using namespace std;


CQuantilStrategy::CQuantilStrategy(double p_init){
  p = p_init;
}

CQuantilStrategy::CQuantilStrategy(){

}

CQuantilStrategy::~CQuantilStrategy(){

}

void CQuantilStrategy::filterFeatures(vector<KeyPoint> *keypoints, vector<double> score){

  int size = keypoints->size();
  ftr_stc features_stcs[size];
  CStrategy::set_and_sort(features_stcs, score);
  double index = (size*p);
  double zero = 0.0;
  double dif = index - (int)index;
  double k = 0.0;
  //possibility to change to fmod((double)keypoints.size(),p)==0.0
  if(dif==zero){
    k = (features_stcs[(int)index].stc+features_stcs[(int)index+1].stc)/2;
  }else{
    k = features_stcs[(int)index].stc;
  }
  for(int i = size -1 ;i>-1;i--){
    if(score[i]<k){
      keypoints->erase(keypoints->begin() + i);
    }
  }
}
