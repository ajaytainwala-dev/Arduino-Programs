void setup()
{
    // Initialize the serial communication
    Serial.begin(9600);

    // Initialize the servo motor
    myservo.attach(servoPin);

    // Set the trigger pin as output and the echo pin as input
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop()
{
    // Trigger the ultrasonic sensor
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the echo pin and calculate the distance
    distance = pulseIn(echoPin, HIGH);
    distance = distance / 58;

    // Move the servo motor to the corresponding angle
    angle = map(distance, 0, 255, 0, 180);
    myservo.write(angle);

    // Print the distance and the angle to the serial monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm");
    Serial.print("  Angle: ");
    Serial.println(angle);
    Serial.println();

    // Delay for 1 second
    delay(1000);
}