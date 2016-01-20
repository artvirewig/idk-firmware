/*
 * spi_display.c
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

uint8_t resetdata[5] = {0xFF,0xFF,0xFF,0xFF,0xFF};

struct spi_device SPI_ADC = {
	//! Board specific select id
	.id = IOPORT_CREATE_PIN(PORTC, 4)
};

static bool spi_init_pins(void)
{
	ioport_configure_port_pin(&PORTC, PIN4_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	//ioport_configure_port_pin(&PORTC, PIN4_bm, IOPORT_PULL_UP | IOPORT_DIR_INPUT);
	ioport_configure_port_pin(&PORTC, PIN5_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	ioport_configure_port_pin(&PORTC, PIN6_bm, IOPORT_DIR_INPUT);
	ioport_configure_port_pin(&PORTC, PIN7_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	return 0;
}

void spi_sensor_init(void)
{
	uint8_t data_buffer[1] = {0x38};
	spi_init_pins();
	spi_master_init(&SPIC);
	spi_master_setup_device(&SPIC, &SPI_ADC, SPI_MODE_3, 500000, 0);
	spi_enable(&SPIC);
	spi_select_device(&SPIC, &SPI_ADC);
	spi_write_packet(&SPIC, resetdata, 5);
	data_buffer[0] = 0x20;
	spi_write_packet(&SPIC, data_buffer, 1);
	//data_buffer[0] = 0x0C;
	data_buffer[0] = clockreg;
	spi_write_packet(&SPIC, data_buffer, 1);
	data_buffer[0] = 0x10;
	spi_write_packet(&SPIC, data_buffer, 1);
	//data_buffer[0] = 0;
	data_buffer[0] = setupreg;
	spi_write_packet(&SPIC, data_buffer, 1);

	spi_deselect_device(&SPIC, &SPI_ADC);
}

void spi_application(void)
{
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
	gfx_mono_draw_string("SPI", 0, 0, &sysfont);
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
					snprintf(string_buf, sizeof(string_buf), " %2.2X%2.2X", read_buffer[0],read_buffer[1]);
					gfx_mono_draw_string(string_buf, 30, 6, &sysfont);
					snprintf(string_buf, sizeof(string_buf), "%5d", result-0x8000);
					//snprintf(string_buf, sizeof(string_buf), "%X",number2);
					gfx_mono_draw_string(string_buf, 30, 16, &sysfont);
					average = average + result;
					median++;
					if (median == 256)
					{
						//snprintf(string_buf, sizeof(string_buf), "%X", (average >> 7));
						snprintf(string_buf, sizeof(string_buf), " %lX", average);
						gfx_mono_draw_string(string_buf, 70, 6, &sysfont);
						snprintf(string_buf, sizeof(string_buf), "%5d", (average >> 8)-0x8000);
						gfx_mono_draw_string(string_buf, 70, 16, &sysfont);
						average = 0;
						median = 0;
					}
				}

			keyboard_get_key_state(&input_key);
			if ((input_key.keycode == KEYBOARD_ENTER) &&
			(input_key.type == KEYBOARD_RELEASE)) {
				spi_deselect_device(&SPIC, &SPI_ADC);
				break;
			}
	}
}
