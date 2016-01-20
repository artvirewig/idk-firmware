/**
 * \file
 *
 * \brief Application CDC Implementation
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include "nvm.h"
#include "keyboard.h"
#include "cdc.h"
#include "usart.h"
#include "usart_serial.h"
#include "usart_spi.h"
#include "stdio_serial.h"

//! USBID position in user signature row
#define USER_SIGNATURE_USBID_POS   8
//! USBID size in user signature row
#define USER_SIGNATURE_USBID_SIZE 12

PROGMEM_DECLARE(char const, cdc_help[]) =
	"\r\n"
	"Welcome to the XMEGA-A3BU Xplained Demo CDC interface!\r\n"
	"\r\n"
	"Key bindings for LCD menu control:\r\n"
	"  Enter      : Enter\r\n"
	"  Backspace  : Back\r\n"
	"  Arrow Up   : Up\r\n"
	"  Arrow Down : Down\r\n";

bool cdc_opened = false;

static void cdc_put_help(void)
{
	const char PROGMEM_PTR_T help = cdc_help;
	char val;

	while ((val = PROGMEM_READ_BYTE(help))) {
		putchar(val);
		help++;
	}
}

void cdc_start(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_BAUDRATE,
		.charlength = CONF_CHARLENGTH,
		.paritytype = CONF_PARITY,
		.stopbits   = CONF_STOPBITS,
	};

	stdio_serial_init(CONF_USART, &usart_serial_options);
}

void cdc_set_dtr(bool enable)
{
	cdc_opened = enable;
}

keycode_t cdc_getkey(void)
{
	char key;
	static uint8_t esc_state = 0;

	// If the cdc was opened, print out the help
	if (cdc_opened) {
		cdc_opened = false;
		cdc_put_help();
	}

	if (!usart_spi_is_rx_ready(CONF_USART)) {
		return KEYBOARD_NO_KEY;
	}

	key = getchar();

	if (esc_state == 1) {
		if (key == 0x5b) {
			esc_state = 2;
		} else {
			esc_state = 0;
		}
	} else if (esc_state == 2) {
		esc_state = 0;
		// Translate up/down arrow keys to keycodes
		switch (key) {
		case 'A':
			key = KEYBOARD_UP;
			break;
		case 'B':
			key = KEYBOARD_DOWN;
			break;
		}
	}

	// Check for escape sequence
	if (key == 0x1b) {
		esc_state = 1;
		return KEYBOARD_NO_KEY;
	}

	// Just return any other key directly
	return key;
}

