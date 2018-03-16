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
    
     ma = (max(sample2,BUF_LEN));
     mi = (min(sample2,BUF_LEN));
     for (i=0; i<BUF_LEN; i++) {  
        sample2_s[i] = 2*(sample2[i]-mi)/float(ma-mi)-1;
    }  
     ma = (max(sample3,BUF_LEN));
     mi = (min(sample3,BUF_LEN));
     for (i=0; i<BUF_LEN; i++) {  
        sample3_s[i] = 2*(sample3[i]-mi)/float(ma-mi)-1;
    }   
     ma = (max(sample4,BUF_LEN));
     mi = (min(sample4,BUF_LEN));
     for (i=0; i<BUF_LEN; i++) {  
        sample4_s[i] = 2*(sample4[i]-mi)/float(ma-mi)-1;
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
        if(abs(j) > 80){
            j = 1/(1-1);
            }
        return j;
}
double cal_angle(){
     double alpha1, alpha2, beta1,beta2,delay1,delay2,delay3,x,y,angle;
     double degree = pi/180;
     delay1 = double(r12)/SAMP_FREQ;
     delay2 = double(r13)/SAMP_FREQ;
     delay3 = double(r24)/SAMP_FREQ;
     alpha1 = 1 - r13*2/double(r12);
     alpha2 = 1 - r24*2/double(-r12);
     phi = (90-acos(sqrt(1-(341*delay1/2/0.1)*(341*delay1/2/0.1)))/degree);
     beta1 = 341*341/0.2*(delay1-delay2)*delay2;
     beta2 = -341*341/0.2*(-delay1-delay3)*delay3;
     x = (beta2-beta1)/(alpha1-alpha2);
     y = x*alpha1 + beta1;
     angle = atan(y/x)/pi*180;
     printf("alpha1 = %f beta1 = %f\nalpha2 = %f beta2 = %f\nphi = %f\n",alpha1, beta1,alpha2 ,beta2,phi);
     //printf("X = %f Y = %f\n",x,y);
     if (abs(alpha1-alpha2)< 0.02){
         angle = atan(alpha1)/pi*180;
         }
     if (r12 > 0){
      angle = angle + 180;
      }
     if (angle < 0){
      angle = angle + 360;
      }
      return angle;
    }
    
int check(){
    if((abs(r13 - r12 - r23) > 2)|| (abs(r14 - r12 - r24) > 2)||(abs(r12)+abs(r13)+abs(r14)<5)||(r12 > 25) || (r13 >25)){
        return 1;
        }
    if ((direction <360) && (direction >= 270)){
        if(abs(direction + phi - 360)> check_r){
            return 1;
            }
        }else if ((direction <270) && (direction >= 180)){
                if(abs(direction - phi - 180)> check_r){
                    return 1;
                 }
                }else if ((direction <180) && (direction >= 90)){
                        if(abs(direction + phi - 180)> check_r){
                            return 1;
                        }
                } else if (abs(direction - phi)> check_r){
                            return 1;
                        }
    return 0;
    }