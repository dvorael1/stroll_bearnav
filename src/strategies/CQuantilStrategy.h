#ifndef CQUANTILSTRATEGY_H
#define CQUANTILSTRATEGY_H

#include <stroll_bearnav/FeatureArray.h>
#include <stroll_bearnav/Feature.h>
#include <vector>
#include "CStrategy.h"
#include <stdlib.h>

using namespace std;

class CQuantilStrategy: public CStrategy{
  public:
    CQuantilStrategy(double p_init);
    CQuantilStrategy();
		~CQuantilStrategy();

    vector<KeyPoint> filterFeatures(vector<KeyPoint> keypoints, vector<double> score);

    double p = 0.5;
};

#endif
