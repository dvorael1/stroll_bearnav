#ifndef CBESTSTRATEGY_H
#define CBESTSTRATEGY_H


#include <vector>
#include "CStrategy.h"
#include <stdlib.h>

using namespace std;

class CBestStrategy: public CStrategy{
  public:
    CBestStrategy(int n_init);
    CBestStrategy();
		~CBestStrategy();

    void filterFeatures(vector<KeyPoint> *keypoints, Mat *descriptors, vector<double> score);

    int n = 100;
};

#endif
