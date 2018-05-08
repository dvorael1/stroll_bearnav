#include "CBestStrategy.h"

using namespace std;
using namespace cv;


CBestStrategy::CBestStrategy(int n_init){
  n = n_init;
}

CBestStrategy::CBestStrategy(){

}

CBestStrategy::~CBestStrategy(){

}

void CBestStrategy::filterFeatures(vector<KeyPoint> *keypoints, Mat *descriptors, vector<KeyPoint> *tmp, Mat *tmp_mat, vector<double> score){
  if(n>=tmp->size()){
    printf("\n\n\n\nbigger\n\n\n\n\n" );
    for (size_t i = 0; i < tmp->size(); i++) {
      keypoints->push_back(tmp->at(i));
      descriptors->push_back(tmp_mat->row(i));
    }
    return;
  }

  ftr_stc features_stcs[(int)tmp->size()];
  CStrategy::set_and_sort(features_stcs, score);
  //
  // Mat tmp_mat = descriptors->clone();
  // descriptors->release();

  // vector<KeyPoint> tmp(*keypoints);
  // keypoints->clear();
  for(int i = 0; i<n; i++){
      keypoints->push_back(tmp->at(features_stcs[i].index));
      descriptors->push_back(tmp_mat->row(features_stcs[i].index));
  }
}
