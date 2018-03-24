#ifndef CSTRATEGY_H
#define CSTRATEGY_H

#include <opencv2/features2d.hpp>
using namespace cv;
using namespace std;
#include <vector>


struct ftr_stc{
  int index;
  double stc;
};

class CStrategy
{
  public:
    virtual vector<KeyPoint> filterFeatures(vector<KeyPoint> keypoints, vector<double> score) = 0;

    void set_and_sort(ftr_stc* ftr_stcs, vector<double> score);

};

#endif
