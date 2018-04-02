#include "CTemporal.h"
#include "CSum.h"

const char *temporalModelName[] =
{
	"Mov_Avg",
	"Sum",
	"W_Sum"
};


CTemporal* spawnTemporalModel(ETemporalType type,int maxPeriod,int elements,int numClasses)
{
	CTemporal *temporalModel;
	switch (type)
	{
		case TT_SUM: 		temporalModel = new CSum(0);		break;
		// case TT_W_SUM: 		temporalModel = new CWSum(0);		break;
		// case TT_MOV_AVG:	temporalModel = new CMovAvg(0);		break;
		default: 		temporalModel = new CSum(0);
	}
	temporalModel->init(maxPeriod,elements,numClasses);
	return temporalModel;
}

CTemporal* spawnTemporalModel(const char* type,int maxPeriod,int elements,int numClasses)
{
	int i = TT_SUM;
	for (i=0;i<TT_MOV_AVG && strcmp(type,temporalModelName[i])!=0;i++){}
	return spawnTemporalModel( (ETemporalType)i,maxPeriod,elements,numClasses);
}
