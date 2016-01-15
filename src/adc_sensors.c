/**
 * \file
 *
 * \brief ADC Sensor interface
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

#include "adc.h"
#include "adc_sensors.h"

#define NTC_SENSOR_MAX_SAMPLES   4
#define LIGHT_SENSOR_MAX_SAMPLES 4
#define ADC_SENSOR_MAX_SAMPLES 4
#define ADC2_SENSOR_MAX_SAMPLES 4
#define ADCB0_SENSOR_MAX_SAMPLES 4
#define ADCB1_SENSOR_MAX_SAMPLES 4
#define ADCB2_SENSOR_MAX_SAMPLES 4
#define ADCB3_SENSOR_MAX_SAMPLES 4

//! bool to hold the data ready flag
bool ntc_sensor_data_ready = false;
bool light_sensor_data_ready = false;
bool adc_sensor_data_ready = false;
bool adc2_sensor_data_ready = false;
bool adcb0_sensor_data_ready = false;
bool adcb1_sensor_data_ready = false;
bool adcb2_sensor_data_ready = false;
bool adcb3_sensor_data_ready = false;
bool adc7_sensor_data_ready = false;
adc_result_t ntc_sensor_sample = 0;
adc_result_t light_sensor_sample = 0;
adc_result_t adc_sensor_sample = 0;
adc_result_t adc2_sensor_sample = 0;
adc_result_t adcb0_sensor_sample = 0;
adc_result_t adcb1_sensor_sample = 0;
adc_result_t adcb2_sensor_sample = 0;
adc_result_t adcb3_sensor_sample = 0;

/**
 * \brief Check of there is NTC data ready to be read
 *
 * When data is ready to be read this function will return true, and assume
 * that the data is going to be read so it sets the ready flag to false.
 *
 * \retval true if the NTC value is ready to be read
 * \retval false if data is not ready yet
 */
bool ntc_data_is_ready(void)
{
	irqflags_t irqflags;
	/* We will need to save and turn of global interrupts to make sure that we
	read the latest NTC value and not the next one if a conversation finish
	before one have time read the data. */
	irqflags = cpu_irq_save();
	if (ntc_sensor_data_ready) {
		ntc_sensor_data_ready = false;
		cpu_irq_restore(irqflags);
		return true;
	} else {
		cpu_irq_restore(irqflags);
		return false;
	}
}

bool lightsensor_data_is_ready(void)
{
	irqflags_t irqflags;
	/* We will need to save and turn of global interrupts to make sure that we
	read the latest NTC value and not the next one if a conversation finish
	before one have time read the data. */
	irqflags = cpu_irq_save();
	if (light_sensor_data_ready) {
		light_sensor_data_ready = false;
		cpu_irq_restore(irqflags);
		return true;
	} else {
		cpu_irq_restore(irqflags);
		return false;
	}
}

bool adc_data_is_ready(void)
{
	irqflags_t irqflags;
	/* We will need to save and turn of global interrupts to make sure that we
	read the latest NTC value and not the next one if a conversation finish
	before one have time read the data. */
	irqflags = cpu_irq_save();
	if (adc_sensor_data_ready) {
		adc_sensor_data_ready = false;
		cpu_irq_restore(irqflags);
		return true;
	} else {
		cpu_irq_restore(irqflags);
		return false;
	}
}

bool adc2_data_is_ready(void)
{
	irqflags_t irqflags;
	/* We will need to save and turn of global interrupts to make sure that we
	read the latest NTC value and not the next one if a conversation finish
	before one have time read the data. */
	irqflags = cpu_irq_save();
	if (adc2_sensor_data_ready) {
		adc2_sensor_data_ready = false;
		cpu_irq_restore(irqflags);
		return true;
	} else {
		cpu_irq_restore(irqflags);
		return false;
	}
}

bool adcb0_data_is_ready(void)
{
	irqflags_t irqflags;
	/* We will need to save and turn of global interrupts to make sure that we
	read the latest NTC value and not the next one if a conversation finish
	before one have time read the data. */
	irqflags = cpu_irq_save();
	if (adcb0_sensor_data_ready) {
		adcb0_sensor_data_ready = false;
		cpu_irq_restore(irqflags);
		return true;
	} else {
		cpu_irq_restore(irqflags);
		return false;
	}
}

