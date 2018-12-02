/* Pro Micro hanukka controller */
int RXLED = 17;  // The RX LED has a defined Arduino pin
// The TX LED has predefined macros (TXLED1, TXLED0) to control it.
// assign digital out pins for LEDs. 0th entry is Shamash, the candle
// that must provide the light for mundane use while the rest provide the
// sacred light. Try using a PWM pin for it if you want to play with brightness
int candles[9] = {10, 2, 3, 4, 5, 6, 7, 8, 9};
void setup()
{
    pinMode(RXLED, OUTPUT);  // Set RX LED as an output
    // TX LED is set as an output behind the scenes
    for (int i = 1; i<9; i++){
        pinMode(candles[i], OUTPUT);
    }
    Serial.begin(9600); //debug purposes only
    // try to turn off the annoying tx/rx lights on pro micro board. Insist.
    delay(1000);
    lightsOff();
    delay(5000);
    lightsOff();
}
void lightsOff()
{
    digitalWrite(RXLED, HIGH);
    TXLED1;
}
void shamashOn()
{
    pinMode(candles[0], OUTPUT);
    // use digitalWrite if the pin doesn't support PWM. My LED was too bright.
    analogWrite(candles[0], 128);
}
void shamashOff()
{
    pinMode(candles[0], OUTPUT);
    digitalWrite(candles[0], LOW);
}

unsigned long DAY = 86400000;
 // set this before burning, to initialize to desired number of already lit
 // candles (in case battery ran down) and offset in milliseconds.
 // for example, this one is set to 4 hours after first candle was lit, at 9pm,
 // so next candle will be lit on time at 5pm.
unsigned long start_offset = DAY+14400000;
int state = 1; // to turn off lights after use
void loop()
{
    Serial.println("Hanukka sameah");  // debug only
    shamashOn();
    delay(500);
    // avoid turning lights on after they were off
    if (!state){
        return;
    }
    int i = 0;
    // get current time
    unsigned long t = millis()+start_offset;
    int count = t/DAY;
    // light proper number of candles
    if (count<9){
        for (i = 1; i<=count; i++){
            digitalWrite(candles[i], HIGH);
        }
    }
    else{
        // turn off the lights, party's over    
        state = 0;
        for (i = 1; i<9; i++){
            digitalWrite(candles[i], LOW);
        }
        delay(1000);
        shamashOff();
    }
}
