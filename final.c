/* 
 * File:   final.c
 * Author: Michael Xiao & Katie Bradford
 *
 * Created on December 13, 2018
 */
#define _SUPPRESS_PLIB_WARNING 1
#include "config.h"
#include "pt_cornell_1_2_1.h"
#include "port_expander.h"
#include "tft_master.h"
#include "tft_gfx.h"

#define in3a BIT_0
#define in2a BIT_1
#define in1a BIT_2
#define in4a BIT_3

#define in3b BIT_7
#define in2b BIT_13
#define in1b BIT_9
#define in4b BIT_11

// Blink LED every BLINK_LED milliseconds
#define BLINK_LED 100

// === Thread Structures =======================================================
static struct pt pt_timer, pt_blink;

// system 1 second interval tick
int sys_time_seconds;

static int pwm_on_time = 3000;
int generate = 4000;
static int on = 0;


// === External Interrupt Service Routine ======================================

void __ISR(_TIMER_3_VECTOR, ipl2) Timer3Handler(void) {
    OpenOC2(OC_ON | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE, pwm_on_time, pwm_on_time); //

    // clear the timer interrupt flag
    mT3ClearIntFlag();
}

void clear(void) {
    mPORTBClearBits(in1a | in2a | in3a | in4a | in1b | in2b | in3b | in4b);

}

// === Timer Thread ============================================================
// update a 1 second tick counter

static PT_THREAD(protothread_timer(struct pt *pt)) {
    PT_BEGIN(pt);
    while (1) {
        // yield time 1 second
        PT_YIELD_TIME_msec(1000);
        sys_time_seconds++;
    } // END WHILE(1)
    PT_END(pt);
} // timer thread
static int turnT = 2; //time between turns
static int stepT = 5; //time between steps
static int print [100];
static int count = 0;
static int drawMode = 0;
// blinks the on board LED every wait_LED mSec

static PT_THREAD(protothread_blink(struct pt *pt)) {
    PT_BEGIN(pt);
    unsigned char out = 255;
    // smiley face test
    //    print[22] = 1;
    //    print[27] = 1;
    //    print[51] = 1;
    //    print[58] = 1;
    //    print[62] = 1;
    //    print[67] = 1;
    //    print[73] = 1;
    //    print[74] = 1;
    //    print[75] = 1;
    //    print[76] = 1;

    static int i, j, k, l, m, q;
    static int zeroCount = 0;

    while (mPORTAReadBits(BIT_3) == 0) PT_YIELD_TIME_msec(1);

    PT_YIELD_TIME_msec(1001);

    for (q = 0; q < 20; q++) {
        if (mPORTAReadBits(BIT_2) == 0) {
            print[count] = 0;
        } else {
            print[count] = 1;
        }
        count++;

        PT_YIELD_TIME_msec(20);
    }
    
    PT_YIELD_TIME_msec(15);
    
    for (q = 0; q < 20; q++) {
        if (mPORTAReadBits(BIT_2) == 0) {
            print[count] = 0;
        } else {
            print[count] = 1;
        }
        count++;

        PT_YIELD_TIME_msec(20);
    }
    
    PT_YIELD_TIME_msec(15);
    
    for (q = 0; q < 20; q++) {
        if (mPORTAReadBits(BIT_2) == 0) {
            print[count] = 0;
        } else {
            print[count] = 1;
        }
        count++;

        PT_YIELD_TIME_msec(20);
    }
    
    PT_YIELD_TIME_msec(15);
    
    for (q = 0; q < 20; q++) {
        if (mPORTAReadBits(BIT_2) == 0) {
            print[count] = 0;
        } else {
            print[count] = 1;
        }
        count++;

        PT_YIELD_TIME_msec(20);
    }
    
    PT_YIELD_TIME_msec(15);
    
    for (q = 0; q < 20; q++) {
        if (mPORTAReadBits(BIT_2) == 0) {
            print[count] = 0;
        } else {
            print[count] = 1;
        }
        count++;

        PT_YIELD_TIME_msec(20);
    }

    //check if we're in sketch mode

    for (l = 0; l < 100; l++) {
        if (print[l] == 0) {
            zeroCount++;
        }
    }

    if (zeroCount > 95) {
        drawMode = 1;
    }

    count = 0;


    while (1) {

        if (drawMode == 0) {
            for (i = 0; i < 10; i++) {

                for (k = 0; k < 10; k++) {

                    if (print[count] == 1) {
                        PT_YIELD_TIME_msec(2000);
                    }


                    count++;

                    for (j = 0; j < 10; j = j + 1) {


                        PT_YIELD_TIME_msec(stepT);

                        PT_YIELD_TIME_msec(turnT);
                        clear();
                        mPORTBSetBits(in1a | in3a);

                        PT_YIELD_TIME_msec(turnT);
                        clear();
                        mPORTBSetBits(in2a | in3a);

                        PT_YIELD_TIME_msec(turnT);
                        clear();
                        mPORTBSetBits(in2a | in4a);

                        PT_YIELD_TIME_msec(turnT);
                        clear();
                        mPORTBSetBits(in1a | in4a);

                    }
                }
                //move back into place
                for (j = 0; j < 100; j = j + 1) {

                    PT_YIELD_TIME_msec(stepT);

                    PT_YIELD_TIME_msec(turnT);
                    clear();
                    mPORTBSetBits(in1a | in4a);

                    PT_YIELD_TIME_msec(turnT);
                    clear();
                    mPORTBSetBits(in2a | in4a);

                    PT_YIELD_TIME_msec(turnT);
                    clear();
                    mPORTBSetBits(in2a | in3a);

                    PT_YIELD_TIME_msec(turnT);
                    clear();
                    mPORTBSetBits(in1a | in3a);

                }
                for (j = 0; j < 10; j++) {

                    PT_YIELD_TIME_msec(stepT);

                    PT_YIELD_TIME_msec(turnT);
                    clear();
                    mPORTBSetBits(in1b | in3b);

                    PT_YIELD_TIME_msec(turnT);
                    clear();
                    mPORTBSetBits(in2b | in3b);

                    PT_YIELD_TIME_msec(turnT);
                    clear();
                    mPORTBSetBits(in2b | in4b);

                    PT_YIELD_TIME_msec(turnT);
                    clear();
                    mPORTBSetBits(in1b | in4b);
                }

            }
            //reset back in place
            for (j = 0; j < 100; j++) {

                PT_YIELD_TIME_msec(stepT);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in1b | in4b);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in2b | in4b);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in2b | in3b);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in1b | in3b);

            }
            
            while(1) PT_YIELD_TIME_msec(30);

        }
        if (drawMode == 1) {
            PT_YIELD_TIME_msec(30);
            int downMovement = mPORTAReadBits(BIT_4);
            int upMovement = mPORTBReadBits(BIT_5);
            int leftMovement = mPORTBReadBits(BIT_14);
            int rightMovement = mPORTBReadBits(BIT_15);

            if (rightMovement != 0) {
                PT_YIELD_TIME_msec(stepT);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in1a | in3a);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in2a | in3a);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in2a | in4a);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in1a | in4a);
                //move right
            } else if (leftMovement != 0) {
                PT_YIELD_TIME_msec(stepT);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in1a | in4a);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in2a | in4a);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in2a | in3a);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in1a | in3a);
                //move left

            } else if (upMovement != 0) {
                PT_YIELD_TIME_msec(stepT);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in1b | in3b);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in2b | in3b);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in2b | in4b);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in1b | in4b);
                //move up 
            } else if (downMovement != 0) {

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in1b | in4b);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in2b | in4b);

                PT_YIELD_TIME_msec(stepT);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in2b | in3b);

                PT_YIELD_TIME_msec(turnT);
                clear();
                mPORTBSetBits(in1b | in3b);

                //move down
            } else {
                //stop moving
            }
        }
    }


    while (1) {
        PT_YIELD_TIME_msec(30);



    } // END WHILE(1)
    PT_END(pt);
} // blink thread

