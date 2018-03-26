#include "key.h"
#include "pga202.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "ad9959.h"
#include "hmi.h"

/**********变量声明***********/
extern uint8_t  ADC_Count;                          //ADC采样的次数
extern uint8_t  ADC_Gears;
extern uint32_t AD9959_FRE;                    //AD9959频率设置
extern uint32_t AD9959_AMP;                    //AD9959幅度设置
extern uint8_t  AMPFRE_Start;                     //开始测量幅频特性
/**********数组声明*********/
char order_cle[10]={"cle 1,0"};

void Key_Settle(uint8_t key)
{

    
    
    switch(key)
    {
           case 1:                       //功能：ADC  1K挡
                TIM6->ARR = 1009;
                ADC_Gears = 1;
                break;
           
           case 2:
                TIM6->ARR = 99;         //功能： ADC  10K挡
                ADC_Gears = 2;
                break;  
           case 3:
                TIM6->ARR = 9;          //功能：  ADC  100K挡
                ADC_Gears = 3; 
                break;
           case 4:                       //功能 ：DAC 频+
                key -= 2;
                HAL_UART_Transmit(&huart3, (uint8_t*)&key ,1, 0xffff);
                break;
           
           case 5:                       //功能 ：DAC  频-
                key -= 4;
                HAL_UART_Transmit(&huart3, (uint8_t*)&key ,1, 0xffff);
                break;
           
           case 6:                           //功能：PGA202  1倍挡
               Pga202_1_multiple();              //PGA202 1倍挡
               ADC_Count = 0;                    //重新采样 
               if (HAL_TIM_Base_Stop(&htim6) == HAL_OK) //若此时定时器6关闭，说明此时处于ADC保护状态，再次开启定时器6
               {
                   HAL_TIM_Base_Start(&htim6);
               }
               break;
       
           case 7:                            //功能：PGA202  10倍挡
               Pga202_10_multiple();              //PGA202 10倍挡
               ADC_Count = 0;                    //重新采样  
               if (HAL_TIM_Base_Stop(&htim6) == HAL_OK) //若此时定时器6关闭，说明此时处于ADC保护状态，再次开启定时器6
               {
                   HAL_TIM_Base_Start(&htim6);
               }
               break;
           
           case 8:                            //功能：PGA202  100倍挡
               Pga202_100_multiple();              //PGA202 100倍挡
               ADC_Count = 0;                    //重新采样 
               if (HAL_TIM_Base_Stop(&htim6) == HAL_OK) //若此时定时器6关闭，说明此时处于ADC保护状态，再次开启定时器6
               {
                   HAL_TIM_Base_Start(&htim6);
               }
               break;
           case 9:                            //功能：AD9959频率+50k
               AD9959_FRE += 50000;      
               Write_frequence(1,AD9959_FRE);    
               break;
           
           case 10:                           //功能：AD9959频率-50k
               AD9959_FRE -= 50000;
               Write_frequence(1,AD9959_FRE);
               break; 
           
           case 11:                           //功能：AD9959幅度+50
               AD9959_AMP += 100;    
               Write_Amplitude(1, AD9959_AMP);
               break;
           
           case 12:
               AD9959_AMP -= 100;             //功能：AD9959幅度-50
               Write_Amplitude(1, AD9959_AMP);
               break;
           case 13:                           //功能：开始测量幅频特性
               AMPFRE_Start = 1;
               TIM6->ARR = 3;                  //提高  ADC  采样频率
               HMISends_Order(order_cle);	  //清除上一次所画的幅频特性曲线图
               AD9959_FRE = 1000;            //初始频率设置为1k
               AD9959_AMP = 800;             //AD9959初始幅度设置400mV
               Write_frequence(1,AD9959_FRE);
               Write_Amplitude(1,AD9959_AMP);
               break;
           case 14:                           //功能：停止测量幅频特性
               AMPFRE_Start = 0; 
               TIM6->ARR = 9;                  //恢复100k采样率
               Write_frequence(1,AD9959_FRE);
               Write_Amplitude(1,AD9959_AMP);
               break;
    }
}

