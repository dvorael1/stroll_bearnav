#include "CSum.h"

CSum::CSum(int idd)
{
}

void CSum::init(int iMaxPeriod,int elements,int numClasses)
{
}

CSum::~CSum()
{
}

// adds new state observations at given times
int CSum::add(uint32_t time,float state)
{
	return -1;
}

void CSum::update(int modelOrder,unsigned int* times,float* signal,int length)
{
}

/*text representation of the fremen model*/
void CSum::print(bool verbose)
{
}

float CSum::estimate(uint32_t time)
{
	return 0.0f;//estimation;
}

float CSum::predict(uint32_t time)
{
	return -1;
}
int CSum::save(const char* name,bool lossy)
{
	return -1;
}

int CSum::load(const char* name)
{
	return -1;
}


int CSum::save(FILE* file,bool lossy)
{
	return -1;
}

int CSum::load(FILE* file)
{
	return -1;
}


int CSum::exportToArray(double* array,int maxLen)
{
	return -1;
}

int CSum::importFromArray(double* array,int len)
{
	return -1;
}

int CSum::get_map_id(string map_name){
  int i = 0;
  for(i = 0; i<scores.size();i++){
    if(scores[i].map_id.compare(map_name)==0){
      break;
    }
  }
  return i;
}

vector<double> CSum::get_map_score(string map_name){
  int map_id = get_map_id(map_name);
  if(scores.size()==0){
    vector<double> ept;
    return ept;
  }else{
    return scores[map_id].f_score;
  }
}

void CSum::prepare(char* fname){
  string line;
  ifstream f(fname);

  if (f.is_open())
  {
    while ( getline (f,line) )
    {
      string map_name;
      vector<string> strings;
      istringstream l(line);
      string s;
      double cur_score = 0.0;
      int index = -1;

      if(getline(l, s, ' ')){
          size_t pos = s.find("_");
          string s_index = s.substr(0,pos);
          map_name = s.substr(pos+1,s.length()-1);
          int map_id = get_map_id(map_name);
          index = atoi(s_index.c_str());
          for(int i = 0; i<6;i++){
            getline(l, s, ' ');
          }


          while (getline(l, s, ' '))
          {
            getline(l, s, ' ');
            cur_score += (double)atoi(s.c_str());

          }
          if(((int)scores.size()-1 ) < map_id )
          {
            SSum el;
            el.map_id = map_name;
            scores.push_back(el);
          }
          scores[map_id].f_score.push_back(cur_score);
      }
    }
    f.close();
  }
}
