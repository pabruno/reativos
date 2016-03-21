/* Funções de registro */

int butPinAumenta;
int butPinDiminui;
int butAumenta;
int butDiminui;
int UltAumenta = 0;
int UltDiminui = 0;
int tempo = 1000;
int state = 1;
unsigned long old;
unsigned long now;

void button_listen(int Pin1, int Pin2){
  butPinAumenta = Pin1;  // pin passado deve gerar notificações
  butPinDiminui = Pin2;
  pinMode(butAumenta, INPUT);
  pinMode(butDiminui, INPUT);
  Serial.print("Botao de aumentar no pino ");
  Serial.println(butAumenta);
  Serial.print("Botao de diminuir no pino ");
  Serial.println(butDiminui);
}

void timer_set(int ms){
  tempo += ms;
  if(tempo <= 0){
    tempo = 0;
  }
}

/* Callbacks */
void button_changed(int pin, int v);
void timer_expired(void);

/* Programa principal */

void setup(){
  Serial.begin(9600);  //inicialização da API
  init();              //inicialização do usuário
}

void loop(){
  now = millis();
  if(now >= old + tempo){
    timer_expired();
  }
  
  butAumenta = digitalRead(butPinAumenta);
  butDiminui = digitalRead(butPinDiminui);

  if(butAumenta) {
    button_changed(butPinAumenta,butAumenta);
  }

  if(butDiminui) {
    button_changed(butPinDiminui,butDiminui);
  }

  if(butDiminui && butAumenta) {
    if(UltAumenta - UltDiminui < 500){
      digitalWrite(RedPin,HIGH);
      while(1);
    }
  }
  
}

#define RedPin 2
#define But13Pin 13
#define But12Pin 12

void button_changed(int pin, int v) {
  if(pin == butPinAumenta){
    tempo -= 10;
    UltAumenta = now;
  }
  else {
    tempo += 10;
    UltDiminui = now;
  }
}

void init () {
  old = millis();
  button_listen(But13Pin,But12Pin);
  pinMode(RedPin, OUTPUT);
  digitalWrite(RedPin, state);
}

void timer_expired(void) {
  old = now;
  state = !state;
  digitalWrite(RedPin,state);
}
