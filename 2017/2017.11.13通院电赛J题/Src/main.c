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
uint8_t UART1_RxBuffer;                           //串口1接收缓存
uint8_t UART2_RxBuffer;                           //串口2接收缓存
uint8_t UART3_RxBuffer;                            //串口3接收缓存
uint8_t UART1_RxKey;                              //串口1接受值对应功能键值
uint8_t UART2_RxKey;                              //串口2接受值对应功能键值

uint8_t PGA202_Status;                            //PGA202放大倍数

float    ADC_Ampli;                           //信号幅度值
uint16_t ADC_Value;                           //ADC每次采样得到的电压值
uint8_t  ADC_Count;                          //ADC采样的次数
uint8_t  ADC_Gears = 1;                          //ADC当前档位

uint8_t  AMPFRE_Start;                     //开始测量幅频特性

uint32_t AD9959_FRE;                    //AD9959频率设置
uint32_t AD9959_AMP;                    //AD9959幅度设置

uint8_t     TIM4CH1_CAPTURE_STA=0;		//输入捕获状态		    				
uint32_t	TIM1_COUNTER_VAL[100];	        //定时器1计数组
uint32_t    TIM2_COUNTER_VAL[100];          //定时器2计数组
float	    TIM1_COUNTER_Val;	            //定时器1计数值
float       TIM2_COUNTER_Val;               //定时器2计数值
float       TIM_FREQ;                       //频率值
uint8_t     TIM4CH1_CAPTURE_GATE=0;         //预设闸门标志位
uint8_t     TIM4CH1_CAPTURE_STB=0;          //数组存满标志位
static uint8_t     i;                       //数组用
uint32_t	TIM1_COUNTER_TEMP;	            //定时器1计数滤波
uint32_t    TIM2_COUNTER_TEMP;              //定时器2计数滤波



/**
  * 函数功能: ASCII码转十进制
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
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
  uint8_t i;                                    //for循环用
  AD9959_FRE = 100000;                          //AD9959初始频率设置为100kHZ
  AD9959_AMP = 500;                             //AD9959初始幅度设置250mV
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
  Pga202_Init();                                   //PGA202控制脚初始化
  Init_AD9959();                  //9959初始化


  /* USER CODE BEGIN 2 */
  HAL_ADC_Start_IT(&hadc1);                           //使能ADC中断
  HAL_TIM_Base_Start(&htim6);                         //开启TIM6，启动ADC采样
  HAL_UART_Receive_IT(&huart1,&UART1_RxBuffer,1);     //开启接收中断（UART1）
  HAL_UART_Receive_IT(&huart2,&UART2_RxBuffer,1);     //开启接收中断（UART2）
  HMISends_ADCFre(1,order3);		  //字符串发送函数
  Pga202_1_multiple();                                             //PGA202放大1倍，保护ADC   
  Write_Amplitude(1, AD9959_AMP);
  Write_frequence(1,AD9959_FRE); 
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */  
    
    while(ADC_Count)                                   //ADC测幅度
    {
        if(ADC_Count > 15)                           //ADC采样次数达到一百次后，输出幅值，关闭定时器，停止采样
        {
            HAL_TIM_Base_Stop(&htim6);                 //关闭定时器            
            ADC_Count =0; 
            if(PGA202_Status == 1)   ADC_Ampli *= 10;    //PGA202为1倍放大时，信号衰减10倍，在程序中进行补偿
            if(PGA202_Status == 10)  ADC_Ampli *= 1;     //PGA202为10倍放大时，信号不衰减， 不补偿
            if(PGA202_Status == 100) ADC_Ampli *= 100;    //PGA202为100倍放大时，信号放大10倍，在程序中进行补偿
           
            ADC_Ampli = (float) ADC_Ampli * (6.6f/4096);
           

            if(PGA202_Status == 1)    
            {
                printf("Ampli:%.1fV\r\n",ADC_Ampli);            //输出幅度值
                HMISends_1_Amp(ADC_Ampli,order);                //串口屏上显示数值
                HMISends_ADCFre(ADC_Gears,order3);               //串口屏上显示ADC当前档位
                HMISends_Range(PGA202_Status,order4);		    //在串口屏上显示当前量程
            }
            if(PGA202_Status == 10) 
            {
                printf("Ampli:%.2fV\r\n",ADC_Ampli);            //输出幅度值
                HMISends_2_Amp(ADC_Ampli,order);                //串口屏上显示数值
                HMISends_ADCFre(ADC_Gears,order3);               //串口屏上显示ADC当前档位
                HMISends_Range(PGA202_Status,order4);		    //在串口屏上显示当前量程
            }
            if(PGA202_Status == 100)  
            {
                if(!AMPFRE_Start)
                {
                    printf("Ampli:%.1fmV\r\n",ADC_Ampli);            //输出幅度值
                    HMISends_3_Amp(ADC_Ampli,order);               //串口屏上显示数值
                    HMISends_ADCFre(ADC_Gears,order3);               //串口屏上显示ADC当前档位
                    HMISends_Range(PGA202_Status,order4);		    //在串口屏上显示当前量程
                }
                else
                {
                    if(ADC_Ampli > 5)                                   //防止出现大的阶跃
                    {    
                        printf("Ampli:%.1fmV\r\n",ADC_Ampli);            //输出幅度值
                        for(i=0;i<4;i++)
                            HMISends_Ampfre(ADC_Ampli,order5);              //发送幅频信号
                    }
                    else
                        AD9959_FRE -= 1000;                             //出现阶跃后，对频率进行补偿
                }
            }
            
            ADC_Ampli = 0;                                   //ADC测量幅度值清0
/***************************开始测量频率*******************************************/            
            HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_1); //使能TIM4输入捕获中断
            __HAL_TIM_ENABLE_IT(&htim4, TIM_CHANNEL_1); //使能更新中断
            HAL_TIM_Base_Start_IT(&htim5);             //使能TIM5定时器中断

            
            __HAL_TIM_SET_COUNTER(&htim1,0);      //定时器1清零
            __HAL_TIM_SET_COUNTER(&htim2,0);      //定时器2清零 
            
            TIM4CH1_CAPTURE_STA=0x80;
            TIM4CH1_CAPTURE_GATE = 1;                   //开启预设闸门
        }
    }
    
    while(TIM4CH1_CAPTURE_STA)                     //测量频率
    {
        if(TIM4CH1_CAPTURE_STB)
        {
            TIM1_COUNTER_Val = (float) TIM1_COUNTER_TEMP / 100;              //数组滤波
            TIM2_COUNTER_Val = (float) TIM2_COUNTER_TEMP / 100;              //数组滤波
            TIM_FREQ = (TIM2_COUNTER_Val*2020.0f)/TIM1_COUNTER_Val;           //计算频率
            
            printf("FREQ:%.2fKHZ\r\n",TIM_FREQ);                             //输出频率
            HMISends_Fre(TIM_FREQ,order2);               //串口屏上显示数值
            
            if(AMPFRE_Start)
            {
               AD9959_FRE += 1000; 
               Write_frequence(1,AD9959_FRE);
               if(AD9959_FRE > 200000)                  //频率达到400k，则一次幅频特性图已经画完
                    AMPFRE_Start = 0;
            }
            
            TIM1_COUNTER_TEMP = 0;                                           //清除缓存
            TIM2_COUNTER_TEMP = 0;                                            //清除缓存
            TIM4CH1_CAPTURE_STB = 0;                                         //关闭频率输出
            TIM4CH1_CAPTURE_STA = 0;                                         //关闭频率测量

/*************************************幅度测量*****************************/            
            
            HAL_TIM_Base_Start(&htim6);                                      //开启幅度测量 
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
  * 函数功能: 重定向c库函数printf到DEBUG_USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch ,1, 0xffff);
    
    return ch;
}

