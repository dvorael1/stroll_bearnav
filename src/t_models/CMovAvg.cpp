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

CMovAvg(char* f_name, string f_id){
	fname = f_name;
	fid = f_id;
	order = 0;
	firstTime = -1;
	lastTime = -1;
	measurements = 0;
	type = TT_SUM;
}

void CMovAvg::init(int iMaxPeriod,int elements,int numClasses)
{
	string line;
	ifstream f(fname);

	if (f.is_open())
	{
		while ( getline (f,line) )
		{
			string map_name;
			istringstream l(line);
			string s;

			if(getline(l, s, ' ')){
					if(fid.compare(s)){
						continue;
					}
					for(int i = 0; i<6;i++){
						getline(l, s, ' ');
					}

					while (getline(l, s, ' '))
					{
						if(firstTime == -1){
							firstTime = atoi(s.c_str());
						}
						lastTime = atoi(s.c_str());
						measurements++;
						getline(l, s, ' ');
						score += atoi(s.c_str());
					}
			}
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
	score += (int)state;
	lastTime = time;
	measurements++;
}

void CMovAvg::update(int modelOrder,unsigned int* times,float* signal,int length)
{
	return -1;
}

/*text representation of the fremen model*/
void CMovAvg::print(bool verbose)
{
}

float CMovAvg::estimate(uint32_t time)
{
	return score;
}

float CMovAvg::predict(uint32_t time)
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
	array[pos++] = positive;
	array[pos++] = measurements;
	return pos;
}

int CMovAvg::importFromArray(double* array,int len)
{
	int pos = 0;
	type = (ETemporalType)array[pos++];
	if (type != TT_SUM) fprintf(stderr,"Error loading the model, type mismatch.\n");
	positive = array[pos++];
	measurements = array[pos++];
	update(0);
	return pos;

}
