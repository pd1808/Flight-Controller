
#include <stdio.h>
#include <cog.h>
#include <sys/driver.h>
#include <propeller.h>
#include "RC_Receiver.h"


long RC_Pins[8];
long RC_PinMask;

static const int Scale = 80/2; // System clock frequency in Mhz, halved - we're converting outputs to 1/2 microsecond resolution


void RC_Start(void)
{
	// Input pins are P0,1,2,3,4,5,26,27                       
  RC_PinMask = 0x0C00003F; // Elev8-FC pins are non-contiguous (27, 26, 5, 4, 3, 2, 1, 0)

  use_cog_driver(RC_Receiver_driver);
  load_cog_driver(RC_Receiver_driver, &RC_Pins[0]);
}


int RC_Get( int _pin ) {
	// Get receiver servo pulse width in uS
	return RC_Pins[_pin] / Scale;     // Get pulse width from Pins[..] , convert to uSec
}

int RC_GetRC(int _pin) {
	// Get receiver servo pulse width as normal r/c values (+/-1000) 
	return RC_Pins[_pin] / Scale - 3000; // Get pulse width from Pins[..], convert to uSec, make 0 center
}

int RC_Channel( int _pin ) {
	return RC_Pins[_pin] / Scale;
}
