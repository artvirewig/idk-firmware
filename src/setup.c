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

void setup_application(void)
{
	struct keyboard_event input_key;
    	// Clear screen
    	gfx_mono_draw_filled_rect(0, 0, 128, 32, GFX_PIXEL_CLR);
    
    	// Draw static strings outside the loop
    	gfx_mono_draw_string("Setup", 0, 0, &sysfont);
    
    	while (true)
    	{
        	keyboard_get_key_state(&input_key);
        	if ((input_key.keycode == KEYBOARD_ENTER) &&
            	(input_key.type == KEYBOARD_RELEASE)) {
            		break;
        	}
    	}
}
