#include "CHyperTimeMV.h"

using namespace std;

CHyperTimeMV::CHyperTimeMV(int id)
{
    type = TT_HYPERMV;
    modelPositive = modelNegative = NULL;
    spaceDimension = 1;
    timeDimension = 0;
    maxTimeDimension = 10;
    covarianceType = EM::COV_MAT_GENERIC;
    positives = negatives = 0;
    corrective = 1.0;
}

CHyperTimeMV::CHyperTimeMV(string f_id)
{
    type = TT_HYPERMV;
    modelPositive = modelNegative = NULL;
    spaceDimension = 1;
    timeDimension = 0;
    maxTimeDimension = 10;
    covarianceType = EM::COV_MAT_GENERIC;
    positives = negatives = 0;
    corrective = 1.0;
}

void CHyperTimeMV::init(int iMaxPeriod,int elements,int numClasses)
{
    maxPeriod = iMaxPeriod;
    numElements = elements;
}

CHyperTimeMV::~CHyperTimeMV()
{
}

// adds new state observations at given times
int CHyperTimeMV::add(uint32_t time,float state)
{
    sampleArray[numSamples].t = time;
    sampleArray[numSamples].v = state;
    numSamples++;
    return 0;
}

/*required in incremental version*/
void CHyperTimeMV::update(int modelOrder,unsigned int* times,float* signal,int length)
{
    int numTraining = numSamples;
    int numEvaluation = 0;
    if (order != modelOrder){
        delete modelPositive;
        delete modelNegative;
        modelPositive = modelNegative = NULL;
        order = modelOrder;
    }
    if (modelPositive == NULL) modelPositive = new EM(order,covarianceType,TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, EM::DEFAULT_MAX_ITERS, FLT_EPSILON));
    if (modelNegative == NULL) modelNegative = new EM(order,covarianceType,TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, EM::DEFAULT_MAX_ITERS, FLT_EPSILON));

    /*separate positives and negative examples*/
    Mat samplesPositive(positives,spaceDimension+timeDimension,CV_32FC1);
    Mat samplesNegative(negatives,spaceDimension+timeDimension,CV_32FC1);

    float vDummy = 0.5;
    long int tDummy = 0.5;
    for (int i = 0;i<numTraining;i++){
        vDummy = sampleArray[i].v;
        if (vDummy > 0.5){
            samplesPositive.push_back(vDummy);
            positives++;
        } else{
            samplesNegative.push_back(vDummy);
            negatives++;
        }
    }
    periods.clear();
    bool stop = false;
    do {
        /*find the gaussian mixtures*/
        if (positives <= order || negatives <= order)break;
        modelPositive->train(samplesPositive);
        modelNegative->train(samplesNegative);
        printf("Model trained with %i clusters, %i dimensions, %i positives and %i negatives\n",order,timeDimension,positives,negatives);
        /*analyse model error for periodicities*/
        CFrelement fremen(0);
        float err = 0;
        float sumErr = 0;
        fremen.init(maxPeriod,maxTimeDimension,1);

        /*calculate model error across time*/
        for (int i = 0;i<numTraining;i++)
        {
            fremen.add(sampleArray[i].t,estimate(sampleArray[i].t)-sampleArray[i].v);
        }

        /*determine model weights*/
        float integral = 0;
        numEvaluation = numSamples;
        for (int i = 0;i<numEvaluation;i++) integral+=estimate(sampleArray[i].t);
        corrective = corrective*positives/integral;

        /*calculate evaluation error*/
        for (int i = 0;i<numEvaluation;i++)
        {
            err = estimate(sampleArray[i].t)-sampleArray[i].v;
            sumErr+=err*err;
        }
        sumErr=sqrt(sumErr/numEvaluation);

        /*retrieve dominant error period*/
        int maxOrder = 1;
        fremen.update(timeDimension/2+1);
        int period = fremen.predictFrelements[0].period;
        bool expand = true;
        fremen.print(true);
        printf("Model error with %i time dimensions and %i clusters is %.3f\n",timeDimension,order,sumErr);

        /*if the period already exists, then skip it*/
        for (int d = 0;d<timeDimension/2;d++)
        {
            if (period == periods[d]) period = fremen.predictFrelements[d+1].period;
        }
        errors[timeDimension/2] = sumErr;
        //cout << samplesPositive.rowRange(0, 1) << endl;

        /*error has increased: cleanup and stop*/
        if (timeDimension > 1 && errors[timeDimension/2-1] <  sumErr)
        {
            printf("Error increased from %.3f to %.3f\n",errors[timeDimension/2-1],errors[timeDimension/2]);
            timeDimension-=2;
            load("model");
            samplesPositive = samplesPositive.colRange(0, samplesPositive.cols-2);
            samplesNegative = samplesNegative.colRange(0, samplesNegative.cols-2);
            if (order < maxOrder){
                delete modelPositive;
                delete modelNegative;
                modelPositive = new EM(order,covarianceType,TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, EM::DEFAULT_MAX_ITERS, FLT_EPSILON));
                modelNegative = new EM(order,covarianceType,TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, EM::DEFAULT_MAX_ITERS, FLT_EPSILON));
            }
            printf("Reducing hypertime dimension to %i: ",timeDimension);
            for (int i = 0;i<timeDimension/2;i++) printf(" %i,",periods[i]);
            printf("\n");
            stop = true;
        }else{
            save("model");
        }
        if (timeDimension >= maxTimeDimension) stop = true;

        /*hypertime expansion*/
        if (stop == false && expand == true){
            printf("Adding period %i \n",period);
            Mat hypertimePositive(positives,2,CV_32FC1);
            Mat hypertimeNegative(negatives,2,CV_32FC1);
            positives = negatives = 0;
            for (int i = 0;i<numTraining;i++)
            {
                vDummy = sampleArray[i].v;
                tDummy = sampleArray[i].t;
                if (vDummy > 0.5){
                    hypertimePositive.at<float>(positives,0)=cos((float)tDummy/period*2*M_PI);
                    hypertimePositive.at<float>(positives,1)=sin((float)tDummy/period*2*M_PI);
                    positives++;
                }else{
                    hypertimeNegative.at<float>(negatives,0)=cos((float)tDummy/period*2*M_PI);
                    hypertimeNegative.at<float>(negatives,1)=sin((float)tDummy/period*2*M_PI);
                    negatives++;
                }
            }
            hconcat(samplesPositive, hypertimePositive,samplesPositive);
            hconcat(samplesNegative, hypertimeNegative,samplesNegative);
            periods.push_back(period);
            timeDimension+=2;
        }
        if (order <  maxOrder) stop = false;
    }while (stop == false);
}

