#ifndef _AD9959_H_
#define _AD9959_H_

#include "stm32f7xx_hal.h"

//AD9959寄存器地址定义
#define CSR_ADD   0x00   //CSR 通道选择寄存器
#define FR1_ADD   0x01   //FR1 功能寄存器1
#define FR2_ADD   0x02   //FR2 功能寄存器2
#define CFR_ADD   0x03   //CFR 通道功能寄存器
#define CFTW0_ADD 0x04   //CTW0 通道频率转换字寄存器
#define CPOW0_ADD 0x05   //CPW0 通道相位转换字寄存器
#define ACR_ADD   0x06   //ACR 幅度控制寄存器
#define LSRR_ADD  0x07   //LSR 通道线性扫描寄存器
#define RDW_ADD   0x08   //RDW 通道线性向上扫描寄存器
#define FDW_ADD   0x09   //FDW 通道线性向下扫描寄存器
//AD9959管脚宏定义
#define CS(n)			(n?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_RESET))
#define SCLK(n)		    (n?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET))
#define UPDATE(n)	    (n?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_RESET))
#define PS0(n)			(n?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_RESET))
#define PS1(n)			(n?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_RESET))
#define PS2(n)			(n?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,GPIO_PIN_RESET))
#define PS3(n)			(n?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,GPIO_PIN_RESET))
#define SDIO0(n)		(n?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_RESET))
#define SDIO1(n)		(n?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_RESET))
#define SDIO2(n)		(n?HAL_GPIO_WritePin(GPIOF,GPIO_PIN_12,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOF,GPIO_PIN_12,GPIO_PIN_RESET))
#define SDIO3(n)		(n?HAL_GPIO_WritePin(GPIOF,GPIO_PIN_13,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOF,GPIO_PIN_13,GPIO_PIN_RESET))
#define AD9959_PWR(n)	(n?HAL_GPIO_WritePin(GPIOF,GPIO_PIN_14,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOF,GPIO_PIN_14,GPIO_PIN_RESET))
#define Reset(n)		(n?HAL_GPIO_WritePin(GPIOF,GPIO_PIN_15,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOF,GPIO_PIN_15,GPIO_PIN_RESET))

void delay1 (uint32_t length);
void IntReset(void);	  //AD9959复位
void IO_Update(void);   //AD9959更新数据
void Intserve(void);		   //IO口初始化
void WriteData_AD9959(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData,uint8_t temp);
void Init_AD9959(void);
void Write_frequence(uint8_t Channel,uint32_t Freq);
void Write_Amplitude(uint8_t Channel, uint16_t Ampli);
void Write_Phase(uint8_t Channel,uint16_t Phase);
















#endif
