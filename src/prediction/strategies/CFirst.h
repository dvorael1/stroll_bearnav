#ifndef CFIRST_H
#define CFIRST_H


#include <vector>
#include "CStrategy.h"
#include <stdlib.h>

using namespace std;
using namespace cv;

class CFirst: public CStrategy{
  public:
    CFirst(float n_init);
    CFirst();
		~CFirst();

    // void filterFeatures(vector<KeyPoint> *keypoints, Mat *descriptors, vector<KeyPoint> *keypoints_out, Mat *descriptors_out, vector<double> score);
    vector<bool> select_features( vector<double> score,vector<bool> selected);

    int n = 100;
};

#endif
