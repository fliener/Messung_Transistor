#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/flash.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "driverlib/rom_map.h"
#include "utils/locator.h"
#include "utils/lwiplib.h"
#include "utils/uartstdio.h"
#include "utils/ustdlib.h"
#include "httpserver_raw/httpd.h"
#include "drivers/pinout.h"
#include "io.h"


//*****************************************************************************
#include <driverlib/pwm.h>
#include <driverlib/pwm.c>
#include <driverlib/adc.c>
#include <driverlib/adc.h>
#include <driverlib/pin_map.h>

#define TASKSTACKSIZE   2048
int Arr_Curr_Base[25];
int Arr_Curr_Colle[25];
float Arr_Volt_BE[25];
float Arr_Volt_CE[25];

float Arr_Spannung[25];
float Arr_Strom[25];

double Vout;
double BASE;
double COLLECTOR;
double EMITTER;
float Voltage_BASE;
float Voltage_COLLECTOR;
float Voltage_EMITTER;
float Voltage_R4;
float Curr_COLLEC;
float Curr_BAS;
float Curr_EMI;
float Volt_BE;
float Volt_CE;

int Current;
uint32_t ulTempValueC;
uint32_t ulTempValueF;
uint32_t adcGetValues;
uint32_t ulADC0Value[8];
uint32_t ON=0;
uint32_t OFF=250;
uint32_t ui32Loop;
uint32_t ui32Lupe;
uint32_t i;
uint32_t volatile help;
uint32_t volatile hilfe;
uint32_t end = 101;


void Funktion_ADC(void);


void ADC0IntHandler(void)
{
    // Clear interrupt Flag
    ADCIntClear(ADC0_BASE, 0);

    ADCSequenceDataGet(ADC0_BASE, 0, ulADC0Value);

    adcGetValues=1;
}
//*****************************************************************************


double A_Aray[]={3.1,32,0.4, 21, 11, 2.2, 3.089, 0.00021};

// Defines for setting up the system clock.
#define SYSTICKHZ               100
#define SYSTICKMS               (1000 / SYSTICKHZ)

#define SYSTICK_INT_PRIORITY    0x80// Interrupt priority definitions.  The top 3 bits of these values are
#define ETHERNET_INT_PRIORITY   0xC0// significant with lower values indicating higher priority interrupts.

extern void httpd_init(void);// External Application references.

// SSI tag indices for each entry in the g_pcSSITags array.
#define SSI_INDEX_0_Var  0
#define SSI_INDEX_1_Var  1
#define SSI_INDEX_2_Var  2
#define SSI_INDEX_3_Var  3
#define SSI_INDEX_4_Var  4
#define SSI_INDEX_5_Var  5
#define SSI_INDEX_6_Var  6
#define SSI_INDEX_7_Var  7
#define SSI_INDEX_8_Var  8
#define SSI_INDEX_9_Var  9
#define SSI_INDEX_10_Var  10
#define SSI_INDEX_11_Var  11
#define SSI_INDEX_12_Var  12
#define SSI_INDEX_13_Var  13
#define SSI_INDEX_14_Var  14
#define SSI_INDEX_15_Var  15
#define SSI_INDEX_16_Var  16
#define SSI_INDEX_17_Var  17
#define SSI_INDEX_18_Var  18
#define SSI_INDEX_19_Var  19
#define SSI_INDEX_20_Var  20
#define SSI_INDEX_21_Var  21
#define SSI_INDEX_22_Var  22
#define SSI_INDEX_23_Var  23
#define SSI_INDEX_24_Var  24
#define SSI_INDEX_Spann_0  25
#define SSI_INDEX_Spann_1  26
#define SSI_INDEX_Spann_2  27
#define SSI_INDEX_Spann_3  28
#define SSI_INDEX_Spann_4  29
#define SSI_INDEX_Spann_5  30
#define SSI_INDEX_Spann_6  31
#define SSI_INDEX_Spann_7  32
#define SSI_INDEX_Spann_8  33
#define SSI_INDEX_Spann_9  34
#define SSI_INDEX_Spann_10  35
#define SSI_INDEX_Spann_11  36
#define SSI_INDEX_Spann_12  37
#define SSI_INDEX_Spann_13  38
#define SSI_INDEX_Spann_14  39
#define SSI_INDEX_Spann_15  40
#define SSI_INDEX_Spann_16  41
#define SSI_INDEX_Spann_17  42
#define SSI_INDEX_Spann_18  43
#define SSI_INDEX_Spann_19  44
#define SSI_INDEX_Spann_20  45
#define SSI_INDEX_Spann_21  46
#define SSI_INDEX_Spann_22  47
#define SSI_INDEX_Spann_23  48
#define SSI_INDEX_Spann_24  49