int main(void) {
    ANSELA = 0;
    ANSELB = 0;

    // === config threads ==========
    // turns OFF UART support and debugger pin, unless defines are set
    PT_setup();

    // === setup system wide interrupts  ========
    INTEnableSystemMultiVectoredInt();

    // === Set up timer ========================================================
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_1, 0xFFFF);
    ConfigIntTimer2(T2_INT_OFF);
    mT2ClearIntFlag(); // and clear the interrupt flag

    OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_1, generate);
    ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_2);
    mT3ClearIntFlag(); // and clear the interrupt flag

    // === PWM ===================================================================
    OpenOC2(OC_ON | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE, pwm_on_time, pwm_on_time); //
    // OC3 is PPS group 4, map to RPB9 (pin 18)
    PPSOutput(2, RPB8, OC2);

    // === set up IO Ports =======================================================
    mPORTASetBits(BIT_0); // makes sure it is off
    mPORTASetPinsDigitalOut(BIT_0); // sets port to output

    //for manual control 
    mPORTBSetPinsDigitalIn(BIT_14 | BIT_15 | BIT_5);
    mPORTASetPinsDigitalIn(BIT_4);


    // Outputs
    mPORTBSetPinsDigitalOut(in1a | in2a | in3a | in4a | in1b | in2b | in3b | in4b); // sets port to output


    // Init interrupt pin on PIC32
    PPSInput(4, INT1, RPA3); // RPA3 (Pin 10)
    ConfigINT1(EXT_INT_PRI_2 | FALLING_EDGE_INT | EXT_INT_ENABLE);

    // init the threads
    PT_INIT(&pt_timer);
    PT_INIT(&pt_blink);

    // Init LEDs
    unsigned char out = 255;
    writePE(GPIOY, out);

    // round-robin scheduler for threads
    while (1) {
        PT_SCHEDULE(protothread_timer(&pt_timer));
        PT_SCHEDULE(protothread_blink(&pt_blink));
    } // round-robin loop
} // main
