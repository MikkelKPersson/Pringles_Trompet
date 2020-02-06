#ifndef Instrument_h
#define Instrument_h

#include "Audio.h"
#include "Wire.h"
#include "SPI.h"
#include "SD.h"
#include "SerialFlash.h"

class Instrument {
  public:
    // public constructor
    Instrument();

    // public variables
    // GUItool: begin automatically generated code
    AudioSynthWaveformSine   sine16;         //xy=174,726
    AudioSynthWaveformSine   sine15;         //xy=185,686
    AudioSynthWaveformSine   sine14;         //xy=186,652
    AudioSynthWaveformSine   sine13;         //xy=187,618
    AudioSynthWaveformSine   sine8;          //xy=190,452
    AudioSynthWaveformSine   sine7;          //xy=191,417
    AudioSynthWaveformSine   sine6;          //xy=192,383
    AudioSynthWaveformSine   sine5;          //xy=193,349
    AudioSynthWaveformSine   sine11;         //xy=193,551
    AudioSynthWaveformSine   sine12;         //xy=193,584
    AudioSynthWaveformSine   sine10;         //xy=194,518
    AudioSynthWaveformSine   sine9;          //xy=195,486
    AudioSynthWaveformSine   sine3;          //xy=199,282
    AudioSynthWaveformSine   sine4;          //xy=199,315
    AudioSynthWaveformSine   sine2;          //xy=200,249
    AudioSynthWaveformSine   sine1;          //xy=201,217
    AudioMixer4              mixer4;         //xy=434,637
    AudioMixer4              mixer3;         //xy=435,573
    AudioMixer4              mixer2;         //xy=440,368
    AudioMixer4              mixer1;         //xy=441,304
    AudioMixer4              tromponeMaster; //xy=600,453
    AudioFilterStateVariable filter1;        //xy=775,450
    AudioEffectEnvelope      env;            //xy=910,387
    AudioEffectFreeverb      freeverb1;      //xy=915,500
    AudioMixer4              FXmixer;        //xy=1103,498
    AudioOutputI2S           i2s1;           //xy=1248,241
    AudioControlSGTL5000     sgtl5000_1;     //xy=64,58
    // GUItool: end automatically generated code

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
    int button1 = 0;
    int button2 = 1;
    int button3 = 2;
    int octButton = 3;
    int effectsButton = 4;

    // states of effects button: activate or deactivate
    boolean isPressing = false;
    boolean isUsingEffect = false;

    // analog sensors
    #define IRSensor A8
    #define airSensor A2

    float distToFreq = 0;
    float vol = 0;

    // public methods
    void updateInstrument();
    void setupInstrument();
    void setFreqAndAmp();
    void checkEffectsButton();
    void checkController();
};

#endif