#define SSI_INDEX_CUR_B_0  50
#define SSI_INDEX_CUR_B_1  51
#define SSI_INDEX_CUR_B_2  52
#define SSI_INDEX_CUR_B_3  53
#define SSI_INDEX_CUR_B_4  54
#define SSI_INDEX_CUR_B_5  55
#define SSI_INDEX_CUR_B_6  56
#define SSI_INDEX_CUR_B_7  57
#define SSI_INDEX_CUR_B_8  58
#define SSI_INDEX_CUR_B_9  59
#define SSI_INDEX_CUR_B_10 60
#define SSI_INDEX_CUR_B_11 61
#define SSI_INDEX_CUR_B_12 62
#define SSI_INDEX_CUR_B_13 63
#define SSI_INDEX_CUR_B_14 64
#define SSI_INDEX_CUR_B_15 65
#define SSI_INDEX_CUR_B_16 66
#define SSI_INDEX_CUR_B_17 67
#define SSI_INDEX_CUR_B_18 68
#define SSI_INDEX_CUR_B_19 69
#define SSI_INDEX_CUR_B_20 70
#define SSI_INDEX_CUR_B_21 71
#define SSI_INDEX_CUR_B_22 72
#define SSI_INDEX_CUR_B_23 73
#define SSI_INDEX_CUR_B_24 74

#define SSI_INDEX_CUR_C_0 75
#define SSI_INDEX_CUR_C_1 76
#define SSI_INDEX_CUR_C_2 77
#define SSI_INDEX_CUR_C_3 78
#define SSI_INDEX_CUR_C_4 79
#define SSI_INDEX_CUR_C_5 80
#define SSI_INDEX_CUR_C_6 81
#define SSI_INDEX_CUR_C_7 82
#define SSI_INDEX_CUR_C_8 83
#define SSI_INDEX_CUR_C_9 84
#define SSI_INDEX_CUR_C_10 85
#define SSI_INDEX_CUR_C_11 86
#define SSI_INDEX_CUR_C_12 87
#define SSI_INDEX_CUR_C_13 88
#define SSI_INDEX_CUR_C_14 89
#define SSI_INDEX_CUR_C_15 90
#define SSI_INDEX_CUR_C_16 91
#define SSI_INDEX_CUR_C_17 92
#define SSI_INDEX_CUR_C_18 93
#define SSI_INDEX_CUR_C_19 94
#define SSI_INDEX_CUR_C_20 95
#define SSI_INDEX_CUR_C_21 96
#define SSI_INDEX_CUR_C_22 97
#define SSI_INDEX_CUR_C_23 98
#define SSI_INDEX_CUR_C_24 99


