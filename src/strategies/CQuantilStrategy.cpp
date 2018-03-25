#include "CQuantilStrategy.h"

using namespace std;


CQuantilStrategy::CQuantilStrategy(double p_init){
  p = p_init;
}

CQuantilStrategy::CQuantilStrategy(){

}

CQuantilStrategy::~CQuantilStrategy(){

}

vector<KeyPoint> CQuantilStrategy::filterFeatures(vector<KeyPoint> keypoints, vector<double> score){

  int size = keypoints.size();
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
  printf("k = %f\n", k);

  vector<KeyPoint> out;
  for(int i = 0;i<size;i++){
    if(score[i]>=k){
      out.push_back(keypoints[i]);
    }else{
      printf("filtering %d\n", i);
    }
  }
  return out;
}
