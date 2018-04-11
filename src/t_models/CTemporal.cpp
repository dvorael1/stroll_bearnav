#include "CTemporal.h"
#include "CSum.h"
#include "CWSum.h"
#include "CMovAvg.h"
#include "CMovAvg.h"
#include "CTimeMean.h"

const char *temporalModelName[] =
{
	"Sum",
	"W_Sum",
	"Mov_Avg",
	"Time_Mean"
};


CTemporal* spawnTemporalModel(ETemporalType type,int maxPeriod,int elements,int numClasses)
{
	CTemporal *temporalModel;
	switch (type)
	{
		case TT_SUM: 		temporalModel = new CSum(0);		break;
		case TT_W_SUM: 		temporalModel = new CWSum(0);		break;
		case TT_MOV_AVG:	temporalModel = new CMovAvg(0);		break;
		case TT_MEAN:	temporalModel = new CMovAvg(0);		break;
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

CTemporal* spawnTemporalModel(ETemporalType type, string f_id)
{
	CTemporal *temporalModel;
	switch (type)
	{
		case TT_SUM: 		temporalModel = new CSum(f_id);		break;
		case TT_W_SUM: 		temporalModel = new CWSum(f_id);		break;
		case TT_MOV_AVG:	temporalModel = new CMovAvg(f_id);		break;
		case TT_MEAN:	temporalModel = new CMovAvg(f_id);		break;
		default: 		temporalModel = new CSum(f_id);
	}

	temporalModel->init(0,0,0);
	return temporalModel;
}

CTemporal* spawnTemporalModel(const char* type, string f_id)
{
	int i = TT_SUM;
	for (i=0;i<TT_MOV_AVG && strcmp(type,temporalModelName[i])!=0;i++){}
	return spawnTemporalModel( (ETemporalType)i,f_id);
}