// This array holds all the strings that are to be recognized as SSI tag
// names by the HTTPD server.  The server will call SSIHandler to request a
// replacement string whenever the pattern <!--#tagname--> (where tagname
// appears in the following array) is found in ".ssi", ".shtml" or ".shtm"
// files that it serves.
static const char *g_pcConfigSSITags[] =
{
    "LEDtxt",        // SSI_INDEX_0_Var
    "1_Var",         // SSI_INDEX_1_Var
    "2_Var",         // SSI_INDEX_2_Var
    "3_Var",         // SSI_INDEX_3_Var
    "4_Var",         // SSI_INDEX_4_Var
    "5_Var",         // SSI_INDEX_5_Var
    "6_Var",         // SSI_INDEX_6_Var
    "7_Var",         // SSI_INDEX_7_Var
    "8_Var",         // SSI_INDEX_8_Var
    "9_Var",         // SSI_INDEX_9_Var
    "10_Var",         // SSI_INDEX_10_Var
    "11_Var",         // SSI_INDEX_11_Var
    "12_Var",         // SSI_INDEX_12_Var
    "13_Var",         // SSI_INDEX_13_Var
    "14_Var",         // SSI_INDEX_14_Var
    "15_Var",         // SSI_INDEX_15_Var
    "16_Var",         // SSI_INDEX_16_Var
    "17_Var",         // SSI_INDEX_17_Var
    "18_Var",         // SSI_INDEX_18_Var
    "19_Var",         // SSI_INDEX_19_Var
    "20_Var",         // SSI_INDEX_20_Var
    "21_Var",         // SSI_INDEX_21_Var
    "22_Var",         // SSI_INDEX_22_Var
    "23_Var",         // SSI_INDEX_23_Var
    "24_Var",         // SSI_INDEX_24_Var
    "Spann_0",         // SSI_INDEX_Spann_0
    "Spann_1",         // SSI_INDEX_Spann_1
    "Spann_2",         // SSI_INDEX_Spann_2
    "Spann_3",         // SSI_INDEX_Spann_3
    "Spann_4",         // SSI_INDEX_Spann_4
    "Spann_5",         // SSI_INDEX_Spann_5
    "Spann_6",         // SSI_INDEX_Spann_6
    "Spann_7",         // SSI_INDEX_Spann_7
    "Spann_8",         // SSI_INDEX_Spann_8
    "Spann_9",         // SSI_INDEX_Spann_9
    "Spann_10",         // SSI_INDEX_Spann_10
    "Spann_11",         // SSI_INDEX_Spann_11
    "Spann_12",         // SSI_INDEX_Spann_12
    "Spann_13",         // SSI_INDEX_Spann_13
    "Spann_14",         // SSI_INDEX_Spann_14
    "Spann_15",         // SSI_INDEX_Spann_15
    "Spann_16",         // SSI_INDEX_Spann_16
    "Spann_17",         // SSI_INDEX_Spann_17
    "Spann_18",         // SSI_INDEX_Spann_18
    "Spann_19",         // SSI_INDEX_Spann_19
    "Spann_20",         // SSI_INDEX_Spann_20
    "Spann_21",         // SSI_INDEX_Spann_21
    "Spann_22",         // SSI_INDEX_Spann_22
    "Spann_23",         // SSI_INDEX_Spann_23
    "Spann_24",         // SSI_INDEX_Spann_24

    "CUR_B_0",         // SSI_INDEX_CUR_B_0
    "CUR_B_1",         // SSI_INDEX_CUR_B_1
    "CUR_B_2",         // SSI_INDEX_CUR_B_2
    "CUR_B_3",         // SSI_INDEX_CUR_B_3
    "CUR_B_4",         // SSI_INDEX_CUR_B_4
    "CUR_B_5",         // SSI_INDEX_CUR_B_5
    "CUR_B_6",         // SSI_INDEX_CUR_B_6
    "CUR_B_7",         // SSI_INDEX_CUR_B_7
    "CUR_B_8",         // SSI_INDEX_CUR_B_8
    "CUR_B_9",         // SSI_INDEX_CUR_B_9
    "CUR_B_10",         // SSI_INDEX_CUR_B_10
    "CUR_B_11",         // SSI_INDEX_CUR_B_11
    "CUR_B_12",         // SSI_INDEX_CUR_B_12
    "CUR_B_13",         // SSI_INDEX_CUR_B_13
    "CUR_B_14",         // SSI_INDEX_CUR_B_14
    "CUR_B_15",         // SSI_INDEX_CUR_B_15
    "CUR_B_16",         // SSI_INDEX_CUR_B_16
    "CUR_B_17",         // SSI_INDEX_CUR_B_17
    "CUR_B_18",         // SSI_INDEX_CUR_B_18
    "CUR_B_19",         // SSI_INDEX_CUR_B_19
    "CUR_B_20",         // SSI_INDEX_CUR_B_20
    "CUR_B_21",         // SSI_INDEX_CUR_B_21
    "CUR_B_22",         // SSI_INDEX_CUR_B_22
    "CUR_B_23",         // SSI_INDEX_CUR_B_23
    "CUR_B_24",         // SSI_INDEX_CUR_B_24

    "CUR_C_0",         // SSI_INDEX_CUR_C_0
    "CUR_C_1",         // SSI_INDEX_CUR_C_1
    "CUR_C_2",         // SSI_INDEX_CUR_C_2
    "CUR_C_3",         // SSI_INDEX_CUR_C_3
    "CUR_C_4",         // SSI_INDEX_CUR_C_4
    "CUR_C_5",         // SSI_INDEX_CUR_C_5
    "CUR_C_6",         // SSI_INDEX_CUR_C_6
    "CUR_C_7",         // SSI_INDEX_CUR_C_7
    "CUR_C_8",         // SSI_INDEX_CUR_C_8
    "CUR_C_9",         // SSI_INDEX_CUR_C_9
    "CUR_C_10",         // SSI_INDEX_CUR_C_10
    "CUR_C_11",         // SSI_INDEX_CUR_C_11
    "CUR_C_12",         // SSI_INDEX_CUR_C_12
    "CUR_C_13",         // SSI_INDEX_CUR_C_13
    "CUR_C_14",         // SSI_INDEX_CUR_C_14
    "CUR_C_15",         // SSI_INDEX_CUR_C_15
    "CUR_C_16",         // SSI_INDEX_CUR_C_16
    "CUR_C_17",         // SSI_INDEX_CUR_C_17
    "CUR_C_18",         // SSI_INDEX_CUR_C_18
    "CUR_C_19",         // SSI_INDEX_CUR_C_19
    "CUR_C_20",         // SSI_INDEX_CUR_C_20
    "CUR_C_21",         // SSI_INDEX_CUR_C_21
    "CUR_C_22",         // SSI_INDEX_CUR_C_22
    "CUR_C_23",         // SSI_INDEX_CUR_C_23
    "CUR_C_24",         // SSI_INDEX_CUR_C_24
};

