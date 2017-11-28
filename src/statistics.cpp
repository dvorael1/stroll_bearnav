#include <iostream>
#include "statistics.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct ftr_stc{
  int index;
  int stc;
};

int compare (const void * a, const void * b)
{
  ftr_stc d = *(ftr_stc*)b;
  ftr_stc c = *(ftr_stc*)a;
  return ( c.stc - d.stc );
}

void set_and_sort(ftr_stc* ftr_stcs, int* stcs, int size){
  for(int i = 0;i<size; i++){
    ftr_stcs[i].index = i;
    ftr_stcs[i].stc = stcs[i];
  }
  qsort (ftr_stcs, size, sizeof(ftr_stc), compare);
}

void pick(int* stcs, int max, int size){
  for(int i = 0;i<size;i++){
    if(stcs[i]<max/2){
      stcs[i] = 0;
    }else{
      stcs[i] = 1;
    }
  }
}

void pick_n_best(int* stcs, int size, int n){
  if(n>=size){
    return;
  }
  ftr_stc features_stcs[size];
  set_and_sort(features_stcs, stcs, size);

  for(int i = 0; i<size; i++){
    if(i>=size-n){
      stcs[features_stcs[i].index] = 1;
    }else{
      stcs[features_stcs[i].index] = 0;
    }
  }
}

void pick_kvantil(int* stcs, int size, double p){
  ftr_stc features_stcs[size];
  set_and_sort(features_stcs, stcs, size);
  double index = size - (size*p);
  double zero = 0.0;
  double dif = index - (int)index;
  int k = 0;
  if(dif==zero){
    k = (stcs[(int)index]+stcs[((int)index)-1])/2;
  }else{
    k = stcs[(int)index];
  }

  for(int i = 0;i<size;i++){
    if(stcs[i]<k){
      stcs[i] = 0;
    }else{
      stcs[i] = 1;
    }
  }
}

int prepare_sum(char* fname, string mapName, int* stcs, int size){

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
      stcs[index] = was_ok;
    }
    f.close();
  }
  return max;
}


int prepare_w_sum(char* fname, string mapName, int* stcs, int size, int w1, int wm1){
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
      stcs[index] = was_ok;
    }
    f.close();
  }
  return max;
}
