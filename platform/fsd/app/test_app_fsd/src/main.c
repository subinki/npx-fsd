#include "platform_info.h" 
#include "ervp_printf.h"
#include "ervp_reg_util.h"
#include "ervp_delay.h"
#include "ervp_user_gpio.h"
#include "ervp_core_id.h"
#include "ervp_multicore_synch.h"
#include "ervp_fakefile.h"

#define OFFSET 0x240 

// 0.7V = 0x0B33
// 0.55V = 0x08CC
// 0.8V -> 12-bit code = round(0.8 * 4095) = 3276 = 0x0CCC
// 0.85V = 0x0D99
// 0.9V = 0x0E66
// 1V = 0x0FFF
#define THRESH_RAW (0x0D99 << 4)
#define THRESH_OVER 2

#define THRESH_HIGH (0x0CCC << 4) 
#define THRESH_LOW (0x08CC << 4)
#define THRESH_DWELL 3

static inline unsigned int get_xadc_addr(unsigned int offset)
{
        return (I_XADC_WIZ_0_SLAVE_BASEADDR+offset);
}

unsigned int get_xadc()
{
        return REG32(get_xadc_addr(OFFSET));
}

#define FENCE() asm volatile("fence rw, rw" ::: "memory")

volatile uint32_t g_gpio_flag = 0;
volatile uint32_t g_done = 0;

volatile uint32_t g_nums = 0;

int main(void)
{
    printf("Start Minimal (global-flag) Demo\n");

    if (EXCLUSIVE_ID == 0) {
        delay_ms(10);
        //for (int i = 0; i < 10; i++) {
        for(;;) {
            user_gpio_set_output(GPIO_INDEX_FOR_GPIO0, 1);
            g_gpio_flag = 1;
            FENCE();
            delay_us(50);

            user_gpio_set_output(GPIO_INDEX_FOR_GPIO0, 0);
            g_gpio_flag = 0;
            FENCE();
            delay_ms(10);
        }
        g_done = 1;
        FENCE();
        printf("Core0 done.\n");
    } else {
        uint32_t last = g_gpio_flag;  
        uint32_t fsd_thr_over = 0;
        uint32_t fsd_thr_dwell = 0;     
        while(1) {
                FENCE();
                uint32_t done = g_done;
                uint32_t flag = g_gpio_flag;
                unsigned int raw = get_xadc();
	if (flag) {
                  if (raw > THRESH_RAW) {
                    fsd_thr_over++;
                  } 
                  if (THRESH_HIGH > raw && THRESH_LOW < raw) {
                    fsd_thr_dwell++;
                  }
                }

                if (last == 1 && flag == 0) {
                        g_nums++;
                        if (fsd_thr_over >= THRESH_OVER && fsd_thr_dwell >= THRESH_DWELL) {
                          printf("[%u] Detection result: REAL\n", g_nums);
                        } else {
                          printf("[%u] Detection result: FAKE\n", g_nums);
                        }
                        fsd_thr_over = 0;
                        fsd_thr_dwell = 0;
                }
                last = flag;

                if (done) break;
        }
        printf("Core1 done.\n");
        return 0;
    }
}

