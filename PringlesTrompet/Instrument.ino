class Instrument {
  public:
    // public constructor
    Instrument();
    
    // public variables
    int note = 440;
    // GUItool: begin automatically generated code
    AudioSynthWaveformSine   sine16; //xy=271,709
    AudioSynthWaveformSine   sine15; //xy=282,669
    AudioSynthWaveformSine   sine14;  //xy=283,635
    AudioSynthWaveformSine   sine13; //xy=284,601
    AudioSynthWaveformSine   sine8; //xy=287,435
    AudioSynthWaveformSine   sine7; //xy=288,400
    AudioSynthWaveformSine   sine6; //xy=289,366
    AudioSynthWaveformSine   sine5; //xy=290,332
    AudioSynthWaveformSine   sine11; //xy=290,534
    AudioSynthWaveformSine   sine12; //xy=290,567
    AudioSynthWaveformSine   sine10; //xy=291,501
    AudioSynthWaveformSine   sine9; //xy=292,469
    AudioSynthWaveformSine   sine3;          //xy=296,265
    AudioSynthWaveformSine   sine4;          //xy=296,298
    AudioSynthWaveformSine   sine2;          //xy=297,232
    AudioSynthWaveformSine   sine1;          //xy=298,200
    AudioMixer4              mixer4; //xy=531,620
    AudioMixer4              mixer3; //xy=532,556
    AudioMixer4              mixer2; //xy=537,351
    AudioMixer4              mixer1;         //xy=538,287
    AudioMixer4              tromponeMaster;         //xy=697,436
    AudioSynthWaveformSine   LFO;          //xy=799,595
    AudioFilterStateVariable filter1;        //xy=872,433
    AudioPlayMemory          playMem1;       //xy=993.0833129882812,625.0833129882812
    AudioEffectEnvelope      env;      //xy=1007,370
    AudioEffectFreeverb      freeverb1;      //xy=1012,483
    AudioMixer4              FXmixer;         //xy=1200,481
    AudioOutputI2S           i2s1;           //xy=1345,224
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
    AudioConnection          patchCord22(LFO, 0, filter1, 1);
    AudioConnection          patchCord23(filter1, 0, env, 0);
    AudioConnection          patchCord24(playMem1, 0, FXmixer, 3);
    AudioConnection          patchCord25(env, freeverb1);
    AudioConnection          patchCord26(env, 0, FXmixer, 0);
    AudioConnection          patchCord27(freeverb1, 0, FXmixer, 1);
    AudioConnection          patchCord28(FXmixer, 0, i2s1, 0);
    AudioConnection          patchCord29(FXmixer, 0, i2s1, 1);
    AudioControlSGTL5000     sgtl5000_1;     //xy=161,41
    // GUItool: end automatically generated code

    // public methods
    void updateInstrument();
    void setupInstruments();

  // private variables
  // private:
};


void Instrument::updateInstrument() {
  sine1.frequency(1*note);
  sine2.frequency(2*note);
  sine3.frequency(3*note);
  sine4.frequency(4*note);
  sine5.frequency(5*note);
  sine6.frequency(6*note);
  sine7.frequency(7*note);
  sine8.frequency(8*note);
  
  sine1.amplitude(0.19);
  sine2.amplitude(0.1);
  sine3.amplitude(0.11);
  sine4.amplitude(0.34);
  sine5.amplitude(0.43);
  sine6.amplitude(0.075);
  sine7.amplitude(0.08);
  sine8.amplitude(0.04);

  LFO.amplitude(1);
  LFO.frequency(4);

  filter1.frequency(note); //set to current tone
  filter1.resonance(3);
  filter1.octaveControl(0.25);

  

  env.attack(50);
  env.sustain(0.3);

  freeverb1.roomsize(0.2);
  freeverb1.damping(1);

  FXmixer.gain(1,0.5);

  env.noteOn();

  // Controller

  if (digitalRead(0) == HIGH) {
    Serial.println("Button is not pressed...");
    note = 440;
  } else {
    Serial.println("Button pressed!!!");
    note = 880;
  }
  delay(100);  
}

void Instrument::setupInstrument() {
  AudioMemory(20);

  // enable the audio shield
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.2);

  // Control
  Serial.begin(38400);
  pinMode(0, INPUT_PULLUP);
}