float CHyperTimeMV::estimate(uint32_t t)
{


    //cout << "Space Dimensions:" << spaceDimension << "      Time Dimensions:" << timeDimension << endl;

    /*is the model valid?*/
    if (modelNegative->isTrained() && modelPositive->isTrained())
    {
        double estPositive[order];
        double estNegative[order];
        Mat expMatrix(1,1, CV_32FC1);
        Mat invCov(timeDimension,timeDimension, CV_32FC1);
        Mat sample(1,spaceDimension+timeDimension,CV_32FC1);
        Mat timePositive[order];
        Mat timeNegative[order];
        //vector<cv::Mat> timePositive;
        //vector<cv::Mat> timeNegative;
        Mat timeT(timeDimension,1,CV_32FC1);
        Mat timeDummy(timeDimension,timeDimension+1,CV_32FC1);
        Mat timeDummy2(1,timeDimension,CV_32FC1);
        Mat positiveCovar[order];
        Mat negativeCovar[order];
        //vector<cv::Mat> positiveCovar;
        //vector<cv::Mat> negativeCovar;
        Mat temp1[order];
        Mat temp2[order];
        //vector<cv::Mat> temp1;
        //vector<cv::Mat> temp2;
        vector<cv::Mat> positiveCovarVector;
        vector<cv::Mat> negativeCovarVector;
        sample.at<float>(0,0)=1;

        Mat meansPositive = modelPositive->get<Mat>("means");
        Mat meansNegative = modelNegative->get<Mat>("means");

        for(int k=0; k<order; k++)
        {
            timeDummy.copyTo(temp1[k]);
            timeDummy.copyTo(temp2[k]);
            invCov.copyTo(positiveCovar[k]);
            invCov.copyTo(negativeCovar[k]);
            timeDummy2.copyTo(timePositive[k]);
            timeDummy2.copyTo(timeNegative[k]);

/*
            temp1.push_back(*new Mat(1,timeDimension+1,CV_32FC1));
            //cout << "here" << endl;
            temp2.push_back(*new Mat(1,timeDimension+1,CV_32FC1));
            positiveCovar.push_back(*new Mat(timeDimension,timeDimension,CV_32FC1));
            negativeCovar.push_back(*new Mat(timeDimension,timeDimension,CV_32FC1));
            timePositive.push_back(*new Mat(1,timeDimension,CV_32FC1));
            timeNegative.push_back(*new Mat(1,timeDimension,CV_32FC1));
*/


//            temp1[k] = timeT.t();
//            temp2[k] = timeT.t();
//            positiveCovar[k] = invCov.t();
//            negativeCovar[k] = invCov.t();
//            timePositive[k] = timeT.t();
//            timeNegative[k] = timeT.t();
        }


        /*augment data sample with hypertime dimensions)*/
        for (int i=0;i<timeDimension/2;i++)
        {
            for(int k=0; k<order; k++)
            {
                sample.at<float>(0,spaceDimension+2*i+0)=cos((float)t/periods[i]*2*M_PI);
                sample.at<float>(0,spaceDimension+2*i+1)=sin((float)t/periods[i]*2*M_PI);

                timePositive[k].at<float>(0,2*i+0) = cos((float)t/periods[i]*2*M_PI) - (float)meansPositive.at<double>(k,2*i+1);
                timePositive[k].at<float>(0,2*i+1) = sin((float)t/periods[i]*2*M_PI) - (float)meansPositive.at<double>(k,2*i+2);

                timeNegative[k].at<float>(0,2*i+0) = cos((float)t/periods[i]*2*M_PI) - (float)meansNegative.at<double>(k,2*i+1);
                timeNegative[k].at<float>(0,2*i+1) = sin((float)t/periods[i]*2*M_PI) - (float)meansNegative.at<double>(k,2*i+2);
            }
        }

//        Mat probs(1,2,CV_32FC1);
//        Vec2f a = modelPositive->predict(sample, probs);
//        sample.at<float>(0,0)=0;
//        Vec2f b = modelNegative->predict(sample, probs);

        if(timeDimension>1 )
        {

            //cout << sample << endl;
            //cout << meansPositive << endl;
            for(int k=0; k<order; k++){
                cout << timePositive[k] << endl;
            }

            positiveCovarVector = modelPositive->get<vector<cv::Mat> >("covs");
            negativeCovarVector = modelNegative->get<vector<cv::Mat> >("covs");



            for(int k=0; k<order; k++)
            {
                for(int i=0; i<timeDimension; i++)
                {
                    positiveCovarVector[k].row(i+1).copyTo(temp2[k].row(i));
                    negativeCovarVector[k].row(i+1).copyTo(temp1[k].row(i));
                }
            }

            for(int k=0; k<order; k++)
            {
                for(int i=0; i<timeDimension; i++)
                {
                    temp2[k].col(i+1).copyTo(positiveCovar[k].col(i));
                    temp1[k].col(i+1).copyTo(negativeCovar[k].col(i));
                }
            }


            for(int k=0; k<order; k++)
            {
                timeT = timePositive[k].t();
                invCov = positiveCovar[k].inv();
                expMatrix = timePositive[k]*invCov*timeT;
                float Const = (pow(2*M_PI, timeDimension/2)*pow(fabs(determinant(positiveCovar[k])),0.5));
                estPositive[k] = pow(Const,-1)*exp((-0.5)*expMatrix.at<float>(0,0));

                timeT = timeNegative[k].t();
                invCov = negativeCovar[k].inv();
                expMatrix = timeNegative[k]*invCov*timeT;
                Const = (pow(2*M_PI, timeDimension/2)*pow(fabs(determinant(negativeCovar[k])),0.5));
                estNegative[k] = pow(Const,-1)*exp((-0.5)*expMatrix.at<float>(0,0));
            }

            float result = 0;
            float predictPositive=0, predictNegative=0;
            for(int k=0; k<order; k++)
            {
                predictPositive = predictPositive + estPositive[k];
                predictNegative = predictNegative + estNegative[k];
            }
            result = result + corrective*positives*predictPositive/(positives*predictPositive+negatives*predictNegative);

            if(result != result){
                return 0;
            }
            return result;

        }else{
            return 0.5;
            Mat probs(1,2,CV_32FC1);
            Vec2f a = modelPositive->predict(sample, probs);
            sample.at<float>(0,0)=0;
            Vec2f b = modelNegative->predict(sample, probs);

            double d = ((positives*exp(a(0))+negatives*exp(b(0))));
            if(d > 0) return corrective*positives*exp(a(0))/d;

        }

        //double d = ((positives*exp(a(0))+negatives*exp(b(0))));
        //float result = (corrective*positives*estPositive)/d;

        //d = ((exp(a(0))+exp(b(0))));
        //if(d > 0) return exp(a(0))/d;
        //if(d > 0) return corrective*positives*exp(a(0))/d;
//      if(d > 0 ) return (corrective*positives*estPositive)/d;
//		double d = ((exp(a(0))+exp(b(0))));
//		if(d > 0) return exp(a(0))/d;
    }
    /*any data available?*/
    //if (negatives+positives > 0) return (float)positives/(positives+negatives);
    return 0.5;
}