bool adcb1_data_is_ready(void)
{
	irqflags_t irqflags;
	/* We will need to save and turn of global interrupts to make sure that we
	read the latest NTC value and not the next one if a conversation finish
	before one have time read the data. */
	irqflags = cpu_irq_save();
	if (adcb1_sensor_data_ready) {
		adcb1_sensor_data_ready = false;
		cpu_irq_restore(irqflags);
		return true;
	} else {
		cpu_irq_restore(irqflags);
		return false;
	}
}

bool adcb2_data_is_ready(void)
{
	irqflags_t irqflags;
	/* We will need to save and turn of global interrupts to make sure that we
	read the latest NTC value and not the next one if a conversation finish
	before one have time read the data. */
	irqflags = cpu_irq_save();
	if (adcb2_sensor_data_ready) {
		adcb2_sensor_data_ready = false;
		cpu_irq_restore(irqflags);
		return true;
	} else {
		cpu_irq_restore(irqflags);
		return false;
	}
}

bool adcb3_data_is_ready(void)
{
	irqflags_t irqflags;
	/* We will need to save and turn of global interrupts to make sure that we
	read the latest NTC value and not the next one if a conversation finish
	before one have time read the data. */
	irqflags = cpu_irq_save();
	if (adcb3_sensor_data_ready) {
		adcb3_sensor_data_ready = false;
		cpu_irq_restore(irqflags);
		return true;
	} else {
		cpu_irq_restore(irqflags);
		return false;
	}
}

/**
 * \brief Callback for the ADC conversion complete
 *
 * The ADC module will call this function on a conversion complete.
 *
 * \param adc the ADC from which the interrupt came
 * \param ch_mask the ch_mask that produced the interrupt
 * \param result the result from the ADC
 */
void adcb_handler(ADC_t *adc, uint8_t ch_mask, adc_result_t result)
{
	static uint8_t adcb0_sensor_samples = 0;
	static uint8_t adcb1_sensor_samples = 0;
	static uint8_t adcb2_sensor_samples = 0;
	static uint8_t adcb3_sensor_samples = 0;

	// Lightsensor on channel 0 , NTC on channel 1
	if (ch_mask == ADC_CH0) {
		adcb0_sensor_samples++;
		if (adcb0_sensor_samples == 1) {
			adcb0_sensor_sample = result;
			adcb0_sensor_data_ready = false;
		} else {
			adcb0_sensor_sample += result;
			adcb0_sensor_sample >>= 1;
		}
		if (adcb0_sensor_samples == ADCB0_SENSOR_MAX_SAMPLES) {
			adcb0_sensor_samples = 0;
			adcb0_sensor_data_ready = true;
		} else {
			adcb0_measure();
		}
	} else if (ch_mask == ADC_CH1) {
		adcb1_sensor_samples++;
		if (adcb1_sensor_samples == 1) {
			adcb1_sensor_sample = result;
			adcb1_sensor_data_ready = false;
		} else {
			adcb1_sensor_sample += result;
			adcb1_sensor_sample >>= 1;
		}
		if (adcb1_sensor_samples == ADCB1_SENSOR_MAX_SAMPLES) {
			adcb1_sensor_samples = 0;
			adcb1_sensor_data_ready = true;
		} else {
			adcb1_measure();
		}
	} else if (ch_mask == ADC_CH2) {
		adcb2_sensor_samples++;
		if (adcb2_sensor_samples == 1) {
			adcb2_sensor_sample = result;
			adcb2_sensor_data_ready = false;
		} else {
			adcb2_sensor_sample += result;
			adcb2_sensor_sample >>= 1;
		}
		if (adcb2_sensor_samples == ADCB2_SENSOR_MAX_SAMPLES) {
			adcb2_sensor_samples = 0;
			adcb2_sensor_data_ready = true;
		} else {
			adcb2_measure();
		}
	} else if (ch_mask == ADC_CH3) {
		adcb3_sensor_samples++;
		if (adcb3_sensor_samples == 1) {
			adcb3_sensor_sample = result;
			adcb3_sensor_data_ready = false;
		} else {
			adcb3_sensor_sample += result;
			adcb3_sensor_sample >>= 1;
		}
		if (adcb3_sensor_samples == ADCB3_SENSOR_MAX_SAMPLES) {
			adcb3_sensor_samples = 0;
			adcb3_sensor_data_ready = true;
		} else {
			adcb3_measure();
		}
	}
}

