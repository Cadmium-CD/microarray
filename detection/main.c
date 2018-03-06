#include "mbed.h"
#include "var.h"
#include "record.h"
#include "function_n.h"


//reset function


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
//////////////////////////////    
    act_detect();
/////////////////////////////////   
    while(((abs(r13 - r12 - r23) > 2) || (abs(r14 - r12 - r24) > 2))||(abs(r12)+abs(r13)+abs(r14)<5)||(r23 == 0) && (r24 == 0)){
        AD7606_Reset();
        convst.write(0.5f);
   
         t.start(); 
         while((wp < BUF_LEN)){
             button.fall(&record); 
          }
  // myled = 0;
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
    printf("Angle = %f\n",cal_angle());
    //break;
  }
   //printSamples();    
}
