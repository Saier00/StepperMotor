#ifndef __SM_CONTROL_H_
#define __SM_CONTROL_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "math.h"
#include "usbd_cdc_if.h"
#include "usb_device.h"
#include "main.h"
//COMMANDS:
//Left rotation
extern void DL(void);
//Right rotation
extern void DR(void);
//Reverse
extern void RS(void);
//Set acceleration
extern void AL(int16_t);
//Set speed
extern void SD(int16_t);
//Set start speed
extern void SS(int16_t);
//Turn on motor + continuous motion
extern void MV(void);
//Make x steps
extern void MVX(uint32_t);
//Continuous motion till recieving [some signal 1]
extern void MH(void);
//Continuous motion till recieving [some signal 2]
extern void ML(void);
//Continuous motion till recieving [some signal 3] with changable speed (by SD)
extern void HM(void);
//Stop for x ms
extern void SP(uint32_t);
//Wait for [some signal 1]
extern void WL(void);
//Wait for [some signal 2]
extern void WH(void);

//Direct control functions
//Turn on motor + continuous motion
extern void MVdc(void);
//Make x steps
extern void MVXdc(uint32_t);
//Continuous motion till recieving [some signal 1]
extern void MHdc(void);
//Continuous motion till recieving [some signal 2]
extern void MLdc(void);
//Continuous motion till recieving [some signal 3] with changable speed (by SD)
extern void HMdc(void);
//Stop for x ms
extern void SPdc(uint32_t);
//Wait for [some signal 1]
extern void WLdc(void);
//Wait for [some signal 2]
extern void WHdc(void);

#ifdef __cplusplus
}
#endif

#endif /*__SM_CONTROL_H_*/
