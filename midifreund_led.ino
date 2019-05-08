//////////////////////
/// der MIDIFREUND ///
/// LED edition //////
//////////////////////
/// version 0.65 /////
//////////////////////
/// stef ♥ 2019 //////
//////////////////////

#include <Tlc5940.h>
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE()

// log tabelle
static const uint8_t table[] PROGMEM = {
  0, 255  , 185  , 160  , 140  , 98 , 90 , 68 , 60 , 53 , 44 , 40 , 35 , 29 , 24 , 22 , 20 , 18 , 16 , 14 , 12 , 10 , 9  , 7  , 6  , 5  , 4  , 3  , 2  , 2  , 1  , 0  , 0
};
const uint8_t step_time = 10; // in ms
const uint8_t anz_chan = 8; // die ersten 8 von 16 in Benutzung

void start_fade(uint8_t channel);
void test_fades();
void reset_fades();
void step();

uint8_t midi_channel;
uint8_t program;

uint8_t max_steps = sizeof(table) / sizeof(table[0]);
uint8_t anz_steps = max_steps;
uint8_t fade_state[anz_chan];

void start_fade(uint8_t channel) {
  fade_state[channel] = 0;
}

void start_fade_velocity(uint8_t channel, uint8_t velocity) {
  fade_state[channel] = (int)map(velocity, 0, 127, anz_steps - 1, 0);
}

void test_fades() {
  for (uint8_t index = 0; index < anz_chan; index++)  {
    fade_state[index] = 0;
  }
}

void reset_fades() {
  for (uint8_t index = 0; index < anz_chan; index++)  {
    fade_state[index] = anz_steps - 1;
  }
}

void step() {
  for (uint8_t channel = 0; channel < anz_chan; channel++) {
    if (fade_state[channel] < (anz_steps - 1)) fade_state[channel]++;
    Tlc.set(channel, pgm_read_byte(&table[fade_state[channel]]) * 16);
  }
  Tlc.update();
}


void set_led(uint8_t channel, uint8_t velocity) {
  Tlc.set(channel, velocity * 32);
  Tlc.update();
}


void handler_note_on(byte channel, byte note, byte velocity)
{
  //digitalWrite(13, HIGH);
  switch (note) {
    case 36:  //C2
      if (program == 0) start_fade(0);
      if (program == 1) start_fade_velocity(0, velocity);
      if (program == 2) set_led(0, velocity);
      break;
    case 38: //d
      if (program == 0) start_fade(1);
      if (program == 1) start_fade_velocity(1, velocity);
      if (program == 2) set_led(1, velocity);
      break;
    case 40: //e
      if (program == 0) start_fade(2);
      if (program == 1) start_fade_velocity(2, velocity);
      if (program == 2) set_led(2, velocity);
      break;
    case 41: //f
      if (program == 0) start_fade(3);
      if (program == 1) start_fade_velocity(3, velocity);
      if (program == 2) set_led(3, velocity);
      break;
    case 43: //g
      if (program == 0) start_fade(4);
      if (program == 1) start_fade_velocity(4, velocity);
      if (program == 2) set_led(4, velocity);
      break;
    case 45: //h
      if (program == 0) start_fade(5);
      if (program == 1) start_fade_velocity(5, velocity);
      if (program == 2) set_led(5, velocity);
      break;
    case 47: //i
      if (program == 0) start_fade(6);
      if (program == 1) start_fade_velocity(6, velocity);
      if (program == 2) set_led(6, velocity);
      break;
    case 48: //j
      if (program == 0) start_fade(7);
      if (program == 1) start_fade_velocity(7, velocity);
      if (program == 2) set_led(7, velocity);
      break;
  }
}

void handler_note_off(byte channel, byte note, byte velocity)
{
  //digitalWrite(13, LOW);
  switch (note) {
    case 36:  //C2
      if (program == 2) set_led(0, 0);
      break;
    case 38: //d
      if (program == 2) set_led(1, 0);
      break;
    case 40: //e
      if (program == 2) set_led(2, 0);
      break;
    case 41: //f
      if (program == 2) set_led(3, 0);
      break;
    case 43: //g
      if (program == 2) set_led(4, 0);
      break;
    case 45: //h
      if (program == 2) set_led(5, 0);
      break;
    case 47: //i
      if (program == 2) set_led(6, 0);
      break;
    case 48: //j
      if (program == 2) set_led(7, 0);
      break;
  }
}

void handler_pressure(byte channel, byte note, byte pressure)
{
  //digitalWrite(13, LOW);
  switch (note) {
    case 36:  //C2
      if (program == 2) set_led(0, pressure);
      break;
    case 38: //d
      if (program == 2) set_led(1, pressure);
      break;
    case 40: //e
      if (program == 2) set_led(2, pressure);
      break;
    case 41: //f
      if (program == 2) set_led(3, pressure);
      break;
    case 43: //g
      if (program == 2) set_led(4, pressure);
      break;
    case 45: //h
      if (program == 2) set_led(5, pressure);
      break;
    case 47: //i
      if (program == 2) set_led(6, pressure);
      break;
    case 48: //j
      if (program == 2) set_led(7, pressure);
      break;
  }
}

void set_address() { // MIDI Schalter auslesen
  midi_channel = !digitalRead(2) + (!digitalRead(8) << 1) + (!digitalRead(4) << 2 ) + (!digitalRead(5) << 3);
  if (midi_channel == 0) midi_channel = 16;
}

void set_program() { // Programmschalter auslesen
  program = !digitalRead(6) + (!digitalRead(7) << 1);
}

void setup() {
  pinMode(2, INPUT_PULLUP);

  //pinMode(3, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);

  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  set_address();
  set_program();

  MIDI.setHandleNoteOn(handler_note_on);
  MIDI.setHandleNoteOff(handler_note_off);
  MIDI.setHandleAfterTouchPoly(handler_pressure);
  Tlc.init();
  reset_fades();
  MIDI.begin(midi_channel);
  //test_fades();
}

void loop() {
  if ((program == 0) || (program == 1)) {
    step();
    unsigned long now = millis();
    while (millis() < (now + step_time)) MIDI.read();
  }
  else {
    MIDI.read();
  }
}
