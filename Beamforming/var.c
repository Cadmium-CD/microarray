#define BUF_LEN 513
#define SAMP_FREQ 36571
//#define INTERAL_US 1e6/SAMP_FREQ
 #define INTERAL_US 100
#define gccNUM 40
#define pi 3.1415926
#define sound 341.0
#define check_r 15
SPI spi(p5, p6, p7); // mosi, miso, sclk
DigitalOut cs(p8);
InterruptIn button(p9);
DigitalOut rst(p10);
DigitalOut a(p20);
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
int16_t sample5[BUF_LEN];  
int16_t sample6[BUF_LEN]; 
int16_t sample7[BUF_LEN]; 
int16_t sample8[BUF_LEN]; 
 
float sample1_s[BUF_LEN];  
float sample2_s[BUF_LEN]; 
float sample3_s[BUF_LEN]; 
float sample4_s[BUF_LEN]; 

int r12 = 0;
int r13 = 5;
int r14 = 5;
int r23 = 10;
int r24 = 10;

volatile int wp = 0;
double direction,phi;