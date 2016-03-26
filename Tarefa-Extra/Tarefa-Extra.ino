#define TempPin A5
#define OrangePin 2
#define YellowPin 4
#define RedPin 7
float temp;

void setup() {
  Serial.begin(9600);
  pinMode(TempPin,INPUT);
  pinMode(OrangePin,OUTPUT);
  pinMode(YellowPin,OUTPUT);
  pinMode(RedPin,OUTPUT);
}

void loop() {
  temp = (analogRead(TempPin)*5)/10.23;
  Serial.print("Temperatura: ");
  Serial.println(temp);

  if(temp > 0.0 && temp < 33) {
    digitalWrite(OrangePin,HIGH);
  }
  else if (temp < 0.0) {
    digitalWrite(OrangePin,LOW);
  }

  if(temp > 33 && temp < 36) {
    digitalWrite(OrangePin,HIGH);
    digitalWrite(YellowPin,HIGH);
  }
  else if(temp < 36) {
    digitalWrite(YellowPin,LOW);
  }

  if(temp > 36) {
    digitalWrite(OrangePin,HIGH);
    digitalWrite(YellowPin,HIGH);
    digitalWrite(RedPin,HIGH);
  }
  else {
    digitalWrite(RedPin,LOW);
  }
}