/**
  * 函数功能: ADC采样完成中断回调函数
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  /* Get the converted value of regular channel */
  ADC_Value = HAL_ADC_GetValue(hadc);         //得到ADC采样的值  
  if(ADC_Value > ADC_Ampli && ADC_Value < 4095) ADC_Ampli = ADC_Value;           //与当前幅度值进行比较，确定是否更新幅度值
  ADC_Count++;        //采样次数加1
}

/**
  * 函数功能: 定时器TIM5溢出中断处理回调函数，频率测量
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//捕获中断发生时执行
{	 
                if(TIM4CH1_CAPTURE_GATE==0)
                {   
                  if(TIM4CH1_CAPTURE_STA&0X40)	//第二次捕获到一个上升沿 		
                  {	                      
                    TIM4CH1_CAPTURE_STA = 0X80;		//标记成功捕获到一次高电平脉宽
                    TIM1_COUNTER_VAL[i] = __HAL_TIM_GET_COUNTER(&htim1); //获得定时器1计数值
                    TIM2_COUNTER_VAL[i] = __HAL_TIM_GET_COUNTER(&htim2); //获得定时器2计数值
                   
                    TIM1_COUNTER_TEMP += TIM1_COUNTER_VAL[i];
                    TIM2_COUNTER_TEMP += TIM2_COUNTER_VAL[i];

                    i++;
                        if(i == 100)
                        {                        
                            i = 0;
                            TIM4CH1_CAPTURE_STB = 1;
                            HAL_TIM_IC_Stop_IT(&htim4,TIM_CHANNEL_1);
                        }
                    
                    
                    HAL_TIM_Base_Stop(&htim1);            //关闭定时器1
                    HAL_TIM_Base_Stop(&htim2);            //关闭定时器2   
                    __HAL_TIM_SET_COUNTER(&htim1,0);      //定时器1清零
                    __HAL_TIM_SET_COUNTER(&htim2,0);      //定时器2清零                

                }
                

			}
                if(TIM4CH1_CAPTURE_GATE==1)
                {
                    if(TIM4CH1_CAPTURE_STA&0X80)//第一次捕获上升沿
			    {
                    TIM4CH1_CAPTURE_STA = 0X40;		//标记捕获到了上升沿
                    HAL_TIM_Base_Start(&htim1);     //使能定时器1，对标准信号计数
                    HAL_TIM_Base_Start(&htim2);     //使能定时器2，对被测信号计数
                }
			}		    
		
}
/**
  * 函数功能: 定时器TIM1中断回调参数，改变预置闸门
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(TIM5 == htim->Instance)
    {
        HAL_UART_Receive_IT(&huart1,&UART1_RxBuffer,1);           //再次开启串口中断（进入一次中断后不重置将不再进入中断）
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
  * 函数功能: 串口接收完成回调函数
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart==&huart1)
  {
    UART1_RxKey = UART1_RxBuffer;
    Key_Settle(UART1_RxKey);                           //按键对应功能设置
  }
  
  if(huart==&huart2)
 {
    UART2_RxKey = UART2_RxBuffer;
    UART2_RxKey = hextoten(UART2_RxKey);            //ascii码转为十进制
    UART1_RxKey = UART2_RxKey;
    Key_Settle(UART1_RxKey);                           //按键对应功能设置
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
