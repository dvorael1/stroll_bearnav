#ifndef CQUANTILSTRATEGY_H
#define CQUANTILSTRATEGY_H


#include <vector>
#include "CStrategy.h"
#include <stdlib.h>

using namespace std;

class CQuantilStrategy: public CStrategy{
  public:
    CQuantilStrategy(double p_init);
    CQuantilStrategy();
		~CQuantilStrategy();

    void filterFeatures(vector<KeyPoint> *keypoints, vector<double> score);

    double p = 0.5;
};

#endif
