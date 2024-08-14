
#include "DSP28x_Project.h"
#include "PinMode.h"

void scia_loopback_init(void);
void scia_fifo_init(void);
void scia_xmit(int a);
void error();
void scia_msg(char *msg);
void Gpio_select(void);

Uint16 LoopCount;
Uint16 ErrorCount;

void main(void)
{
    Uint16 ReceivedChar;

    InitSysCtrl();
    Gpio_select();
    InitSciGpio();

    DINT;
    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable();

    EnableInterrupts();

    LoopCount = 0;
    ErrorCount = 0;

    scia_fifo_init();	   // Initialize the SCI FIFO
    scia_loopback_init();  // Initalize SCI for digital loop back

    for(;;)
    {
        scia_msg("\n\r#######################################"
                "\n Welcome to Communication Screen"
                "\n Please Select: \n\r "
                "1 Light up all LEDs\n\r "
                "2 Turn off all LEDs\n\r"
                "#######################################  \0");

        while(SciaRegs.SCIFFRX.bit.RXFFST !=1)
        {
            //
            // wait for XRDY =1 for empty state
            //
        }

        ReceivedChar = SciaRegs.SCIRXBUF.all;

        //
        // Echo character back
        //
        scia_msg("  You sent: \0");
        scia_xmit(ReceivedChar);

        switch(ReceivedChar) {
            case '1':
//                GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;
//                GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
                PinMode(34,0);
                PinMode(39,0);
                break;
            case '2':
//                GpioDataRegs.GPBSET.bit.GPIO39 = 1;
//                GpioDataRegs.GPBSET.bit.GPIO34 = 1;
                PinMode(34,PIN_HIGH);
                PinMode(39,PIN_HIGH);
                break;
            default:
                break;
        }


        LoopCount++;
    }
}


void
error(void)
{
    ErrorCount++;
    //__asm("     ESTOP0");  // Uncomment to stop the test here
    //for (;;);
}

//
// scia_loopback_init - Test 1,SCIA  DLB, 8-bit word, baud rate 0x000F, 
// default, 1 STOP bit, no parity
//
void
scia_loopback_init()
{
    SciaRegs.SCICCR.all =0x0007;
    SciaRegs.SCICTL1.all =0x0003;
    SciaRegs.SCICTL2.all =0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA = 0;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 0;
    SciaRegs.SCIHBAUD    =0x0001;
    SciaRegs.SCILBAUD    =0x0024;
    SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
}


void
scia_xmit(int a)
{
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0)  // --> Buffer boþ deðilse
    {

    }
    SciaRegs.SCITXBUF=a;   // --> Mesajý göndermeye devam et
}

void
scia_msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scia_xmit(msg[i]);
        i++;
    }
}

//
// scia_fifo_init - Initalize the SCI FIFO
//
void
scia_fifo_init()
{
    SciaRegs.SCIFFTX.all=0xE040;
    SciaRegs.SCIFFRX.all=0x2044;
    SciaRegs.SCIFFCT.all=0x0;
}


void
Gpio_select(void)
{
    EALLOW;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;   // GPIO34 I/O olarak seçildi
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;    // GPIO 34 çýkýþ olarark ayarlandý
    GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;   // GPIO39 I/O olarak seçildi
    GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;    // GPIO 39 çýkýþ olarark ayarlandý
    EDIS;
}
//
// End of File
//

