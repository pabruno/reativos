byte Digitos[10][7] =            { { 1,1,1,1,1,1,0 },  // = Digito 0
                                 { 0,1,1,0,0,0,0 },  // = Digito 1
                                 { 1,1,0,1,1,0,1 },  // = Digito 2
                                 { 1,1,1,1,0,0,1 },  // = Digito 3
                                 { 0,1,1,0,0,1,1 },  // = Digito 4
                                 { 1,0,1,1,0,1,1 },  // = Digito 5
                                 { 1,0,1,1,1,1,1 },  // = Digito 6
                                 { 1,1,1,0,0,0,0 },  // = Digito 7
                                 { 1,1,1,1,1,1,1 },  // = Digito 8
                                 { 1,1,1,0,0,1,1 }   // = Digito 9
                                 };

byte trigger = 12; // Pino TRIGGER do sensor.
byte echo = 13; // Pino ECHO do sensor.
float distancia; // Distancia da pessoa.
float ultima; // Ultima distancia medida
float ambiente; // Distancia entre sensor e obstáculo do ambiente.
float tempo; // Tempo do pulso entre a pessoa e o sensor.
byte buzzer = 11; // Pino do buzzer
byte qtd; // Quantidade de pessoas
byte acao; // Entrando ou saindo "  1-ENTRANDO |||| 0-SAINDO  "
byte ultAcoes[5]; // Ultimas ações
byte auxiliar1, auxiliar2;
unsigned long now, old;
unsigned long ultContagem; // Tempo da ultima vez que contou uma pessoa.
                         
void setup() 
{  
  pinMode(2, OUTPUT); //Pino 2 -> segmento A  
  pinMode(3, OUTPUT); //Pino 3 -> segmento B
  pinMode(4, OUTPUT); //Pino 4 -> segmento C
  pinMode(5, OUTPUT); //Pino 5 -> segmento D
  pinMode(6, OUTPUT); //Pino 6 -> segmento E
  pinMode(7, OUTPUT); //Pino 7 -> segmento F
  pinMode(8, OUTPUT); //Pino 8 -> segmento G
  pinMode(9, OUTPUT); //Pino 9 -> segmento PONTO
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  old = millis();
  ultima = 100;
  qtd = 1;
  acao = 2;
  ultAcoes[0] = ultAcoes[1] = ultAcoes[2] = ultAcoes[3] = ultAcoes[4] = 2;
  medicao(5);
  ambiente = distancia - 5;
  escreve(qtd);
  ultContagem = 0;
  ultima = ambiente + 20;
}

void escreve(byte digit) { //Funcao que aciona o display
  byte pin = 2;
  
  for (byte Count = 0; Count < 7; Count++)  
  { 
    digitalWrite(pin, Digitos[digit][Count]);
    pin++;
  }
  digitalWrite(9,1);
  digitalWrite(9,0);  
}

void medicao(byte num) { // Mede a distancia entre obstáculo e o sensor
  int i = 0;
  float media = 0;
  while(i < num) {
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    tempo = pulseIn(echo, HIGH);
    distancia = (tempo / 29.4) / 2;
    media += distancia;
    i++;
  }
  distancia = media/num;
}

void tocaBuzzer() { // Toca o buzzer
  tone(buzzer,50);
  delay(100);
  noTone(buzzer);
}

void loop() 
{
  int j, conta_acoes;
  now = millis();
  if(now >= old + 200) {
    old = now;
    medicao(3);
    if(distancia < ambiente && now >= ultContagem + 350){
      if(distancia < ultima) {
        acao = 1;
      }
      else if(distancia > ultima) {
        acao = 0;
      }
    }
    for(j=4;j>=0;j--) {
      if(j == 4) {
        auxiliar1 = ultAcoes[j];
        ultAcoes[j] = acao;
      }
      else {
        auxiliar2 = ultAcoes[j];
        ultAcoes[j] = auxiliar1;
        auxiliar1 = auxiliar2;
      }
    }
    ultima = distancia;
  }

  if(distancia >= ambiente && acao != 2){
    for(j=0,conta_acoes=0;j<5;j++){
      if(acao == ultAcoes[j]) {
        conta_acoes++;
      }
    }
    if(conta_acoes <= 3) {
      acao = !acao;
    }
    
    if(acao == 1){
      qtd++;
    }
    else if(acao == 0) {
      qtd--;
    }
    acao = 2;
    escreve(qtd);
    ultContagem = millis();
  }
}
