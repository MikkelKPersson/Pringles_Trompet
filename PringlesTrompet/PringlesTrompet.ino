#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     noise2;         //xy=183.0500030517578,684.0499877929688
AudioSynthNoiseWhite     noise1;         //xy=185.0500030517578,648.0500030517578
AudioSynthNoisePink      pink1;          //xy=187.0500030517578,723.0499267578125
AudioSynthWaveformSine   sine8;          //xy=189.5,458
AudioSynthWaveformSine   sine7;          //xy=190.5,423
AudioSynthWaveformSine   sine6;          //xy=191.5,389
AudioSynthNoisePink      pink2;          //xy=190.0500030517578,760.0500030517578
AudioSynthWaveform       waveform2;      //xy=191.0500030517578,534.0500030517578
AudioSynthWaveformSine   sine5;          //xy=192.5,355
AudioSynthWaveform       waveform1;      //xy=192.0500030517578,500.0500030517578
AudioSynthWaveform       waveform3;      //xy=195.0500030517578,567.0500030517578
AudioSynthWaveformSine   sine3;          //xy=198.5,288
AudioSynthWaveformSine   sine4;          //xy=198.5,321
AudioSynthWaveformSine   sine2;          //xy=199.5,255
AudioSynthWaveformSine   sine1;          //xy=200.5,223
AudioSynthWaveform       waveform4;      //xy=204.0500030517578,602.0499877929688
AudioMixer4              mixer4;         //xy=433.5,643
AudioMixer4              mixer3;         //xy=434.5,579
AudioMixer4              mixer2;         //xy=439.5,374
AudioMixer4              mixer1;         //xy=440.5,310
AudioMixer4              tromponeMaster; //xy=599.5,459
AudioEffectEnvelope      env;            //xy=753.5,398
AudioEffectDelay         delay1;         //xy=938.0499877929688,556.0499877929688
AudioEffectBitcrusher    bitcrusher1;    //xy=943.0500030517578,666.0500030517578
AudioEffectFreeverb      freeverb1;      //xy=954.5000610351562,462
AudioFilterStateVariable filter1;        //xy=966.5,374
AudioMixer4              FXmixer;        //xy=1140.5,491
AudioOutputI2S           i2s1;           //xy=1247.5,247
AudioConnection          patchCord1(noise2, 0, mixer4, 1);
AudioConnection          patchCord2(noise1, 0, mixer4, 0);
AudioConnection          patchCord3(pink1, 0, mixer4, 2);
AudioConnection          patchCord4(sine8, 0, mixer2, 3);
AudioConnection          patchCord5(sine7, 0, mixer2, 2);
AudioConnection          patchCord6(sine6, 0, mixer2, 1);
AudioConnection          patchCord7(pink2, 0, mixer4, 3);
AudioConnection          patchCord8(waveform2, 0, mixer3, 1);
AudioConnection          patchCord9(sine5, 0, mixer2, 0);
AudioConnection          patchCord10(waveform1, 0, mixer3, 0);
AudioConnection          patchCord11(waveform3, 0, mixer3, 2);
AudioConnection          patchCord12(sine3, 0, mixer1, 2);
AudioConnection          patchCord13(sine4, 0, mixer1, 3);
AudioConnection          patchCord14(sine2, 0, mixer1, 1);
AudioConnection          patchCord15(sine1, 0, mixer1, 0);
AudioConnection          patchCord16(waveform4, 0, mixer3, 3);
AudioConnection          patchCord17(mixer4, 0, tromponeMaster, 3);
AudioConnection          patchCord18(mixer3, 0, tromponeMaster, 2);
AudioConnection          patchCord19(mixer2, 0, tromponeMaster, 1);
AudioConnection          patchCord20(mixer1, 0, tromponeMaster, 0);
AudioConnection          patchCord21(tromponeMaster, env);
AudioConnection          patchCord22(env, freeverb1);
AudioConnection          patchCord23(env, delay1);
AudioConnection          patchCord24(env, bitcrusher1);
AudioConnection          patchCord25(env, 0, filter1, 0);
AudioConnection          patchCord26(delay1, 0, FXmixer, 2);
AudioConnection          patchCord27(bitcrusher1, 0, FXmixer, 3);
AudioConnection          patchCord28(freeverb1, 0, FXmixer, 1);
AudioConnection          patchCord29(filter1, 0, FXmixer, 0);
AudioConnection          patchCord30(FXmixer, 0, i2s1, 0);
AudioConnection          patchCord31(FXmixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=63.5,64
// GUItool: end automatically generated code

bool lastNoteLow = true;

float note = 0;
// base notes
float e4 = 329.6;
float fSharp4 = 370;
float g4 = 392.0;
float a4 = 440;
float b4 = 493.3;
float cSharp5 = 554.4;
float d5 = 587.3;

// buttons
int button1 = 3;
int button3 = 1;
int button2 = 2;
int octButton = 4;
int effectsButton = 0;

// states of effects button: activate or deactivate
boolean isPressing = false;
boolean isUsingEffect = false;

// analog sensors
#define IRSensor A8
#define airSensor A2

float distToFreq = 0;
float vol = 0;

float airPressure = 0;

int noiseAmp = 0, pinkAmp = 0;

int waveformAmp = 0;
boolean notePlaying = false;

// ------------------------ ARDUINO SETUP METHOD ------------------------

void setup() {
  AudioMemory(20);

  // enable the audio shield
  sgtl5000_1.enable();

  sgtl5000_1.volume(vol);

  // env.noteOn();

  // Control
  Serial.begin(38400);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(effectsButton, INPUT_PULLUP);
  pinMode(octButton, INPUT_PULLUP);

  // delay1.delay(0, 666.7);

}


// ------------------------ ARDUINO LOOP METHOD ------------------------

void loop() {
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
  sine1.amplitude(0.50);
  sine2.amplitude(0.1);
  sine3.amplitude(0.20);
  sine4.amplitude(0.174);
  sine5.amplitude(0.2);
  sine6.amplitude(0.3);
  sine7.amplitude(0.2);
  sine8.amplitude(0.1);

  // setting the waveforms
  waveform1.begin(WAVEFORM_SAWTOOTH);
  waveform2.begin(WAVEFORM_SAWTOOTH);
  waveform3.begin(WAVEFORM_SAWTOOTH);
  waveform4.begin(WAVEFORM_SAWTOOTH);
  waveform1.frequency(1 * note + 0.2);
  waveform2.frequency(2 * note + 0.2);
  waveform3.frequency(3 * note + 0.2);
  waveform4.frequency(4 * note + 0.2);
  waveform1.amplitude(waveformAmp);
  waveform2.amplitude(waveformAmp);
  waveform3.amplitude(waveformAmp);
  waveform4.amplitude(waveformAmp);

  noiseAmp = map(airPressure, 150, 1000, 0.5, 0);
  pinkAmp = map(airPressure, 150, 1000, 0.5, 0);

  noise1.amplitude(noiseAmp);
  noise2.amplitude(noiseAmp);

  pink1.amplitude(pinkAmp);
  pink2.amplitude(pinkAmp);

  // 5v
  //float volts = analogRead(IRSensor) * 0.0048828125; // value from IR sensor * (5/1024)
  //float distance = 13 * pow(volts, -1); // worked out from datasheet graph
  float distance = analogRead(IRSensor);
  //if (distance > 50) {
  //  distance = 50;
  // }
  distToFreq = map(distance, 850, 200, 1, 4);
  distToFreq = pow(10, distToFreq);


  //Serial.println(distance);
  //Serial.println(distToFreq);

  //ADSR
  env.attack(50);
  env.sustain(0.3);

  // FX

  // setting the frequency, resonance and octave of the filter
  filter1.frequency(distToFreq); //set to current tone
  filter1.resonance(5);
  filter1.octaveControl(7);



  freeverb1.roomsize(0.5);
  freeverb1.damping(0.7);

  FXmixer.gain(0, 0.7);
  FXmixer.gain(1, 0.7);


  if (digitalRead(button1) == LOW) Serial.println("button1 pressed");
  if (digitalRead(button2) == LOW) Serial.println("button2 pressed");
  if (digitalRead(button3) == LOW) Serial.println("button3 pressed");

  // Controller
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


  // check the state of the effects button
  checkEffectsButton();



  // delay(10);
  airPressure = analogRead(airSensor);

  Serial.println(airPressure);
 // delay(100);


  //play
  if (lastNoteLow)
    note = note / 8;

  if (airPressure > 150 && !notePlaying) {
    notePlaying = true;
    lastNoteLow = false;
    noiseAmp = 0;
    pinkAmp = 0;
    env.noteOn();
  }

  else if (airPressure < 75 && !notePlaying) {
    lastNoteLow = true;
    notePlaying = true;
    noiseAmp = 0;
    pinkAmp = 0;
    note = note / 8;
    env.noteOn();
    
  }


  if (airPressure >= 150) {
    vol = map(airPressure, 150, 1000, 0.5, 1);
    waveformAmp = map(airPressure, 150, 1000, 0, 0.7);
    sgtl5000_1.volume(vol);
  }
  if (airPressure < 75) {
    //note = note / 8;
    vol = map(airPressure, 75, 0, 0.9, 1);
    waveformAmp = map(airPressure, 75, 0, 0.9, 1);
    sgtl5000_1.volume(vol);
  }

  if (airPressure < 150 && airPressure > 75) {
    notePlaying = false;
    env.noteOff();
    vol = 0;
  }
}



void checkEffectsButton() {
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
    Serial.println("KABOOM");
    FXmixer.gain(2, 0.5);
  }
  else {
    FXmixer.gain(2, 0);
    // delay1.disable(0);
  }

}
