#include "Arduino.h"
#include "Instrument.h"

#include "Audio.h"
#include "Wire.h"
#include "SPI.h"
#include "SD.h"
#include "SerialFlash.h"

// --------------------------- INSTRUMENT METHODS IMPLEMENTATION ---------------------------

// Constructor
Instrument::Instrument() {}

// setup of the instrument instance
void Instrument::setupInstrument() {
  // GUItool: begin automatically generated code
  AudioConnection          patchCord1(sine16, 0, mixer4, 3);
  AudioConnection          patchCord2(sine15, 0, mixer4, 2);
  AudioConnection          patchCord3(sine14, 0, mixer4, 1);
  AudioConnection          patchCord4(sine13, 0, mixer4, 0);
  AudioConnection          patchCord5(sine8, 0, mixer2, 3);
  AudioConnection          patchCord6(sine7, 0, mixer2, 2);
  AudioConnection          patchCord7(sine6, 0, mixer2, 1);
  AudioConnection          patchCord8(sine5, 0, mixer2, 0);
  AudioConnection          patchCord9(sine11, 0, mixer3, 2);
  AudioConnection          patchCord10(sine12, 0, mixer3, 3);
  AudioConnection          patchCord11(sine10, 0, mixer3, 1);
  AudioConnection          patchCord12(sine9, 0, mixer3, 0);
  AudioConnection          patchCord13(sine3, 0, mixer1, 2);
  AudioConnection          patchCord14(sine4, 0, mixer1, 3);
  AudioConnection          patchCord15(sine2, 0, mixer1, 1);
  AudioConnection          patchCord16(sine1, 0, mixer1, 0);
  AudioConnection          patchCord17(mixer4, 0, tromponeMaster, 3);
  AudioConnection          patchCord18(mixer3, 0, tromponeMaster, 2);
  AudioConnection          patchCord19(mixer2, 0, tromponeMaster, 1);
  AudioConnection          patchCord20(mixer1, 0, tromponeMaster, 0);
  AudioConnection          patchCord21(tromponeMaster, 0, filter1, 0);
  AudioConnection          patchCord22(filter1, 0, env, 0);
  AudioConnection          patchCord23(env, freeverb1);
  AudioConnection          patchCord24(env, 0, FXmixer, 0);
  AudioConnection          patchCord25(freeverb1, 0, FXmixer, 1);
  AudioConnection          patchCord26(FXmixer, 0, i2s1, 0);
  AudioConnection          patchCord27(FXmixer, 0, i2s1, 1);
  // GUItool: end automatically generated code

  AudioMemory(20);

  // enable the audio shield
  sgtl5000_1.enable();
  sgtl5000_1.volume(vol);

  // Control
  Serial.begin(38400);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(effectsButton, INPUT_PULLUP);
  pinMode(octButton, INPUT_PULLUP);
}

// update method of the instrument instance
void Instrument::updateInstrument() {
  // setting the frequency and amplitude of the sines
  setFreqAndAmp();

  // 5v
  // float volts = analogRead(IRSensor) * 0.0048828125; // value from IR sensor * (5/1024)
  // float distance = 13 * pow(volts, -1); // worked out from datasheet graph
  float distance = analogRead(IRSensor);
  //if (distance > 50) {
  //  distance = 50;
  // }
  distToFreq = map(distance, 700, 90, 300, 9000);

  //Serial.println(distance);
  //Serial.println(distToFreq);

  // setting the frequency, resonance and octave of the filter
  filter1.frequency(distToFreq); //set to current tone
  filter1.resonance(5);
  filter1.octaveControl(1);

  env.attack(50);
  env.sustain(0.3);

  freeverb1.roomsize(0.2);
  freeverb1.damping(1);

  FXmixer.gain(1, 0.5);

  // Controller
  checkController();

  // check the state of the effects button
  checkEffectsButton();

  delay(10);
  float airPressure = analogRead(airSensor);

  Serial.println(airPressure);
  delay(100);

  // play
  boolean notePlaying = false;
  if (airPressure > 150 && !notePlaying) {
    notePlaying = true;
    env.noteOn();
  }
  if (airPressure < 150) {
    notePlaying = false;
    env.noteOff();
  }

  vol = map(airPressure, 150, 1000, 0, 1);
  sgtl5000_1.volume(vol);
}

