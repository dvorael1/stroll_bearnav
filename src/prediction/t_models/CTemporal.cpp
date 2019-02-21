#include "CTemporal.h"
#include "CSum.h"
#include "CDummy.h"
#include "CWSum.h"
#include "CMovAvg.h"
#include "CTimeMean.h"
#include "CTimeHist.h"
#include "CFrelement.h"
// #include "CHyperTime.h"
// #include "CHyperTimeMV.h"

const char *temporalModelName[] =
{
	"Dummy",
	"Sum",
	"W_Sum",
	"Mov_Avg",
	"Time_Mean",
	"Histogram",
	"Fremen",
	"Hyper_Time",
	"Hyper_Time_MV"
};


CTemporal* spawnTemporalModel(ETemporalType type,int maxPeriod,int elements,int numClasses)
{
	CTemporal *temporalModel;
	switch (type)
	{
		case TT_DUMMY:		temporalModel = new CDummy(0);		break;
		case TT_SUM: 		temporalModel = new CSum(0);		break;
		case TT_W_SUM: 		temporalModel = new CWSum(0);		break;
		case TT_MOV_AVG:	temporalModel = new CMovAvg(0,60*60*7.0f);		break;
		case TT_MEAN:		temporalModel = new CTimeMean(0);		break;
		case TT_HISTOGRAM:		temporalModel = new CTimeHist(0);		break;
		case TT_FREMEN:		temporalModel = new CFrelement(0);		break;
		// case TT_HYPER:		temporalModel = new CHyperTime(0);		break;
		// case TT_HYPERMV:		temporalModel = new CHyperTimeMV(0);		break;
		default: 		temporalModel = new CDummy(0);
	}
	temporalModel->init(maxPeriod,elements,numClasses);
	return temporalModel;
}

CTemporal* spawnTemporalModel(const char* type,int maxPeriod,int elements,int numClasses)
{
	int i = TT_DUMMY;
	for (i=0;i<TT_NUMBER && strcmp(type,temporalModelName[i])!=0;i++){}
	return spawnTemporalModel( (ETemporalType)i,maxPeriod,elements,numClasses);
}

CTemporal* spawnTemporalModel(ETemporalType type, string f_id, float param)
{
	CTemporal *temporalModel;
	switch (type)
	{
		case TT_DUMMY:	temporalModel = new CDummy(f_id);		break;
		case TT_SUM: 		temporalModel = new CSum(f_id);		break;
		case TT_W_SUM: 		temporalModel = new CWSum(f_id,param);		break;
		case TT_MOV_AVG:	temporalModel = new CMovAvg(f_id,param);		break;
		case TT_MEAN:	temporalModel = new CTimeMean(f_id);		break;
		case TT_HISTOGRAM:		temporalModel = new CTimeHist(f_id);		break;
		case TT_FREMEN:	temporalModel = new CFrelement(f_id);		break;
		// case TT_HYPER:		temporalModel = new CHyperTime(f_id);		break;
		// case TT_HYPERMV:		temporalModel = new CHyperTimeMV(f_id);		break;
		default: 		temporalModel = new CDummy(f_id);
	}
	temporalModel->type = type;
	temporalModel->init(0,0,0);
	return temporalModel;
}

CTemporal* spawnTemporalModel(const char* type, string f_id, float param)
{
	int i = TT_DUMMY;
	for (i=0;i<TT_NUMBER && strcmp(type,temporalModelName[i])!=0;i++){}
	return spawnTemporalModel( (ETemporalType)i,f_id, param);
}
