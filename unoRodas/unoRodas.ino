// ==================================================================================================
// --- Definindo as funções ---
  // MOTOR
  void desliga();
  void confereSentido();
  void microPasso();
// ==================================================================================================

////////////////////////////////////////////////////////////////////////////////
// MOTOR
int pinMotorA1 = 5, pinMotorA2 = 9, pinMotorB1 = 6, pinMotorB2 = 10;
int pinConfereSentido = 3, pinLigaMotor = 2;
void desliga(){
  digitalWrite(pinMotorA1,LOW);
  digitalWrite(pinMotorB1,LOW);
  digitalWrite(pinMotorA2,LOW);
  digitalWrite(pinMotorB2,LOW);
}// desliga motor 

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
int microStep = 1, PWM = 0 + microStep, PWMToPin = 0, PWMPin = 0, i = 1, lastPin = 5, delayMicroPasso = 50;
void microPasso(){
  if(digitalRead(lastPin) == LOW)digitalWrite(lastPin,HIGH);
  switch(i){
    case 1: PWMPin = pinMotorB1; break;
    case 2: PWMPin = pinMotorA1; break;
    case 3: PWMPin = pinMotorA2; break;
    case 4: PWMPin = pinMotorB1; break;
    case 5: PWMPin = pinMotorB2; break;
    case 6: PWMPin = pinMotorA2; break;
    case 7: PWMPin = pinMotorA1; break;
    case 8: PWMPin = pinMotorB2; break;
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
////////////////////////////////////////////////////////////////////////////////

void setup(){
  pinMode(pinMotorA1, OUTPUT);
  pinMode(pinMotorB1, OUTPUT);
  pinMode(pinMotorA2, OUTPUT);
  pinMode(pinMotorB2, OUTPUT);
  pinMode(pinConfereSentido, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinLigaMotor), confereSentido, CHANGE);
  delay(500);
}

void loop(){
  andar == HIGH ? microPasso() : desliga();
}//loop
