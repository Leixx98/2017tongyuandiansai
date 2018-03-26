#include "key.h"
#include "pga202.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "ad9959.h"
#include "hmi.h"

/**********��������***********/
extern uint8_t  ADC_Count;                          //ADC�����Ĵ���
extern uint8_t  ADC_Gears;
extern uint32_t AD9959_FRE;                    //AD9959Ƶ������
extern uint32_t AD9959_AMP;                    //AD9959��������
extern uint8_t  AMPFRE_Start;                     //��ʼ������Ƶ����
/**********��������*********/
char order_cle[10]={"cle 1,0"};

void Key_Settle(uint8_t key)
{

    
    
    switch(key)
    {
           case 1:                       //���ܣ�ADC  1K��
                TIM6->ARR = 1009;
                ADC_Gears = 1;
                break;
           
           case 2:
                TIM6->ARR = 99;         //���ܣ� ADC  10K��
                ADC_Gears = 2;
                break;  
           case 3:
                TIM6->ARR = 9;          //���ܣ�  ADC  100K��
                ADC_Gears = 3; 
                break;
           case 4:                       //���� ��DAC Ƶ+
                key -= 2;
                HAL_UART_Transmit(&huart3, (uint8_t*)&key ,1, 0xffff);
                break;
           
           case 5:                       //���� ��DAC  Ƶ-
                key -= 4;
                HAL_UART_Transmit(&huart3, (uint8_t*)&key ,1, 0xffff);
                break;
           
           case 6:                           //���ܣ�PGA202  1����
               Pga202_1_multiple();              //PGA202 1����
               ADC_Count = 0;                    //���²��� 
               if (HAL_TIM_Base_Stop(&htim6) == HAL_OK) //����ʱ��ʱ��6�رգ�˵����ʱ����ADC����״̬���ٴο�����ʱ��6
               {
                   HAL_TIM_Base_Start(&htim6);
               }
               break;
       
           case 7:                            //���ܣ�PGA202  10����
               Pga202_10_multiple();              //PGA202 10����
               ADC_Count = 0;                    //���²���  
               if (HAL_TIM_Base_Stop(&htim6) == HAL_OK) //����ʱ��ʱ��6�رգ�˵����ʱ����ADC����״̬���ٴο�����ʱ��6
               {
                   HAL_TIM_Base_Start(&htim6);
               }
               break;
           
           case 8:                            //���ܣ�PGA202  100����
               Pga202_100_multiple();              //PGA202 100����
               ADC_Count = 0;                    //���²��� 
               if (HAL_TIM_Base_Stop(&htim6) == HAL_OK) //����ʱ��ʱ��6�رգ�˵����ʱ����ADC����״̬���ٴο�����ʱ��6
               {
                   HAL_TIM_Base_Start(&htim6);
               }
               break;
           case 9:                            //���ܣ�AD9959Ƶ��+50k
               AD9959_FRE += 50000;      
               Write_frequence(1,AD9959_FRE);    
               break;
           
           case 10:                           //���ܣ�AD9959Ƶ��-50k
               AD9959_FRE -= 50000;
               Write_frequence(1,AD9959_FRE);
               break; 
           
           case 11:                           //���ܣ�AD9959����+50
               AD9959_AMP += 100;    
               Write_Amplitude(1, AD9959_AMP);
               break;
           
           case 12:
               AD9959_AMP -= 100;             //���ܣ�AD9959����-50
               Write_Amplitude(1, AD9959_AMP);
               break;
           case 13:                           //���ܣ���ʼ������Ƶ����
               AMPFRE_Start = 1;
               TIM6->ARR = 3;                  //���  ADC  ����Ƶ��
               HMISends_Order(order_cle);	  //�����һ�������ķ�Ƶ��������ͼ
               AD9959_FRE = 1000;            //��ʼƵ������Ϊ1k
               AD9959_AMP = 800;             //AD9959��ʼ��������400mV
               Write_frequence(1,AD9959_FRE);
               Write_Amplitude(1,AD9959_AMP);
               break;
           case 14:                           //���ܣ�ֹͣ������Ƶ����
               AMPFRE_Start = 0; 
               TIM6->ARR = 9;                  //�ָ�100k������
               Write_frequence(1,AD9959_FRE);
               Write_Amplitude(1,AD9959_AMP);
               break;
    }
}

