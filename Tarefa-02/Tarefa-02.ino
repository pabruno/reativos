#define RedPin 2
#define ButPinAcelera 13
#define ButPinDiminui 12
int state = 1;
int tempo = 1000;
unsigned long old;
int butAcelera;
int UltimoClickAcelera = 0;
int butDiminui;
int UltimoClickDiminui = 0;
unsigned long now;

void setup() {
  Serial.begin(9600);
  pinMode(RedPin,OUTPUT);
  pinMode(ButPinAcelera,INPUT);
  pinMode(ButPinDiminui,INPUT);
  digitalWrite(RedPin,state);
  old = millis();
}

void loop() {
  unsigned long now = millis();
  Serial.println(tempo);
  if(tempo < 0) {
    tempo = 0;
  }
  if(now >= old+tempo) {
    old = now;
    state = !state;
    digitalWrite(RedPin,state);
  }

  butAcelera = digitalRead(ButPinAcelera);
  butDiminui = digitalRead(ButPinDiminui);

  if(butAcelera && butDiminui) {
    if(UltimoClickDiminui - UltimoClickAcelera < 500) {
      Serial.print("Fim");
      digitalWrite(RedPin,HIGH);
      while(1);
    }
  }
  
  if(butAcelera && (now - UltimoClickAcelera) > 150) {
    tempo -= 10;
    UltimoClickAcelera = now;
  }

  if(butDiminui && (now - UltimoClickDiminui) > 150){
    tempo += 10;
    UltimoClickDiminui = now;
  }
}