/**
 * \brief Callback for the ADC conversion complete
 *
 * The ADC module will call this function on a conversion complete.
 *
 * \param adc the ADC from which the interrupt came
 * \param ch_mask the ch_mask that produced the interrupt
 * \param result the result from the ADC
 */
void adc_handler(ADC_t *adc, uint8_t ch_mask, adc_result_t result)
{
	static uint8_t light_sensor_samples = 0;
	static uint8_t ntc_sensor_samples = 0;
	static uint8_t adc_sensor_samples = 0;
	static uint8_t adc2_sensor_samples = 0;

	// Lightsensor on channel 0 , NTC on channel 1
	if (ch_mask == ADC_CH0) {
		light_sensor_samples++;
		if (light_sensor_samples == 1) {
			light_sensor_sample = result;
			light_sensor_data_ready = false;
		} else {
			light_sensor_sample += result;
			light_sensor_sample >>= 1;
		}
		if (light_sensor_samples == LIGHT_SENSOR_MAX_SAMPLES) {
			light_sensor_samples = 0;
			light_sensor_data_ready = true;
		} else {
			lightsensor_measure();
		}
	} else if (ch_mask == ADC_CH1) {
		ntc_sensor_samples++;
		if (ntc_sensor_samples == 1) {
			ntc_sensor_sample = result;
			ntc_sensor_data_ready = false;
		} else {
			ntc_sensor_sample += result;
			ntc_sensor_sample >>= 1;
		}
		if (ntc_sensor_samples == NTC_SENSOR_MAX_SAMPLES) {
			ntc_sensor_samples = 0;
			ntc_sensor_data_ready = true;
		} else {
			ntc_measure();
		}
	} else if (ch_mask == ADC_CH2) {
		adc_sensor_samples++;
		if (adc_sensor_samples == 1) {
			adc_sensor_sample = result;
			adc_sensor_data_ready = false;
		} else {
			adc_sensor_sample += result;
			adc_sensor_sample >>= 1;
		}
		if (adc_sensor_samples == ADC_SENSOR_MAX_SAMPLES) {
			adc_sensor_samples = 0;
			adc_sensor_data_ready = true;
		} else {
			adc_measure();
		}
	} else if (ch_mask == ADC_CH3) {
		adc2_sensor_samples++;
		if (adc2_sensor_samples == 1) {
			adc2_sensor_sample = result;
			adc2_sensor_data_ready = false;
		} else {
			adc2_sensor_sample += result;
			adc2_sensor_sample >>= 1;
		}
		if (adc2_sensor_samples == ADC2_SENSOR_MAX_SAMPLES) {
			adc2_sensor_samples = 0;
			adc2_sensor_data_ready = true;
		} else {
			adc2_measure();
		}
	}
}

/**
 * \brief Initialize ADC channels for ADCB
 *
 * This will set up the ADC for reading t on the A3BU-Xplained board.
 */
