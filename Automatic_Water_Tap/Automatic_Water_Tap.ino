// ===== PIN =====
const int trigPin = 10;
const int echoPin = 11;
const int relayPin = 7;

// Jarak tangan agar pump nyala (cm)
const int distanceThreshold = 10;

bool pumped = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);

  // Relay OFF awal
  digitalWrite(relayPin, HIGH);

  Serial.begin(9600);
}

void loop() {
  long duration;
  long distance;

  // Kirim gelombang ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Baca pantulan dengan timeout 30ms
  duration = pulseIn(echoPin, HIGH, 30000);

  // Ubah jadi cm
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Gelas terdeteksi jika distance = 0 ATAU tangan sangat dekat
  if (distance == 0 || (distance > 0 && distance <= distanceThreshold)) {
    if (!pumped) {
      Serial.println("Pump ON");
      digitalWrite(relayPin, LOW);   // Pump ON
      delay(500);                    // Pompa selama 0.5 detik
      digitalWrite(relayPin, HIGH);  // Pump OFF
      pumped = true;                 // Tandai sudah dipompa
    }
  } else {
    Serial.println("Pump OFF");
    pumped = false; // Reset saat gelas diangkat
  }

  delay(200);
}