// The number of individual SSI tags that the HTTPD server can expect to
// find in our configuration pages.

#define NUM_CONFIG_SSI_TAGS     (sizeof(g_pcConfigSSITags) / sizeof (char *))

// Prototype for the main handler used to process server-side-includes for the
// application's web-based configuration screens.
static int32_t SSIHandler(int32_t iIndex, char *pcInsert, int32_t iInsertLen);

// Timeout for DHCP address request (in seconds).
#ifndef DHCP_EXPIRE_TIMER_SECS
#define DHCP_EXPIRE_TIMER_SECS  45
#endif

uint32_t g_ui32IPAddress;// The current IP address.
uint32_t g_ui32SysClock;// The system clock frequency.  Used by the SD card driver.


// This function is called by the HTTP server whenever it encounters an SSI
// tag in a web page.  The iIndex parameter provides the index of the tag in
// the g_pcConfigSSITags array. This function writes the substitution text
// into the pcInsert array, writing no more than iInsertLen characters.

//*****************************************************************************
static int32_t SSIHandler(int32_t iIndex, char *pcInsert, int32_t iInsertLen)
{
    // Which SSI tag have we been passed?
    switch(iIndex)
    {
        case SSI_INDEX_0_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[2];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_1_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[3];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_2_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[4];
        post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_3_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[5];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_4_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[6];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_5_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[7];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_6_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[8];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_7_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[9];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_8_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[10];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_9_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[11];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_10_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[12];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_11_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[13];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_12_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[14];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_13_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[15];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_14_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[16];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_15_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[17];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_16_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[18];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_17_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[19];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_18_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[20];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_19_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[21];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_20_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[22];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_21_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[23];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_22_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[24];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_23_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[0];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_24_Var:
            g_ulAnimSpeed2=Arr_Volt_CE[1];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_0:
            g_ulAnimSpeed2=Arr_Volt_BE[2];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_1:
            g_ulAnimSpeed2=Arr_Volt_BE[3];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_2:
            g_ulAnimSpeed2=Arr_Volt_BE[4];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_3:
            g_ulAnimSpeed2=Arr_Volt_BE[5];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_4:
            g_ulAnimSpeed2=Arr_Volt_BE[6];
            post_to_server2(pcInsert, iInsertLen);
            break;

        case SSI_INDEX_Spann_5:
            g_ulAnimSpeed2=Arr_Volt_BE[7];
            post_to_server2(pcInsert, iInsertLen);
            break;

        case SSI_INDEX_Spann_6:
            g_ulAnimSpeed2=Arr_Volt_BE[8];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_7:
            g_ulAnimSpeed2=Arr_Volt_BE[9];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_8:
            g_ulAnimSpeed2=Arr_Volt_BE[10];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_9:
            g_ulAnimSpeed2=Arr_Volt_BE[11];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_10:
            g_ulAnimSpeed2=Arr_Volt_BE[12];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_11:
            g_ulAnimSpeed2=Arr_Volt_BE[13];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_12:
            g_ulAnimSpeed2=Arr_Volt_BE[14];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_13:
            g_ulAnimSpeed2=Arr_Volt_BE[15];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_14:
            g_ulAnimSpeed2=Arr_Volt_BE[16];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_15:
            g_ulAnimSpeed2=Arr_Volt_BE[17];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_16:
            g_ulAnimSpeed2=Arr_Volt_BE[18];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_17:
            g_ulAnimSpeed2=Arr_Volt_BE[19];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_18:
            g_ulAnimSpeed2=Arr_Volt_BE[20];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_19:
            g_ulAnimSpeed2=Arr_Volt_BE[21];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_20:
            g_ulAnimSpeed2=Arr_Volt_BE[22];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_21:
            g_ulAnimSpeed2=Arr_Volt_BE[23];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_22:
            g_ulAnimSpeed2=Arr_Volt_BE[24];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_23:
            g_ulAnimSpeed2=Arr_Volt_BE[0];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_Spann_24:
            g_ulAnimSpeed2=Arr_Volt_BE[1];
            post_to_server2(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_0:
            g_ulAnimSpeed=Arr_Curr_Base[2];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_1:
            g_ulAnimSpeed=Arr_Curr_Base[3];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_2:
            g_ulAnimSpeed=Arr_Curr_Base[4];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_3:
            g_ulAnimSpeed=Arr_Curr_Base[5];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_4:
            g_ulAnimSpeed=Arr_Curr_Base[6];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_5:
            g_ulAnimSpeed=Arr_Curr_Base[7];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_6:
            g_ulAnimSpeed=Arr_Curr_Base[8];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_7:
            g_ulAnimSpeed=Arr_Curr_Base[9];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_8:
            g_ulAnimSpeed=Arr_Curr_Base[10];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_9:
            g_ulAnimSpeed=Arr_Curr_Base[11];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_10:
            g_ulAnimSpeed=Arr_Curr_Base[12];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_11:
            g_ulAnimSpeed=Arr_Curr_Base[13];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_12:
            g_ulAnimSpeed=Arr_Curr_Base[14];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_13:
            g_ulAnimSpeed=Arr_Curr_Base[15];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_14:
            g_ulAnimSpeed=Arr_Curr_Base[16];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_15:
            g_ulAnimSpeed=Arr_Curr_Base[17];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_16:
            g_ulAnimSpeed=Arr_Curr_Base[18];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_17:
            g_ulAnimSpeed=Arr_Curr_Base[19];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_18:
            g_ulAnimSpeed=Arr_Curr_Base[20];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_19:
            g_ulAnimSpeed=Arr_Curr_Base[21];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_20:
            g_ulAnimSpeed=Arr_Curr_Base[22];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_21:
            g_ulAnimSpeed=Arr_Curr_Base[23];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_22:
            g_ulAnimSpeed=Arr_Curr_Base[24];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_23:
            g_ulAnimSpeed=Arr_Curr_Base[0];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_B_24:
            g_ulAnimSpeed=Arr_Curr_Base[1];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_0:
            g_ulAnimSpeed=Arr_Curr_Colle[2];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_1:
            g_ulAnimSpeed=Arr_Curr_Colle[3];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_2:
            g_ulAnimSpeed=Arr_Curr_Colle[4];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_3:
            g_ulAnimSpeed=Arr_Curr_Colle[5];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_4:
            g_ulAnimSpeed=Arr_Curr_Colle[6];
            post_to_server(pcInsert, iInsertLen);
            break;
//*******************
        case SSI_INDEX_CUR_C_5:
            g_ulAnimSpeed=Arr_Curr_Colle[7];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_6:
            g_ulAnimSpeed=Arr_Curr_Colle[8];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_7:
            g_ulAnimSpeed=Arr_Curr_Colle[9];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_8:
            g_ulAnimSpeed=Arr_Curr_Colle[10];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_9:
            g_ulAnimSpeed=Arr_Curr_Colle[11];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_10:
            g_ulAnimSpeed=Arr_Curr_Colle[12];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_11:
            g_ulAnimSpeed=Arr_Curr_Colle[13];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_12:
            g_ulAnimSpeed=Arr_Curr_Colle[14];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_13:
            g_ulAnimSpeed=Arr_Curr_Colle[15];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_14:
            g_ulAnimSpeed=Arr_Curr_Colle[16];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_15:
            g_ulAnimSpeed=Arr_Curr_Colle[17];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_16:
            g_ulAnimSpeed=Arr_Curr_Colle[18];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_17:
            g_ulAnimSpeed=Arr_Curr_Colle[19];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_18:
            g_ulAnimSpeed=Arr_Curr_Colle[20];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_19:
            g_ulAnimSpeed=Arr_Curr_Colle[21];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_20:
            g_ulAnimSpeed=Arr_Curr_Colle[22];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_21:
            g_ulAnimSpeed=Arr_Curr_Colle[23];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_22:
            g_ulAnimSpeed=Arr_Curr_Colle[24];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_23:
            g_ulAnimSpeed=Arr_Curr_Colle[0];
            post_to_server(pcInsert, iInsertLen);
            break;
        case SSI_INDEX_CUR_C_24:
            g_ulAnimSpeed=Arr_Curr_Colle[1];
            post_to_server(pcInsert, iInsertLen);
            break;

        default:
            usnprintf(pcInsert, iInsertLen, "??");
            break;

    }

    // Tell the server how many characters our insert string contains.
    return(strlen(pcInsert));
}
//*****************************************************************************

// The interrupt handler for the SysTick interrupt.
//*****************************************************************************
void SysTickIntHandler(void)
{
    // Call the lwIP timer handler.
    lwIPTimer(SYSTICKMS);
}
//*****************************************************************************

// Display an lwIP type IP Address.
//*****************************************************************************
void DisplayIPAddress(uint32_t ui32Addr)
{
    char pcBuf[16];

    // Convert the IP Address into a string.
    usprintf(pcBuf, "%d.%d.%d.%d", ui32Addr & 0xff, (ui32Addr >> 8) & 0xff,
            (ui32Addr >> 16) & 0xff, (ui32Addr >> 24) & 0xff);

    // Display the string.
    UARTprintf(pcBuf);
}
//*****************************************************************************

// Required by lwIP library to support any host-related timer functions.
//*****************************************************************************
void lwIPHostTimerHandler(void)
{
    uint32_t ui32NewIPAddress;

    // Get the current IP address.
    ui32NewIPAddress = lwIPLocalIPAddrGet();

    // See if the IP address has changed.
    if(ui32NewIPAddress != g_ui32IPAddress)
    {
        // See if there is an IP address assigned.
        if(ui32NewIPAddress == 0xffffffff)
        {
            // Indicate that there is no link.
            UARTprintf("Waiting for link.\n");
        }
        else if(ui32NewIPAddress == 0)
        {
            // There is no IP address, so indicate that the DHCP process is
            // running.
            UARTprintf("Waiting for IP address.\n");
        }
        else
        {
            // Display the new IP address.
            UARTprintf("IP Address: ");
            DisplayIPAddress(ui32NewIPAddress);
            UARTprintf("\n");
            UARTprintf("Open a browser and enter the IP address.\n");
        }

        // Save the new IP address.
        g_ui32IPAddress = ui32NewIPAddress;
    }

    // If there is not an IP address.
    if((ui32NewIPAddress == 0) || (ui32NewIPAddress == 0xffffffff))
    {
        // Do nothing and keep waiting.
    }
}
//*****************************************************************************

int main(void)
{
    uint32_t ui32User0, ui32User1;
    uint8_t pui8MACArray[8];


    SysCtlMOSCConfigSet(SYSCTL_MOSC_HIGHFREQ);
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |SYSCTL_OSC_MAIN |SYSCTL_USE_PLL |SYSCTL_CFG_VCO_480), 120000000);

    // LED´s werden als Ethernet LED´s konfiguriert
    PinoutSet(true, false);

    UARTStdioConfig(0, 115200, g_ui32SysClock);

    // Clear the terminal and print a banner.
    UARTprintf("\033[2J\033[H");
    UARTprintf("STROM- SPANNUNGSKENNLINIE\n\n");

    // Configure SysTick for a periodic interrupt.
    MAP_SysTickPeriodSet(g_ui32SysClock / SYSTICKHZ);
    MAP_SysTickEnable();
    MAP_SysTickIntEnable();

    // Configure the hardware MAC address for Ethernet Controller filtering of
    // incoming packets.  The MAC address will be stored in the non-volatile
    // USER0 and USER1 registers.
    MAP_FlashUserGet(&ui32User0, &ui32User1);

    // Tell the user what we are doing just now.
    UARTprintf("Waiting for IP.\n");

    // Convert the 24/24 split MAC address from NV ram into a 32/16 split
    // MAC address needed to program the hardware registers, then program
    // the MAC address into the Ethernet Controller registers.
    pui8MACArray[0] = ((ui32User0 >>  0) & 0xff);
    pui8MACArray[1] = ((ui32User0 >>  8) & 0xff);
    pui8MACArray[2] = ((ui32User0 >> 16) & 0xff);
    pui8MACArray[3] = ((ui32User1 >>  0) & 0xff);
    pui8MACArray[4] = ((ui32User1 >>  8) & 0xff);
    pui8MACArray[5] = ((ui32User1 >> 16) & 0xff);

    // Initialze the lwIP library, using DHCP. lwIP = TCP/IP-Stack für ES-Controller
    // 0xC0A8166F is 192.168.22.111
    // 0xFFFFFF00 is 255.255.255.0
    lwIPInit(g_ui32SysClock, pui8MACArray, 0xC0A8166F, 0xFFFFFF00, 0, IPADDR_USE_STATIC);

