// Obstacle Avoiding Car
// Arduino + L298N + HC-SR04

// ===== L298N Motor Driver Pins =====
#define ENA 5
#define IN1 6
#define IN2 7

#define IN3 8
#define IN4 9
#define ENB 10

// ===== Ultrasonic Sensor Pins =====
#define TRIG_PIN 11
#define ECHO_PIN 12

// Obstacle detection distance
#define OBSTACLE_DISTANCE 20

void setup()
{
  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Ultrasonic pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Start with car stopped
  Stop();

  delay(1000);
}

void loop()
{
  long distance = getDistance();

  if (distance > OBSTACLE_DISTANCE)
  {
    // No obstacle
    forward();
  }
  else
  {
    // Obstacle detected
    Stop();
    delay(300);

    // Move backward slightly
    back();
    delay(300);

    Stop();
    delay(200);

    // Turn right
    right();
    delay(500);

    Stop();
    delay(200);
  }
}

// ===== Measure Distance =====
long getDistance()
{
  long duration;
  long distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // If no echo received
  if (duration == 0)
  {
    return 400;
  }

  distance = duration * 0.0343 / 2;

  return distance;
}

// ===== Forward =====
void forward()
{
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ===== Backward =====
void back()
{
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// ===== Turn Left =====
void left()
{
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ===== Turn Right =====
void right()
{
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// ===== Stop =====
void Stop()
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}