// set the frequencies and amplitudes of the instrument
void Instrument::setFreqAndAmp() {
  // setting the frequency of the sines
  sine1.frequency(1 * note);
  sine2.frequency(2 * note);
  sine3.frequency(3 * note);
  sine4.frequency(4 * note);
  sine5.frequency(5 * note);
  sine6.frequency(6 * note);
  sine7.frequency(7 * note);
  sine8.frequency(8 * note);

  // setting the amplitude of the sines
  sine1.amplitude(0.19);
  sine2.amplitude(0.1);
  sine3.amplitude(0.11);
  sine4.amplitude(0.34);
  sine5.amplitude(0.43);
  sine6.amplitude(0.075);
  sine7.amplitude(0.08);
  sine8.amplitude(0.04);
}

// control the instrument dependding on which buttons are pressed
void Instrument::checkController() {
  if (digitalRead(button1) == HIGH && digitalRead(button2) == HIGH && digitalRead(button3) == HIGH) {
    if (digitalRead(octButton) == LOW) {
      // Serial.println("e5");
      note = e4 * 2;
    } else {
      // Serial.println("e4");
      note = e4;
    }

  } else if (digitalRead(button1) == LOW && digitalRead(button2) == HIGH && digitalRead(button3) == HIGH) {
    if (digitalRead(octButton) == LOW) {
      // Serial.println("f#5");
      note = fSharp4 * 2;
    } else {
      // Serial.println("f#4");
      note = fSharp4;
    }
  } else if (digitalRead(button1) == LOW && digitalRead(button2) == LOW && digitalRead(button3) == HIGH) {
    if (digitalRead(octButton) == LOW) {
      // Serial.println("g5");
      note = g4 * 2;
    } else {
      // Serial.println("g4");
      note = g4;
    }

  } else if (digitalRead(button1) == LOW && digitalRead(button2) == LOW && digitalRead(button3) == LOW) {
    if (digitalRead(octButton) == LOW) {
      // Serial.println("a5");
      note = a4 * 2;
    } else {
      // Serial.println("a4");
      note = a4;
    }

  } else if (digitalRead(button1) == HIGH && digitalRead(button2) == LOW && digitalRead(button3) == HIGH) {
    if (digitalRead(octButton) == LOW) {
      // Serial.println("b5");
      note = b4 * 2;
    } else {
      // Serial.println("b4");
      note = b4;
    }

  } else if (digitalRead(button1) == HIGH && digitalRead(button2) == LOW && digitalRead(button3) == LOW) {
    if (digitalRead(octButton) == LOW) {
      // Serial.println("c#5");
      note = cSharp5 * 2;
    } else {
      // Serial.println("c#4");
      note = cSharp5;
    }

  } else if (digitalRead(button1) == HIGH && digitalRead(button2) == HIGH && digitalRead(button3) == LOW) {
    if (digitalRead(octButton) == LOW) {
      // Serial.println("d6");
      note = d5 * 2;
    } else {
      // Serial.println("d5");
      note = d5;
    }

  } else if (digitalRead(button1) == LOW && digitalRead(button2) == HIGH && digitalRead(button3) == LOW) {
    if (digitalRead(octButton) == LOW) {
      // Serial.println("e6");
      note = e4 * 2 * 2;
    } else {
      // Serial.println("e5");
      note = e4 * 2;
    }
  }
}

// check what the effects button is doing --> is it activating or deactivating the effect?
void Instrument::checkEffectsButton() {
  if (digitalRead(effectsButton) == LOW) {
    if (!isPressing) { // if the user is not pressing anymore
      isUsingEffect = !isUsingEffect; // set the effect state to its opposite
      isPressing = true;
    }
  }
  else if (digitalRead(effectsButton) == HIGH) {
    isPressing = false;
  }
  if (isUsingEffect) {
    //  Serial.println("KABOOM");
  }
}
