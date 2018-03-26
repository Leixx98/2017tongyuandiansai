/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include "pga202.h"
#include "key.h"
#include "hmi.h"
#include "ad9959.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */
char order[10]= {"t0.txt="};
char order2[10] = {"t1.txt="};
char order3[10] = {"t2.txt="};
char order4[10] = {"t3.txt="};
char order5[10] = {"add 1,0,"};
/* USER CODE BEGIN 0 */
uint8_t UART1_RxBuffer;                           //����1���ջ���
uint8_t UART2_RxBuffer;                           //����2���ջ���
uint8_t UART3_RxBuffer;                            //����3���ջ���
uint8_t UART1_RxKey;                              //����1����ֵ��Ӧ���ܼ�ֵ
uint8_t UART2_RxKey;                              //����2����ֵ��Ӧ���ܼ�ֵ

uint8_t PGA202_Status;                            //PGA202�Ŵ���

float    ADC_Ampli;                           //�źŷ���ֵ
uint16_t ADC_Value;                           //ADCÿ�β����õ��ĵ�ѹֵ
uint8_t  ADC_Count;                          //ADC�����Ĵ���
uint8_t  ADC_Gears = 1;                          //ADC��ǰ��λ

uint8_t  AMPFRE_Start;                     //��ʼ������Ƶ����

uint32_t AD9959_FRE;                    //AD9959Ƶ������
uint32_t AD9959_AMP;                    //AD9959��������

uint8_t     TIM4CH1_CAPTURE_STA=0;		//���벶��״̬		    				
uint32_t	TIM1_COUNTER_VAL[100];	        //��ʱ��1������
uint32_t    TIM2_COUNTER_VAL[100];          //��ʱ��2������
float	    TIM1_COUNTER_Val;	            //��ʱ��1����ֵ
float       TIM2_COUNTER_Val;               //��ʱ��2����ֵ
float       TIM_FREQ;                       //Ƶ��ֵ
uint8_t     TIM4CH1_CAPTURE_GATE=0;         //Ԥ��բ�ű�־λ
uint8_t     TIM4CH1_CAPTURE_STB=0;          //���������־λ
static uint8_t     i;                       //������
uint32_t	TIM1_COUNTER_TEMP;	            //��ʱ��1�����˲�
uint32_t    TIM2_COUNTER_TEMP;              //��ʱ��2�����˲�



