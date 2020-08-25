#define DATA 2

void setup() {
  // put your setup code here, to run once:
  pinMode(DATA, INPUT);

  Serial.begin(19200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(DATA));
}
