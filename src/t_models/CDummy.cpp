#include "CDummy.h"

CDummy::CDummy(int idd)
{
	id = idd;
	order = 0;
	firstTime = -1;
	lastTime = -1;
	measurements = 0;
	type = TT_DUMMY;
}

CDummy::CDummy(string f_id){
	score = 0.0;

	fid = f_id;
	order = 0;
	firstTime = -1;
	lastTime = -1;
	measurements = 0;
	type = TT_DUMMY;
}

void CDummy::init(int iMaxPeriod,int elements,int numClasses)
{
	score = 0.0;
}

CDummy::~CDummy()
{
}

// adds new state observations at given times
int CDummy::add(uint32_t time,float state)
{
	return 0;
}

void CDummy::update(int modelOrder,unsigned int* times,float* signal,int length)
{

}

/*text representation of the fremen model*/
void CDummy::print(bool verbose)
{
}

void CDummy::setParam(float param)
{

}

float CDummy::estimate(uint32_t time)
{
	return 0.0;
}

float CDummy::predict(uint32_t time)
{
	return 0.0;
}
int CDummy::save(const char* name,bool lossy)
{
	FILE* file = fopen(name,"w");
	save(file);
	fclose(file);
	return 0;
}

int CDummy::load(const char* name)
{
	FILE* file = fopen(name,"r");
	load(file);
	fclose(file);
	return 0;
}


int CDummy::save(FILE* file,bool lossy)
{
	double array[10000];
	int len = exportToArray(array,10000);
	fwrite(array,sizeof(double),len,file);
	return 0;
}

int CDummy::load(FILE* file)
{
	double *array = (double*)malloc(MAX_TEMPORAL_MODEL_SIZE*sizeof(double));
	int len = fread(array,sizeof(double),MAX_TEMPORAL_MODEL_SIZE,file);
	importFromArray(array,len);
	free(array);
	return 0;
}


int CDummy::exportToArray(double* array,int maxLen)
{
	int pos = 0;
	array[pos++] = type;
	array[pos++] = score;
	array[pos++] = measurements;
	return pos;
}

int CDummy::importFromArray(double* array,int len)
{
	int pos = 0;
	type = (ETemporalType)array[pos++];
	if (type != TT_SUM) fprintf(stderr,"Error loading the model, type mismatch.\n");
	score = array[pos++];
	measurements = array[pos++];
	update(0);
	return pos;

}
