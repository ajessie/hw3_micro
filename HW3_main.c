// A simple stopwatch
// The sys clock is modified in system_msp432p401r.c to be 48MHz

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"


// A structure that holds a large set of characteristics for graphics including foreground color, background color, fot of
Graphics_Context g_sContext;

void InitGraphics();
void InitFonts();
void Initialize();
void InitTimer();


// makeString gets min, sec and tenth and returns the string made up of them.
// Important note: char *string should already have enough space to hold "00:00:0" format
// example: makeString(2, 3, 9, myString) will update the content of myString to "02:03:9"
void makeString(unsigned int min, unsigned int sec, int unsigned tenth, char *string)
{
}

int main(void)
{
    Initialize();

    unsigned int min = 0, sec = 0, tenth = 0;
    char string[8] = "00:00:0";


    Graphics_drawString(&g_sContext, string, -1, 10, 70, false);

    while (1)
    {
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
}

void Initialize() {
    // Stop the watchdog timer
    WDT_A_hold(WDT_A_BASE);

    // Initialize the graphics
    InitGraphics();

    // Initialize the timer
    InitTimer();
}
