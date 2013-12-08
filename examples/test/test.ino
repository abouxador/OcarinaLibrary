/*  Openpipe Ocarina test
 *
 *  Reads ocarina fingers and pressure and outputs the values to the serial port
 *
 *  Connect the OpenPipe Ocarina directly to an Arduino UNO compatible board.
 *
 *  OpenPipe Labs. 2013
 *  www.openpipe.cc
 *
 *  This example code is in the public domain.
 */

#include <Ocarina.h>

int fingers;
int pressure;

void setup(){

  Serial.begin(115200);
  Ocarina.setMinPressure(250);

}

void loop(){

  // Read fingers
  Serial.print("FINGERS: ");
  fingers=Ocarina.fingers();
  Serial.print(fingers, HEX);
  Serial.print(" ");
  for (int i=7; i>=0; i--){
    if (fingers & (1<<i)) Serial.print("1");
    else Serial.print("0");
  }

  // Read pressure
  Serial.print(" PRESSURE: ");
  pressure=Ocarina.pressure();
  Serial.print(pressure);
  Serial.println();

  // Wait some time
  delay(100);

}
