int trig = 9;
int echo = 10;
int buzzer = 4;
int red = 3;
int blue = 2;

int time_interval = 1000;
int toned = 0;
bool initalize = true;

long duration, inches;

int last_time = 0;
int current_time = millis();

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  digitalWrite(red,HIGH);
}

void sensor() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);

  inches = duration / 74 / 2;
}

void loop() {
  sensor();
  while(inches <= 30)
  {
    inches >= 20 ? ((time_interval = 1000), (toned = 500)) : (inches >= 10 ? ((time_interval = 750), (toned = 750)): (inches >= 5 ? ((time_interval = 500), (toned = 1000)) : ((time_interval = 250), (toned = 1250)))); // Depending on how close the oject is to the sensor the LEDs will change at a varying rate
    current_time = millis();
    if(initalize) // Initalizes either the Red or Blue LED to turn on when an object is first in proximity 
    {
      last_time = current_time;
      int first_lit = random(2);
      first_lit == 0 ? digitalWrite(red, HIGH) : digitalWrite(blue, HIGH);
      initalize = false;
    }
    if(current_time - last_time >= time_interval) // After the initalization the LEDs will go between On and Off
    {
      last_time = current_time;
      digitalRead(red) ? digitalWrite(red, LOW) : digitalWrite(red, HIGH);
      digitalRead(blue) ? digitalWrite(blue, LOW) : digitalWrite(blue, HIGH);
    }

    Serial.print("Inches: ");
    Serial.println(inches);
    Serial.print("Red Value: ");
    Serial.println(digitalRead(red));
    Serial.print("Blue Value: ");
    Serial.println(digitalRead(blue));
    Serial.print("Time Interval: ");
    Serial.println(time_interval);
    Serial.print("Tone: ");
    Serial.println(toned);
    Serial.println();

    tone(buzzer, toned);
    sensor();
  }

  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  noTone(buzzer);
  initalize = true;

  delay(100);

}
