#ifndef CMONTECARLOSTRATEGY_H
#define CMONTECARLOSTRATEGY_H

#include <vector>
#include "CStrategy.h"
#include <stdlib.h>

using namespace std;

class CMonteCarloStrategy: public CStrategy{
  public:
    CMonteCarloStrategy(int n_init);
    CMonteCarloStrategy();
		~CMonteCarloStrategy();

    void filterFeatures(vector<KeyPoint> *keypoints, Mat *descriptors, vector<double> score);

    int n = 100;
};

#endif
