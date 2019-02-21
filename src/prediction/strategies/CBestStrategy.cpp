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

// void CBestStrategy::filterFeatures(vector<KeyPoint> *keypoints, Mat *descriptors, vector<KeyPoint> *tmp, Mat *tmp_mat, vector<double> score){
//
//   if(n>=tmp->size()){
//     for (size_t i = 0; i < tmp->size(); i++) {
//       keypoints->push_back(tmp->at(i));
//       descriptors->push_back(tmp_mat->row(i));
//     }
//     return;
//   }
//
//   ftr_stc features_stcs[(int)tmp->size()];
//   CStrategy::set_and_sort(features_stcs, score);
//   //
//   // Mat tmp_mat = descriptors->clone();
//   // descriptors->release();
//
//   // vector<KeyPoint> tmp(*keypoints);
//   // keypoints->clear();
//   int last = tmp->size()-1;
//   for(int i = 0; i<n; i++){
//       keypoints->push_back(tmp->at(features_stcs[last-i].index));
//       descriptors->push_back(tmp_mat->row(features_stcs[last-i].index));
//   }
// }

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
