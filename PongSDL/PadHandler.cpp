//##includes
#include <cstdint>
#include <tamtypes.h>
#include <kernel.h>
#include <loadfile.h>
#include <sifrpc.h>
#include <gs_privileged.h>
#include <libpad.h>
#include "PadHandler.h"
#include <iostream>
//HELLO THIS IS COMPLETELY ROBBED FROM THE PS2SDK SAMPLES - I JUST PORTED THE CODE I NEEDED TO C++
//IT'S NOT TAGGED WITH A MAKER AND (ADMITTEDLY) I HAVEN'T READ THE LICENSE SO SORRY IF THIS IS PLAGIARISED
//ONLY DOING THIS BECAUSE IT'S A PERSONAL PROJECT :)
static char* padTypeStr[] = {	"Unsupported controller", "Mouse", "Nejicon","Konami Gun", "Digital", "Analog", "Namco Gun","DualShock"};
static char *padBuf[2];
static uint32_t portConnected[2];
static uint32_t paddata[2];
static uint32_t old_pad[2];
static uint32_t new_pad[2];
static uint8_t actDirect[2][6] = { {0,0,0,0,0,0}, {0,0,0,0,0,0}};
static int dualshock[2];
static int acts[2];
static void wait_vsync()
{
	// Enable the vsync interrupt.
	*GS_REG_CSR |= GS_SET_CSR(0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);

	// Wait for the vsync interrupt.
	while (!(*GS_REG_CSR & (GS_SET_CSR(0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0)))) { }

	// Disable the vsync interrupt.
	*GS_REG_CSR &= ~GS_SET_CSR(0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
}
static void padWait(int port)
{
	// /* Wait for request to complete. */
	// while(padGetReqState(port, 0) != PAD_RSTAT_COMPLETE){
	// 	//wait_vsync();
    // }
	// /* Wait for pad to be stable. */
	// while(padGetState(port, 0) != PAD_STATE_STABLE){
	// 	//wait_vsync();
    // }
}

static void padStartAct(int port, int act, int speed)
{
	if(actDirect[port][act] != speed)
	{
		actDirect[port][act] = speed;

		padSetActDirect(port, 0, actDirect[port]);
		padWait(port);
	}
}

static void padStopAct(int port, int act)
{
	padStartAct(port, act, 0);
}

void PadInit(){
    //uint32_t port;
    //struct padButtonStatus buttons;
    
    SifInitRpc(0);
     std::cout<<"LOAD\n";
    int ret;
    if((ret = SifLoadModule("rom0:XSIO2MAN", 0, NULL)) < 0)
		{
			std::cout<<"Failed to load XISO2MAN module\n";
			SleepThread();
		}
 std::cout<<"LOAD2\n";
		if((ret = SifLoadModule("rom0:XPADMAN", 0, NULL)) < 0)
		{
			std::cout<<"Failed to load XPADMAN module\n";
			SleepThread();
		}
    std::cout<<"PADINT\n";
   std::cout << padInit(0);
    std::cout<<"PADINIT SUCCESS\n";
    padBuf[0] = new(std::align_val_t(64)) char[256];
    padBuf[1] = new(std::align_val_t(64)) char[256];
    old_pad[0] = 0;
    old_pad[1] = 0;

    portConnected[0] = 0;
    portConnected[1] = 0;

    dualshock[0] = 0;
    dualshock[1] = 0;

    acts[0] = 0;
    acts[1] = 0;

    padPortOpen(0, 0, padBuf[0]);
    padPortOpen(1, 0, padBuf[1]);

}
AllButtons* PadGetInputs(){
    AllButtons* output = new AllButtons[2];
    //REMEMBER TO DELETE THIS ONCE YOU'RE DONE - I COULD PROBABLY LEARN SMART POINTERS BUT IM LAZY SO 
    uint32_t port;
    padButtonStatus buttons;
    for(port=0; port < 2; port++)
    {
        int32_t state = padGetState(port, 0);

        if((state == PAD_STATE_STABLE) && (portConnected[port] == 0))
        {
            uint32_t i;
            uint8_t mTable[8];
            uint32_t ModeCurId;
            uint32_t ModeCurOffs;
            uint32_t ModeCurExId;
            uint32_t ModeTableNum = padInfoMode(port, 0, PAD_MODETABLE, -1);

            std::cout<<"Controller "<< port<<" connected\n";

            /* Check if dualshock and if so, activate analog mode */
            for(i = 0; i < ModeTableNum; i++)
                mTable[i] = padInfoMode(port, 0, PAD_MODETABLE, i);

            /* Works for dualshock2 */
            if((mTable[0] == 4) && (mTable[1] == 7) && (ModeTableNum == 2))
                dualshock[port] = 1;

            /* Active and lock analog mode */
            if(dualshock[port] == 1)
            {
                padSetMainMode(port, 0, PAD_MMODE_DUALSHOCK, PAD_MMODE_LOCK);
                padWait(port);
            }

            ModeCurId = padInfoMode(port, 0, PAD_MODECURID, 0);
            ModeCurOffs = padInfoMode(port, 0, PAD_MODECUROFFS, 0);
            ModeCurExId = padInfoMode(port, 0, PAD_MODECUREXID, 0);
            ModeTableNum = padInfoMode(port, 0, PAD_MODETABLE, -1);
            acts[port] = padInfoAct(port, 0, -1, 0);


            for(i = 0; i < ModeTableNum; i++)
            {
                mTable[i] = padInfoMode(port, 0, PAD_MODETABLE, i);
                //printf("%i ", (int)mTable[i]);
            }



            if(acts[port] > 0)
            {
                u8 actAlign[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

                /* Set offsets for motor parameters for SetActDirect. */
                for(i=0; i < acts[port]; i++)
                    actAlign[i] = i;

                padSetActAlign(port, 0, actAlign);
                padWait(port);
            }

            //printf("  EnterPressMode : %i\n", (int)padEnterPressMode(port, 0));
            padWait(port);

            //printf("Ready\n");

            portConnected[port] = 1;
        }

        if((state == PAD_STATE_DISCONN) && (portConnected[port] == 1))
        {
            std::cout<<"Controller "<< port<<" disconnected\n";
            portConnected[port] = 0;
        }

        if(portConnected[port] == 1)
        {
            int32_t ret = padRead(port, 0, &buttons);

            if(ret != 0)
            {
                paddata[port] = 0xffff ^ buttons.btns;

                new_pad[port] = paddata[port];
                old_pad[port] = paddata[port];

                // Values 50 and 200 used because my controllers are worn out :-)

                // if((buttons.ljoy_h <= 50) || (buttons.ljoy_h >= 200)) printf("Left Analog  X: %i\n", (int)buttons.ljoy_h);
                // if((buttons.ljoy_v <= 50) || (buttons.ljoy_v >= 200)) printf("Left Analog  Y: %i\n", (int)buttons.ljoy_v);
                // if((buttons.rjoy_h <= 50) || (buttons.rjoy_h >= 200)) printf("Right Analog X: %i\n", (int)buttons.rjoy_h);
                // if((buttons.rjoy_v <= 50) || (buttons.rjoy_v >= 200)) printf("Right Analog Y: %i\n", (int)buttons.rjoy_v);


                //if(new_pad[port]) printf("Controller (%i) button(s) pressed: ", (int)port);
                if(new_pad[port] & PAD_LEFT)		{output[port].left = true;}
                if(new_pad[port] & PAD_RIGHT) 		output[port].right = true;
                if(new_pad[port] & PAD_UP) 			output[port].up = true;
                if(new_pad[port] & PAD_DOWN) 		output[port].down = true;
                if(new_pad[port] & PAD_START) 		output[port].start = true;
                if(new_pad[port] & PAD_SELECT) 		output[port].select = true;
                if(new_pad[port] & PAD_SQUARE) 		output[port].square = true;
                if(new_pad[port] & PAD_TRIANGLE)	output[port].triangle = true;
                if(new_pad[port] & PAD_CIRCLE)		output[port].circle = true;
                if(new_pad[port] & PAD_CROSS)		output[port].cross = true;
                if(new_pad[port] & PAD_L1)
                {output[port].l1 = true;
                    //printf("L1 (Start Little Motor) ");
                    //padStartAct(port, 0, 1);
                }
                if(new_pad[port] & PAD_L2)
                {output[port].l2 = true;
                    //printf("L2 (Stop Little Motor) ");
                    //padStartAct(port, 0, 0);
                }
                if(new_pad[port] & PAD_L3)			output[port].l3 = true;
                if(new_pad[port] & PAD_R1)
                {
                    output[port].r1 = true;
                    //printf("R1 (Start Big Motor) ");
                    //padStartAct(port, 1, 255);
                }
                if(new_pad[port] & PAD_R2)
                {
                    output[port].r2 = true;
                    //printf("R2 (Stop Big Motor) ");
                    //padStopAct(port, 1);
                }
                if(new_pad[port] & PAD_R3)			output[port].r3 = true;

                if(new_pad[port]){}
            }
        }
    }
    return output;
}