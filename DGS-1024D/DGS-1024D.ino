
//**************************************************************//
//  Name    : D-Link DGS-1024D led on Arduino
//  Author  : Alberto Panu
//  Date    : 26 Mar 2016
//  Version : 1.0
//  Notes   : Code for using the 74HC164 Shift Register board   //
//          : of the D-Link DGS-1024D switch
//****************************************************************

/* Old config
// Pin connected to 74HC164 led board
#define clockPin5e6 12 // pin 5 DGS-1024D CP5E6
#define clockPin3e4 10 // pin 9 DGS-1024D CP3E4
#define clockPin1e2 8 // pin 13 DGS-1024D CP1E2
////Pin connected to DS of 74HC164
#define dataPin5e6 11 // pin 7 DGS-1024D DS5
#define dataPin3e4 9 // pin 11 DGS-1024D DS3
#define dataPin1e2 7 // pin 15 DGS-1024D DS1
*/

// Pin connected to 74HC164 led board new config better
// with original cable and Arduino Nano.
// Original cable has a GND wire between signals and has
// better crosstalk performance, you can decrease the delay!
#define clockPin5e6 7 // pin 5 DGS-1024D CP5E6
#define clockPin3e4 9 // pin 9 DGS-1024D CP3E4
#define clockPin1e2 11 // pin 13 DGS-1024D CP1E2
////Pin connected to DS of 74HC164
#define dataPin5e6 8 // pin 7 DGS-1024D DS5
#define dataPin3e4 10 // pin 11 DGS-1024D DS3
#define dataPin1e2 12 // pin 15 DGS-1024D DS1

/*
// Pin connected to 74HC164 led board new config better
// with original cable and Arduino Mini.
// Original cable has a GND wire between signals and has
// better crosstalk performance, you can decrease the delay!
#define clockPin5e6 4 // pin 5 DGS-1024D CP5E6
#define clockPin3e4 6 // pin 9 DGS-1024D CP3E4
#define clockPin1e2 8 // pin 13 DGS-1024D CP1E2
////Pin connected to DS of 74HC164
#define dataPin5e6 5 // pin 7 DGS-1024D DS5
#define dataPin3e4 7 // pin 11 DGS-1024D DS3
#define dataPin1e2 9 // pin 15 DGS-1024D DS1
*/

//#define DEBUG

void cancella(unsigned char dataPin, unsigned char clockPin) {
  shiftOut(dataPin, clockPin, LSBFIRST, ~0);
  shiftOut(dataPin, clockPin, LSBFIRST, ~0 );
}

void newfai(unsigned char dataPin, unsigned char clockPin, boolean verso) {
  unsigned char numberToDisplay;
  unsigned char chip;
  if (verso) {
    chip = 0;
  } else {
    chip = 1;
  }
  for ( char x = 0; x <= 1; x++) {
    for ( char power = 0; power <= 7; power++) {
#if defined DEBUG
      Serial.print(power, DEC);
      Serial.print('\t');
#endif
      if ( power == 0 ) {
        if (verso) {
          numberToDisplay = 1;
        } else {
          numberToDisplay = 128;
        }
      } else {
        if (verso) {
          numberToDisplay = numberToDisplay * 2;
        } else {
          numberToDisplay = numberToDisplay / 2;
        }
      }
#if defined DEBUG
      Serial.println(numberToDisplay);
#endif
      if (chip == 0) {
        shiftOut(dataPin, clockPin, LSBFIRST, ~numberToDisplay);
        shiftOut(dataPin, clockPin, LSBFIRST, ~0);
      } else {
        shiftOut(dataPin, clockPin, LSBFIRST, ~0);
        shiftOut(dataPin, clockPin, LSBFIRST, ~numberToDisplay );
      }
      // pause before next value:
      delay(50);
    }
    if (verso) {
      chip++;
    } else {
      chip--;
    }
  }
  cancella(dataPin, clockPin);
}

void setup() {
  //set pins to output so you can control the shift registerå
  pinMode(clockPin5e6, OUTPUT);
  pinMode(dataPin5e6, OUTPUT);
  pinMode(clockPin3e4, OUTPUT);
  pinMode(dataPin3e4, OUTPUT);
  pinMode(clockPin1e2, OUTPUT);
  pinMode(dataPin1e2, OUTPUT);
#if defined DEBUG
  Serial.begin(9600);
#endif
  cancella(dataPin5e6, clockPin5e6);
  cancella(dataPin3e4, clockPin3e4);
  cancella(dataPin1e2, clockPin1e2);
}

void loop() {
  newfai(dataPin5e6, clockPin5e6, true);
  newfai(dataPin3e4, clockPin3e4, true);
  newfai(dataPin1e2, clockPin1e2, true);
  newfai(dataPin1e2, clockPin1e2, false);
  newfai(dataPin3e4, clockPin3e4, false);
  newfai(dataPin5e6, clockPin5e6, false);
}