void CHyperTimeMV::print(bool all)
{
    Mat meansPositive = modelPositive->get<Mat>("means");
    Mat meansNegative = modelNegative->get<Mat>("means");
    std::cout << meansPositive << std::endl;
    std::cout << meansNegative << std::endl;
    //std::cout << periods << std::endl;
    printf("%i %i\n",order,timeDimension);
}

float CHyperTimeMV::predict(uint32_t time)
{
    return estimate(time);
}

int CHyperTimeMV::save(const char* name,bool lossy)
{
    /*EM models have to be saved separately and adding a '.' to the filename causes the saving to fail*/
    char filename[strlen(name)+5];

    sprintf(filename,"%spos",name);
    FileStorage fsp(filename, FileStorage::WRITE);
    fsp << "periods" << periods;
    fsp << "order" << order;
    fsp << "positives" << positives;
    fsp << "negatives" << negatives;
    fsp << "corrective" << corrective;
    if (modelPositive->isTrained()) modelPositive->write(fsp);
    fsp.release();

    sprintf(filename,"%sneg",name);
    fsp.open(filename, FileStorage::WRITE);
    if (modelNegative->isTrained())	modelNegative->write(fsp);
    fsp.release();

    return 0;
}

int CHyperTimeMV::load(const char* name)
{
    /*EM models have to be saved separately and adding a '.' to the filename causes the saving to fail*/
    char filename[strlen(name)+5];

    sprintf(filename,"%spos",name);
    FileStorage fs(filename, FileStorage::READ);
    fs["periods"] >> periods;
    fs["order"] >> order;
    fs["positives"] >> positives;
    fs["negatives"] >> negatives;
    fs["corrective"] >> corrective;

    delete modelPositive;
    delete modelNegative;
    modelPositive = new EM(order,covarianceType,TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, EM::DEFAULT_MAX_ITERS, FLT_EPSILON));
    modelNegative = new EM(order,covarianceType,TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, EM::DEFAULT_MAX_ITERS, FLT_EPSILON));

    FileNode fn = fs["StatModel.EM"];
    timeDimension = periods.size()*2;
    modelPositive->read(fn);
    fs.release();

    sprintf(filename,"%sneg",name);
    fs.open(filename, FileStorage::READ);
    fn = fs["StatModel.EM"];
    modelNegative->read(fn);
    fs.release();

    return 0;
}

