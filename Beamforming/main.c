#include "mbed.h"
#ifndef lround
#define lround(var)    (long)(var+0.5f)
#endif
#include "var.h"
#include "function_n.h"
#include "bf.h"

//reset function
void AD7606_Reset(){
        cs = 1;
        
        rst = 0;
       
        rst = 1;
        rst = 1;
        rst = 1;
      
        rst = 0;
}


 
void printSamples()
{   ///////
    myled = 1; 
    //printf("aa\n");
    FILE *fp1 = fopen("/local/samples1.csv","w");
    for (int i = 1; i < BUF_LEN; i++) {
        fprintf(fp1, "%d\n", sample1[i]);
        myled = 0;
    }
    fclose(fp1);
    
   ///////
    FILE *fp2 = fopen("/local/samples2.csv","w");
    for (int i = 1; i < BUF_LEN; i++) {
        fprintf(fp2, "%d\n", sample2[i]);
        myled = 0;
    }
    fclose(fp2);
    myled = 1;
    ///////
    FILE *fp3 = fopen("/local/samples3.csv","w");
    for (int i = 1; i < BUF_LEN; i++) {
        fprintf(fp3, "%d\n", sample3[i]);
        myled = 0;
    }
    fclose(fp3);
    myled = 1;
     ///////
    FILE *fp4 = fopen("/local/samples4.csv","w");
    for (int i = 1; i < BUF_LEN; i++) {
        fprintf(fp4, "%d\n", sample4[i]);
        myled = 0;
    }
    fclose(fp4);
    myled = 1;
    
    FILE *fpr = fopen("/local/results.csv","w");
    for (int i = 1; i < TOL_LEN; i++) {
        fprintf(fpr, "%d\n", results[i]);
        myled = 0;
    }
    fclose(fpr);


} 
void record(){
        //a = 1;
        cs = 0;
        sample1[wp] = spi.write(0x0000);
        sample2[wp] = spi.write(0x0000);
        sample3[wp] = spi.write(0x0000);
        sample4[wp] = spi.write(0x0000);
        cs = 1;
        //a = 0;
        wp++;
 }

int main() {
    spi.format(16,2);
    spi.frequency(50000000);
    //total.start();
    
    //convst.period(1.0f); 
    while(1){
    //total.reset();
    r12 = 0;
    r13 = 5;
    r14 = 5;
    r23 = 10;
    r24 = 10;
    convst.write(1.0f);
    convst.period_us(INTERAL_US);
    
    while(((abs(r13 - r12 - r23) > 2) || (abs(r14 - r12 - r24) > 2))||(abs(r12)+abs(r13)+abs(r14)<5)||(r23 == 0) && (r24 == 0)){
        AD7606_Reset();
        convst.write(0.5f);
   
         t.start(); 
         while((wp < BUF_LEN)){
             button.fall(&record); 
          }
   //myled = 1;
         s = t.read();
         t.stop();
         t.reset();
         convst.write(1.0f);   
         wp = 0;
         scalling();
         r12 = xcorr(sample1_s, sample2_s);
         r13 = xcorr(sample1_s, sample3_s);
         r14 = xcorr(sample1_s, sample4_s);
         r23 = xcorr(sample2_s, sample3_s);
         r24 = xcorr(sample2_s, sample4_s);
   } 
    
    
    printf("Running time = %f\n",s);
    //printf("Total time = %f\n",total.read());
    printf("r12 = %d\nr13 = %d\nr14 = %d\nr23 = %d\nr24 = %d\n",r12,r13,r14,r23,r24);
    direction = cal_angle();
    printf("Angle = %f\n",direction);
    initialize();
   beamforming();
   printf("1 = %d\n2 = %d\n3 = %d\n4 = %d\n",ang_tri[0],ang_tri[1],ang_tri[2],ang_tri[3]);
    break;
  }
  
   //printResults();
   printSamples();    
}
