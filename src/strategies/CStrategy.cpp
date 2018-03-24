#include <vector>
#include "CStrategy.h"
#include <stdlib.h>

int comp (const void * a, const void * b){
  ftr_stc d = *(ftr_stc*)b;
  ftr_stc c = *(ftr_stc*)a;
  if (d.stc > c.stc) return -1;
  else if (d.stc < c.stc) return 1;
  else return 0;
}

void CStrategy::set_and_sort(ftr_stc* ftr_stcs, vector<double> score){
  for(int i = 0;i<score.size(); i++){
    ftr_stcs[i].index = i;
    ftr_stcs[i].stc = score[i];
  }
  qsort (ftr_stcs, (int) score.size(), sizeof(ftr_stc), comp);
}
