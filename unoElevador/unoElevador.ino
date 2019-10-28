#include <Wire.h>
#include <VL53L0X.h>

// Filtro de média do sensor infravermelho
#define qtdMedia 25

// Altura dos andares para o elevador
#define A 120
#define B 80
#define C 40
#define T 12
#define D  0    // tem que calibrar pra zerar ele

// ==================================================================================================
// --- Definindo as funções ---
  // INFRAVERMELHO
  void infravermelho();
  // SERIAL
  void readSerial();
  // MOTOR
  void desliga();
  void confereSentido();
  void microPasso();
// ==================================================================================================

////////////////////////////////////////////////////////////////////////////////
// INFRAVERMELHO
VL53L0X sensor;
int inf_e = 8;
float mediaLeft;

void infravermelho(){
  for (int j = 0; j<qtdMedia; j++){
    if (sensor.timeoutOccurred()) j--;
    else mediaLeft += sensor.readRangeContinuousMillimeters(); 
  }
  mediaLeft = mediaLeft/qtdMedia;
  Serial.println(mediaLeft);
}// infravermelho
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SERIAL
float distElevator = 0, lastPosition = 0;

void readSerial(){
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();
    switch(incomingByte){
      case 'A': distElevator = lastPosition - A; distMicroPasso(distElevator, A); break;
      case 'B': distElevator = lastPosition - B; distMicroPasso(distElevator, B); break;
      case 'C': distElevator = lastPosition - C; distMicroPasso(distElevator, C); break;
      case 'D': distElevator = lastPosition - D; distMicroPasso(distElevator, D); break;
      case 'E': infravermelho(); mediaLeft = 0; break;
    }
  }
}//void readSerial
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MOTOR

int a1 = 5, a2 = 9, b1 = 6, b2 = 10;
void desliga(){
  digitalWrite(a1,LOW);
  digitalWrite(b1,LOW);
  digitalWrite(a2,LOW);
  digitalWrite(b2,LOW);
}// desliga motor 


int pinLigaMotor = 2, pinConfereSentido = 3;
bool Up = HIGH, clockWise = HIGH, clockWiseLast = HIGH, trocou = false, andar = LOW;

void confereSentido(){
  if(digitalRead(pinLigaMotor) == HIGH){
    andar = HIGH;           
    clockWise = digitalRead(pinConfereSentido);
    if(clockWiseLast != clockWise){
      Up = !Up;
      clockWiseLast = clockWise;
      //Serial.println("trocou");
      trocou = true;
    }            
  }
  else  andar = LOW;
}// confereSentido


bool first = true;
byte passo = 0, passo1 = 8, passo2 = 1;
int microStep = 1, PWM = 0 + microStep, PWMToPin = 0, PWMPin = 0, i = 1, lastPin = 5;
int delayMicroPasso = 50;
void microPasso(){
  if(digitalRead(lastPin) == LOW)digitalWrite(lastPin,HIGH);
  switch(i){
    case 1: PWMPin = b1; break;
    case 2: PWMPin = a1; break;
    case 3: PWMPin = a2; break;
    case 4: PWMPin = b1; break;
    case 5: PWMPin = b2; break;
    case 6: PWMPin = a2; break;
    case 7: PWMPin = a1; break;
    case 8: PWMPin = b2; break;
  }
  for(int j = 0; j < (256/microStep); j++){      
    if(Up == HIGH)PWM = (j+1)*microStep;
    if(Up == LOW)PWM = 256-((j+1)*microStep);          
    if(trocou == true){ trocou = false; PWM = 256;}
    PWMToPin = PWM;
    if(PWMToPin == 256) PWMToPin = 255;
    analogWrite(PWMPin, PWMToPin);
//    Serial.print(Up);
//    Serial.print(" : ");
//    Serial.print(lastPin);
//    Serial.print(" : ");
//    Serial.print(PWMToPin);
//    Serial.print(" : ");
//    Serial.print(PWMPin);
//    Serial.print(" : ");
//    Serial.println(i);
    delayMicroseconds(delayMicroPasso*microStep); //delayMicroPasso*microStep para manter aa velocidade constante, independente do micropasso       
    if(PWM >= 256 && Up == HIGH){ lastPin = PWMPin; Up = LOW; break;}
    if(PWM <= 0 && Up == LOW){  Up = HIGH; break;}          
  }
  clockWise == HIGH ? i++ : i--;  
  if(i == 0)  i = 8;
  if(i == 9)  i = 1;
}//microPasso


float seguranca = 2, passos = 1;
int distPassos = 0;

void distMicroPasso(float distElevator, float andar){
  if(distElevator < 0){
    clockWise = LOW;
    distPassos = (int)(abs(distElevator) + seguranca)*passos;
    lastPosition = andar + seguranca;
  }
  else{
    clockWise = HIGH;
    distPassos = (int)distElevator*passos;
    lastPosition = andar;
  }
  confereSentido();
  for(int k = 0; k < distPassos; k++){
    microPasso();
  }
}//distMicroPasso
////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  //////////////////////////////////
  // MOTOR
  pinMode(a1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b2, OUTPUT);
  //////////////////////////////////

  //////////////////////////////////
  // INFRAVERMELHO
  pinMode(inf_e, OUTPUT);
  digitalWrite(inf_e, LOW);
  
  delay(500);
  Wire.begin();
  
  Serial.begin (9600);
  
  digitalWrite(inf_e, HIGH);
  delay(150);
  sensor.init(true);
  delay(100);
  sensor.setAddress((uint8_t)01);
  sensor.startContinuous();
  //////////////////////////////////
}

void loop(){
  readSerial();
}//void loop
