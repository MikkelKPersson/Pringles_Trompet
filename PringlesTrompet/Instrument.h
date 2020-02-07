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
