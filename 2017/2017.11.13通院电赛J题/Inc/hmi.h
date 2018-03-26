#ifndef __HMI_H
#define __HMI_H 		

#include "stm32f7xx_hal.h"



void HMISends_1_Amp(float Value,char *order);
void HMISends_2_Amp(float Value,char *order);
void HMISends_3_Amp(float Value,char *order);
void HMISends_Fre(float Value,char *order);
extern void HMISends_ADCFre(uint8_t Key,char *order);		  //×Ö·û´®·¢ËÍº¯Êý
extern void HMISends_Range(uint8_t Key,char *order);		  //×Ö·û´®·¢ËÍº¯Êý
extern void HMISends_Ampfre(float Value,char *order);		  //×Ö·û´®·¢ËÍº¯Êý
extern void HMISends_Order(char *order);		                      //×Ö·û´®·¢ËÍº¯Êý


#endif





























