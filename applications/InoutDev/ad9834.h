#ifndef __AD9834_H
#define __AD9834_H

#include "drv_common.h"
#include <rtdevice.h>
#include <board.h>

#define Triangle_Wave 0x2002
#define Sine_Wave 0x2028
#define AD9834_SYSTEM_COLCK 75000000UL

#define AD9834_FSYNC GET_PIN(A, 0)
#define AD9834_SCLK GET_PIN(A, 1)
#define AD9834_SDATA GET_PIN(A, 2)
#define AD9834_RESET GET_PIN(A, 3)

#define AD9834_FSYNC_SET rt_pin_write(AD9834_FSYNC, PIN_HIGH);
#define AD9834_FSYNC_CLR rt_pin_write(AD9834_FSYNC, PIN_LOW);
#define AD9834_SCLK_SET rt_pin_write(AD9834_SCLK, PIN_HIGH);
#define AD9834_SCLK_CLR rt_pin_write(AD9834_SCLK, PIN_LOW);
#define AD9834_SDATA_SET rt_pin_write(AD9834_SDATA, PIN_HIGH);
#define AD9834_SDATA_CLR rt_pin_write(AD9834_SDATA, PIN_LOW);
#define AD9834_RESET_SET rt_pin_write(AD9834_RESET, PIN_HIGH);
#define AD9834_RESET_CLR rt_pin_write(AD9834_RESET, PIN_LOW);

#define FREQ_0 0
#define FREQ_1 1
#define DB15 0
#define DB14 0
#define DB13 B28
#define DB12 HLB
#define DB11 FSEL
#define DB10 PSEL
#define DB9 PIN_SW
#define DB8 RESET
#define DB7 SLEEP1
#define DB6 SLEEP12
#define DB5 OPBITEN
#define DB4 SIGN_PIB
#define DB3 DIV2
#define DB2 0
#define DB1 MODE
#define DB0 0

#define CONTROL_REGISTER (DB15 << 15) | (DB14 << 14) | (DB13 << 13) | (DB12 << 12) | (DB11 << 1 1) | (DB10 << 10) | (DB9 << 9) | (DB8 << 8) | (DB7 << 7) | (DB6 << 6) | (DB5 << 5) | (DB4 << 4) | (DB3 << 3) | (DB2 << 2) | (DB1 << 1) | (DB0 << 0)

extern void Init_AD9834();                                                  //初始化配置
extern void AD9834_Write_16Bits(unsigned int data);                         //写一个字到AD9834
extern void AD9834_Select_Wave(unsigned int initdata);                      //选择输出波形
extern void AD9834_Set_Freq(unsigned char freq_number, unsigned long freq); //选择输出寄存器和输出频率值

#endif /* AD9834_H */