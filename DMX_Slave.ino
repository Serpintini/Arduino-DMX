/*
  DMX_Slave.ino - Example code for using the Conceptinetics DMX library
  Copyright (c) 2013 W.A. van der Meeren <danny@illogic.nl>.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

// This is an edited version of DMX_Slave.ino from the examples in the conceptinetics library
// If you are using a different sheild, check that file for info on the other ways it may have to be configured
// I cut this one down for clarity, with the hope it includes all the info you need

#include "Conceptinetics.h"


// This variable controls how many DMX Channels the arduino will look at
// ex. If this number is 3 and the start address is 50, the shield will check 
// addresses 50-53. 
#define DMX_SLAVE_CHANNELS   1

// Creates the dmx_slave device 
DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS );

//If you want an LED to turn on, change this to whatever port your LED is plugged into
const int ledPin = 41;

// the setup routine runs once when you press reset:
void setup() {      
  Serial.begin(9600);       
  
  // Enable DMX slave interface and start recording DMX data
  dmx_slave.enable ();  
  
  // The start address, similar to the number you would change on any other light
  // Indicating the start of the block of addresses it should be reading, as patched in the light board
  // You can change this address at any time during the program, but I don't know why you would
  dmx_slave.setStartAddress (190);
  
  // Set led pin as output pin
  pinMode ( ledPin, OUTPUT );
}

// the loop routine runs over and over again forever:
void loop() 
{
  

  // getChannelValue is relative to the configured startaddress
  // The index starts at 1
  // ex. if we had a start address of 50, address 50 would be accessed by (1), 51 by (2), etc
  // if you try to put a number higher than the ammount of channels you allotted on initialization, it always reads 0
  Serial.println(dmx_slave.getChannelValue (1));

  //if the value is greater than 10, it turns an LED on.
  if ( dmx_slave.getChannelValue (1) > 10 )
    digitalWrite ( ledPin, HIGH );
  else
    digitalWrite ( ledPin, LOW );
}
