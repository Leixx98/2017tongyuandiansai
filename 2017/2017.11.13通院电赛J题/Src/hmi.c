#include "hmi.h"
#include "usart.h"

/***********adc��λΪ1kʱ���͵���ʾ*******/
void HMISends_1_Amp(float Value,char *order)		  //�ַ������ͺ���
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
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //����һ���ֽ�
        i++;
    }
    i=0;
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //����һ���ֽ�
    while(Buffer[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&Buffer[i],1, 0xffff); //����һ���ֽ�
        i++;
    }
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //����һ���ֽ�
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //����һ���ֽ�
    }
}
/***********adc��λΪ10kʱ���͵���ʾ*******/
void HMISends_2_Amp(float Value,char *order)		  //�ַ������ͺ���
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
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //����һ���ֽ�
        i++;
    }
    i=0;
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //����һ���ֽ�
    while(Buffer[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&Buffer[i],1, 0xffff); //����һ���ֽ�
        i++;
    }
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //����һ���ֽ�
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //����һ���ֽ�
    }
}
/***********adc��λΪ100kʱ���͵���ʾ*******/
void HMISends_3_Amp(float Value,char *order)		  //�ַ������ͺ���
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
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //����һ���ֽ�
        i++;
    }
    i=0;
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //����һ���ֽ�
    while(Buffer[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&Buffer[i],1, 0xffff); //����һ���ֽ�
        i++;
    }
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //����һ���ֽ�
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //����һ���ֽ�
    }
}
/***********��ʾƵ��ֵ*******/
void HMISends_Fre(float Value,char *order)		  //�ַ������ͺ���
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
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //����һ���ֽ�
        i++;
    }
    i=0;
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //����һ���ֽ�
    while(Buffer[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&Buffer[i],1, 0xffff); //����һ���ֽ�
        i++;
    }
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //����һ���ֽ�
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //����һ���ֽ�
    }
}

/***********��ʾADC��λ*******/
void HMISends_ADCFre(uint8_t Key,char *order)		  //�ַ������ͺ���
{
    uint8_t i=0;
    uint8_t x='\"';
    uint8_t f=0xff;
    uint8_t Buffer[20];
    
    if(Key == 1)               //��ͬ��ADC���ö�Ӧ��ͬ����ʾģʽ
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
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //����һ���ֽ�
        i++;
    }
    i=0;
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //����һ���ֽ�
    while(Buffer[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&Buffer[i],1, 0xffff); //����һ���ֽ�
        i++;
    }
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //����һ���ֽ�
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //����һ���ֽ�
    }
}
/***********��ʾ��ǰ����*******/
void HMISends_Range(uint8_t Key,char *order)		  //�ַ������ͺ���
{
    uint8_t i=0;
    uint8_t x='\"';
    uint8_t f=0xff;
    uint8_t Buffer[20];
    
    if(Key == 1)               //��ͬ��ADC���ö�Ӧ��ͬ����ʾģʽ
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
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //����һ���ֽ�
        i++;
    }
    i=0;
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //����һ���ֽ�
    while(Buffer[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&Buffer[i],1, 0xffff); //����һ���ֽ�
        i++;
    }
    HAL_UART_Transmit(&huart2,(uint8_t*)&x,1, 0xffff); //����һ���ֽ�
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //����һ���ֽ�
    }
}


/***********���ͷ�Ƶ�ź�**********/
void HMISends_Ampfre(float Value,char *order)		  //�ַ������ͺ���
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
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //����һ���ֽ�
        i++;
    }
    i=0;
    while(Buffer[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&Buffer[i],1, 0xffff); //����һ���ֽ�
        i++;
    }
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //����һ���ֽ�
    }
    i=0;
    
}

/***********��������**********/
void HMISends_Order(char *order)		  //�ַ������ͺ���
{
    uint8_t i=0;
    uint8_t f=0xff;

   
    while(order[i]!='\0')
    {
        HAL_UART_Transmit(&huart2,(uint8_t*)&order[i],1, 0xffff); //����һ���ֽ�
        i++;
    }
    for(i=0;i<3;i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t*)&f,1, 0xffff); //����һ���ֽ�
    }
}