//    LocatorInit();
//    LocatorMACAddrSet(pui8MACArray);
//    LocatorAppTitleSet("file_index_htm");

    // Server init
    httpd_init();

    // Pass our tag information to the HTTP server.
    http_set_ssi_handler((tSSIHandler)SSIHandler, g_pcConfigSSITags,
            NUM_CONFIG_SSI_TAGS);

    // Initialize IO controls
    io_init();
//*****************************************************************************
    Funktion_ADC();

    IntPrioritySet(INT_ADC0SS0, 1);
    ADCIntRegister(ADC0_BASE, 0, ADC0IntHandler);
    IntRegister(INT_ADC0SS0, ADC0IntHandler);
    ADCIntEnable(ADC0_BASE, 0);
    IntEnable(INT_ADC0SS0);
    IntMasterEnable();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinConfigure(GPIO_PF2_M0PWM2);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);    //PWM OutputPin PF2 !!!

    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenEnable(PWM0_BASE, PWM_GEN_1);

    PWMOutputState(PWM0_BASE, (PWM_OUT_2_BIT | PWM_OUT_3_BIT), true);

    ADCSequenceEnable(ADC0_BASE, 0);
//*****************************************************************************


    // Loop forever, processing the on-screen animation.  All other work is
    // done in the interrupt handlers.

    while(1)
    {

        ON=0;
        OFF=250;
        help=0;
        // Toggle the GPIO
        MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1,
                (MAP_GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_1) ^
                 GPIO_PIN_1));

