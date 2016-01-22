/*
 * serial.c
 *
 * Created: 12/30/2015 4:55:47 PM
 *  Author: Art Navsegda
 */

#include "stdio.h"
#include "sysfont.h"
#include "bitmaps.h"
#include "keyboard.h"
#include "spi_master.h"
#include "spi_display.h"
#include "setup.h"
#include "sensor.h"
#include "sensor_bus.h"

void serial_application(void)
{
	sensor_t barometer;
	sensor_data_t press_data;
	sensor_data_t temp_data;
	int median;
	long average = 0;
	int number = 0;
	int number2 = 0;
	unsigned int result = 0;
	uint8_t data_buffer[1] = {0x38};
	uint8_t read_buffer[2] = {0x00, 0x00};
	struct keyboard_event input_key;
	char string_buf[10];

	// Clear screen
	gfx_mono_draw_filled_rect(0, 0, 128, 32, GFX_PIXEL_CLR);

	// Draw static strings outside the loop
	gfx_mono_draw_string("Serial", 0, 0, &sysfont);

	sensor_bus_init(&TWIE, 400000);
	delay_ms(50);
	sensor_attach(&barometer, SENSOR_TYPE_BAROMETER, 0, 0);
	sensor_set_state(&barometer, SENSOR_STATE_HIGHEST_POWER);
	press_data.scaled = true;
	temp_data.scaled = true;

	spi_sensor_init();
	spi_select_device(&SPIC, &SPI_ADC);
	while (true) {
			data_buffer[0] = 0x08;
			spi_write_packet(&SPIC, data_buffer, 1);
			spi_read_packet(&SPIC, &number, 1);

				if (number == 8)
				{
					data_buffer[0] = 0x38;
					spi_write_packet(&SPIC, data_buffer, 1);
					spi_read_packet(&SPIC, &read_buffer, 2);
					//spi_read_packet(&SPIC, &number2, 2);
					MSB(result) = read_buffer[0];
					LSB(result) = read_buffer[1];
					//printf("%2.2X %2.2X\n",read_buffer[0],read_buffer[1]);
					printf("%d ",result-0x8000);
					//snprintf(string_buf, sizeof(string_buf), " %2.2X%2.2X", read_buffer[0],read_buffer[1]);
					//gfx_mono_draw_string(string_buf, 30, 6, &sysfont);
					//snprintf(string_buf, sizeof(string_buf), "%5d ", result-0x8000);
					//snprintf(string_buf, sizeof(string_buf), "%X",number2);
					//gfx_mono_draw_string(string_buf, 30, 16, &sysfont);
					average = average + result;
					median++;
					if (median == 256)
					{
						//snprintf(string_buf, sizeof(string_buf), "%X", (average >> 7));
						//snprintf(string_buf, sizeof(string_buf), " %lX", average);
						//gfx_mono_draw_string(string_buf, 70, 6, &sysfont);
						//snprintf(string_buf, sizeof(string_buf), "%5d", (average >> 8)-0x8000);
						//gfx_mono_draw_string(string_buf, 70, 16, &sysfont);
						average = 0;
						median = 0;
					}
					sensor_get_pressure(&barometer, &press_data);
					sensor_get_temperature(&barometer, &temp_data);
					printf("%.2f ", (press_data.pressure.value / 100.0));
					printf("%.1f\n", (temp_data.temperature.value / 10.0));
				}

			keyboard_get_key_state(&input_key);
			if ((input_key.keycode == KEYBOARD_ENTER) &&
			(input_key.type == KEYBOARD_RELEASE)) {
				spi_deselect_device(&SPIC, &SPI_ADC);
				break;
			}
	}
}
