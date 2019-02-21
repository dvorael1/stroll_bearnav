#include "CFirst.h"
#include <ros/ros.h>

using namespace std;


CFirst::CFirst(float n_init){
  n = (int)n_init;
}

CFirst::CFirst(){

}

CFirst::~CFirst(){

}

// void CFirst::filterFeatures(vector<KeyPoint> *keypoints, Mat *descriptors, vector<KeyPoint> *tmp, Mat *tmp_mat, vector<double> score){
//
//   if(n>=tmp->size() || n<0){
//     for (size_t i = 0; i < tmp->size(); i++) {
//       keypoints->push_back(tmp->at(i));
//       descriptors->push_back(tmp_mat->row(i));
//     }
//     return;
//   }
//
//   for(int i = 0; i<n; i++){
//       keypoints->push_back(tmp->at(i));
//       descriptors->push_back(tmp_mat->row(i));
//   }
// }

vector<bool> CFirst::select_features( vector<double> score,vector<bool> selected){
  selected.clear();
  if(n>=score.size()){
    for (size_t i = 0; i < score.size(); i++) {
      selected.push_back(true);
    }
    return selected;
  }

  int chosen = 0;
  for(int i = 0; i<score.size(); i++){
      if(chosen<n){
        chosen++;
        selected.push_back(true);
      }else{
        selected.push_back(false);
      }
  }
  return selected;
}
