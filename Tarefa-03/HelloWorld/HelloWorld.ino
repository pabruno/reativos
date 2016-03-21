/* Funções de registro */

int pin;

void button_listen(int Pin){
  pin = Pin;  // pin passado deve gerar notificações
  pinMode(pin, INPUT);
  Serial.print("Botao no pino ");
  Serial.println(pin);
}

void timer_set(int ms){
  // timer deve expirar após "ms" milissegundos 
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
  int botao = digitalRead(pin);
  if(botao){
    Serial.print("Botao do pino ");
    Serial.print(pin);
    Serial.println(" acionado");
    button_changed(pin,botao);
  }
  else {
    button_changed(pin,botao);
  }
}

#define RedPin 2
#define But13Pin 13

void button_changed(int pin, int v) {
  digitalWrite(RedPin, v);
}

void init () {
  button_listen(But13Pin);
  pinMode(RedPin, OUTPUT);
}
