#include "CWSum.h"

CWSum::CWSum(int idd)
{
	id=idd;
	measurements = 0;
	numElements = 0;
	type = TT_W_SUM;
}

void CWSum::init(int iMaxPeriod,int elements,int numClasses)
{
	maxPeriod = iMaxPeriod;
	numElements = 1;
	estimation = 1.0/numClasses;
}

CWSum::~CWSum()
{
}

// adds new state observations at given times
int CWSum::add(uint32_t time,float state)
{
	measurements++;
	return 0;
}

void CWSum::update(int modelOrder,unsigned int* times,float* signal,int length)
{
}

/*text representation of the fremen model*/
void CWSum::print(bool verbose)
{
	std::cout << "Model " << id << " Size: " << measurements << " ";
	if (verbose) printf("Value: %.3f \n",estimation);
}

float CWSum::estimate(uint32_t time)
{
	return 0;//estimation;
}

float CWSum::predict(uint32_t time)
{
	return 0;//estimation;
	return estimation;
}
int CWSum::save(const char* name,bool lossy)
{
	FILE* file = fopen(name,"w");
	save(file);
	fclose(file);
	return 0;
}

int CWSum::load(const char* name)
{
	FILE* file = fopen(name,"r");
	load(file);
	fclose(file);
	return 0;
}


int CWSum::save(FILE* file,bool lossy)
{
	return -1;
}

int CWSum::load(FILE* file)
{
	return -1;
}


int CWSum::exportToArray(double* array,int maxLen)
{
	int pos = 0;
	array[pos++] = type;
	array[pos++] = estimation;
	array[pos++] = id;
	array[pos++] = measurements;
	return pos;
}

int CWSum::importFromArray(double* array,int len)
{
	int pos = 0;
	type = (ETemporalType)array[pos++];
	if (type != TT_NONE) fprintf(stderr,"Error loading the model, type mismatch.\n");
	estimation = array[pos++];
	id = array[pos++];
	measurements = array[pos++];
	return pos;
}
