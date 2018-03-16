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
        fprintf(fpr, "%f\n", results[i]);
        myled = 0;
    }
    fclose(fpr);
    
    /*FILE *fp5 = fopen("/local/samples5.csv","w");
    for (int i = 1; i < BUF_LEN; i++) {
        fprintf(fp5, "%d\n", sample5[i]);
        myled = 0;
    }
    fclose(fp5);
    myled = 1;
    
    FILE *fp6 = fopen("/local/samples6.csv","w");
    for (int i = 1; i < BUF_LEN; i++) {
        fprintf(fp6, "%d\n", sample6[i]);
        myled = 0;
    }
    fclose(fp6);
    myled = 1;
    FILE *fp7 = fopen("/local/samples7.csv","w");
    for (int i = 1; i < BUF_LEN; i++) {
        fprintf(fp7, "%d\n", sample7[i]);
        myled = 0;
    }
    fclose(fp7);
    myled = 1;
    FILE *fp8 = fopen("/local/samples8.csv","w");
    for (int i = 1; i < BUF_LEN; i++) {
        fprintf(fp8, "%d\n", sample8[i]);
        myled = 0;
    }
    fclose(fp8);
    myled = 1;*/


} 
void record(){
        a = 1;
        cs = 0;
        sample1[wp] = spi.write(0x0000);
        sample2[wp] = spi.write(0x0000);
        sample3[wp] = spi.write(0x0000);
        sample4[wp] = spi.write(0x0000);
        sample5[wp] = spi.write(0x0000);
        sample6[wp] = spi.write(0x0000);
        sample7[wp] = spi.write(0x0000);
        sample8[wp] = spi.write(0x0000);
        cs = 1;
        a = 0;
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
    button.fall(&record); 
    //while((abs(r13 - r12 - r23) > 2)|| (abs(r14 - r12 - r24) > 2)||(abs(r12)+abs(r13)+abs(r14)<5)||(r12 > 25) || (r13 >25)){
    while(check()){
        //printf("%d\n",check());
        AD7606_Reset();
        convst.write(0.5f);
   
         t.start(); 
         while((wp < BUF_LEN)){
             
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
    
    //printf("%d\n",check());
    printf("Running time = %f\n",s);
    //printf("Total time = %f\n",total.read());
    printf("r12 = %d\nr13 = %d\nr14 = %d\nr23 = %d\nr24 = %d\n",r12,r13,r14,r23,r24);
    direction = cal_angle();
    printf("Angle = %f\n",direction);
    initialize();
   beamforming();
   printf("1 = %d\n2 = %d\n3 = %d\n4 = %d\n5 = %d\n6 = %d\n7 = %d\n7 = %d\n",ang_tri[0],ang_tri[2],ang_tri[4],ang_tri[6],ang_tri[1],ang_tri[3],ang_tri[5],ang_tri[7]);
    //break;
  }
  
   //printResults();
   //printSamples();    
}