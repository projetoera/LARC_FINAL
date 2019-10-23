#define maxTime 10
#define qtdMedia 20

// ==================================================================================================
// --- Definindo as funções ---
  // BOIZÃO
  void boizao();
  // COR
  void calculo_RGB();  // Função para calcular o valor de R G B de cada cor.
  void color();        // Função para identificar a cor que o sensor identificou.
  // SERIAL
  void readSerial();
// ==================================================================================================

////////////////////////////////////////////////////////////////////////////////
// BOIZÃO
int LED = 3;
int ledPWM = 0, tempo = 0, tempoAnt = 0;
byte stateLed = false;

void boizao(){
  tempo = millis();
  if((tempo - tempoAnt) >= maxTime){
    if(stateLed){ ledPWM++;}
    else{ ledPWM--;}
    if(ledPWM > 255){  ledPWM = 254;  stateLed = !stateLed;}
    else if(ledPWM < 0){  ledPWM = 1;  stateLed = !stateLed;}
    analogWrite(LED, ledPWM);
    tempoAnt = tempo;
  }
}// timer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//COR
int s2 = 9, s3 = 7, out = 10, GND = 4, VCC = 2;
int mediaR, mediaG, mediaB; 

void calculo_RGB(){
  mediaR = 0;
  mediaG = 0;
  mediaB = 0;
  for(int j=0; j<qtdMedia; j++){
    //Lê a cor vermelha
    digitalWrite(s2, LOW);   
    digitalWrite(s3, LOW);       
    mediaR += pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
    //Lê a cor azul
    digitalWrite(s3, HIGH);        
    mediaB += pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
    //Lê a cor verde
    digitalWrite(s2, HIGH);      
    mediaG += pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); 
  }
  mediaR = mediaR/qtdMedia;
  mediaB = mediaB/qtdMedia;
  mediaG = mediaG/qtdMedia;
}// calculo_RGB

void color(){
  calculo_RGB();
//  Serial.print("Vermelho :");
//  Serial.print(mediaR, DEC);
//  Serial.print(" Verde : ");
//  Serial.print(mediaG, DEC);
//  Serial.print(" Azul : ");
//  Serial.print(mediaB, DEC);
//  Serial.println();

  //Verifica se a cor vermelha foi detectada
  if (mediaR < mediaB && mediaR < mediaG && mediaR < 90){
    Serial.print("R");     
  }
  //Verifica se a cor verde foi detectada    
  else if (mediaG < mediaR && mediaG < mediaB && mediaG < 90){
    Serial.print("G");
  }
  //Verifica se a cor azul foi detectada    
  else if (mediaB < mediaR && mediaB < mediaG  && mediaB < 90){
    Serial.print("B");     
  }
  //Verifica se uma outra cor foi detectada
  else{
    Serial.print("E");
  }
}// color
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SERIAL
int eletroIma = 11; 

void readSerial(){
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();
    switch(incomingByte){
      case 'I': digitalWrite(eletroIma, HIGH); break;
      case 'S': digitalWrite(eletroIma, LOW); break;
      case 'L': color(); break;
    }
  }
}// readSerial
////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600); 
  // COR
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);  
  pinMode(GND, OUTPUT);
  pinMode(VCC, OUTPUT);
  digitalWrite(GND, LOW);  
  digitalWrite(VCC, HIGH);
  // BOIZÃO
  pinMode(LED, OUTPUT);
  pinMode(eletroIma, OUTPUT);
}// setup

void loop(){
  boizao();
  readSerial();
}// loop
