// =====================
// PIN CONFIGURATION
// =====================

// Motor Driver Pins (L298N or similar)
#define ENA 9    // Speed control for left motor
#define ENB 10   // Speed control for right motor
#define IN1 8    // Left motor direction pin 1
#define IN2 7    // Left motor direction pin 2
#define IN3 6    // Right motor direction pin 1
#define IN4 5    // Right motor direction pin 2

// Variable to store incoming command
char command;

// =====================
// SETUP FUNCTION (runs once)
// =====================
void setup() {

  // Set motor pins as output
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);  // Start serial communication (Bluetooth/USB)

  // Stop motors at start for safety
  stopCar();
}

// =====================
// MAIN LOOP (runs continuously)
// =====================
void loop() {

  // Check if any data is received via Serial (Bluetooth/USB)
  if (Serial.available()) {

    // Read one character command
    command = Serial.read();

    // Decision based on received command
    if (command == 'F') {
      forward();     // Move forward
    }
    else if (command == 'B') {
      backward();    // Move backward
    }
    else if (command == 'L') {
      left();        // Turn left
    }
    else if (command == 'R') {
      right();       // Turn right
    }
    else if (command == 'S') {
      stopCar();     // Stop the car
    }
  }
}

// =====================
// MOTOR CONTROL FUNCTIONS
// =====================

// Move forward
void forward() {
  analogWrite(ENA, 180);   // Set speed of left motor
  analogWrite(ENB, 180);   // Set speed of right motor

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Move backward
void backward() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Turn left (left motor backward, right motor forward)
void left() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Turn right (left motor forward, right motor backward)
void right() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Stop the car completely
void stopCar() {
  analogWrite(ENA, 0);   // Stop motors
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
