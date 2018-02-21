#define CH_NUM  8
#define BUF_LEN 1025
#define SAMP_FREQ 50000
//#define INTERAL_US 1e6/SAMP_FREQ
 #define INTERAL_US 20
#define gccNUM 101
#define pi 3.1415926
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
float sample1_s[BUF_LEN];  
float sample2_s[BUF_LEN]; 
float sample3_s[BUF_LEN]; 
int r12 = 0;
int r13 = 5;
int r23 = 10;

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
        sample2_s[i] = 2*(sample1[i]-mi)/float(ma-mi)-1;
    }  
    
     ma = (max(sample2,BUF_LEN));
     mi = (min(sample2,BUF_LEN));
     for (i=0; i<BUF_LEN; i++) {  
        sample3_s[i] = 2*(sample2[i]-mi)/float(ma-mi)-1;
    }  
     ma = (max(sample3,BUF_LEN));
     mi = (min(sample3,BUF_LEN));
     for (i=0; i<BUF_LEN; i++) {  
        sample1_s[i] = 2*(sample3[i]-mi)/float(ma-mi)-1;
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
     double alpha, angle;
     alpha = 1 - r13*2/double(r12);
     angle = atan(alpha)/pi*180;
     
     if (r12 > 0){
      angle = angle + 180;
      }
      return angle;
    }
