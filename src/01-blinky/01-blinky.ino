// Arduino pin number of the blue LED 
const byte ledPin = A12;

void setup() {
  // Set the LED pin to OUTPUT as we want to provide a signal to the
  // pin instead of reading from it (INPUT). If you do not set the mode
  // the LED may appear dim.
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Set the voltage of the pin to 5V
  digitalWrite(ledPin, HIGH);

  // Wait for 50 miliseconds to notice for a human that the LED is on
  delay(50);
  
  // Set the voltage of the pin to 0v
  digitalWrite(ledPin, LOW);

  // Wait for 2 seconds before continue
  delay(2000);
}
