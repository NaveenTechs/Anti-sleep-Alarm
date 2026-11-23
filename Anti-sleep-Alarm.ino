
const int IR_SENSOR = 2;
const int GREEN_LED = 5;
const int YELLOW_LED = 6;
const int RED_LED = 7;
const int BUZZER = 8;

const unsigned long ALERT_TIME = 3000;

unsigned long closedStartTime = 0;
bool eyesClosed = false;

void setup() {
  pinMode(IR_SENSOR, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int sensorValue = digitalRead(IR_SENSOR);

  // Assumption: LOW means eyes closed
  if (sensorValue == LOW) {
    if (!eyesClosed) {
      eyesClosed = true;
      closedStartTime = millis();
    }

    if (millis() - closedStartTime >= ALERT_TIME) {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(BUZZER, HIGH);
      Serial.println("Drowsiness Alert!");
    } else {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      digitalWrite(BUZZER, LOW);
    }
  } else {
    eyesClosed = false;
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
  }

  delay(20);
}
