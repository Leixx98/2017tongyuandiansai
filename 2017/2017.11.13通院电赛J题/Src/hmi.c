#include "hmi.h"
#include "usart.h"

/***********adc档位为1k时发送的显示*******/
void HMISends_1_Amp(float Value,char *order)		  //字符串发送函数
{
    uint8_t i=0;
    uint8_t x='\"';
    uint8_t f=0xff;
    int temp;
    uint8_t Buffer[10];
    
    temp=Value*10;
    Buffer[0] = temp/10%10 + '0';
    Buffer[1] = '.';
    Buffer[2] = temp%10  + '0';
    Buffer[3] = 'V';
    while(order[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //发送一个字节
        i++;
    }
    i=0;
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //发送一个字节
    while(Buffer[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&Buffer[i],1, 0xffff); //发送一个字节
        i++;
    }
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //发送一个字节
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //发送一个字节
    }
}
/***********adc档位为10k时发送的显示*******/
void HMISends_2_Amp(float Value,char *order)		  //字符串发送函数
{
    uint8_t i=0;
    uint8_t x='\"';
    uint8_t f=0xff;
    int temp;
    uint8_t Buffer[10];
    
    temp=Value*100;
    Buffer[0] = temp/100 + '0';
    Buffer[1] = '.';
    Buffer[2] = temp/10%10  + '0';
    Buffer[3] = temp%10  + '0';
    Buffer[4] = 'V';
    while(order[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //发送一个字节
        i++;
    }
    i=0;
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //发送一个字节
    while(Buffer[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&Buffer[i],1, 0xffff); //发送一个字节
        i++;
    }
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //发送一个字节
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //发送一个字节
    }
}
/***********adc档位为100k时发送的显示*******/
void HMISends_3_Amp(float Value,char *order)		  //字符串发送函数
{
    uint8_t i=0;
    uint8_t x='\"';
    uint8_t f=0xff;
    int temp;
    uint8_t Buffer[10];
    
    temp = Value;
    Buffer[0] = temp/100%10 + '0';
    Buffer[1] = temp/10%10  + '0';
    Buffer[2] = temp%10  + '0';
    Buffer[3] = 'm';
    Buffer[4] = 'V';
    
    while(order[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //发送一个字节
        i++;
    }
    i=0;
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //发送一个字节
    while(Buffer[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&Buffer[i],1, 0xffff); //发送一个字节
        i++;
    }
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //发送一个字节
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //发送一个字节
    }
}
/***********显示频率值*******/
void HMISends_Fre(float Value,char *order)		  //字符串发送函数
{
    uint8_t i=0;
    uint8_t x='\"';
    uint8_t f=0xff;
    int temp;
    uint8_t Buffer[20];
    
    temp=Value*100;
    Buffer[0] = temp/100000%10 + '0';
    Buffer[1] = temp/10000%10 + '0';
    Buffer[2] = temp/1000%10  + '0';
    Buffer[3] = temp/100%10 + '0';
    Buffer[4] = '.';
    Buffer[5] = temp/10%10  + '0';
    Buffer[6] = temp/1%10  + '0';
    Buffer[7] = 'k';
    Buffer[8] = 'H';
    Buffer[9] = 'Z';
    
    while(order[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //发送一个字节
        i++;
    }
    i=0;
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //发送一个字节
    while(Buffer[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&Buffer[i],1, 0xffff); //发送一个字节
        i++;
    }
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //发送一个字节
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //发送一个字节
    }
}

/***********显示ADC档位*******/
void HMISends_ADCFre(uint8_t Key,char *order)		  //字符串发送函数
{
    uint8_t i=0;
    uint8_t x='\"';
    uint8_t f=0xff;
    uint8_t Buffer[20];
    
    if(Key == 1)               //不同的ADC设置对应不同的显示模式
    {
        Buffer[0] = '1';
        Buffer[1] = 'K';
        Buffer[2] = ' ';
        Buffer[3] = ' ';
        Buffer[4] = ' ';
    }
    else if(Key == 2)
    {
        Buffer[0] = '1';
        Buffer[1] = '0';
        Buffer[2] = 'K';
        Buffer[3] = ' ';
        Buffer[4] = ' ';
    }
    else if(Key == 3)
    {
        Buffer[0] = '1';
        Buffer[1] = '0';
        Buffer[2] = '0';
        Buffer[3] = 'K';
        Buffer[4] = ' ';
    }

    
    while(order[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //发送一个字节
        i++;
    }
    i=0;
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //发送一个字节
    while(Buffer[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&Buffer[i],1, 0xffff); //发送一个字节
        i++;
    }
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //发送一个字节
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //发送一个字节
    }
}
/***********显示当前量程*******/
void HMISends_Range(uint8_t Key,char *order)		  //字符串发送函数
{
    uint8_t i=0;
    uint8_t x='\"';
    uint8_t f=0xff;
    uint8_t Buffer[20];
    
    if(Key == 1)               //不同的ADC设置对应不同的显示模式
    {
        Buffer[0] = '1';
        Buffer[1] = '/';
        Buffer[2] = '1';
        Buffer[3] = '0';
        Buffer[4] = ' ';
    }
    else if(Key == 10)
    {
        Buffer[0] = '1';
        Buffer[1] = ' ';
        Buffer[2] = ' ';
        Buffer[3] = ' ';
        Buffer[4] = ' ';
    }
    else if(Key == 100)
    {
        Buffer[0] = '1';
        Buffer[1] = '0';
        Buffer[2] = ' ';
        Buffer[3] = ' ';
        Buffer[4] = ' ';
    }

    
    while(order[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //发送一个字节
        i++;
    }
    i=0;
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //发送一个字节
    while(Buffer[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&Buffer[i],1, 0xffff); //发送一个字节
        i++;
    }
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //发送一个字节
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //发送一个字节
    }
}


/***********发送幅频信号**********/
void HMISends_Ampfre(float Value,char *order)		  //字符串发送函数
{
    uint8_t i=0;
    uint8_t f=0xff;
    int temp;
    uint8_t Buffer[20];
    

    temp=Value*36;
    Buffer[0] = temp/10000%10 + '0';
    Buffer[1] = temp/1000%10 + '0';
    Buffer[2] = temp/100%10  + '0';

    

    while(order[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //发送一个字节
        i++;
    }
    i=0;
    while(Buffer[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&Buffer[i],1, 0xffff); //发送一个字节
        i++;
    }
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //发送一个字节
    }
    i=0;
    
}

/***********发送命令**********/
void HMISends_Order(char *order)		  //字符串发送函数
{
    uint8_t i=0;
    uint8_t f=0xff;

   
    while(order[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //发送一个字节
        i++;
    }
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //发送一个字节
    }
}

