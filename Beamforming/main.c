#include "mbed.h"
#ifndef lround
#define lround(var)    (long)(var+0.5f)
#endif
#include "var.h"
#include "function_n.h"
#include "bf.h"

//reset function
void AD7606_Reset(){
        cs1 = 1;
        cs2 = 1;
        
        rst = 0;
       
        rst = 1;
        rst = 1;
        rst = 1;
      
        rst = 0;
}


 
void printSamples()
{   ///////
    myled = 1; 
    FILE *fp1 = fopen("/local/data1.csv","w");
    for (int i = 1; i < BUF_LEN; i++) {
        fprintf(fp1, "%d,%d,%d,%d,%d,%d,%d,%d\n", sample1[i],sample2[i],sample3[i],sample4[i],sample5[i],sample6[i],sample7[i],sample8[i]);
        myled = 0;
    }
    fclose(fp1);
    
    myled = 1; 
    FILE *fp2 = fopen("/local/data2.csv","w");
    for (int i = 1; i < BUF_LEN; i++) {
        fprintf(fp2, "%d,%d,%d,%d,%d,%d,%d,%d\n", sample9[i],sample10[i],sample11[i],sample12[i],sample13[i],sample14[i],sample15[i],sample16[i]);
        myled = 0;
    }
    fclose(fp2);
  
    myled = 1; 
    FILE *fpr = fopen("/local/results.csv","w");
    for (int i = 1; i < TOL_LEN; i++) {
        fprintf(fpr, "%f\n", results[i]);
        myled = 0;
    }
    fclose(fpr);
    
    myled = 1; 
    FILE *fpa = fopen("/local/angle.csv","w");

    fprintf(fpa,",%d,%d,%d,%d,%d\n",r12,r13,r14,r23,r24);
    fprintf(fpa,",%f\n",direction);
    fclose(fpa);
    


} 
void record(){
        a = 1;
        cs1 = 0;
        sample1[wp] = spi.write(0x0000);
        sample2[wp] = spi.write(0x0000);
        sample3[wp] = spi.write(0x0000);
        sample4[wp] = spi.write(0x0000);
        sample5[wp] = spi.write(0x0000);
        sample6[wp] = spi.write(0x0000);
        sample7[wp] = spi.write(0x0000);
        sample8[wp] = spi.write(0x0000);
        cs1 = 1;
        cs2 = 0;
        sample16[wp] = spi.write(0x0000);
        sample15[wp] = spi.write(0x0000);
        sample14[wp] = spi.write(0x0000);
        sample13[wp] = spi.write(0x0000);
        sample12[wp] = spi.write(0x0000);
        sample11[wp] = spi.write(0x0000);
        sample10[wp] = spi.write(0x0000);
        sample9[wp] = spi.write(0x0000);
        cs2 = 1;
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
         direction = cal_angle();
         //break;
   } 
    
    //printf("%d\n",check());
    printf("Running time = %f\n",s);
    //printf("Total time = %f\n",total.read());
    printf("r12 = %d\nr13 = %d\nr14 = %d\nr23 = %d\nr24 = %d\n",r12,r13,r14,r23,r24);
    //direction = cal_angle();
    printf("Phi = %f\n",phi);
    printf("Angle = %f\n",direction);
    initialize();
   beamforming();
   //printf("1 = %d\n2 = %d\n3 = %d\n4 = %d\n5 = %d\n6 = %d\n7 = %d\n7 = %d\n",ang_tri[0],ang_tri[2],ang_tri[4],ang_tri[6],ang_tri[1],ang_tri[3],ang_tri[5],ang_tri[7]);
    //break;
  }
  
   //printResults();
   printSamples();    
}