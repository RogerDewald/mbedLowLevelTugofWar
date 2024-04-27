volatile int count = 0;
volatile int busywork = 0;
//sw1 p8  p0.6  Pull-down  PINMODE0.12:13
//sw2 p29  p0.5  Pull-down  PINMODE0.10:11
//gled1 p15  p0.23
//gled2 p19  p1.30
//rled1 p25  p2.1
//rled2 p22  p2.4
//led1  p1.18
//led2  p1.20
//led3  p1.21
//led4  p1.23

#define FIO0DIR (*(volatile unsigned int *) 0x2009c000)
#define FIO0PIN (*(volatile unsigned int *) 0x2009c014)

#define FIO1DIR (*(volatile unsigned int *)0x2009c020)
#define FIO1PIN (*(volatile unsigned int *)0x2009c034)

#define FIO2DIR (*(volatile unsigned int *)0x2009c040)
#define FIO2PIN (*(volatile unsigned int *)0x2009c054)

#define PINMODE0 (*(volatile unsigned int *)0x4002c040)
#define PINMODE1 (*(volatile unsigned int *)0x4002c044)
#define PINMODE2 (*(volatile unsigned int *)0x4002c048)
#define PINMODE3 (*(volatile unsigned int *)0x4002c04c)
#define PINMODE4 (*(volatile unsigned int *)0x4002c050)
#define PINMODE5 (*(volatile unsigned int *)0x4002c054)


void wait(float secs){
    volatile int secCount  = secs*21.33e6;
    while (secCount > 0) {
        secCount--;
    }
}

int getSw1(void){
    return ((FIO0PIN >> 6) & 1);
}
int getSw2(void){
    return ((FIO0PIN >> 5) & 1);
}
void setGled1 (int state){
    if (state){
        FIO2PIN |= (1 << 1);
    }
    else{
        FIO2PIN &= ~(1 << 1);
    }
    busywork++;
}
void setGled2 (int state){
    if (state){
        FIO2PIN |= (1 << 4);
    }
    else{
        FIO2PIN &= ~(1 << 4);
    }
    busywork++;
}
void setRled1 (int state){
    if (state){
        FIO0PIN |= (1 << 23);
    }
    else{
        FIO0PIN &= ~(1 << 23);
    }
    busywork++;
}
void setRled2 (int state){
    if (state){
        FIO1PIN |= (1 << 30);
    }
    else{
        FIO1PIN &= ~(1 << 30);
    }
    busywork++;
}
void setBled1 (int state){
    if (state){
        FIO1PIN |= (1 << 18);
    }
    else{
        FIO1PIN &= ~(1 << 18);
    }
    busywork++;
}
void setBled2 (int state){
    if (state){
        FIO1PIN |= (1 << 20);
    }
    else{
        FIO1PIN &= ~(1 << 20);
    }
    busywork++;
}
void setBled3 (int state){
    if (state){
        FIO1PIN |= (1 << 21);
    }
    else{
        FIO1PIN &= ~(1 << 21);
    }
    busywork++;
}
void setBled4 (int state){
    if (state){
        FIO1PIN |= (1 << 23);
    }
    else{
        FIO1PIN &= ~(1 << 23);
    }
    busywork++;
}
void initializePorts(void){
    FIO0DIR &= ~(1 << 6);
    FIO0DIR &= ~(1 << 5);

    FIO0DIR |= (1 << 23);
    FIO1DIR |= (1 << 30);

    FIO2DIR |= (1 << 1);
    FIO2DIR |= (1 << 4);

    FIO1DIR |= (1 << 18);
    FIO1DIR |= (1 << 20);
    FIO1DIR |= (1 << 21);
    FIO1DIR |= (1 << 23);

    
    PINMODE0 |= ~(1 << 12) | ~(1 << 13);
    PINMODE0 |= ~(1 << 10) | ~(1 << 11);

    
    PINMODE3 |= (1 << 4) & (1 << 5);
    PINMODE3 |= (1 << 8) & (1 << 9);
    PINMODE3 |= (1 << 10) & (1 << 11);
    PINMODE3 |= (1 << 14) & (1 << 15);
    
    wait(0.001);
}

void updateLEDs(){
    setGled1(count == 2 | count == 3);
    setGled2(count == 3);

    setRled1(count == -2 | count == -3);
    setRled2(count == -3);

    setBled1(count == -1 | count == -2);
    setBled2(count == -1 | count == 0);
    setBled3(count == 0 | count == 1);
    setBled4(count == 1 | count == 2);


}


int main() {
    initializePorts();
    updateLEDs();
    
    while(1) {

        if (getSw1()){
            count--;
            updateLEDs();
            wait(0.4);
        }
        if (getSw2()){
            count++;
            updateLEDs();
            wait(0.4);
        }


        if (count == 3){
            updateLEDs();
            wait(0.4);
            while(1){
            }
        }
        if (count == -3){
            updateLEDs();
            wait(0.4);
            while(1){
            }
        }

  }
}
