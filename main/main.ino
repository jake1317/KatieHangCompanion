// Pins
const int HCSR04_TRIG_PIN = 7;
const int HCSR04_ECHO_PIN = 8;

void setupHCSR04()
{
  pinMode(HCSR04_TRIG_PIN, OUTPUT);
  digitalWrite(HCSR04_TRIG_PIN, LOW);
  pinMode(HCSR04_ECHO_PIN, INPUT);
}

float getHCSR04Distance()
{
  const unsigned int MAX_DIST = 23200;
  const unsigned float PULSE_TO_INCH_CONVERSION = 148.0;

  // 10us pulse on trigger
  digitalWrite(HCSR04_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(HCSR04_TRIG_PIN, LOW);

  // Wait for rising edge of echo
  while (digitalRead(HCSR04_ECHO_PIN) == 0);
  unsigned long myPulseStart = micros();
  while (digitalRead(HCSR04_ECHO_PIN) == 1);
  unsigned long myPulseEnd = micros();

  // Convert to pulse width to inches
  unsigned long myPulseWidth = myPulseEnd - myPulseStart;
  if (myPulseWidth > MAX_DIST)
  {
    myPulseWidth = MAX_DIST;
  }
  return myPulseWidth / 148.0;
}

void setup()
{
  setupHCSR04();

  Serial.begin(9600);
}

void loop()
{
  float myDistance = getHCSR04Distance();

  // Print out results
  Serial.print(myDistance);
  Serial.println(" in");

  delay(60);
}
