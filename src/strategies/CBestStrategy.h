#ifndef CBESTSTRATEGY_H
#define CBESTSTRATEGY_H

#include <stroll_bearnav/FeatureArray.h>
#include <stroll_bearnav/Feature.h>
#include <vector>
#include "CStrategy.h"
#include <stdlib.h>

using namespace std;

class CBestStrategy: public CStrategy{
  public:
    CBestStrategy(int n_init);
    CBestStrategy();
		~CBestStrategy();

    vector<KeyPoint> filterFeatures(vector<KeyPoint> keypoints, vector<double> score);

    int n = 100;
};

#endif
