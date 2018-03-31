#ifndef CSUM_H
#define CSUM_H

#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include "CTimer.h"
#include "CTemporal.h"

#define	MAX_TEMPORAL_MODEL_SIZE 10000
#define MAX_ID_LENGTH 100

using namespace std;



class CSum:CTemporal
{
	public:

		//adds a serie of measurements to the data
		int add(uint32_t time,float state) = 0;

		//initialize
    void init(int maxPeriod,int elements,int numActivities) = 0;

		//estimates the probability for the given times
    float estimate(uint32_t time) = 0;
    float predict(uint32_t time) = 0;

    void update(int maxOrder,unsigned int* times = NULL,float* signal = NULL,int length = 0) = 0;
    void print(bool verbose=true) = 0;

    int exportToArray(double* array,int maxLen) = 0;
    int importFromArray(double* array,int len) = 0;
    int save(FILE* file,bool lossy = false) = 0;
    int load(FILE* file) = 0;
    int save(const char* name,bool lossy = false) = 0;
    int load(const char* name) = 0;


};

CTemporal* spawnTemporalModel(const char* type,int maxPeriod,int elements,int numClasses);
CTemporal* spawnTemporalModel(ETemporalType type,int maxPeriod,int elements,int numClasses);
#endif