/**
  * ��������: ASCII��תʮ����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
uint8_t hextoten(uint8_t hex)
{
    uint8_t ten;
    ten = hex - 96;
    return ten;
}    
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
  uint8_t i;                                    //forѭ����
  AD9959_FRE = 100000;                          //AD9959��ʼƵ������Ϊ100kHZ
  AD9959_AMP = 500;                             //AD9959��ʼ��������250mV
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM6_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  Pga202_Init();                                   //PGA202���ƽų�ʼ��
  Init_AD9959();                  //9959��ʼ��


  /* USER CODE BEGIN 2 */
  HAL_ADC_Start_IT(&hadc1);                           //ʹ��ADC�ж�
  HAL_TIM_Base_Start(&htim6);                         //����TIM6������ADC����
  HAL_UART_Receive_IT(&huart1,&UART1_RxBuffer,1);     //���������жϣ�UART1��
  HAL_UART_Receive_IT(&huart2,&UART2_RxBuffer,1);     //���������жϣ�UART2��
  HMISends_ADCFre(1,order3);		  //�ַ������ͺ���
  Pga202_1_multiple();                                             //PGA202�Ŵ�1��������ADC   
  Write_Amplitude(1, AD9959_AMP);
  Write_frequence(1,AD9959_FRE); 
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */  
    
    while(ADC_Count)                                   //ADC�����
    {
        if(ADC_Count > 15)                           //ADC���������ﵽһ�ٴκ������ֵ���رն�ʱ����ֹͣ����
        {
            HAL_TIM_Base_Stop(&htim6);                 //�رն�ʱ��            
            ADC_Count =0; 
            if(PGA202_Status == 1)   ADC_Ampli *= 10;    //PGA202Ϊ1���Ŵ�ʱ���ź�˥��10�����ڳ����н��в���
            if(PGA202_Status == 10)  ADC_Ampli *= 1;     //PGA202Ϊ10���Ŵ�ʱ���źŲ�˥���� ������
            if(PGA202_Status == 100) ADC_Ampli *= 100;    //PGA202Ϊ100���Ŵ�ʱ���źŷŴ�10�����ڳ����н��в���
           
            ADC_Ampli = (float) ADC_Ampli * (6.6f/4096);
           

            if(PGA202_Status == 1)    
            {
                printf("Ampli:%.1fV\r\n",ADC_Ampli);            //�������ֵ
                HMISends_1_Amp(ADC_Ampli,order);                //����������ʾ��ֵ
                HMISends_ADCFre(ADC_Gears,order3);               //����������ʾADC��ǰ��λ
                HMISends_Range(PGA202_Status,order4);		    //�ڴ���������ʾ��ǰ����
            }
            if(PGA202_Status == 10) 
            {
                printf("Ampli:%.2fV\r\n",ADC_Ampli);            //�������ֵ
                HMISends_2_Amp(ADC_Ampli,order);                //����������ʾ��ֵ
                HMISends_ADCFre(ADC_Gears,order3);               //����������ʾADC��ǰ��λ
                HMISends_Range(PGA202_Status,order4);		    //�ڴ���������ʾ��ǰ����
            }
            if(PGA202_Status == 100)  
            {
                if(!AMPFRE_Start)
                {
                    printf("Ampli:%.1fmV\r\n",ADC_Ampli);            //�������ֵ
                    HMISends_3_Amp(ADC_Ampli,order);               //����������ʾ��ֵ
                    HMISends_ADCFre(ADC_Gears,order3);               //����������ʾADC��ǰ��λ
                    HMISends_Range(PGA202_Status,order4);		    //�ڴ���������ʾ��ǰ����
                }
                else
                {
                    if(ADC_Ampli > 5)                                   //��ֹ���ִ�Ľ�Ծ
                    {    
                        printf("Ampli:%.1fmV\r\n",ADC_Ampli);            //�������ֵ
                        for(i=0;i<4;i++)
                            HMISends_Ampfre(ADC_Ampli,order5);              //���ͷ�Ƶ�ź�
                    }
                    else
                        AD9959_FRE -= 1000;                             //���ֽ�Ծ�󣬶�Ƶ�ʽ��в���
                }
            }
            
            ADC_Ampli = 0;                                   //ADC��������ֵ��0
/***************************��ʼ����Ƶ��*******************************************/            
            HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_1); //ʹ��TIM4���벶���ж�
            __HAL_TIM_ENABLE_IT(&htim4, TIM_CHANNEL_1); //ʹ�ܸ����ж�
            HAL_TIM_Base_Start_IT(&htim5);             //ʹ��TIM5��ʱ���ж�

            
            __HAL_TIM_SET_COUNTER(&htim1,0);      //��ʱ��1����
            __HAL_TIM_SET_COUNTER(&htim2,0);      //��ʱ��2���� 
            
            TIM4CH1_CAPTURE_STA=0x80;
            TIM4CH1_CAPTURE_GATE = 1;                   //����Ԥ��բ��
        }
    }
    
    while(TIM4CH1_CAPTURE_STA)                     //����Ƶ��
    {
        if(TIM4CH1_CAPTURE_STB)
        {
            TIM1_COUNTER_Val = (float) TIM1_COUNTER_TEMP / 100;              //�����˲�
            TIM2_COUNTER_Val = (float) TIM2_COUNTER_TEMP / 100;              //�����˲�
            TIM_FREQ = (TIM2_COUNTER_Val*2020.0f)/TIM1_COUNTER_Val;           //����Ƶ��
            
            printf("FREQ:%.2fKHZ\r\n",TIM_FREQ);                             //���Ƶ��
            HMISends_Fre(TIM_FREQ,order2);               //����������ʾ��ֵ
            
            if(AMPFRE_Start)
            {
               AD9959_FRE += 1000; 
               Write_frequence(1,AD9959_FRE);
               if(AD9959_FRE > 200000)                  //Ƶ�ʴﵽ400k����һ�η�Ƶ����ͼ�Ѿ�����
                    AMPFRE_Start = 0;
            }
            
            TIM1_COUNTER_TEMP = 0;                                           //�������
            TIM2_COUNTER_TEMP = 0;                                            //�������
            TIM4CH1_CAPTURE_STB = 0;                                         //�ر�Ƶ�����
            TIM4CH1_CAPTURE_STA = 0;                                         //�ر�Ƶ�ʲ���

/*************************************���Ȳ���*****************************/            
            
            HAL_TIM_Base_Start(&htim6);                                      //�������Ȳ��� 
        }
        
     

    
    }
    

    
    
    
  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = 7;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_USART3;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
