#include "pga202.h"
#include "gpio.h"
#include "hmi.h"
/***********************************
PGA202����ģʽ��
PB3��Ӧ���ƶ�0��PB4��Ӧ���ƶ�1
1����0�ˣ�0��1�ˣ�0�� 
10����0�ˣ�1��1�ˣ�0��
100����0�ˣ�0��1�ˣ�1��
1000����0�ˣ�1��1�ˣ�0��
************************************/

extern uint8_t PGA202_Status;             //PGA202�Ŵ���
extern char order4[10];
/**
  * ��������: PGA202�������ų�ʼ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void Pga202_Init()
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();			//GPIOBʱ�ӳ�ʼ��
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1; //ѡ��PB14,15
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������ģʽ
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����ģʽ
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);     //��ʼ��
	
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);	//PB3�õ�
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET);	//PB4�õ�
}

/**
  * ��������: PGA202�Ŵ�1��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void Pga202_1_multiple()
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);	//PB3�õ�
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);	//PB4�õ�
    PGA202_Status = 1;
}


/**
  * ��������: PGA202�Ŵ�10��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void Pga202_10_multiple()
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);	//PB3�ø�
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);	//PB4�õ�
    PGA202_Status = 10;
}    

/**
  * ��������: PGA202�Ŵ�100��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void Pga202_100_multiple()
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);	//PB3�õ�
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);	//PB4�ø�
    PGA202_Status = 100;
}




