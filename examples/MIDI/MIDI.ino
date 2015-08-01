/*  Openpipe Ocarina MIDI example
 *
 *  Send MIDI commands to MIDI synths
 *  This examples needs Arduino MIDI Library (https://github.com/FortySevenEffects/arduino_midi_library/)
 *
 *  OpenPipe Labs. 2015
 *  www.openpipe.cc
 *
 *  This example code is in the public domain.
 */


// Uncomment the following line for using Hairless MIDI<->Serial Bridge (http://projectgus.github.io/hairless-midiserial/)
#define SERIAL_MIDI

#include <Ocarina.h>
#include <MIDI.h>


#define MIN_PRESSURE 250

int fingers, previous_fingers;
int note, previous_note;
int pressure, previous_pressure;
int volume, previous_volume;


const unsigned char fingerings[]      ={0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00};
const unsigned char fingerings_mask[] ={0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00};
const char notes[]={60, 62, 64, 65, 67, 69, 71, 72, 74};

MIDI_CREATE_DEFAULT_INSTANCE();

void setup(){


  MIDI.begin(1);
#ifdef SERIAL_MIDI
  Serial.begin(115200);
#endif
  Ocarina.setMinPressure(MIN_PRESSURE);

}

void loop(){

  int i;

  // Read pressure and use this value to control MIDI volume (control #7)
  pressure=Ocarina.pressure();

  if ( pressure != previous_pressure ){
    previous_pressure = pressure;

    // Calculate MIDI volume
    volume = (pressure-MIN_PRESSURE)/4+20;
    if ( volume < 0)  volume = 0;
    if ( volume > 127 ) volume = 127;

    // Update MIDI volume if it changed
    if ( volume != previous_volume ){
        MIDI.sendControlChange(7, volume, 1);
        previous_volume = volume;
      }

  }

  // Read fingers and send NOTE ON and NOTE OFF commands
  fingers=Ocarina.fingers();

  if ( fingers != previous_fingers ){
    previous_fingers = fingers;

    // Search MIDI note in fingerings/notes map
    i=0;
    while( ( (fingers&fingerings_mask[i]) != fingerings[i]) && (fingerings[i] != 0x00) ) i++;
    if ( (fingers&fingerings_mask[i]) == fingerings[i] ){
      note = notes[i];

      // Update MIDI note if it changed
      if ( (note != previous_note) && (note != 0xFF) ) {
        MIDI.sendNoteOff(previous_note, 127, 1);
        MIDI.sendNoteOn(note, 127, 1);
        previous_note = note;
      }
    }

  }

}
