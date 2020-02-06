#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// declare the instrument instance
Instrument instrument;
void setup() {
  instrument = new Instrument();
  intrument.setupInstrument();
}


void loop() {  
  instrument.updateInstrument();
}