void adcb_sensors_init(void)
{
	struct adc_config adc_conf;
	struct adc_channel_config adc_ch_conf;

	/* Clear the ADC configuration structs */
	adc_read_configuration(&ADCB, &adc_conf);
	adcch_read_configuration(&ADCB, ADC_CH0, &adc_ch_conf);

	/* configure the ADCA module:
	- signed, 12-bit resolution
	- VCC / 1.6 reference
	- 31 kHz max clock rate
	- manual conversion triggering
	- callback function
	*/
	adc_set_conversion_parameters(&adc_conf, ADC_SIGN_ON, ADC_RES_12,
			ADC_REF_VCC);
	adc_set_clock_rate(&adc_conf, 125000UL);
	adc_set_conversion_trigger(&adc_conf, ADC_TRIG_MANUAL, 1, 0);
	adc_write_configuration(&ADCB, &adc_conf);
	adc_set_callback(&ADCB, &adcb_handler);

	/* Configure ADC B channel 0:
	 * - single-ended measurement
	 * - interrupt flag set on completed conversion
	 * - interrupts enabled
	 */
	adcch_set_input(&adc_ch_conf, ADCCH_POS_PIN0, ADCCH_NEG_NONE, 1);
	adcch_set_interrupt_mode(&adc_ch_conf, ADCCH_MODE_COMPLETE);
	adcch_enable_interrupt(&adc_ch_conf);
	adcch_write_configuration(&ADCB, ADC_CH0, &adc_ch_conf);

	/* Configure ADC A channel 1:
	 * - single-ended measurement
	 * - interrupt flag set on completed conversion
	 * - interrupts enabled
	 */
	adcch_set_input(&adc_ch_conf, ADCCH_POS_PIN1, ADCCH_NEG_NONE, 1);
	adcch_write_configuration(&ADCB, ADC_CH1, &adc_ch_conf);

	/* Configure ADC A channel 2 (ADC0):
	 * - single-ended measurement
	 * - interrupt flag set on completed conversion
	 * - interrupts enabled
	 */
	adcch_set_input(&adc_ch_conf, ADCCH_POS_PIN2, ADCCH_NEG_NONE, 1);
	adcch_write_configuration(&ADCB, ADC_CH2, &adc_ch_conf);

	/* Configure ADC A channel 3 (ADC2):
	 * - single-ended measurement
	 * - interrupt flag set on completed conversion
	 * - interrupts enabled
	 */
	adcch_set_input(&adc_ch_conf, ADCCH_POS_PIN3, ADCCH_NEG_NONE, 1);
	adcch_write_configuration(&ADCB, ADC_CH3, &adc_ch_conf);

	adc_enable(&ADCB);
}

/**
 * \brief Initialize ADC channels for NTC and lightsensor
 *
 * This will set up the ADC for reading the NTC and light sensor
 * present on the A3BU-Xplained board.
 */
void adc_sensors_init(void)
{
	struct adc_config adc_conf;
	struct adc_channel_config adc_ch_conf;

	/* Clear the ADC configuration structs */
	adc_read_configuration(&ADCA, &adc_conf);
	adcch_read_configuration(&ADCA, ADC_CH0, &adc_ch_conf);

	/* configure the ADCA module:
	- signed, 12-bit resolution
	- VCC / 1.6 reference
	- 31 kHz max clock rate
	- manual conversion triggering
	- callback function
	*/
	adc_set_conversion_parameters(&adc_conf, ADC_SIGN_ON, ADC_RES_12,
			ADC_REF_VCC);
	adc_set_clock_rate(&adc_conf, 125000UL);
	adc_set_conversion_trigger(&adc_conf, ADC_TRIG_MANUAL, 1, 0);
	adc_write_configuration(&ADCA, &adc_conf);
	adc_set_callback(&ADCA, &adc_handler);

	/* Configure ADC A channel 0 (lightsensor):
	 * - single-ended measurement
	 * - interrupt flag set on completed conversion
	 * - interrupts enabled
	 */
	adcch_set_input(&adc_ch_conf, ADCCH_POS_PIN0, ADCCH_NEG_NONE, 1);
	adcch_set_interrupt_mode(&adc_ch_conf, ADCCH_MODE_COMPLETE);
	adcch_enable_interrupt(&adc_ch_conf);
	adcch_write_configuration(&ADCA, ADC_CH0, &adc_ch_conf);

	/* Configure ADC A channel 1 (NTC sensor):
	 * - single-ended measurement
	 * - interrupt flag set on completed conversion
	 * - interrupts enabled
	 */
	adcch_set_input(&adc_ch_conf, ADCCH_POS_PIN1, ADCCH_NEG_NONE, 1);
	adcch_write_configuration(&ADCA, ADC_CH1, &adc_ch_conf);

	/* Configure ADC A channel 2 (ADC0):
	 * - single-ended measurement
	 * - interrupt flag set on completed conversion
	 * - interrupts enabled
	 */
	adcch_set_input(&adc_ch_conf, ADCCH_POS_PIN4, ADCCH_NEG_NONE, 1);
	adcch_write_configuration(&ADCA, ADC_CH2, &adc_ch_conf);

	/* Configure ADC A channel 2 (ADC2):
	 * - single-ended measurement
	 * - interrupt flag set on completed conversion
	 * - interrupts enabled
	 */
	adcch_set_input(&adc_ch_conf, ADCCH_POS_PIN5, ADCCH_NEG_NONE, 1);
	adcch_write_configuration(&ADCA, ADC_CH3, &adc_ch_conf);

	adc_enable(&ADCA);
}

