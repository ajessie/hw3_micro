// A simple stopwatch
// The sys clock is modified in system_msp432p401r.c to be 48MHz

////////////////////////////////////////////////
//Jessie Acfalle
//9/21/18
//file implements the use of a timer to create a simple timer
//the program is supposed to convert integer to ascii, however mine does not
//only the timer is implented and displayed on screen
//
////////////////////////////////////////////////
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"


// Example program to demonstrate sprintf()
#include<stdio.h>

// A structure that holds a large set of characteristics for graphics including foreground color, background color, fot of
Graphics_Context g_sContext;

volatile uint32_t curValue;

#define ONE_SEC_COUNT   48000000
#define TENTH_SEC_COUNT 4800000

//#define ONE_SEC_COUNT  3000000
//#define HALF_SEC_COUNT 1500000
//#define TWO_SEC_COUNT  6000000

void InitGraphics();
void InitFonts();
void Initialize();
void InitTimer();


// makeString gets min, sec and tenth and returns the string made up of them.
// Important note: char *string should already have enough space to hold "00:00:0" format
// example: makeString(2, 3, 9, myString) will update the content of myString to "02:03:9"
void makeString(unsigned min, unsigned int sec, int unsigned tenth, char *string)
{
    int x,y,z,i;
for (i = 0;i<=9;i++)
{
    x = (char)(min%10);
    x = x/10;
    x = '0' + x;

    y = (char)(sec%10);
    y = y/10;
    y = '0' + y;

    z = (char)(tenth);

    z = '0' + z;
}

}

int main(void)
{
    Initialize();
    char string[10];
    unsigned int min = 0, sec = 0, tenth = 0;

    while (1)
    {
        curValue = Timer32_getValue(TIMER32_BASE);
        int tenth_of_sec = tenth;


            if(curValue==0)
            {
                for (tenth_of_sec=0; tenth_of_sec < 9;)                    //if tenth of second is less than 9, go into the loop
                {

                tenth_of_sec++;                                            //increment the tenth second counter

                if(tenth_of_sec == 9)                                      //if the tenth of second counter reaches zero
                {
                    sec++;                                                 //increment the second counter
                    tenth_of_sec = 0;                                      //reset tenth of second counter
                }
                if (sec == 60)                                             //check to see if the second counter has reached 60
                {
                    min++;                                                 //increment minute counter here
                    sec = 0;                                               //reset the second counter
                }

                if ((min == 59) && (sec == 59) && (tenth_of_sec == 9))       //check to see if we have reached the limit
                {
                    min = 0;                                               //reset everything
                    sec = 0;
                    tenth_of_sec = 0;
                }

            //makeString(min,sec,tenth_of_sec,string);
             sprintf(string,"%d:%d:%d",min, sec, tenth_of_sec);
             Graphics_drawString(&g_sContext, string, -1, 10, 70, true);

                }
           }

    }
}

void InitGraphics() {

    Graphics_initContext(&g_sContext,
                         &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    Graphics_setFont(&g_sContext, &g_sFontCmtt16);

    InitFonts();
    Graphics_setFont(&g_sContext, &g_sFontCmss18b);

    Graphics_clearDisplay(&g_sContext);
}

void InitFonts() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
}


void InitTimer() {
    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    Timer32_setCount(TIMER32_BASE,TENTH_SEC_COUNT);
    Timer32_startTimer(TIMER32_0_BASE, false);

}

void Initialize() {
    // Stop the watchdog timer
    WDT_A_hold(WDT_A_BASE);

    // Initialize the graphics
    InitGraphics();

    // Initialize the timer
    InitTimer();
}
