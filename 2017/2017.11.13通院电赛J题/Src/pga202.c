#include "pga202.h"
#include "gpio.h"
#include "hmi.h"
/***********************************
PGA202控制模式：
PB3对应控制端0，PB4对应控制端1
1倍（0端：0，1端：0） 
10倍（0端：1，1端：0）
100倍（0端：0，1端：1）
1000倍（0端：1，1端：0）
************************************/

extern uint8_t PGA202_Status;             //PGA202放大倍数
extern char order4[10];
/**
  * 函数功能: PGA202控制引脚初始化
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void Pga202_Init()
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();			//GPIOB时钟初始化
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1; //选择PB14,15
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出模式
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速模式
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);     //初始化
	
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);	//PB3置低
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET);	//PB4置低
}

/**
  * 函数功能: PGA202放大1倍
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void Pga202_1_multiple()
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);	//PB3置低
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);	//PB4置低
    PGA202_Status = 1;
}


/**
  * 函数功能: PGA202放大10倍
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void Pga202_10_multiple()
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);	//PB3置高
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);	//PB4置低
    PGA202_Status = 10;
}    

/**
  * 函数功能: PGA202放大100倍
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void Pga202_100_multiple()
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);	//PB3置低
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);	//PB4置高
    PGA202_Status = 100;
}




