#include "PredictionController.h"


using namespace std;

PredictionController::PredictionController(){

}

PredictionController::~PredictionController(){

}

void PredictionController::init(string stc_model_type_in, float stc_model_param_in, string stc_strategy_type_in, float stc_strategy_param_in, string file){
  stc_model_type = stc_model_type_in;
  stc_model_param = stc_model_param_in;
  stc_strategy_type = stc_strategy_type_in;
  stc_strategy_param = stc_strategy_param_in;
  fileName = file;
  strategy = spawnStrategy(stc_strategy_type.c_str(),stc_strategy_param);
}

void PredictionController::update_all(){
  for (map<string,vector<CTemporal*> >::iterator it=models.begin(); it!=models.end(); ++it){
    for (size_t i = 0; i < it->second.size(); i++) {
      it->second[i]->update(stc_model_param);
    }
  }
}

vector<double> PredictionController::predict_score (string map,vector<double> score) {
  size_t size = models[map].size();
  score.clear();
  for (size_t i = 0; i < size; i++) {
    score.push_back(models[map][i]->predict(prediction_time));
  }
  return score;
}

vector<bool> PredictionController::select_features (string map,vector<bool> vec) {
  vector<double> scores;
  scores = predict_score(map,scores);
  vec = strategy->select_features(scores,vec);
  filters[map] = vec;
  return vec;
}

void PredictionController::filter_features (string map,vector<KeyPoint> *keypoints, Mat *descriptors, vector<KeyPoint> *keypoints_out, Mat *descriptors_out) {
  vector<bool> vec;
  if(precomputed){
    vec = filters[map];
  }else{
    vec = select_features(map,vec);
  }
  for (size_t i = 0; i < vec.size(); i++) {
    if(vec[i]){
      keypoints_out->push_back(keypoints->at(i));
      descriptors_out->push_back(descriptors->row(i));
    }
  }
}

void PredictionController::build_models(){
  ifstream f(fileName.c_str());
  if (f.is_open())
  {
    string line;
    string map_name = "";
    ROS_ERROR("creating models");

    while ( getline (f,line))
    {

      istringstream l(line);
      string s;
      string id;
      getline(l, s, ' ');

      id = s;
      size_t pos = id.find("_");
      if(map_name.compare(id.substr (pos))){
        map_name = id.substr (pos);
      }
      models[map_name].push_back(spawnTemporalModel(stc_model_type.c_str(), id, stc_model_param));
      CTemporal* model = models[map_name][models[map_name].size()-1];
      for(int j = 0; j<6;j++){
        getline(l, s, ' ');
      }
      while (getline(l, s, ' '))
      {
        uint32_t t = atoi(s.c_str());

        getline(l, s, ' ');
        float state = (float)atoi(s.c_str());
        model->add(t,state);
      }
      model->update(stc_model_param);
    }

  }else{
    ROS_ERROR("Can not open history file %s",fileName.c_str());
  }

  f.close();
}

void PredictionController::set_time(uint32_t t){
  prediction_time = t;
}

void PredictionController::precompute(string map, uint32_t t){
  vector<double> score;
  vector<bool> vec;
  size_t size = models[map].size();
  for (size_t i = 0; i < size; i++) {
    score.push_back(models[map][i]->predict(t));
  }
  vec = strategy->select_features(score,vec);
  filters[map] = vec;
}

void PredictionController::precompute_all( uint32_t t){
  vector<bool> vec;
  for (map<string,vector<CTemporal*> >::iterator it=models.begin(); it!=models.end(); ++it){
    vector<double> score;
    for (size_t i = 0; i < it->second.size(); i++) {
      score.push_back(it->second[i]->predict(t));
    }
    strategy->select_features(score,filters[it->first]);
  }
}
