const int sensorPin = A0;
const int laserPin = 2;
String wheelPosType = "segment";
String prevWheelPosType = "none";
int currentSegmentIndex = 0;
unsigned long lastReportTime = 0;

void setup()
{
  // Initialize serial communication
  Serial.begin(9600);

  // Set the sensor pin as an input
  pinMode(sensorPin, INPUT);
  pinMode(laserPin, OUTPUT);

  digitalWrite(laserPin, HIGH);

  // delay in setup, allowing laser and sensor to be stable first
  delay(1000);
  Serial.println("\n\nSystem ready");
}

void loop()
{
  int sensorState = analogRead(sensorPin);

  // Serial.println(sensorState);

  if (sensorState > 700)
  {
    wheelPosType = "divider";
  }
  else
  {
    wheelPosType = "segment";
  }

  // Check for transition from divider to segment
  if (prevWheelPosType == "divider" && wheelPosType == "segment")
  {
    // wheel position count go back to 0 after 7
    currentSegmentIndex = (currentSegmentIndex + 1) % 50;

    // Serial.print("Segment count: ");
    // Serial.println(currentSegmentIndex);
  }

  // Update previous wheel position type
  prevWheelPosType = wheelPosType;

  unsigned long currentTime = millis();
  if (currentTime - lastReportTime >= 750)
  {
    lastReportTime = currentTime;
    Serial.print("Current Wheel Position: ");
    Serial.println(currentSegmentIndex);
    // Serial.print("Current sensor value: ");
    // Serial.println(sensorState);
  }

  // Check for Serial input to reset the count
  if (Serial.available() > 0)
  {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.equalsIgnoreCase("reset"))
    {
      currentSegmentIndex = 0;
      Serial.println("Wheel position now at 0");
    }
  }

  // System delay, keep low for accurate sensor
  delay(0);
}
