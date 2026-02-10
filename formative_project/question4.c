const int sensorPin = A0;   // TMP36 analog pin
const int ledPin = 9;       // LED pin
int sensorValue;
float temperature;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); // optional for debugging
}

void loop() {
  sensorValue = analogRead(sensorPin);          // read sensor value (0-1023)
  temperature = (sensorValue * (5.0 / 1023.0) - 0.5) * 100.0; // TMP36 conversion

  Serial.print("Temperature: ");
  Serial.println(temperature);

  if (temperature > 30.0) {   // threshold
    digitalWrite(ledPin, HIGH);  // turn on LED
  } else {
    digitalWrite(ledPin, LOW);   // turn off LED
  }

  delay(500); // half-second delay
}

