#include "Instrument.h"

Instrument* instrument;

// ------------------------ ARDUINO SETUP METHOD ------------------------

void setup() {
  instrument = new Instrument();
  // instrument::Instrument();
  instrument -> setupInstrument();
}

// ------------------------ ARDUINO LOOP METHOD ------------------------

void loop() {
  instrument -> updateInstrument();
}
