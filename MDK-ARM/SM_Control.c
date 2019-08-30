#include "SM_Control.h"

//speed multiplier
#define SMP 1e3
//acceleration multiplayer
#define AMP 1

//Step pin:
uint16_t SPin=GPIO_PIN_12;
GPIO_TypeDef *SPinSer=GPIOB;

//Direction pin:
uint16_t DPin=GPIO_PIN_13;
GPIO_TypeDef *DPinSer=GPIOB;

//Pin 1:
uint16_t Pin1=GPIO_PIN_14;
GPIO_TypeDef *Pin1Ser=GPIOB;

//Pin 2:
uint16_t Pin2=GPIO_PIN_15;
GPIO_TypeDef *Pin2Ser=GPIOB;

//Pin 3:
uint16_t Pin3=GPIO_PIN_8;
GPIO_TypeDef *Pin3Ser=GPIOA;


//Motor private fields:
//1 for right and -1 for left rotation
int8_t dir=1;
//acceleration [-1000;+1000]
int16_t al=0;
//start speed [1;2000]
uint16_t ss=1;
//speed we want to achieve [1;10000]
uint16_t sd=200;
//current speed [1;10000]
uint16_t cs=1;


//Prototypes of private functions
void Dir(void);
void Step(void);
void Change(void);

//Algorithm functions:
//PARAMETRES CHANGING FUNCTIONS:
//Left rotation
void DL(){
    Debug("DL\n");
    
    dir=-1;
    Dir();
}
//Right rotation
void DR(){
    Debug("DR\n");
    
    dir=1;
    Dir();
}
//Reverse
void RS(){
    Debug("RS\n");
    
    dir=-dir;
    Dir();
}
//Set acceleration
void AL(int16_t a){
    Debug("AL\n");
    
    if(-1000<=a&&a<=1000)
        al=a;
}
//Set speed
void SD(int16_t s){
    Debug("SD\n");
    
    if(1<=s&&s<=10000)
    {
        sd=s;
    }
}
//Set start speed
void SS(int16_t s){
    Debug("SS\n");
    
    if(1<=s&&s<=2000)
        ss=s;
}


//MOTION FUNCTIONS:
//Turn on motor + continuous motion
void MV(){
    Debug("MV\n");
    
    cs=ss;
    while(1)
        Step();
}
//Make x steps
void MVX(uint32_t x){
    Debug("MVX\n");
        
    cs=ss;
    for(uint8_t i=0;i<x;i++)
        Step();
}
//Continuous motion till recieving [some signal 1]
void MH(){
    Debug("MH\n");
    
    cs=ss;
    while(HAL_GPIO_ReadPin(Pin1Ser, Pin1))
        Step();
}
//Continuous motion till recieving [some signal 2]
void ML(){
    Debug("ML\n");
    
    cs=ss;
    while(HAL_GPIO_ReadPin(Pin2Ser, Pin2))
        Step();
}
//Continuous motion till recieving [some signal 3]
void HM(){
    Debug("HM\n");
    
    cs=ss;
    while(HAL_GPIO_ReadPin(Pin3Ser, Pin3))
        Step();
}

//STOP FUNCTIONS:
//Stop for x ms
void SP(uint32_t x){
    Debug("SP\n");
    
    HAL_Delay(x);
}
//Wait for [some signal 2]
void WL(){
    Debug("WL\n");
    
    while(HAL_GPIO_ReadPin(Pin2Ser, Pin2))
       HAL_Delay(10);
}
//Wait for [some signal 1]
void WH(){
    Debug("WH\n");
    
    while(HAL_GPIO_ReadPin(Pin1Ser, Pin1))
       HAL_Delay(10);
}

//Direct control functions:
//Turn on motor + continuous motion
extern void MVdc(){
    Debug("MVdc\n");
    uint8_t bc;
    cs=ss;
    while(1)
    {
        bc=BufferCheck();
        if(bc==1)
        {
            break;
        }
        else if(bc==2)
        {
            NoInterrupt();
            continue;
        }
        Step();
        Change();
    }
}
//Make x steps
extern void MVXdc(uint32_t x){
    Debug("MVXdc\n");
    
    uint8_t bc;
    cs=ss;
    for(uint8_t i=0;i<x;i++)
    {
        bc=BufferCheck();
        if(bc==1)
        {
            break;
        }
        else if(bc==2)
        {
            NoInterrupt();
            continue;
        }
        Step();
        Change();
    }
}
//Continuous motion till recieving [some signal 1]
extern void MHdc(){
    Debug("MHdc\n");
    
    cs=ss;
    while(!HAL_GPIO_ReadPin(Pin1Ser, Pin1))
    {
        Step();
        Change();
    }
}
//Continuous motion till recieving [some signal 2]
extern void MLdc(){
    Debug("MLdc\n");
    
    cs=ss;
    while(!HAL_GPIO_ReadPin(Pin2Ser, Pin2))
    {
        Step();
        Change();
    }
}
//Continuous motion till recieving [some signal 3] with changable speed (by SD)
extern void HMdc(){
    Debug("HMdc\n");
    
    cs=ss;
    while(HAL_GPIO_ReadPin(Pin3Ser, Pin3)!=GPIO_PIN_SET)
    {
        Step();
        Change();
        if(BufferCheck()==2)
        {
            NoInterrupt();
            continue;
        }
    }
}
//Stop for x ms and check new command every 100 ms
extern void SPdc(uint32_t x){
    Debug("SDdc\n");
    
    for(int64_t i=0;i<(int64_t)(x/100);i++){
        HAL_Delay(100);
        if(BufferCheck()==1)
        {
            break;
        }
    }
}
//Private functions
void Step(){
    //Debug("Step\n");
    
    HAL_GPIO_WritePin(SPinSer,SPin,GPIO_PIN_SET);
    HAL_Delay(SMP/cs);
    HAL_GPIO_WritePin(SPinSer,SPin,GPIO_PIN_RESET);
    HAL_Delay(SMP/cs);
}
void Dir(){
    if (dir==1)
        HAL_GPIO_WritePin(DPinSer,DPin,GPIO_PIN_RESET);
    if (dir==-1)
        HAL_GPIO_WritePin(DPinSer,DPin,GPIO_PIN_SET);
}

void Change(){
    if(al==0||al*(sd-cs)<0)
    {
        cs=sd;
    }
    else 
    {
        while(fabs((float)(sd-cs))-fabs((float)al))
        {
            cs+=al;
            if(AMP)
                HAL_Delay(AMP);
        }
        cs=sd;
    }
}

