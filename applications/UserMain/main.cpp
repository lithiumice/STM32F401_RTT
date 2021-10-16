#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <string>
#include "util.h"

#include "tasks_manage.h"
#include "sys_config.h"
#include "inout_dev.h"
#include "ad9834.h"

using namespace std;

#define LED0_PIN GET_PIN(C, 13)

uint32_t get_enc();
void encoder_init();
uint32_t enc1;

void display_thread(void *param)
{
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    while (1)
    {
        //enc1 = get_enc();
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}

int main(void)
{
    Init_AD9834();
    AD9834_Select_Wave(Triangle_Wave);
    // AD9834_Select_Wave(Sine_Wave);
    AD9834_Set_Freq(FREQ_0, 1000000); //1kHz

    xTaskReg(display_thread, ByteUnit(512), RT_MAIN_THREAD_PRIORITY);

    while (1)
    {
    }

    return RT_EOK;
}
