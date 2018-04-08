#include "CMovAvg.h"

CMovAvg::CMovAvg(int idd)
{
	id = idd;
	order = 0;
	firstTime = -1;
	lastTime = -1;
	measurements = 0;
	type = TT_SUM;
}

CMovAvg::CMovAvg(const char* f_name, string f_id, uint32_t tau_in){
  tau = tau_in;
	fname = f_name;
	fid = f_id;
	order = 0;
	firstTime = -1;
	lastTime = -1;
	measurements = 0;
	type = TT_MOV_AVG;
}

void CMovAvg::init(int iMaxPeriod,int elements,int numClasses)
{
	string line;
	ifstream f(fname);
	max_dif = 1800;
	score = 0.0;

  double W = 0.0;
  double E = 0.0;

	if (f.is_open())
	{
		while ( getline (f,line) )
		{
			istringstream l(line);
			string s;
			uint32_t t_now = time(NULL);
			t_now = 1523128924;
			if(getline(l, s, ' ')){
					if(fid.compare(s)){
						continue;
					}
					for(int i = 0; i<6;i++){
						getline(l, s, ' ');
					}

					while (getline(l, s, ' '))
					{
            uint32_t t = atoi(s.c_str());
						if(firstTime == -1){
							firstTime = t;
						}
            times.push_back(t);
						lastTime = t_now;
						measurements++;
						getline(l, s, ' ');
            int state = atoi(s.c_str());
						states.push_back(state);
		        double wi = exp(-1*(((double)t_now-(double)t)/(double)tau));
		        W += wi;
		        E += wi*(double)state;
					}
			}
		}
		if(W==0.0){
			score = 0.0;
		}else{
			score = E/W;
		}
		f.close();
	}


}

CMovAvg::~CMovAvg()
{
}

// adds new state observations at given times
int CMovAvg::add(uint32_t time,float state)
{
	if(time-lastTime>max_dif){
		score = 0.0;
	  double W = 0.0;
	  double E = 0.0;

		for (size_t i = 0; i < times.size(); i++) {
			uint32_t t = times[i];
			double wi = exp(-1*(((double)time-(double)t)/(double)tau));
			int state = states[i];
			W += wi;
			E += wi*(double)state;
		}
		if(W==0.0){
			score = 0.0;
		}else{
			score = E/W;
		}
	}
}

void CMovAvg::update(int modelOrder,unsigned int* times,float* signal,int length)
{

}

/*text representation of the fremen model*/
void CMovAvg::print(bool verbose)
{
}

double CMovAvg::estimate(uint32_t time)
{
	return score;
}

double CMovAvg::predict(uint32_t time)
{
	return score;
}
int CMovAvg::save(const char* name,bool lossy)
{
	FILE* file = fopen(name,"w");
	save(file);
	fclose(file);
	return 0;
}

int CMovAvg::load(const char* name)
{
	FILE* file = fopen(name,"r");
	load(file);
	fclose(file);
	return 0;
}


int CMovAvg::save(FILE* file,bool lossy)
{
	double array[10000];
	int len = exportToArray(array,10000);
	fwrite(array,sizeof(double),len,file);
	return 0;
}

int CMovAvg::load(FILE* file)
{
	double *array = (double*)malloc(MAX_TEMPORAL_MODEL_SIZE*sizeof(double));
	int len = fread(array,sizeof(double),MAX_TEMPORAL_MODEL_SIZE,file);
	importFromArray(array,len);
	free(array);
	return 0;
}


int CMovAvg::exportToArray(double* array,int maxLen)
{
	int pos = 0;
	array[pos++] = type;
	array[pos++] = score;
	array[pos++] = measurements;
	return pos;
}

int CMovAvg::importFromArray(double* array,int len)
{
	int pos = 0;
	type = (ETemporalType)array[pos++];
	if (type != TT_SUM) fprintf(stderr,"Error loading the model, type mismatch.\n");
	score = array[pos++];
	measurements = array[pos++];
	update(0);
	return pos;

}
