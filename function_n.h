#define CH_NUM  8
#define BUF_LEN 1025
#define SAMP_FREQ 37925
//#define INTERAL_US 1e6/SAMP_FREQ
 #define INTERAL_US 22
#define gccNUM 101
#define pi 3.1415926
#define sound 341.0
SPI spi(p5, p6, p7); // mosi, miso, sclk
DigitalOut cs(p8);
InterruptIn button(p9);
DigitalOut rst(p10);
DigitalIn busy(p20);
PwmOut convst(p21);
DigitalOut myled(LED1);
DigitalOut myled2(LED2);
LocalFileSystem local("local");
Timer t;
Timer total;
float s;
int16_t sample1[BUF_LEN];  // store the values read from ADC
int16_t sample2[BUF_LEN]; 
int16_t sample3[BUF_LEN]; 
int16_t sample4[BUF_LEN]; 
float sample1_s[BUF_LEN];  
float sample2_s[BUF_LEN]; 
float sample3_s[BUF_LEN]; 
float sample4_s[BUF_LEN]; 

int r12 = 0;
int r13 = 5;
int r14 = 5;
int r23 = 10;
int r24 = 10;

int wp = 0;



int max(int16_t *num, int N){
    int i;  
    int max=*num;  
    for (i=0; i<N; i++) {  
        if (max<*(num+i)) {  
            max=*(num+i);  
        }  
    }  
    return max;  
    }
    
int min(int16_t *num, int N){
    int i;  
    int min=*num;  
    for (i=0; i<N; i++) {  
        if (min>*(num+i)) {  
            min=*(num+i);  
        }  
    }  
    return min;  
    }
    
void scalling(){
     int i;
     float ma,mi;
     ma = (max(sample1,BUF_LEN));
     mi = (min(sample1,BUF_LEN));
     for (i=0; i<BUF_LEN; i++) {  
        sample1_s[i] = 2*(sample1[i]-mi)/float(ma-mi)-1;
    }  
    
     ma = (max(sample4,BUF_LEN));
     mi = (min(sample4,BUF_LEN));
     for (i=0; i<BUF_LEN; i++) {  
        sample2_s[i] = 2*(sample4[i]-mi)/float(ma-mi)-1;
    }  
     ma = (max(sample3,BUF_LEN));
     mi = (min(sample3,BUF_LEN));
     for (i=0; i<BUF_LEN; i++) {  
        sample3_s[i] = 2*(sample3[i]-mi)/float(ma-mi)-1;
    }   
     ma = (max(sample2,BUF_LEN));
     mi = (min(sample2,BUF_LEN));
     for (i=0; i<BUF_LEN; i++) {  
        sample4_s[i] = 2*(sample2[i]-mi)/float(ma-mi)-1;
    }    
}
int xcorr(float *x1,float *x2){
    
        int i,j;
        float ma;
        float cc[2*gccNUM-1];                     
        for(i=0;i<2*gccNUM-1;i++)
        {
                cc[i]=0;
        }
        // m>=0
        for(i=0;i<gccNUM;i++)
        {
                for(j=0;j<BUF_LEN-i;j++)
                {
                        cc[gccNUM+i-1] += x1[j+i]*x2[j];        
                }
        }
        // m<0
        for(i=1;i<gccNUM;i++)
        {
                for(j=0;j<BUF_LEN-i;j++)
                {
                        cc[gccNUM-i-1] += x1[j]*x2[j+i];        
                }
        }
        //get max[cc]
        ma = cc[0];
        for(i=1;i<2*gccNUM-1;i++)
        {
                if(ma<cc[i])
                {
                        ma = cc[i];
                        j = i;
                }
        }
        //printf("\n%f\n",max);
        j = j - gccNUM+1;        //j-n-1
        return j;
}
double cal_angle(){
     double alpha1, alpha2, beta1,beta2,delay1,delay2,delay3,x,y,angle;
     delay1 = double(r12)/SAMP_FREQ;
     delay2 = double(r13)/SAMP_FREQ;
     delay3 = double(r24)/SAMP_FREQ;
     alpha1 = 1 - r13*2/double(r12);
     alpha2 = 1 - r24*2/double(-r12);
     beta1 = 341*341*2*(delay1-delay2)*delay2;
     beta2 = 341*341*2*(-delay1-delay3)*delay3;
     x = (-beta2-beta1)/(alpha1-alpha2);
     y = x*alpha1 + beta1;
     angle = atan(y/x)/pi*180;
     //printf("alpha1 = %f beta1 = %f\nalpha2 = %f beta2 = %f\n",alpha1, beta1,alpha2 ,beta2);
     //printf("X = %f Y = %f\n",x,y);
     if (r12 > 0){
      angle = angle + 180;
      }
      return angle;
    }
