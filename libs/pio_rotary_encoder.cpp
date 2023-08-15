/*===================================================================

PIO Rotary Encoder

by GitJer

https://github.com/GitJer/Some_RPI-Pico_stuff/tree/main/Rotary_encoder

=====================================================================*/


#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/irq.h"

#include "pio_rotary_encoder.pio.h"

// class to read the rotation of the rotary encoder
class RotaryEncoder
{
public:

    // constructor
    // rotary_encoder_A is the pin for the A of the rotary encoder.
    // The B of the rotary encoder has to be connected to the next GPIO.
    RotaryEncoder(uint rotary_encoder_A, uint rotary_encoder_C, bool pullup, bool pulldown)
    {

        pio00 = pio0;
        pio01 = pio1;
        
        uint8_t rotary_encoder_B = rotary_encoder_A + 1;
        uint8_t rotary_encoder_D = rotary_encoder_C + 1;
        
        // state machine 0
        uint8_t sm = 0;
        uint8_t sm1 = 0;
        // configure the used pins as input with pull up
        pio_gpio_init(pio0, rotary_encoder_A);
        gpio_set_pulls(rotary_encoder_A, pullup, pulldown);
        pio_gpio_init(pio0, rotary_encoder_B);
        gpio_set_pulls(rotary_encoder_B, pullup, pulldown);

        pio_gpio_init(pio1, rotary_encoder_C);
        gpio_set_pulls(rotary_encoder_C, pullup, pulldown);
        pio_gpio_init(pio1, rotary_encoder_D);
        gpio_set_pulls(rotary_encoder_D, pullup, pulldown);
        // load the pio program into the pio memory
        uint offset = pio_add_program(pio0, &pio_rotary_encoder_program);
        uint offset1 = pio_add_program(pio1, &pio_rotary_encoder_program);
        // make a sm config
        pio_sm_config c = pio_rotary_encoder_program_get_default_config(offset);
        pio_sm_config c1 = pio_rotary_encoder_program_get_default_config(offset1);
        // set the 'in' pins
        sm_config_set_in_pins(&c, rotary_encoder_A);
        sm_config_set_in_pins(&c1, rotary_encoder_C);
        // set shift to left: bits shifted by 'in' enter at the least
        // significant bit (LSB), no autopush
        sm_config_set_in_shift(&c, false, false, 0);
        sm_config_set_in_shift(&c1, false, false, 0);
        // set the IRQ handler
        irq_set_exclusive_handler(PIO0_IRQ_0, pio_irq_handler0);
        irq_set_exclusive_handler(PIO1_IRQ_0, pio_irq_handler1);
        // enable the IRQ
        irq_set_enabled(PIO0_IRQ_0, true);
        irq_set_enabled(PIO1_IRQ_0, true);

        pio0_hw->inte0 = PIO_IRQ0_INTE_SM0_BITS | PIO_IRQ0_INTE_SM1_BITS;
        pio1_hw->inte0 = PIO_IRQ0_INTE_SM0_BITS | PIO_IRQ0_INTE_SM1_BITS;
        // init the sm.
        // Note: the program starts after the jump table -> initial_pc = 16
        pio_sm_init(pio0, sm, 16, &c);
        pio_sm_init(pio1, sm1, 16, &c1);
        // enable the sm
        pio_sm_set_enabled(pio0, sm, true);
        pio_sm_set_enabled(pio1, sm1, true);
      
    }

    // set the current rotation to a specific value
    void set_rotation0(int _rotation)
    {
        rotation = _rotation;
    }

    // get the current rotation
    int get_rotation0(void)
    {
        return rotation;
    }

    // set the current rotation to a specific value
    void set_rotation1(int _rotation)
    {
        rotation1 = _rotation;
    }

    // get the current rotation
    int get_rotation1(void)
    {
        return rotation1;
    }

private:
    
    static void pio_irq_handler0()
    {
        
        // test if irq 0 was raised
        if (pio0_hw->irq & 1)
        {
            rotation = rotation - 1;
        }
        // test if irq 1 was raised
        if (pio0_hw->irq & 2)
        {
            rotation = rotation + 1;
        }
        // clear both interrupts
        pio0_hw->irq = 3;
        
    }

    static void pio_irq_handler1()
    {
        
        // test if irq 1 was raised
        if (pio1_hw->irq & 1)
        {
            rotation1 = rotation1 - 1;
        }
        // test if irq 1 was raised
        if (pio1_hw->irq & 2)
        {
            rotation1 = rotation1 + 1;
        }
        // clear both interrupts
        pio1_hw->irq = 3;
        
    }

    // the pio instance
    PIO pio00;
    PIO pio01;
    // the state machine
    uint sm;
    uint sm1;
    // the current location of rotation
    
    static int rotation;
    static int rotation1;
};