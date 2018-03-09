#define D 0.07
#define CH_NUM  4
#define RES 2
#define ANG_NUM 360/RES
#define OUT_LEN 10
#define TOL_LEN 1000



//int ang_tri[ANG_NUM];
int ang_tri[CH_NUM];
double mic_pos[36/CH_NUM];
int results[TOL_LEN]; 
double dir_es;


void initialize(){
    
    dir_es = lround(direction/RES)*RES*1.0f;
    double degree = pi/180;
    for(int i = 0;i < CH_NUM;i++){
        mic_pos[i] = 360/CH_NUM*i; 
        }
    for(int i = 0;i < CH_NUM;i++){
        ang_tri[i] = lround(D/sound*SAMP_FREQ*cos((dir_es - mic_pos[i])*degree));
        //printf("%f\n",cos((dir_es - mic_pos[i])/degree));
        }
  
    }


void beamforming(){
     for(int i = 0;i < TOL_LEN;i++){
        results[i] = (sample1[OUT_LEN-ang_tri[0]+i]+sample2[OUT_LEN-ang_tri[1]+i]+sample3[OUT_LEN-ang_tri[2]+i]+sample4[OUT_LEN-ang_tri[3]+i])/CH_NUM; 
        }
    
    }
    
void printResults()
{   //////
    /*for(int i = 0;i < OUT_LEN;i++){
        printf("%d\n",results[i]); 
        }*/
}
