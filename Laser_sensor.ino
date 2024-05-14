
const int sensorPin = A0;
const int laserPin = 2;
String wheelPos = "segment";
String prevWheelPos = "segment";
int segmentCount = 0;

void setup()
{
  // Initialize serial communication
  Serial.begin(9600);

  // Set the sensor pin as an input
  pinMode(sensorPin, INPUT);
  pinMode(laserPin, OUTPUT);
}

void loop()
{
  digitalWrite(laserPin, HIGH);
  int sensorState = analogRead(sensorPin);

  // Serial.println(sensorState);

  if (sensorState > 700)
  {
    wheelPos = "divider";
  }
  else
  {
    wheelPos = "segment";
  }

  // Check for transition from divider to segment
  if (prevWheelPos == "divider" && wheelPos == "segment")
  {
    segmentCount++; // Increment segment count only on transition from divider to segment
    Serial.print("Segment count: ");
    Serial.println(segmentCount);
  }

  // Update previous wheel position
  prevWheelPos = wheelPos;

  // Check for Serial input to reset the count
  if (Serial.available() > 0)
  {
    String input = Serial.readStringUntil('\n'); // Read the incoming data as a string until newline
    input.trim();                                // Trim any whitespace

    if (input.equalsIgnoreCase("reset"))
    {
      segmentCount = 0; // Reset the segment count
      Serial.println("Segment count reset to 0");
    }
  }

  // Add a short delay before the next reading
  delay(1);
}