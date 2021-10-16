#include "AD9834.h"

void AD9834_Write_16Bits(unsigned int data)
{
    unsigned char i = 0;
    AD9834_SCLK_SET;
    AD9834_FSYNC_CLR;
    for (i = 0; i < 16; i++)
    {
        if (data & 0x8000)
        {
            AD9834_SDATA_SET;
        }
        else
        {
            AD9834_SDATA_CLR;
        }
        AD9834_SCLK_CLR;
        data <<= 1;
        AD9834_SCLK_SET;
    }
    AD9834_FSYNC_SET;
}

void AD9834_Select_Wave(unsigned int initdata)
{
    AD9834_FSYNC_SET;
    AD9834_SCLK_SET;
    AD9834_RESET_SET;
    AD9834_RESET_SET;
    AD9834_RESET_CLR;
    AD9834_Write_16Bits(initdata);
}

void Init_AD9834()
{
    rt_pin_mode(AD9834_FSYNC, PIN_MODE_OUTPUT);
    rt_pin_mode(AD9834_SCLK, PIN_MODE_OUTPUT);
    rt_pin_mode(AD9834_SDATA, PIN_MODE_OUTPUT);
    rt_pin_mode(AD9834_RESET, PIN_MODE_OUTPUT);
}

// freq_number -- 要写入的平率寄存器(FREQ_0或FREQ_1)
// freq -- 频率值 (Freq_value(value)=Freq_data(data)*FCLK/2^28)
void AD9834_Set_Freq(unsigned char freq_number, unsigned long freq)
{
    unsigned long FREQREG = (unsigned long)(268435456.0 / AD9834_SYSTEM_COLCK * freq);
    unsigned int FREQREG_LSB_14BIT = (unsigned int)FREQREG;
    unsigned int FREQREG_MSB_14BIT = (unsigned int)(FREQREG >> 14);
    if (freq_number == FREQ_0)
    {
        FREQREG_LSB_14BIT &= ~(1U << 15);
        FREQREG_LSB_14BIT |= 1 << 14;
        FREQREG_MSB_14BIT &= ~(1U << 15);
        FREQREG_MSB_14BIT |= 1 << 14;
    }
    else
    {
        FREQREG_LSB_14BIT &= ~(1 << 14);
        FREQREG_LSB_14BIT |= 1U << 15;
        FREQREG_MSB_14BIT &= ~(1 << 14);
        FREQREG_MSB_14BIT |= 1U << 15;
    }
    AD9834_Write_16Bits(FREQREG_LSB_14BIT);
    AD9834_Write_16Bits(FREQREG_MSB_14BIT);
}
