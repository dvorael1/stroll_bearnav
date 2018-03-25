#include "CMonteCarloStrategy.h"

using namespace std;


CMonteCarloStrategy::CMonteCarloStrategy(int n_init){
  n = n_init;
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

void CMonteCarloStrategy::filterFeatures(vector<KeyPoint> *keypoints, vector<double> score){
  int size=keypoints->size();
  if (size==0){
    return;
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
  if(n>size){
    n = size;
  }
  srand (time(NULL));

  vector<KeyPoint> tmp(*keypoints);
  keypoints->clear();

  for (int i = 0; i<n;++i){
    int r_next = 0.0 + double((all*rand())/(RAND_MAX + 1.0) );
    bool picked = false;
    double diff = 0.0;
    for(int j = 0; j<size;j++){
      if(mnt_crl[j]>r_next){
        if(picked){
          mnt_crl[j]-=diff;
          continue;
        }

        if(score[j]>0.0){
          break;
        }else{
          if(j==0){
            diff = mnt_crl[j];
          }else{
            diff = mnt_crl[j] - mnt_crl[j-1];
          }
          mnt_crl[j] -= diff;
          all -=diff;
          picked = true;
          score[j] = 1.0;
          keypoints->push_back(tmp[j]);
        }
      }
    }

  }
}
