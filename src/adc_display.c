/*
 * spectrometer.c
 *
 * Created: 12/21/2015 7:57:59 PM
 *  Author: Art Navsegda
 */ 

#include "stdio.h"
#include "adc_sensors.h"
#include "sysfont.h"
#include "bitmaps.h"
#include "keyboard.h"
#include "adc_display.h"

void adc_application(void)
{
	struct keyboard_event input_key;
	char string_buf[10];
	uint32_t adca0_val = 0;
	uint32_t adca1_val = 0;
	uint32_t adca2_val = 0;
	uint32_t adca3_val = 0;
	uint32_t adcb0_val = 0;
	uint32_t adcb1_val = 0;
	uint32_t adcb2_val = 0;
	uint32_t adcb3_val = 0;

	// Clear screen
	gfx_mono_draw_filled_rect(0, 0, 128, 32, GFX_PIXEL_CLR);

	// Draw static strings outside the loop
	gfx_mono_draw_string("ADC0", 100, 0, &sysfont);
	gfx_mono_draw_string("ADC1", 100, 8, &sysfont);
	gfx_mono_draw_string("ADC2", 100, 16, &sysfont);
	gfx_mono_draw_string("ADC3", 100, 24, &sysfont);
	gfx_mono_draw_string("ADC4", 0, 0, &sysfont);
	gfx_mono_draw_string("ADC5", 0, 8, &sysfont);
//	gfx_mono_draw_string("ADC6", 0, 16, &sysfont);
//	gfx_mono_draw_string("ADC7", 0, 24, &sysfont);
	gfx_mono_draw_string("Light", 0, 16, &sysfont);
	gfx_mono_draw_string("NTC", 0, 24, &sysfont);
	
	while (true) {
			// Start an ADC conversion
			/*adc_start_conversion(&ADCA, ADC_CH0);
			adc_start_conversion(&ADCA, ADC_CH1);
			adc_start_conversion(&ADCA, ADC_CH2);
			adc_start_conversion(&ADCA, ADC_CH3);*/
			lightsensor_measure();
			ntc_measure();
			adc_measure();
			adc2_measure();
			
			while (!adc_data_is_ready() && !adc2_data_is_ready() && !ntc_data_is_ready() && !lightsensor_data_is_ready()) {
				// Wait until the conversion is complete
			}
			
			//adc_wait_for_interrupt_flag(&ADCA, ADC_CH0);
			/*adc0_val = adc_get_result(&ADCA, ADC_CH0);
			adc1_val = adc_get_result(&ADCA, ADC_CH1);
			adc2_val = adc_get_result(&ADCA, ADC_CH2);
			adc3_val = adc_get_result(&ADCA, ADC_CH3);*/
			adca0_val = lightsensor_get_raw_value();
			adca1_val = ntc_get_raw_value();
			adca2_val = adc_get_raw_value();
			adca3_val = adc2_get_raw_value();
			snprintf(string_buf, sizeof(string_buf), "%4ld", adca0_val);
			gfx_mono_draw_string(string_buf, 30, 16, &sysfont);
			snprintf(string_buf, sizeof(string_buf), "%4ld", adca1_val);
			gfx_mono_draw_string(string_buf, 30, 24, &sysfont);
			snprintf(string_buf, sizeof(string_buf), "%4ld", adca2_val);
			gfx_mono_draw_string(string_buf, 30, 0, &sysfont);
			snprintf(string_buf, sizeof(string_buf), "%4ld", adca3_val);
			gfx_mono_draw_string(string_buf, 30, 8, &sysfont);
			
			// Start an ADCB conversion
			/*adc_start_conversion(&ADCB, ADC_CH0);
			adc_start_conversion(&ADCB, ADC_CH1);
			adc_start_conversion(&ADCB, ADC_CH2);
			adc_start_conversion(&ADCB, ADC_CH3);*/
			adcb0_measure();
			adcb1_measure();
			adcb2_measure();
			adcb3_measure();
			
			while (!adcb0_data_is_ready() && !adcb1_data_is_ready() && !adcb2_data_is_ready() && !adcb3_data_is_ready()) {
				// Wait until the conversion is complete
			}
			
			//adc_wait_for_interrupt_flag(&ADCB, ADC_CH0);
			/*adc0_val = adc_get_result(&ADCA, ADC_CH0);
			adc1_val = adc_get_result(&ADCA, ADC_CH1);
			adc2_val = adc_get_result(&ADCA, ADC_CH2);
			adc3_val = adc_get_result(&ADCA, ADC_CH3);*/
			adcb0_val = adcb0_get_raw_value();
			adcb1_val = adcb1_get_raw_value();
			adcb2_val = adcb2_get_raw_value();
			adcb3_val = adcb3_get_raw_value();
			snprintf(string_buf, sizeof(string_buf), "%4ld", adcb0_val);
			gfx_mono_draw_string(string_buf, 60, 0, &sysfont);
			snprintf(string_buf, sizeof(string_buf), "%4ld", adcb1_val);
			gfx_mono_draw_string(string_buf, 60, 8, &sysfont);
			snprintf(string_buf, sizeof(string_buf), "%4ld", adcb2_val);
			gfx_mono_draw_string(string_buf, 60, 16, &sysfont);
			snprintf(string_buf, sizeof(string_buf), "%4ld", adcb3_val);
			gfx_mono_draw_string(string_buf, 60, 24, &sysfont);
			
			keyboard_get_key_state(&input_key);
			if ((input_key.keycode == KEYBOARD_ENTER) &&
					(input_key.type == KEYBOARD_RELEASE)) {
				break;
			}
	}
}
