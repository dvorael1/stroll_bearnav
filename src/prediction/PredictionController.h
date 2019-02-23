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
/**
* Prediction controller connects prediction models and filter stategies with other
* clasess.
* Stores model and strategy types and parameters, map of string which contains
* name of map and vector of map feature models. The controller also contains map
* of string and vector of bools (filters), which are precomputed filters and ment
* to be use for online prediction.
*/
class PredictionController {

    /**
    * Dictionary of map names and vectors of prediction models for each feature
    * in map.
    */
    map<string,vector<CTemporal*> > models;

    /**
    * Dictionary of computed filters for each map identified by map name.
    * The vector of bools contains true on i-th index if the i-th feature of map
    * is visible. False otherwise.
    */
    map<string,vector<bool> > filters;

    /**
    * Filter strategy that will be use for feature filtering.
    */
    CStrategy* strategy;

    /**
    * Path to the file that contains history of observation.
    */
    string fileName;

    /**
    * Time to use for prediction as default value.
    */
    uint32_t prediction_time = time(NULL);

    /**
    * Type of prediction models that will be created.
    */
    string stc_model_type;

    /**
    * Parameter of prediction models.
    */
    float stc_model_param;

    /**
    * Type of filter strategy.
    */
    string stc_strategy_type;

    /**
    * Parameter of filter strategy.
    */
    float stc_strategy_param;

    /**
    * Defines if precomputed filters will be used or will be computed online.
    */
    bool precomputed = false;

  public:
    /**
    * Default constructor with no parameters.
    */
    PredictionController();

    /**
    * Default decstuctor.
    */
    ~PredictionController();

    /**
    * Constructor that asignes parameters of strategy and models. The strategy
    * is created inside this method.
    * @param stc_model_type_in string containing the name of prediction model type.
    * @param stc_model_param_in float containing the value of prediction model parameter.
    * @param stc_strategy_type_in string containing the name of filter strategy type.
    * @param stc_strategy_param_in float containing the value of filter strategy parameter.
    * @param file strin containing the path to the file with observation history.
    */
    void init(string stc_model_type_in, float stc_model_param_in, string stc_strategy_type_in, float stc_strategy_param_in, string file);

    /**
    * Call update() on all created models in models map.
    */
    void update_all();

    /**
    * Filters keypoints and descriptors acoording to the previsously created
    * prediction models and strategy for given map.
    * @param map is string containing the name (id) of map that the features belongs to.
    * @param keypoints vector of KeyPoint that is source of features.
    * @param descriptors Mat which is a source of descriptors.
    * @param keypoints_out is vector of KeyPoint which is empty at the beggining
    * and contains visible features after the function is finished.
    * @param descriptors_out is Mat of descriptors which is empty at the beggining
    * and contains descriptors of visible features after the function is finished.
    */
    void filter_features(string map,vector<KeyPoint> *keypoints, Mat *descriptors, vector<KeyPoint> *keypoints_out, Mat *descriptors_out);

    /**
    * Creates all models from observation history file which was provided earlier.
    * Nothing is created if file does not exist.
    */
    void build_models();

    /**
    * predict visibility score for features in map given as first argument.
    */
    vector<double> predict_score (string map,vector<double> score);

    /**
    * Creates filter for map given as first argument.
    */
    vector<bool> select_features(string map,vector<bool> vec);

    /**
    * Change default time of prediction.
    */
    void set_time(uint32_t t);

    /**
    * Precomputes filter for map given in string as first parameter at time t given as second parameter.
    */
    void precompute(string map, uint32_t t);

    /**
    * Precomputes filter for map given in string as first parameter at time t given as second parameter.
    */
    void precompute_all(uint32_t t);
};

#endif
