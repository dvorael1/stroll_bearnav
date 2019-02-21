#ifndef PREDICTION_CONTROLLER
#define PREDICTION_CONTROLLER

#include "strategies/CStrategy.h"
#include "t_models/CTemporal.h"
#include <time.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <ros/ros.h>
#include <fstream>

using namespace std;

class PredictionController {
    map<string,vector<CTemporal*> > models;
    map<string,vector<bool> > filters;
    CStrategy* strategy;
    string fileName;
    uint32_t prediction_time = time(NULL);
    string stc_model_type;
    float stc_model_param;
    string stc_strategy_type;
    float stc_strategy_param;
    //pridat funkci na nacteni ze souboru?

  public:
    PredictionController();
    ~PredictionController();
    PredictionController(string stc_model_type_in, float stc_model_param_in, string stc_strategy_type_in, float stc_strategy_param_in, string file);
    void update_all();
    void filter_features(string map,vector<KeyPoint> *keypoints, Mat *descriptors, vector<KeyPoint> *keypoints_out, Mat *descriptors_out);
    //private
    void build_models();
    vector<double> predict_score (string map,vector<double> score);
    vector<bool> select_features(string map,vector<bool> vec);
};

#endif
