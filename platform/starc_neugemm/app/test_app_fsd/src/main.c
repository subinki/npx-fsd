#include "platform_info.h"
#include "ervp_printf.h"
#include "ervp_reg_util.h"
#include "ervp_delay.h"
#include "ervp_user_gpio.h"

#define OFFSET 0x240

static inline unsigned int get_xadc_addr(unsigned int offset)
{
        return (I_XADC_WIZ_0_SLAVE_BASEADDR+offset);
}

unsigned int get_xadc()
{
        return REG32(get_xadc_addr(OFFSET));
}

//int main() {
//	printf("Start FSD Test\n");
//	delay_ms(1);
//
//	user_gpio_set_output(GPIO_INDEX_FOR_GPIO0, 1);
//	delay_us(50);
//	user_gpio_set_output(GPIO_INDEX_FOR_GPIO0, 0);
//
//	for(int i=0; i<50; i++)
//	{	
//		unsigned int raw_val = get_xadc();
//        	unsigned int xadc_val = raw_val >> 4;                 // MSB 12-bit
//        	float voltage = (xadc_val / 4096.0f) * 1.0f;          // 0~1V full-scale
//
//        	printf("\nraw_val: 0x%04X  xadc_val: 0x%03X  voltage: %.3f V", raw_val, xadc_val, voltage);
//        	delay_ms(10);
//	}
//	//user_gpio_set_output(GPIO_INDEX_FOR_GPIO0, 0);
//	printf("\nFSD Test complete\n");
//	return 0;
//}

int main() {
        printf("Start FSD Test\n");
	unsigned int raw_buf[200];

	for(int i=0; i<5; i++) {
        	user_gpio_set_output(GPIO_INDEX_FOR_GPIO0, 1);
		//delay_us(50);
		for(int i=0; i<200; i++)
        	{
			raw_buf[i] = get_xadc();
		}
        	user_gpio_set_output(GPIO_INDEX_FOR_GPIO0, 0);
		//delay_us(20);

		for(int i=0; i<200; i++) {
			unsigned int raw_val  = raw_buf[i];
            		unsigned int xadc_val = (raw_val >> 4) & 0xFFF;
            		float       voltage   = (float)xadc_val * (1.0f/4096.0f);

            		printf("\n[idx: %d] raw_val: 0x%04X  xadc_val: 0x%03X  voltage: %.3f V",
            		       i, raw_val, xadc_val, voltage);
		}
	}
        printf("\nFSD Test complete\n");
        return 0;
}