/**
  * ��������: �ض���c�⺯��printf��DEBUG_USARTx
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch ,1, 0xffff);
    
    return ch;
}

/**
  * ��������: ADC��������жϻص�����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  /* Get the converted value of regular channel */
  ADC_Value = HAL_ADC_GetValue(hadc);         //�õ�ADC������ֵ  
  if(ADC_Value > ADC_Ampli && ADC_Value < 4095) ADC_Ampli = ADC_Value;           //�뵱ǰ����ֵ���бȽϣ�ȷ���Ƿ���·���ֵ
  ADC_Count++;        //����������1
}

/**
  * ��������: ��ʱ��TIM5����жϴ���ص�������Ƶ�ʲ���
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//�����жϷ���ʱִ��
{	 
                if(TIM4CH1_CAPTURE_GATE==0)
                {   
                  if(TIM4CH1_CAPTURE_STA&0X40)	//�ڶ��β���һ�������� 		
                  {	                      
                    TIM4CH1_CAPTURE_STA = 0X80;		//��ǳɹ�����һ�θߵ�ƽ����
                    TIM1_COUNTER_VAL[i] = __HAL_TIM_GET_COUNTER(&htim1); //��ö�ʱ��1����ֵ
                    TIM2_COUNTER_VAL[i] = __HAL_TIM_GET_COUNTER(&htim2); //��ö�ʱ��2����ֵ
                   
                    TIM1_COUNTER_TEMP += TIM1_COUNTER_VAL[i];
                    TIM2_COUNTER_TEMP += TIM2_COUNTER_VAL[i];

                    i++;
                        if(i == 100)
                        {                        
                            i = 0;
                            TIM4CH1_CAPTURE_STB = 1;
                            HAL_TIM_IC_Stop_IT(&htim4,TIM_CHANNEL_1);
                        }
                    
                    
                    HAL_TIM_Base_Stop(&htim1);            //�رն�ʱ��1
                    HAL_TIM_Base_Stop(&htim2);            //�رն�ʱ��2   
                    __HAL_TIM_SET_COUNTER(&htim1,0);      //��ʱ��1����
                    __HAL_TIM_SET_COUNTER(&htim2,0);      //��ʱ��2����                

                }
                

			}
                if(TIM4CH1_CAPTURE_GATE==1)
                {
                    if(TIM4CH1_CAPTURE_STA&0X80)//��һ�β���������
			    {
                    TIM4CH1_CAPTURE_STA = 0X40;		//��ǲ�����������
                    HAL_TIM_Base_Start(&htim1);     //ʹ�ܶ�ʱ��1���Ա�׼�źż���
                    HAL_TIM_Base_Start(&htim2);     //ʹ�ܶ�ʱ��2���Ա����źż���
                }
			}		    
		
}
/**
  * ��������: ��ʱ��TIM1�жϻص��������ı�Ԥ��բ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(TIM5 == htim->Instance)
    {
        HAL_UART_Receive_IT(&huart1,&UART1_RxBuffer,1);           //�ٴο��������жϣ�����һ���жϺ����ý����ٽ����жϣ�
        HAL_UART_Receive_IT(&huart2,&UART2_RxBuffer,1);
       if(TIM4CH1_CAPTURE_GATE)
       {
            TIM4CH1_CAPTURE_GATE = 0;
       }
       else 
       {
            TIM4CH1_CAPTURE_GATE = 1;
       }
    }
} 

/**
  * ��������: ���ڽ�����ɻص�����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart==&huart1)
  {
    UART1_RxKey = UART1_RxBuffer;
    Key_Settle(UART1_RxKey);                           //������Ӧ��������
  }
  
  if(huart==&huart2)
 {
    UART2_RxKey = UART2_RxBuffer;
    UART2_RxKey = hextoten(UART2_RxKey);            //ascii��תΪʮ����
    UART1_RxKey = UART2_RxKey;
    Key_Settle(UART1_RxKey);                           //������Ӧ��������
  }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
