#include <iostream>
#include "statistics.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <math.h>

using namespace std;

struct ftr_stc{
  int index;
  double stc;
};

int compare (const void * a, const void * b)
{
  ftr_stc d = *(ftr_stc*)b;
  ftr_stc c = *(ftr_stc*)a;
  if (d.stc > c.stc) return -1;
  else if (d.stc < c.stc) return 1;
  else return 0;
}

void set_and_sort(ftr_stc* ftr_stcs, double* stcs, int size){
  for(int i = 0;i<size; i++){
    ftr_stcs[i].index = i;
    ftr_stcs[i].stc = stcs[i];
  }
  qsort (ftr_stcs, size, sizeof(ftr_stc), compare);

}

void pick(double* stcs, int max, int size){
  for(int i = 0;i<size;i++){
    if(stcs[i]< max/2){
      stcs[i] = 0.0;
    }else{
      stcs[i] = 1.0;
    }
  }
}

void pick_n_best(double* stcs, int size, int n){
  if(n>=size){
    return;
  }
  ftr_stc features_stcs[size];
  set_and_sort(features_stcs, stcs, size);

  for(int i = 0; i<size; i++){
    if(i>=size - (n+1)){
      stcs[features_stcs[i].index] = 1.0;
    }else{
      stcs[features_stcs[i].index] = 0.0;
    }
  }
}

void pick_kvantil(double* stcs, int size, double p){
  ftr_stc features_stcs[size];
  set_and_sort(features_stcs, stcs, size);
  double index = (size*p);
  double zero = 0.0;
  double dif = index - (int)index;
  double k = 0;
  if(dif==zero){
    k = (features_stcs[(int)index].stc+features_stcs[(int)index+1].stc)/2;
  }else{
    k = features_stcs[(int)index].stc;
  }
  for(int i = 0;i<size;i++){
    if(stcs[i]<k){
      stcs[i] = 0.0;
    }else{
      stcs[i] = 1.0;
    }
  }
}

double find_min(double* stcs, int size){
  double min = stcs[0];
  for(int i = 1;i<size;++i){
    if(min>stcs[i]){
      min = stcs[i];
    }
  }
  return min;
}

void pick_mnt_crl(double* stcs, int size, int n){
  if (size==0){
    return;
  }
  double min = find_min(stcs,size);
  double add = 0;
  if(min<=0){
    add = 1 - min;
  }
  int count = 0;
  double all = 0;
  double mnt_crl[size];
  for (int i = 0; i<size;++i){
    all += add + stcs[i];
    mnt_crl[i] = all;
    stcs[i]=0.0;
  }
  if(n>size){
    n = size;
  }
  srand (time(NULL));
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

        if(stcs[j]>0.0){
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
          stcs[j] = 1.0;

        }
      }
    }

  }
}

int prepare_sum(char* fname, string mapName, double* stcs, int size){

  string line;
  ifstream f(fname);
  int max = 0;
  if (f.is_open())
  {
    while ( getline (f,line) )
    {
      int was_ok = 0;
      vector<string> strings;
      istringstream l(line);
      string s;
      int index = -1;

      bool right_map_id = false;
      if(getline(l, s, ' ')){
        if(s.find(mapName) != string::npos){
          right_map_id=true;
          size_t pos = s.find("_");
          string s_index = s.substr(0,pos);
          index = atoi(s_index.c_str());
          for(int i = 0; i<6;i++){
            getline(l, s, ' ');
          }
        }
      }
      while (getline(l, s, ' ') && right_map_id)
      {
        getline(l, s, ' ');
        was_ok += atoi(s.c_str());
      }
      if(max<was_ok){
        max = was_ok;
      }
      stcs[index] =(double) was_ok;
    }
    f.close();
  }
  return max;
}


int prepare_w_sum(char* fname, string mapName, double* stcs, int size, int w1, int wm1){
  string line;

  ifstream f(fname);
  int max = 0;
  if (f.is_open())
  {
    while ( getline (f,line) )
    {
      int was_ok = 0;
      vector<string> strings;
      istringstream l(line);
      string s;
      int index = -1;

      bool right_map_id = false;
      if(getline(l, s, ' ')){
        if(s.find(mapName) != string::npos){
          right_map_id=true;
          size_t pos = s.find("_");
          string s_index = s.substr(0,pos);
          index = atoi(s_index.c_str());
          for(int i = 0; i<6;i++){
            getline(l, s, ' ');
          }
        }
      }
      while (getline(l, s, ' ') && right_map_id)
      {
        getline(l, s, ' ');
        int stc = atoi(s.c_str());
        if(stc == 1){
          was_ok += w1;
        }else if(stc == -1){
          was_ok -= wm1;
        }
      }

      if(max<was_ok){
        max = was_ok;
      }
      stcs[index] = (double) was_ok;
    }
    f.close();
  }
  return max;
}


void prepare_mov_avg(char* fname, std::string mapName, double* stcs, int size){
  string line;
  int t = (int) time (NULL);
  t = 1523128924;
  int tau =60;
  ifstream f(fname);

  if (f.is_open())
  {

    while ( getline (f,line) )
    {
      double W = 0.0;
      double E = 0.0;
      int was_ok = 0;
      vector<string> strings;
      istringstream l(line);
      string s;
      int index = -1;

      bool right_map_id = false;
      if(getline(l, s, ' ')){
        if(s.find(mapName) != string::npos){
          right_map_id=true;
          size_t pos = s.find("_");
          string s_index = s.substr(0,pos);
          index = atoi(s_index.c_str());
          stcs[index] = 0.0;
          for(int i = 0; i<6;i++){
            getline(l, s, ' ');
          }
        }
      }
      while (getline(l, s, ' ') && right_map_id)
      {
        uint32_t t1 = atoi(s.c_str());
        double wi = exp(-1*(((double)t-(double)t1)/(double)tau));
        W += wi;
        getline(l, s, ' ');
        int stc = atoi(s.c_str());
        E += wi*(double)stc;

      }
      if(right_map_id){
        if(W==0.0){
          stcs[index] = 0.0;
        }else{
          stcs[index] =  E/W;
        }

      }

    }
    f.close();
  }
}