//*****************************************************************************

        for(i=0;i<25;i++)
        {
        Vout = ulADC0Value[0];
        BASE = ulADC0Value[1];
        COLLECTOR = ulADC0Value[2];
        EMITTER = ulADC0Value[3];

        Voltage_BASE = ((BASE/4095)*3.3);
        Voltage_COLLECTOR = ((COLLECTOR/4095)*3.3);
        Voltage_EMITTER = ((EMITTER/4095)*3.3);

        Voltage_R4 = (3 - Voltage_COLLECTOR);
        Curr_COLLEC = ((Voltage_R4 / 98)*1000000);             // Kollektor_Strom

        Curr_EMI = ((Voltage_EMITTER / 500)*1000000);
        Curr_BAS = ((Vout - Voltage_BASE) / 100);                // Basis_Strom

        Volt_BE = (Voltage_BASE - Voltage_EMITTER);         // Basis_Emitter

        Volt_CE = (Voltage_COLLECTOR - Voltage_EMITTER);    // Kollektor_Emitter


        Arr_Volt_BE[i]=Volt_BE;
        Arr_Volt_CE[i]=Volt_CE;
        Arr_Curr_Base[i]=Curr_BAS;

        if(Curr_COLLEC<0)
        {Arr_Curr_Colle[i]=0;}
        else
        {
        Arr_Curr_Colle[i]=Curr_COLLEC;
        }
//        Current = Voltage / 100 * 1000;
//        Arr_Strom[i]=Current;

            PWMGenPeriodSet(PWM0_BASE,  PWM_GEN_1, 500);     /* 100% (40us) Tpwm_clk=80ns, 80n*500 = 40us (25kHz)    */
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, ON);      /* 50%  (20us)  (PWM0_BASE, PWM_OUT_2, 250)                                        */
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, OFF);     /* 25%  (10us)  (PWM0_BASE, PWM_OUT_3, 125)                                        */

       for(ui32Lupe=0;ui32Lupe<6000000;ui32Lupe++)
       {
           help=help+10;
       }

       ON=(ON+20);
       OFF=(OFF-10);
        }

        for(ui32Lupe=0;ui32Lupe<10000000;ui32Lupe++)
        {
            hilfe=hilfe+10;
        }

        if (adcGetValues==1)
        {
            ADCSequenceDisable(ADC0_BASE, 0);
            ADCIntDisable(ADC0_BASE, 0);
            IntDisable(INT_ADC0SS0);

            adcGetValues = 0;

            ADCIntEnable(ADC0_BASE, 0);
            IntEnable(INT_ADC0SS0);
            ADCSequenceEnable(ADC0_BASE, 0);


        }
//*****************************************************************************


    }

    return (0);
}

void Funktion_ADC(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_5);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_0);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_1);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2);


    ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PLL | ADC_CLOCK_RATE_FULL, 30);
//                             INPUT Clock PLL=480Hz     ALL SAMPLES      480MHz/30=ADC Clock
    ADCSequenceDisable(ADC0_BASE, 0);


    ADCHardwareOversampleConfigure(ADC0_BASE, 16);//DURCHSCHNITT

    ADCReferenceSet(ADC0_BASE, ADC_REF_INT);//INTERNE 3V WERDEN VERWENDET

    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_ALWAYS, 0);

    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH1);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_CH8);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 2, ADC_CTL_CH3);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 3, (ADC_CTL_CH2 | ADC_CTL_IE | ADC_CTL_END));
}

