#include <vector>
#include "CStrategy.h"
#include "CBestStrategy.h"
#include "CMonteCarloStrategy.h"
#include "CQuantilStrategy.h"
#include "CFirst.h"
#include <stdlib.h>


const char *strategyName[] =
{
  "Best",
  "Monte_Carlo",
  "Quantile",
  "First"
};

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


CStrategy* spawnStrategy(EStrategyType type, float param)
{
	CStrategy *strategy;
	switch (type)
	{
		case TT_BEST: 		strategy = new CBestStrategy(param);		break;
		case TT_MONTE_CARLO: 		strategy = new CMonteCarloStrategy(param);		break;
    case TT_QUANTIL:	strategy = new CQuantilStrategy(param);		break;
		case TT_FIRST:	strategy = new CFirst(param);		break;
		default: 		strategy = new CBestStrategy(param);
	}

	return strategy;
}

CStrategy* spawnStrategy(const char* type, float param)
{
	int i = TT_BEST;
	for (i=0;i<TT_LAST && strcmp(type,strategyName[i])!=0;i++){}
	return spawnStrategy( (EStrategyType)i,param);
}