/**
 * \brief Read the NTC value from the ADC
 *
 * This will read the ADC value of the channel and pin connected to the NTC
 * on the A3BU-Xplained.
 *
 * \retval the raw ADC value from the current ntc_sensor_sample
 */
int16_t ntc_get_raw_value(void)
{
	return ntc_sensor_sample;
}

/**
 * \brief Read the actual temperature from the NTC
 *
 * This function returns the temperature in Celsius by piecewise linearisation
 * of the complex transfer function between NTC resistance and ADC codes. The
 * accuracy of the temperature is somewhat limited.
 *
 * \note The result is inaccurate for temperatures outside 5-45 degrees.
 *
 * \retval the temperature in Celsius
 */
int8_t ntc_get_temperature(void)
{
	int8_t retval = 0;
	float ntc_sample = ntc_sensor_sample;
	if (ntc_sensor_sample > 697) {
		retval = (int8_t)((-0.0295 * ntc_sample) + 40.5);
	} if (ntc_sensor_sample > 420) {
		retval = (int8_t)((-0.0474 * ntc_sample) + 53.3);
	} else {
		retval = (int8_t)((-0.0777 * ntc_sample) + 65.1);
	}
	return retval;
}

/**
 * \brief Read the lightsensor value from the ADC
 *
 * This will read the ADC value of the channel and pin connected to the
 * lightsensor on the A3BU-Xplained.
 *
 * \retval the raw ADC value from the current ntc_sensor_sample
 */
int16_t lightsensor_get_raw_value(void)
{
	return light_sensor_sample;
}

/**
 * \brief Read the lightsensor value from the ADC
 *
 * This will read the ADC value of the channel and pin connected to the
 * lightsensor on the A3BU-Xplained.
 *
 * \retval the raw ADC value from the current ntc_sensor_sample
 */
int16_t adc_get_raw_value(void)
{
	return adc_sensor_sample;
}

/**
 * \brief Read the lightsensor value from the ADC
 *
 * This will read the ADC value of the channel and pin connected to the
 * lightsensor on the A3BU-Xplained.
 *
 * \retval the raw ADC value from the current ntc_sensor_sample
 */
int16_t adc2_get_raw_value(void)
{
	return adc2_sensor_sample;
}

/**
 * \brief Read the lightsensor value from the ADC
 *
 * This will read the ADC value of the channel and pin connected to the
 * lightsensor on the A3BU-Xplained.
 *
 * \retval the raw ADC value from the current ntc_sensor_sample
 */
int16_t adcb0_get_raw_value(void)
{
	return adcb0_sensor_sample;
}

/**
 * \brief Read the lightsensor value from the ADC
 *
 * This will read the ADC value of the channel and pin connected to the
 * lightsensor on the A3BU-Xplained.
 *
 * \retval the raw ADC value from the current ntc_sensor_sample
 */
int16_t adcb1_get_raw_value(void)
{
	return adcb1_sensor_sample;
}

/**
 * \brief Read the lightsensor value from the ADC
 *
 * This will read the ADC value of the channel and pin connected to the
 * lightsensor on the A3BU-Xplained.
 *
 * \retval the raw ADC value from the current ntc_sensor_sample
 */
int16_t adcb2_get_raw_value(void)
{
	return adcb2_sensor_sample;
}

/**
 * \brief Read the lightsensor value from the ADC
 *
 * This will read the ADC value of the channel and pin connected to the
 * lightsensor on the A3BU-Xplained.
 *
 * \retval the raw ADC value from the current ntc_sensor_sample
 */
int16_t adcb3_get_raw_value(void)
{
	return adcb3_sensor_sample;
}