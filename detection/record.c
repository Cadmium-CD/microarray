



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
        fprintf(fp1, "%f\n", sample1_s[i]);
        myled = 0;
    }
    fclose(fp1);
    
   ///////
    FILE *fp2 = fopen("/local/samples2.csv","w");
    for (int i = 1; i < BUF_LEN; i++) {
        fprintf(fp2, "%f\n", sample2_s[i]);
        myled = 0;
    }
    fclose(fp2);
    myled = 1;
    ///////
    FILE *fp3 = fopen("/local/samples3.csv","w");
    for (int i = 1; i < BUF_LEN; i++) {
        fprintf(fp3, "%f\n", sample3_s[i]);
        myled = 0;
    }
    fclose(fp3);
    myled = 1;
     ///////
    FILE *fp4 = fopen("/local/samples4.csv","w");
    for (int i = 1; i < BUF_LEN; i++) {
        fprintf(fp4, "%f\n", sample4_s[i]);
        myled = 0;
    }
    fclose(fp4);
    myled = 1;

} 
void record(){
        cs = 0;
        sample1[wp] = spi.write(0x0000);
        sample2[wp] = spi.write(0x0000);
        sample3[wp] = spi.write(0x0000);
        sample4[wp] = spi.write(0x0000);
        cs = 1;
        wp++;
 }
 
 void rec_detect(){
        cs = 0;
        detection[dp] = spi.write(0x0000);
        cs = 1;
        dp++;
 }