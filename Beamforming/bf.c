#define D 0.1
#define CH_NUM  8
#define RES 2
#define ANG_NUM 360/RES
#define OUT_LEN 100
#define TOL_LEN 256



//int ang_tri[ANG_NUM];
int ang_tri[CH_NUM];
double mic_pos[360/CH_NUM];
double results[TOL_LEN]; 
double dir_es;


void initialize(){
    
    dir_es = lround(direction/RES)*RES*1.0f;
    //double dir_g = 172;
    double degree = pi/180;
    double nne;
    for(int i = 0;i < CH_NUM;i++){
        mic_pos[i] = 360/CH_NUM*i; 
        }
    for(int i = 0;i < CH_NUM;i++){
        
        nne = (D/sound*SAMP_FREQ*cos((dir_es - mic_pos[i])*degree));
        if (nne>=0){
            ang_tri[i] = lround(nne);
            }else{
                ang_tri[i] = lround(nne) - 1;
                }
        //printf("%f\n",nne);
        }
    /*for(int i = 0;i < BUF_LEN;i++){
        sample1[i] =  sample1[i] /CH_NUM;
        sample2[i] =  sample2[i] /CH_NUM;
        sample3[i] =  sample3[i] /CH_NUM;
        sample4[i] =  sample4[i] /CH_NUM;
        sample5[i] =  sample5[i] /CH_NUM;
        sample6[i] =  sample6[i] /CH_NUM;
        sample7[i] =  sample7[i] /CH_NUM;
        sample8[i] =  sample8[i] /CH_NUM;
        }*/    
    
  
    }


void beamforming(){
     double buffer;
     for(int i = 0;i < TOL_LEN;i++){
        buffer = double(sample1[OUT_LEN-ang_tri[0]+i]+sample2[OUT_LEN-ang_tri[2]+i]+sample3[OUT_LEN-ang_tri[4]+i]+sample4[OUT_LEN-ang_tri[6]+i]\
                       +sample5[OUT_LEN-ang_tri[1]+i]+sample6[OUT_LEN-ang_tri[3]+i]+sample7[OUT_LEN-ang_tri[5]+i]+sample8[OUT_LEN-ang_tri[7]+i]);
        results[i] = buffer/CH_NUM;
        //printf("%f\n",buffer);
        buffer = 0;
        }
    }
    
void printResults()
{   //////
    for(int i = 0;i < TOL_LEN;i++){
        printf("%f\n",results[i]); 
        }
}