int CHyperTimeMV::save(FILE* file,bool lossy)
{
//	int frk = numElements;
//	fwrite(&frk,sizeof(uint32_t),1,file);
//	fwrite(&storedGain,sizeof(float),1,file);
//	fwrite(storedFrelements,sizeof(SFrelement),numElements,file);
    return 0;
}

int CHyperTimeMV::load(FILE* file)
{
//	int frk = numElements;
//	fwrite(&frk,sizeof(uint32_t),1,file);
//	fwrite(&storedGain,sizeof(float),1,file);
//	fwrite(storedFrelements,sizeof(SFrelement),numElements,file);
    return 0;
}

/*this is very DIRTY, but I don't see any other way*/
int CHyperTimeMV::exportToArray(double* array,int maxLen)
{
    save("hypertime.tmp");
    array[0] = TT_HYPER;
    if (modelNegative->isTrained() && modelPositive->isTrained()){
        FILE*  file = fopen("hypertime.tmpneg","r");
        int len = fread(&array[5],1,maxLen,file);
        fclose(file);
        array[1] = len;
        file = fopen("hypertime.tmppos","r");
        len = fread(&array[len+5],1,maxLen,file);
        array[2] = len;
        fclose(file);
        return array[1]+array[2]+5;
    }else{
        array[1] = 0;
        array[2] = positives;
        array[3] = negatives;
        array[4] = order;
        return 5;
    }
}

/*this is very DIRTY, but I don't see any other way*/
int CHyperTimeMV::importFromArray(double* array,int len)
{
    if (array[1] > 0){
        FILE*  file = fopen("hypertime.tmpneg","w");
        fwrite(&array[5],1,array[1],file);
        fclose(file);
        file = fopen("hypertime.tmppos","w");
        fwrite(&array[(int)array[1]+5],1,array[2],file);
        fclose(file);
        load("hypertime.tmp");
    }else{
        periods.clear();
        positives = array[2];
        negatives = array[3];
        order = array[4];
        if (modelPositive == NULL) modelPositive = new EM(order,covarianceType,TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, EM::DEFAULT_MAX_ITERS, FLT_EPSILON));
        if (modelNegative == NULL) modelNegative = new EM(order,covarianceType,TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, EM::DEFAULT_MAX_ITERS, FLT_EPSILON));
    }
    return 0;
}
