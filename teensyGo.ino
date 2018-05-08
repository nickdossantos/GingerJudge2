const int PIN_DAT = 23;
const int PIN_CLK = 22;
const int PIN_CSN = 21;
const int PIN_THV = 20;
const int PIN_LED_BLINK = 13;
double throttle_val;

// Value to send to the Remote Throttle Handle
unsigned volatile int motorValue = 1000;
unsigned volatile int message;
int volatile message_index = 0;

void setup() {
  delay (2500); // Startup Delay
  delay (2500); // Startup Delay

  pinMode(PIN_LED_BLINK, OUTPUT);
  
  pinMode(PIN_DAT, OUTPUT);  
  pinMode(PIN_CLK, INPUT);   
  pinMode(PIN_CSN, INPUT);   
  pinMode(PIN_THV, INPUT);
  
  attachInterrupt(PIN_CLK, PIN_CLK_INTERRUPT, CHANGE);
  attachInterrupt(PIN_CSN, PIN_CSN_INTERRUPT, CHANGE);
}

const int FORWARD_VAL = 1990;
const int NEUTRAL_VAL = 1000;
const int HALF_THROTTLE = 1499;
const int REVERSE = 500; 


int last_time = 0;
void loop()
{  
//  1,000 neutral 
//  2,000 Forward 
//  0 Reverse
  throttle_val = pulseIn(PIN_THV, HIGH);
  if(throttle_val > 1600) {
    motorValue = HALF_THROTTLE;
  }else if(throttle_val <= 1600 && throttle_val >= 1400 || throttle_val == 0) {
    motorValue = NEUTRAL_VAL;
  }else if(throttle_val < 1400) {
    motorValue = REVERSE;
  }
}

char old_csn = LOW;
void PIN_CSN_INTERRUPT()
{
  char new_csn = digitalRead(PIN_CSN);
  if (old_csn != new_csn)
  { 
    old_csn = new_csn;
    digitalWrite(PIN_DAT, LOW);
    if (new_csn == LOW)
    {  
      message = (motorValue << 6) | B100100;
      message_index = 36;
    }
  }
}


char old_clock = LOW; // store the last clock reading
void PIN_CLK_INTERRUPT()
{ 
  if (old_csn == LOW) // If we are mid transfer.
  {
    char new_clock = digitalRead(PIN_CLK);
    if (old_clock != new_clock)  // This helps prevent pin bouncing on interrupts.
    {
      old_clock = new_clock;
      message_index--; // Move to the next half byte.
      if (message_index > -1) // If we have more bytes to send
      {
        unsigned int flag = B1 << (message_index / 2); // Divide 
        digitalWrite(PIN_DAT, (message & flag) ? HIGH : LOW);
      }
    }  
  }
  else old_clock = HIGH;
} 
