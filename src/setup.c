//
//  setup.c
//  avrnavsegda
//
//  Created by Art Navsegda on 1/19/16.
//  Copyright © 2016 Art Navsegda. All rights reserved.
//

#include "stdio.h"
#include "sysfont.h"
#include "bitmaps.h"
#include "keyboard.h"
#include "setup.h"
#include "gfx_mono_menu.h"
#include "gfx_mono_spinctrl.h"

PROGMEM_DECLARE(char const, spinnertitle[]) = "Approx:";
PROGMEM_DECLARE(char const, spinnertitle2[]) = "Clock reg:";
PROGMEM_DECLARE(char const, spinnertitle3[]) = "Setup reg:";
PROGMEM_DECLARE(char const, spinner_choice1[]) = "Single";
PROGMEM_DECLARE(char const, spinner_choice2[]) = "Double";
PROGMEM_DECLARE(char const, spinner_choice3[]) = "String 3";
PROGMEM_DECLARE(char const, spinner_choice4[]) = "String 4";

PROGMEM_STRING_T spinner_choicestrings[] = {
	spinner_choice1,
	spinner_choice2,
	spinner_choice3,
	spinner_choice4,
};

void setup_application(void)
{
	struct gfx_mono_spinctrl spinner1;
	struct gfx_mono_spinctrl spinner2;
	struct gfx_mono_spinctrl spinner3;
	struct gfx_mono_spinctrl_spincollection spinners;
	int16_t results[GFX_MONO_SPINCTRL_MAX_ELEMENTS_IN_SPINCOLLECTION];
	uint8_t spinner_status;
	struct keyboard_event input;
	
    // Clear screen
    gfx_mono_draw_filled_rect(0, 0, 128, 32, GFX_PIXEL_CLR);
    
    // Draw static strings outside the loop
    //gfx_mono_draw_string("Setup", 0, 0, &sysfont);
		
	// Initialize spinners
	gfx_mono_spinctrl_init(&spinner1, SPINTYPE_STRING, spinnertitle, spinner_choicestrings, 0, 3, 0);
	gfx_mono_spinctrl_init(&spinner2, SPINTYPE_INTEGER,	spinnertitle2, NULL, 0x00, 0xFF, 0);
	gfx_mono_spinctrl_init(&spinner3, SPINTYPE_INTEGER,	spinnertitle3, NULL, 0x00, 0xFF, 0);

	// Initialize spincollection
	gfx_mono_spinctrl_spincollection_init(&spinners);

	// Add spinners to spincollection
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner1, &spinners);
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner2, &spinners);
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner3, &spinners);
	
	spinner2.integer_data = clockreg;
	spinner3.integer_data = setupreg;

	// Show spincollection on screen
	gfx_mono_spinctrl_spincollection_show(&spinners);

	// Spincollection is now ready to process input from user
	do {
		do {
			keyboard_get_key_state(&input);
			// Wait for key release
		} while (input.type != KEYBOARD_RELEASE);
		// Send key to spinnercollection
		spinner_status = gfx_mono_spinctrl_spincollection_process_key(
		&spinners, input.keycode, results);
	} while (spinner_status != GFX_MONO_SPINCTRL_EVENT_FINISH);
	
	clockreg = results[1];
	setupreg = results[2];
    
}
