#include "CMonteCarloStrategy.h"

using namespace std;


CMonteCarloStrategy::CMonteCarloStrategy(float n_init){
  n = (int)n_init;
  if(n<=0){
    n=100;
  }
}

CMonteCarloStrategy::CMonteCarloStrategy(){

}

CMonteCarloStrategy::~CMonteCarloStrategy(){

}

double find_min(vector<double> stcs, int size){
  double min = stcs[0];
  for(int i = 1;i<size;++i){
    if(min>stcs[i]){
      min = stcs[i];
    }
  }
  return min;
}

void CMonteCarloStrategy::filterFeatures(vector<KeyPoint> *keypoints, Mat *descriptors, vector<KeyPoint> *tmp, Mat *tmp_mat, vector<double> score){
  int size=tmp->size();
  if (size==0){
    return;
  }if(n>=size){
    for(int i = 0; i<size;++i){
      keypoints->push_back(tmp->at(i));
      descriptors->push_back(tmp_mat->row(i));
    }
  }


  double min = find_min(score,size);
  double add = 0.0;
  if(min<=0.0){
    add = 1.0 - min;
  }
  int count = 0;
  double all = 0.0;
  double mnt_crl[size];
  for (int i = 0; i<size;++i){
    all += add + score[i];
    mnt_crl[i] = all;
    score[i] = 0.0;
  }

  srand (time(NULL));

  for (int i = 0; i<n;++i){
    int r_next = 0.0 + double((all*rand())/(RAND_MAX + 1.0) );
    bool picked = false;
    double diff = 0.0;
    for(int j = 0; j<size && !picked;j++){
      if(mnt_crl[j]>r_next){

        if(score[j]>0.0){
          i--;
          break;
        }else{
          picked = true;
          score[j] = 1.0;
          keypoints->push_back(tmp->at(j));
          descriptors->push_back(tmp_mat->row(j));
        }
      }
    }

  }
}
